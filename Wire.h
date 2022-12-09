// This is the Wire attribute file
// Created by Joshua Cappella and Jaeden Biermeier
// 11/16/2022
#pragma once
#include <string>
#include <vector>

using namespace std;

class Gate;

class Wire {

public:
    string name;
    Wire(string N, int I);

    void SetValue(int V);
    void SetHistory(string H);
    void SetDrives(vector<Gate*> D);

    int GetValue() const;
    int GetIndex() const;
    string GetName() const;
    string GetHistory() const;
    vector<Gate*> GetDrives() const;

    int OutputBacktrack();

    void FixHistory(int time);
    void NMorpher(int time);

    void printHistory() const;

private:
    int value;
    int index;
    string history;
    vector<Gate*> drives;
};