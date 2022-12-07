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
	wire = "";
	time = -1;
	boolVal = 2;
}

Event::Event(int I, int T, int V) {
	wire = I;
	time = T;
	boolVal = V;
	OOA = k;
	k += 1;
}

bool operator<(const Event& c1, const Event& c2) {

	// by default the queue is a MAX queue, so we reverse the comparison
	// from '<' to '>' (see the return statements) to make it a MIN queue
	if (c1.time == c2.time) {
		return c1.OOA > c2.OOA;
	}

	return c1.OOA > c2.OOA;
}