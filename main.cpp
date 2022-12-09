#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <queue>
#include <vector>
#include "Gate.h"
#include "Wire.h"
#include "Event.h"
using namespace std;

Wire* getWireIndex(string wName, int wIndex, vector<Wire*> wIndexVec) {
	// get the wire pointer for access of the data members of the wire using the wire string ("ab" per se)
	for (int i = 1; i < wIndexVec.size(); i++) {
		Wire* wNameThing = wIndexVec.at(i);
		string wn = wNameThing->GetName();
		if (wn == wName) {
			return wIndexVec.at(i);
		}
		if (wNameThing->GetIndex() == wIndex) {
			return wIndexVec.at(i);
		}
	}
	Wire* newWire = new Wire(wName, wIndex);
	return newWire;
}
void readCircuitDescription(ifstream& f, vector<Gate*>& g, vector<Wire*>& w, string &circuitName) {
	string circuitWord, keyword;
	int gateCount = 0;
	// Read  the cirucit description
	f >> circuitWord >> circuitName;
	// Read the first keyword
	f >> keyword;
	while(!f.eof()) {
		string delayStr = "";
		string padLetters = "";
		int delay, in1, in2, out, wireNum = -1;
		if ((keyword == "INPUT") || (keyword == "OUTPUT")) {
			// assign elements
			f >> padLetters >> wireNum;
			// Maybe call a function that assigns this date before it is lost to reassigned variables??
			// g.push_back(padLetters);

			// if necessary, put the wire in the wire vector
			if (wireNum < 0) {
				cout << "Wire number less than 0." << endl;
			}
			else if (w.size() >= (wireNum + 1)) {//the wire vector is large enough
				if (w[wireNum] == NULL) {// does not exist / is a NULL
					//w[wireNum + 1] = padLetters;  //set current wire at that index  //this is currently wrong
					Wire* newWirePtr = new Wire(padLetters, wireNum);	// creates new wire pointer
					w[wireNum] = newWirePtr; // places the wirepointer in the vector
				}
			}
			else if (w.size() < (wireNum + 1)) {//the wire vector is too small
				//w.resize((wireNum + 1), NULL); //expand vector to accomidate current wire and set all added elements to NULL
				//set current wire at that index
				while (w.size() < (wireNum + 1)) {
					w.push_back(NULL);
				}
				Wire* newWirePointer = new Wire(padLetters, wireNum);
				// places pointer to newWire in w, the wire pointer vector
				w[wireNum] = newWirePointer;
			}

		}
		else if ((keyword == "AND") || (keyword == "OR") || (keyword == "XOR") ||
			(keyword == "NAND") || (keyword == "NOR") || (keyword == "NANDX") ||
			(keyword == "XNOR") || (keyword == "NORX")) {
			gateCount += 1;
			// assign elements for the gate
			f >> delayStr >> in1 >> in2 >> out;
			// remove the nanosecond specification "ns" from the delayStr
			delayStr.pop_back();
			delayStr.pop_back();
			delay = atoi(delayStr.c_str());

			// some wires you don't see as inputs and outputs
			/// handle these like above


			// expands vector to accomidate all wirePtrs for this Gate
			while (w.size() < (out + 1)) {
				w.push_back(NULL);
			}
			
			//creates any unspecified wires
			if (w[in1] == NULL) {
				Wire* newWirePtr = new Wire("", in1);
				w[in1] = newWirePtr;
			}
			if (w[in2] == NULL) {
				Wire* newWirePtr = new Wire("", in2);
				w[in2] = newWirePtr;
			}
			if (w[out] == NULL) {
				Wire* newWirePtr = new Wire("", out);
				w[out] = newWirePtr;
			}
			//creates Gate
			Gate* newGatePtr = new Gate(keyword, delay, w[in1], w[in2], w[out]);
			g.push_back(newGatePtr);
			//FIXME use setDrives to correctly assign the driving wires for each gate
			w[in1]->SetDrives(g);
			w[in2]->SetDrives(g);
			w[out]->SetDrives(g);
		}
		else if (keyword == "NOT") {
			gateCount += 1;
			f >> delayStr >> in1 >> out;
			// remove the nanosecond specification "ns" from the delayStr
			delayStr.pop_back();
			delayStr.pop_back();
			delay = atoi(delayStr.c_str());
			// resize w vector to the size it needs to be
			while (w.size() < (out + 1)) {
				w.push_back(NULL);
			}
			if (w[out] == NULL) {
				Wire* newWirePtr = new Wire("", out);
				w[out] = newWirePtr;
			}
			w[in1]->SetDrives(g);
			w[out]->SetDrives(g);
			// creates gate
			Gate* newGatePtr = new Gate(keyword, delay, w[in1], w[out]);
			// inserts gate onto end of vector of gate pointers
			g.push_back(newGatePtr);
			w[in1]->SetDrives(g);
			w[out]->SetDrives(g);
		}
		f >> keyword;
	}
	return;
}
// make the queue from initial state of the circuit
void readInitialConditions(ifstream& f, priority_queue<Event> &Qu, const vector<Wire*> &w) {
	// Declarations
	string vectorWord, keyword, name, wireLetters;
	int OOA = 0;
	// Read the first line
	f >> vectorWord >> name;
	// While loop for assigning values of conditions
	f >> keyword;
	
	while (!f.eof()) {
		int eventTime, newValue;
		if (keyword == "INPUT") {
			f >> wireLetters >> eventTime >> newValue;
			Wire* wIndex = getWireIndex(wireLetters, -1, w);
			int index = wIndex->GetIndex();
			//create event and store info in event
			Event newEvent = Event(index, eventTime, newValue, OOA);

			// Store event in the queue
			Qu.push(newEvent);
		}
		f >> keyword;
		OOA += 1;
	}
}
string GetHiOrLoOrNo(int B) {
	if (B == 1) {
		return "-";
	}
	else if (B == 0) {
		return "_";
	}
	else if (B == 2) {
		return "X";
	}
	else {
		return "N";
	}
}
vector<int> WSafegaurd(vector<Wire*> W) {
	vector<int> Dangerous;
	for (int i = 0; i < W.size(); ++i) {
		Wire* tPointer = W[i];
		if (tPointer == NULL) {
			Dangerous.push_back(i);
		}
	}
	return Dangerous;
}
int GetNextPriority(priority_queue<Event> qu) {
	vector<Event> qv;
	priority_queue<Event> cu = qu;
	for (int i = 0; i < qu.size(); i++) {
		qv.push_back(cu.top());
		cu.pop();
	}

	int highest = 0;
	for (int i = 0; i < (qu.size()); i++) {
		if (qv[i].GetOOArrival() > highest) {
			highest = qv[i].GetOOArrival();
		}
	}
	return highest + 1;
}
void simulate(vector<Wire*> w, priority_queue<Event> &p, int &time, string& cFileName) {
	// grab items from the queue to run the simulation
	while (!p.empty()) {
		Event currEvent = p.top();
		// update wire states based on read events
		// if (time != currEvent.GetTime()) {
			time = currEvent.GetTime();
		// }
		int currWireNum = currEvent.GetWireNum();
		// string currHistory = currEvent.GetHistory();	
		Wire* tempWirePtr = w[currWireNum];
		vector<Gate*> g = tempWirePtr->GetDrives();
		for (int i = 0; i < g.size(); i++) {
			//Wire* tempWirePtr = w[currWireNum];
			int BAD = tempWirePtr->OutputBacktrack();
			Wire* f = g[i]->getOutput();
			int E1 = f->GetValue();
			tempWirePtr->SetValue(currEvent.GetVoltVal());
			// After the setting of VoltVal compare the outputs before and after the currEvent
			vector<Gate*> g = tempWirePtr->GetDrives();
			int E2 = g[i]->evaluate();
			int OOA = GetNextPriority(p);
			int index = f->GetIndex(); //wrong
			// if the inputs from befor and after do not match, change to new value
			if ((E1 != E2) && (BAD != E2)) {
				f->SetValue(E2);
				// If different, make and store an event that changes the wire
				// at the ouput of the gate at currTime + GateDelay;
				// create event and store info in event
				int eventTime = (time + g[i]->getDelay());
				Event newEvent = Event(index, eventTime, E2, OOA);

				// Store event in the queue
				p.push(newEvent);
			}
		}
		// pull history
		string tempHistory = tempWirePtr->GetHistory();
		if ((time == 0)) {
			// sets the first member of a history string to _ or -
			tempWirePtr->SetHistory(GetHiOrLoOrNo(currEvent.GetVoltVal()));
		}
		else if ((tempHistory.at(0) == '_') || (tempHistory.at(0) == '-')) {
			for (int i = tempHistory.length(); i < time; ++i) {
				tempHistory = tempHistory + 'N';
			}
			tempWirePtr->SetHistory(tempHistory + GetHiOrLoOrNo(currEvent.GetVoltVal()));
		}
		else if (tempHistory.at(0) == 'X') {
			for (int i = tempHistory.length(); i < time; ++i) {
				tempHistory = tempHistory + 'N';
			}
			tempWirePtr->SetHistory(tempHistory + GetHiOrLoOrNo(currEvent.GetVoltVal()));
		}
		// destroy top of priority queue
		p.pop();
	}
}
// visually show what happened, using the stored results from the simulation
void print(vector<Wire*> w, int& time, string &circuitName) {
	int maxTime = 0;
	time = time - 2;
	string printHeading = "      ";
	string printHeading2 = "      ";
	string printBorder = "_";
	string tickMarks = "0----0----1----1----2----2----3----3----4----4----5----5----6";
	string tickMarks2 = "0    5    0    5    0    5    0    5    0    5    0    5    0";
	// add number of time intervals to header
	for (int i = 0; i <= time; i++) {
		// string s = to_string(i);
		string t = "_";
		printHeading += tickMarks[i];
		printHeading2 += tickMarks2[i];
		printBorder += t;
	}
	cout << "Wire traces with internal wires:\n";
	maxTime = time;
	// output wire histories
	for (int i = 1; i < w.size(); i++) {
		w[i]->FixHistory(maxTime);
		if (w[i] != w.back()) {
			w[i]->printHistory();
			cout << " " << endl;
		}
		else {
			w[i]->printHistory();
		}
	}
	cout << printBorder << endl;
	cout << printHeading << endl;;
	cout << printHeading2 << endl << endl;
	cout << "Circuit name: " << circuitName << endl;
	cout << "Time elapsed: " << time << "ns\n" << endl;
}

