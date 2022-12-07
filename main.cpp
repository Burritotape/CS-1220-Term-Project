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

void readCircuitDescription(ifstream& f, vector<Gate*>& g, vector<Wire*>& w) {
	string circuitWord, keyword, name;
	int gateCount = 0;
	// Read  the cirucit description
	f >> circuitWord >> name;
	// Read the first keyword
	f >> keyword;
	while(!f.eof()) {
		string delayStr, padLetters;
		int delay, in1, in2, out, wireNum;
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
					Wire* newWirePtr = new Wire(name, wireNum);	// creates new wire pointer
					w[wireNum] = newWirePtr; // places the wirepointer in the vector
				}
			}
			else if (w.size() < (wireNum + 1)) {//the wire vector is too small
				//w.resize((wireNum + 1), NULL); //expand vector to accomidate current wire and set all added elements to NULL
				//set current wire at that index
				while (w.size() < (wireNum + 1)) {
					w.push_back(NULL);
				}
				Wire* newWirePointer = new Wire(name, wireNum);
				w[wireNum] = newWirePointer;	// FAILS to place wireNum in the vector
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
		}
		else if (keyword == "NOT") {
			gateCount += 1;
			f >> delayStr >> in1 >> out;
			// remove the nanosecond specification "ns" from the delayStr
			delayStr.pop_back();
			delayStr.pop_back();
			delay = atoi(delayStr.c_str());
		}
		f >> keyword;
	}

	return;
}

// make the queue from initial state of the circuit
void readInitialConditions(ifstream& f, priority_queue<Event> Qu, vector<Wire*> w) {
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

void simulate(vector<Wire*> w, priority_queue<Event> &p, int &time) {
	// grab items from the queue to run the simulation
	Event currEvent = p.top();
	// update wire states based on read events
	if (time != currEvent.GetTime()) {
		time = currEvent.GetTime();
	}
	// update wire history, preferably in a history string, for printing
	int currWireNum = currEvent.GetWireNum();
	// string currHistory = currEvent.GetHistory();	
	Wire* tempWirePtr = w[currWireNum];
	Wire tempWire = *tempWirePtr;
	tempWire.SetValue(currEvent.GetVoltVal());

	// destroy top of priority queue
	p.pop();
}
// visually show what happened, using the stored results from the simulation
void print(vector<Wire*> w, int time) {
	// fetch results of simulation and display
	for (int i = 1; i < w.size(); i++) {
		w[1]->GetHistory();
	}
	
}

int main() {
	// vector<Event> queue;
	bool yes = false;
	int time = 0;
	vector<Gate*> gates;
	vector<Wire*> wires;
	priority_queue<Event> PQ;
	ifstream cfile, vfile; // circuit file and initial conditions file
	string cFileName, newCFN, vFileName;
	while(!yes) {
		//ask for curcuit file input
		cout << "To see available options, re-run this command with \"-u\" on the command line.\n" << endl;
		cout << "Press <ENTER> only at prompt to quit program." << endl << "What is the name of the circuit test file (base name only):  ";


		// parse circuit description file
		cin >> cFileName;
		newCFN = cFileName + ".txt";
		cfile.open(newCFN);
		if (!cfile.is_open()) {
			cout << "Error 404 : Circuit file not found.  Please try again." << endl;
		}
		// construct event queue
		else if (cfile.is_open()) {
			cout << "Knock knock\n";
			readCircuitDescription(cfile, gates, wires);
			cout << "Who's there?\n";
			// parse vector file
			vFileName = cFileName + "_v.txt";
			vfile.open(vFileName);
			if (!vfile.is_open()) {
				
				cout << "Error 405 : Vector file not found.  Please try again." << endl;
			}
			else if (vfile.is_open()) {
				readInitialConditions(vfile, PQ, wires);
				cout << "Cow's go.\n";
				yes = true;
			}
		}
		


	}
	// simulate the circuit with the events
	simulate(wires, PQ, time);
	cout << "Cow's go 'Who'?\n";
	// print out the results of the simulation graphically
}