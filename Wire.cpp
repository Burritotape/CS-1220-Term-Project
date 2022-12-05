// This is the wire implmentation file

#include "Wire.h"
#include "Gate.h"
#include <string>
#include <iostream>
using namespace std;

//Default Constructor
Wire::Wire() {
	value = 2;
	index = -1;
	name = "";
	history = "";
	drives[0] = NULL;
}

//constructor that accepts a name and index
Wire::Wire(string N, int I) {
	value = 2;
	index = I;
	name = N;
	history = "";
	drives[0] = NULL;
}

//The three set functions to set the component info
void Wire::SetValue(int V) {
	value = V;
}

void Wire::SetHistory(string H) {
	history = H;
}

void Wire::SetDrives(vector<Gate*> D) {
	drives = D;
}

//The five Get funtions to obtain the component info
int Wire::GetValue() const {
	return value;
}

int Wire::GetIndex() const {
	return index;
}

string Wire::GetName() const {
	return name; 
}

string Wire::GetHistory() const {
	return history;
}

vector<Gate*> Wire::GetDrives() const {
	return drives;
}

//The function used to print the history of the circuit 
void Wire::printHistory() const {
	cout << history << endl;
}