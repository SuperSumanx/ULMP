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
    ULMP(std::string expression);
    double parseString();
    double parseString(std::string expression);
    double parseString(char * expression);
    void setString(const char* expression); //used if first parseString function is used

private:
    //list of allowable operators
    char operatorList[5];
    Array<double> *numbers;
    Array<char> *operators;
    Array<short> *operatorLocations;
    std::string s;
    int charToInt(char c);
    bool isOperator(char c);
    bool doesSucceedOperator(std::string &s, int index) const;
    double stringToDouble(std::string &s);
    std::string doubleToString (double d);
    void checkForBrackets(std::string &s);
    void removeWhiteSpace(std::string &s);
    void populateOperators(std::string &s);
    void populateNumbers(std::string &s);
    double evaluateExpression();
};

#endif // ULMP_H
