// This is the Event implementation file
// Created by Joshua Cappella and Jaeden Biermeier
// 12/1/2022
#pragma once
#include <queue>
#include <iostream>
#include <iomanip>
#include <string>
#include "Event.h"

Event::Event() {
	wireNum = -1;
	time = -1;
	voltVal = 2;
	OOArrival = -1;
}

Event::Event(int I, int T, int V, int O) {
	wireNum = I;
	time = T;
	voltVal = V;
	OOArrival = O;
}

int Event::GetTime() const {
	return time;
}

int Event::GetWireNum() const{
	return wireNum;
}

int Event::GetVoltVal() const {
	return voltVal;
}

int Event::GetOOArrival() const {
	return OOArrival;
}

bool operator<(const Event& c1, const Event& c2) {

	// by default the queue is a MAX queue, so we reverse the comparison
	// from '<' to '>' (see the return statements) to make it a MIN queue
	if (c1.time == c2.time) {
		return c1.OOArrival > c2.OOArrival;
	}
	
	return c1.OOArrival > c2.OOArrival;
	
	
}