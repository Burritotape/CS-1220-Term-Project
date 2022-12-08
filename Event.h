// This is the Event attribute file
// Created by Joshua Cappella and Jaeden Biermeier
// 12/1/2022
#pragma once
#include <iostream>
using namespace std;

class Event {   // take the information from the initially populated vectors to create events in a queue, which will be called in order during simulate
public:
    // public stuff goes here
    Event();
    Event(int I, int T, int V, int O);
    int wireNum; // 
    int time; // determines time of arrival; this is first priority for the queue
    int voltVal; // determines whether the wire value goes high or low
    int OOArrival; // Order_of_Arrival; this is second priority for sorting the queue
    // constructor for events

    // comparator for event order of operations
    friend bool operator<(const Event& c1, const Event& c2);
    int GetWireNum() const;
    int GetTime() const;
    int GetVoltVal() const;
    int GetOOArrival() const;

private:
    int k = 0;
    vector<Event> priorityQueue; // for storing the queue of events to be read in simulation
};