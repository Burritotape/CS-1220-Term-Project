// This is the Gate attribute file
// Created by Joshua Cappella and Jaeden Biermeier
// 11/16/2022
#pragma once
#include <string>
#include <vector>
using namespace std;

class Wire;

class Gate {
public:
    Gate(string gateT, int delayT, Wire* wirePtr1,
        Wire* wirePtr2, Wire* wirePtr3);
    int getDelay() const;
    Wire* getInput(int) const;
    Wire* getOutput() const;
    int evaluate() const; // exercise Gate logic

private:
    string gateType;
    int delayTime;
    Wire* wireIn1, * wireIn2;
    Wire* wireOut;
};