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
	wireNum = k;
	time = -1;
	voltVal = 2;
}

Event::Event(int I, int T, int V) {
	wireNum = I;
	time = T;
	voltVal = V;
	OOA = k;
	k += 1;
}

int Event::GetTime() const {
	return time;
}

int Event::GetWireNum() const{
	return wireNum;
}

bool operator<(const Event& c1, const Event& c2) {

	// by default the queue is a MAX queue, so we reverse the comparison
	// from '<' to '>' (see the return statements) to make it a MIN queue
	if (c1.time == c2.time) {
		return c1.OOA > c2.OOA;
	}

	return c1.OOA > c2.OOA;
}