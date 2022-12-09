// This is the Event implementation file
// Created by Joshua Cappella and Jaeden Biermeier
// 12/1/2022
#pragma once
#include <queue>
#include <iostream>
#include <iomanip>
#include <string>
#include "Event.h"

// default event constructor
Event::Event() {
	wireNum = -1;
	time = -1;
	voltVal = 2;
	OOArrival = -1;
}
// event constructor
Event::Event(int I, int T, int V, int O) {
	wireNum = I;
	time = T;
	voltVal = V;
	OOArrival = O;
}
// returns event time
int Event::GetTime() const {
	return time;
}
// returns the number assigned to the wire
int Event::GetWireNum() const{
	return wireNum;
}
// returns value of the wire: hi, lo, or don't care
int Event::GetVoltVal() const {
	return voltVal;
}
// returns the order of arrival of the wire
int Event::GetOOArrival() const {
	return OOArrival;
}
// logic for priority_queue
bool operator<(const Event& c1, const Event& c2) {
	// by default the queue is a MAX queue, so we reverse the comparison
	// from '<' to '>' (see the return statements) to make it a MIN queue
	if (c1.time == c2.time) {
		return c1.OOArrival > c2.OOArrival;
	}
	return c1.OOArrival > c2.OOArrival;
}