// This is the wire implmentation file
// Created by Joshua Cappella and Jaeden Biermeier
// 11/16/2022
#pragma once
#include "Wire.h"
#include "Gate.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//constructor that accepts a name and index
Wire::Wire(string N, int I = -1) {
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
// assigns wire history with H
void Wire::SetHistory(string H) {
	history = H;
}
// assigns vector of gate pointers with drives
void Wire::SetDrives(vector<Gate*> D) {
	drives = D;
}
//returns wire value
int Wire::GetValue() const {
	return value;
}
// returns wire index
int Wire::GetIndex() const {
	return index;
}
// returns wire name
string Wire::GetName() const {
	return name;
}
// returns wire history
string Wire::GetHistory() const {
	return history;
}
// returns drives
vector<Gate*> Wire::GetDrives() const {
	return drives;
}
// return the wire index for the output wire from a gate
int Wire::OutputBacktrack() {
	for (int i = 0; i < drives.size(); ++i) {
		Gate* tempGatePtr = drives.at(i);
		Wire* tempWirePtr= tempGatePtr->getOutput();
		int WOutIndex = tempWirePtr->GetIndex();

		if (WOutIndex == index) {
			return WOutIndex;
		}
	}
	return -1;
}
// replaces Ns with correct character for history
void Wire::NMorpher(int time) {
	char A1, B2;
	int j;
	for (int i = 0; i <= (time - 1); ++i) {
		j = i + 1;
		A1 = history[i];
		B2 = history[j];

		if ((A1 != 'N') && (B2 == 'N')) {
			history[j] = history[i];
		}
	}
}

void Wire::FixHistory(int maxTime) {
	// make history correct length by adding N's or chopping the string
	if (history.size() < (maxTime+1)) {
		int j = (maxTime+1) - history.length();
		for (int i = 0; i < j; ++i){
			history = history + "N";
		}
	}
	else if (history.size() > (maxTime+1)) {
		int j = history.length() - (maxTime+1);
		for (int i = 0; i < j; ++i) {
			history.pop_back();
		}
	}
	NMorpher(maxTime);
}
//The function used to print the history of the circuit 
void Wire::printHistory() const {
	if (name == "") {
		cout << " -" << index << " | " << history << " \n" << "    |";
	}
	else {
		cout << name << "-" << index << " | " << history << " \n" << "    |";
	}
}