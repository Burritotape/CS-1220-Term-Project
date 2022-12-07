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
void readInitialConditions(ifstream& f, priority_queue<Event> Qu) {
	// Declarations
	string vectorWord, keyword, name, wireLetters;
	// Read the first line
	f >> vectorWord >> name;
	// While loop for assigning values of conditions
	f >> keyword;
	
	while (!f.eof()) {
		int eventTime, newValue;
		if (keyword == "INPUT") {
			f >> wireLetters >> eventTime >> newValue;

			//create event and store info in event
			Event newEvent = Event(wireLetters, eventTime, newValue);

			// Store event in the queue
			Qu.push(newEvent);

		}
		f >> keyword;
	}
}

Wire* getWireIndex(string wName, string wIndex, vector<Wire*> w) {
	// get the wire pointer for access of the date members of the wire using the wire string ("ab" per se)
}

void simulate() {
	// grab items from the queue to run the simulation
	
	// add and subtract events as necessary
	
	// record what happens for printing
}
// visually show what happened, using the stored results from the simulation
void print() {
	// fetch results of simulation and display
}

int main() {
	// vector<Event> queue;
	vector<Gate*> gates;
	vector<Wire*> wires;
	priority_queue<Event> PQ;
	ifstream cfile, vfile; // circuit file and initial conditions file
	string cFileName, newCFN, vFileName;
	
	//ask for curcuit file input
	cout << "To see available options, re-run this command with \"-u\" on the command line.\n" << endl;
	cout << "Press <ENTER> only at promt to quit program." << endl << "What is the name of the circuit test file (base name only):  ";


	// parse circuit description file
	cin >> cFileName;
	newCFN = cFileName + ".txt";
	cfile.open(newCFN);
	cout << "Knock knock\n";
	readCircuitDescription(cfile, gates, wires);
	cout << "Who's there?\n";
	// parse vector file
	vFileName = cFileName + "_v.txt";
	vfile.open(vFileName);
	readInitialConditions(vfile, PQ);
	cout << "Cow's go.\n";

	// construct events

	// simulate the circuit with the events

	// print out the results of the simulation graphically
}