// This is the Gate implementation file
// Created by Joshua Cappella and Jaeden Biermeier
// 11/16/2022

#include "Gate.h"
#include "Wire.h"
#include <string>
#include <vector>


// gate constructor
Gate::Gate(string gateT, int delayT, Wire * wirePtr1, Wire * wirePtr2, Wire * wirePtr3){
    gateType = gateT;
    delayTime = delayT;
    wireIn1 = wirePtr1;
    wireIn2 = wirePtr2;
    wireOut = wirePtr3;
}
// NOT gate constructor
Gate::Gate(string gateT, int delayT, Wire* wirePtr1, Wire* wirePtr3) {
    gateType = gateT;
    delayTime = delayT;
    wireIn1 = wirePtr1;
    wireOut = wirePtr3;
}
// returns the delay associated with a gate in nanoseconds
int Gate::getDelay() const {
    return delayTime;
}
// returns a wire pointer for a gate's input
Wire* Gate::getInput(int q) const {
    if (q == 1) {
        return wireIn1;
    }
    else {
        return wireIn2;
    }
}
// returns a wire pointer for a gate's output
Wire* Gate::getOutput() const {
    return wireOut;
}
// returns an int for the output value of a gate
int Gate::evaluate() const {
    // Assign value to x
    int x = wireIn1->GetValue();
    // completed logic for NOT
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
    // assign value to y
    int y = wireIn2->GetValue();
    // completed logic for overlapping AND and OR
    if (gateType == "OR" || "AND") {
        if (x == 0 && y == 0) {
            return 0;
        }
        else if (x == 2 && y == 2) {
            return 2;
        }
    }
    // completed logic for OR
    if (gateType == "OR") {
        if (x == 1 || y == 1) {
            return 1;
        }
        else {
            return 2;
        }
    }
    // completed remaining logic for AND
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
    // completed logic for XOR
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
    // completed logic for NAND
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
    // completed logic for NOR and NANDX
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
    // completed logic for XNOR and NORX
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