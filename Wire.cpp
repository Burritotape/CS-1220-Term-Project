// This is the wire implmentation file
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

OutputBacktrack()

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
	if (history.size() < maxTime) {
		int j = maxTime - history.length();
		for (int i = 0; i < j; ++i){
			history = history + "N";
		}
	}
	else if (history.size() > maxTime) {
		int j = history.length() - maxTime;
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