int main() {
	// vector<Event> queue;
	bool exit = false;
	int time = 0;
	string circuitName = " ";
	vector<Gate*> gates;
	vector<Wire*> wires;
	priority_queue<Event> PQ;
	ifstream cfile, vfile; // circuit file and initial conditions file
	string cFileName;
	string newCFN, vFileName;
	//while (!exit) {
	while (!exit) {
		//ask for circuit file input
		cout << "Press <ENTER> only at prompt to quit program.\n";
		cout << "What is the name of the circuit test file (base name only):  ";
		// parse circuit description file
		getline(cin, cFileName);
		if (cFileName == "") {
			return 0;
		}
		newCFN = cFileName + ".txt";
		cfile.open(newCFN);
		cout << "\nSimulating " << cFileName << ".txt.\n" << endl << endl << endl;	
		if (!cfile.is_open()) {
			cout << "Error opening file " << cFileName << ".txt\n";
			cout << "Error reading circuit description file" << endl;
		}
		// construct event queue
		else {
			readCircuitDescription(cfile, gates, wires, circuitName);
			// parse vector file
			cfile.close();
			vFileName = cFileName + "_v.txt";
			vfile.open(vFileName);
			if (!vfile.is_open()) {
				cout << "Error reading circuit description file" << endl;
			}
			else {
				readInitialConditions(vfile, PQ, wires);
			}
			vfile.close();
			// simulate the circuit with the events
			simulate(wires, PQ, time, cFileName);
			// print out the histories of the wires
			print(wires, time, circuitName);
			cFileName = "0";
		}
	}
}
// Circuits status report:
// circuit0: working!
// circuit1: program references wire index 2, which is a nullptr
// circuit2: wires 5 and 6's outputs are incorrect, time appears to be wrong, since outputs are shortened, multiple attempts yield different lengths: 1st attempt: 4ns; 2nd-infinity attempts: 9ns
// circuit3: same as wire 2, but with one more output (D), both output wires are incorrect, indicates that output wire function is likely broken
// circuit4: first run has a time of 1ns, second run produces no output, initial values for run 1 are correct
// circuit5: could not be loaded
// circuit6: first run 38ns, second run 37ns, should be 30ns, all output valued are correct, aside from extras due to incorrect timing
// circuit7: both runs are 4ns, should be 6ns, all shown outputs correct
// circuit8: time of 5ns is correct, wires 2, 3, and 4 show incorrect output
// circuit9: could not be loaded
// flipflop1: first run is 0ns, second run is 4ns, should be 60ns, wires 3 and 4 are incorrect, wire 4 may have an incorrect string name
// flipflop2: both runs are 8ns, should be 60ns, wires 3 and 4 are again incorrect, with wire 4 again having an incorrect string name