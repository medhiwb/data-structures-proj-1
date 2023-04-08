// Medhi Welsh - Brito
// U47469189
//
// Main file for the calculator project. 
#include <iostream>

#include "CalcList.hpp"
#include "CalcListInterface.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    CalcList calc;                            // Total == 0
    calc.newOperation(ADDITION, 10);          // Total == 10
    calc.newOperation(MULTIPLICATION, 5);     // Total == 50
    calc.newOperation(SUBTRACTION, 15);       // Total == 35
    calc.newOperation(DIVISION, 7);           // Total == 5
    calc.removeLastOperation();               // Total == 35
    calc.newOperation(SUBTRACTION, 30);       // Total == 5
    calc.newOperation(ADDITION, 5);           // Total == 10
    calc.removeLastOperation();               // Total == 5
    cout << calc.toString(2);
    calc.removeLastOperation();               // Total == 35
    cout << calc.toString(0);
    return 0;
}
