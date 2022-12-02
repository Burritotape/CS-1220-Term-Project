#include <iostream>
#include <fstream>
#include "Gate.h"
#include "Wire.h"
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
				cout << ">:\ Try again..." << endl;
			}
			else if (w.size() >= (wireNum + 1)) {//the wire vector is large enough
				if (w[wireNum] == NULL) {// does not exist / is a NULL
					w[wireNum + 1] = padLetters;  //set current wire at that index  //this is currently wrong
				}
			}
			else if (w.size() < (wireNum + 1)) {//the vector is not large enough
				w.resize(wireNum + 1); //expand vector to accomidate current wire and set all added elements to NULL
				//set current wire at that index
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
void readInitialConditions(ifstream& f) {
	// Declarations
	string vectorWord, keyword, name;
	// Read the first line
	f >> vectorWord >> name;
	// While loop for assigning values of conditions
	f >> keyword;
	while (!f.eof()) {
		string wireLetters;
		int initialTime, initialValue;
		if (keyword == "INPUT") {
			f >> wireLetters >> initialTime >> initialValue;

			// Store this info where it can be accessed later
		}
	}
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
	ifstream cfile, vfile; // circuit file and initial conditions file
	// get the file name
	string fileName;
	cin >> fileName;

	cfile.open(fileName);
	// hand off tasks to the rest of the functions outside of main
}