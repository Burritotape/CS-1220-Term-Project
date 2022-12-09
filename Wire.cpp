// This is the wire implmentation file
#pragma once
#include "Wire.h"
#include "Gate.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//constructor that accepts a name and index
Wire::Wire(string N = "", int I = -1) {
	value = 2;
	index = I;
	name = N;
	history = "X";
	drives.push_back(NULL);
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

//The five Get funtions to obtain the stored wire data 
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
	if (name == "") {
		cout << " -" << index << " | " << history << " " << endl;
	}
	else {
		cout << name << "-" << index << " | " << history << " \n" << "    | \n";
	}
}