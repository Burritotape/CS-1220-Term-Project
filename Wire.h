// This is the Wire attribute file
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

    void printHistory() const;

private:
    int value;
    int index;
    string history;
    vector<Gate*> drives;
};