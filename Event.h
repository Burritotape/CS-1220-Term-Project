// This is the Event attribute file
// Created by Joshua Cappella and Jaeden Biermeier
// 12/1/2022
#pragma once
#include <iostream>
using namespace std;

class Event {
public:
    Event();
    Event(int I, int T, int V, int O);
    int wireNum;
    int time;
    int voltVal;
    int OOArrival;
    friend bool operator<(const Event& c1, const Event& c2);
    int GetWireNum() const;
    int GetTime() const;
    int GetVoltVal() const;
    int GetOOArrival() const;

private:
    int k = 0;
    vector<Event> priorityQueue;
};