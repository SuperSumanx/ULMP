/*
The MIT License (MIT)

Copyright (c) 2013 Sumanth V

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef ULMP_H
#define ULMP_H

/* *****************************
 * ULMP
 * Ultra Light Math Parser
 * Main Class
 * Written by Sumanth - 2013
 * -----------------------------
 * *****************************
 *-----------------------------
 * KNOWN BUGS/ISSUES
 * -----------------------------
 * None currently known
 * -----------------------------
 * ******************************
 * -----------------------------
 * PLANNED FEATURES
 * -----------------------------
 * 1. Functions (sin, cos, tan, arcsin, arccos, arctan, abs, etc.), Constants
 * 2. Error checking
 * 3. (Least priority) Variables
 * ******************************
 */

#include <cmath> //required for sin, cos(to be implementated) , pow , etc.
#include "Array.hpp"
#include <string>
#include <iostream>
#include <stack> //Used in parenthesis processing

class ULMP
{
public:
    ULMP();
    double parseString(std::string expression="");
    bool checkIfMultiFunc();
    std::string& getProcessedString();
private:
    //list of allowable operators
    char operatorList[5];
    bool multiFunc;
    Array<std::string> * functionList;
    Array<double> *numbers;
    Array<char> *operators;
    Array<int> *operatorLocations;
    std::string s;
    int charToInt(char c);
    bool isOperator(char c);
    bool doesSucceedOperator( int index) const;
    int findNextOperator(int index);
    double stringToDouble(std::string s);
    std::string doubleToString (double d);
    void specialParse(std::string &expression);
    void checkForBrackets();
    double computeFunction( int index, double fArg, double fArg2);
    bool solveFunctions();
    void removeWhiteSpace();
    void populateOperators();
    void populateNumbers();
    double evaluateExpression();
};

#endif // ULMP_H
