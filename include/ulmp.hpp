/*
   The MIT License (MIT)

   Copyright (c) <year> <copyright holders>

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
 * 1. Error checking
 * 2. (Least priority) Variables
 * ******************************
 */

#include <cmath> //required for sin, cos(to be implementated) , pow , etc.
#include "Array.hpp"
#include <string>
#include <iostream>
#include <stack> //Used in parenthesis processing

enum ULMPErrorEnum {
    ULMPNoFunctionParameter,
    ULMPUnknownToken,
    ULMPIllegalOperator,
    ULMPIllegalBracket,
    ULMPIllegalDecimal,
    ULMPBracketMismatch
};

class ULMPError {
public:
    ULMPError(ULMPErrorEnum errorType, std::string errorMessage);
    std::string& getErrorMessage();
    ULMPErrorEnum getErrorType();
private:
    ULMPErrorEnum er;
    std::string erMesg;
};

class ULMP {
public:
    ULMP();
    void checkForErrors();
    long double parseString(std::string expr);
    bool isNumber ( char c );
private:
    void removeWhiteSpace();
    std::string s;
    //bool isNumber(char c);
};
class ULMPCore
{
public:
    ULMPCore();
    long double parseString(std::string expression="");
    bool checkIfMultiFunc();
    bool isOperator(char c);
    bool checkIfFuncIndexIsMultiFunc(unsigned int index);
    std::string& getProcessedString();
private:
    //list of allowable operators
    bool multiFunc;
    Array<std::string> * functionList;
    Array<long double> *numbers;
    Array<char> *operators;
    Array<int> *operatorLocations;
    char operatorList[5];
    std::string s;
    int charToInt(char c);
    bool doesSucceedOperator( int index) const;
    int findNextOperator(int index);
    long double stringToDouble(std::string s);
    std::string doubleToString (long double d);
    void specialParse(std::string &expression);
    void checkForBrackets();
    long double computeFunction( int index, long double *fArg, long double *fArg2) throw(ULMPError);
    bool solveFunctions();
    void populateOperators();
    void populateNumbers();
    long double evaluateExpression();
};
extern "C" long double ULMPParse(const char * expr);

#endif // ULMP_H
