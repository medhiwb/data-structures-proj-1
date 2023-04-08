// Medhi Welsh - Brito
// U47469189
//
// Header file for calculator problem. Main file is "CalcList.cpp".

#ifndef CALCLIST_H
#define CALCLIST_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include "CalcListInterface.hpp"

using namespace std;

class CalcNode {
    CalcNode *next;
    FUNCTIONS operation;
    double total;
    double operand;
    friend class CalcList;
};

class CalcList : public CalcListInterface {
private:
    CalcNode *cursor;
protected:
    void add_node(const double &poop);
    void remove_node();
    int steps = 0;
public:
    CalcList();
    ~CalcList();

    bool is_empty() const {
        return (steps == 0);
    }
    
    double total() const;
    void newOperation(const FUNCTIONS func, const double operand);
    void removeLastOperation();
    string toString(unsigned short precision) const;
};

CalcList :: CalcList() : CalcListInterface() {
    cursor = new CalcNode;
    cursor->operand = 0.0;
    cursor->total = 0.0;
    cursor->operation = ADDITION;
    cursor->next = cursor;
}

CalcList :: ~CalcList() {
    while (is_empty() != true) {
        remove_node();
    }
}

void CalcList :: add_node(const double &poop) {
    ++steps;
    CalcNode *prevcsr = new CalcNode;

    prevcsr->next = nullptr;
    prevcsr->total = 0.0;
    prevcsr->operand = 0.0;
    prevcsr->operation = ADDITION;

    if (cursor == nullptr) {
        prevcsr->total = poop;
        cursor = prevcsr;
        cursor->next = prevcsr;
    }
    else {
        prevcsr->next = cursor->next;
        prevcsr->total = cursor->next->total;
        cursor->next = prevcsr;
    }
}

void CalcList :: remove_node() {
    
    if (is_empty()) {
        cout << ("No node in list.");
    }
    
    else {
        --steps;
        CalcNode *old = cursor->next;
        
        if (old == cursor) {
            cursor = nullptr;
        }
        else {
            cursor->next = old->next;
        }
        delete old;
    }
}
double CalcList :: total() const {
    return cursor->next->total;
}

void CalcList :: newOperation(const FUNCTIONS func, const double operand) {

    add_node(0);
    
    switch (func) {
        case ADDITION:
            cursor->next->operation = ADDITION;
            cursor->next->operand = operand;
            cursor->next->total += operand;
            break;
        case SUBTRACTION:
            cursor->next->operation = SUBTRACTION;
            cursor->next->operand = operand;
            cursor->next->total -= operand;
            break;
        case MULTIPLICATION:
            cursor->next->operation = MULTIPLICATION;
            cursor->next->operand = operand;
            cursor->next->total *= operand;
            break;
        case DIVISION:
            if (operand >= 0 && operand < 1) {
                removeLastOperation();
                cout << ("Divide by zero.");
            } else {
                cursor->next->operation = DIVISION;
                cursor->next->operand = operand;
                cursor->next->total /= operand;
                break;
            }
        }
    }

void CalcList :: removeLastOperation() {
    remove_node();
}

string CalcList :: toString(unsigned short precision) const {
    
    stringstream ss;
    string datastring = "";
    int reverse = steps;
    CalcNode *pointer = new CalcNode;
    pointer = cursor->next;

    ss.precision(precision);
   
    while (pointer->total != 0) {
        ss << reverse << ": ";

        ss << fixed << pointer->next->total; /*one before that*/

        if (pointer->operation == ADDITION) {
            ss << " + ";
        }
        else if (pointer->operation == SUBTRACTION) {
            ss << " - ";
        }
        else if (pointer->operation == MULTIPLICATION) {
            ss << " * ";
        }
        else if (pointer->operation == DIVISION) {
            ss << " / ";
        }
        ss << pointer->operand;
        ss << " = ";
        ss << pointer->total << endl;
        
        pointer = pointer->next;
        --reverse;
    }
    datastring = ss.str();
    return datastring;
}
#endif //!CALCLIST_H
