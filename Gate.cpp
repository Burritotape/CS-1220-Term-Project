// This is the Gate implementation file
// Created by Joshua Cappella and Jaeden Biermeier
// 11/16/2022

#include "Gate.h"
#include "Wire.h"
#include <string>
#include <vector>

// using namespace std;

Gate::Gate(string gateT, int delayT, Wire * wirePtr1, Wire * wirePtr2, Wire * wirePtr3){
    gateType = gateT;
    delayTime = delayT;
    wireIn1 = wirePtr1;
    wireIn2 = wirePtr2;
    wireOut = wirePtr3;
}
int Gate::getDelay() const {
    return delayTime;
}
Wire* Gate::getInput(int q) const {
    if (q == 1) {
        return wireIn1;
    }
    else {
        return wireIn2;
    }
}
Wire* Gate::getOutput() const {
    return wireOut;
}
int Gate::evaluate() const {
    // Assign values to x and y
    int x = wireIn1->GetValue();
    int y = wireIn2->GetValue();
    // Completed logic for NOT
    if (gateType == "NOT") {
        if (x == 0) {
            return 1;
        }
        else if (x == 1) {
            return 0;
        }
        else {
            return 2;
        }
    }
    // Completed logic for overlapping AND and OR
    else if (gateType == "OR" || "AND") {
        if (x == 0 && y == 0) {
            return 0;
        }
        else if (x == 2 && y == 2) {
            return 2;
        }
    }
    // Completed logic for OR
    if (gateType == "OR") {
        if (x == 1 || y == 1) {
            return 1;
        }
        else {
            return 2;
        }
    }
    // Completed remaining logic for AND
    if (gateType == "AND") {
        if (x == 1 && y == 1) {
            return 1;
        }
        else if (x == 0 || y == 0) {
            return 0;
        }
        else {
            return 2;
        }
    }
    // Completed logic for XOR
    else if (gateType == "XOR") {
        if ((x == y) && (x != 2)) {
            return 1;
        }
        else if (x == 2 || y == 2) {
            return 2;
        }
        else {
            return 0;
        }
    }
    // Completed logic for NAND
    else if (gateType == "NAND") {
        if ((x == 1) && (y == 1)) {
            return 0;
        }
        else if (((x == 1) && (y == 2)) || ((x == 2) && (y == 1)) || ((x == 2) && (y == 2))) {
            return 2;
        }
        else {
            return 1;
        }
    }
    // Completed logic for NOR and NANDX
    else if ((gateType == "NOR") || (gateType == "NANDX")) {
        if ((x == 0) && (y == 0)) {
            return 1;
        }
        else if (((x == 0) && (y == 2)) || ((x == 2) && (y == 0)) || ((x == 2) && (y == 2))) {
            return 2;
        }
        else {
            return 0;
        }
    }
    // Completed logic for XNOR and NORX
    else if ((gateType == "XNOR") || (gateType == "NORX")) {
        if ((x == 2) || (y == 2)){
            return 2;
        }
        else if (x == y) {
            return 1;
        }
        else {
            return 0;
        }
    }
}