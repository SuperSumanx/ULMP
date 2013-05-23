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
 * 1. Power (^) function
 * 2. Parenthesis for precedence
 * 3. Functions (sin, cos, tan, arcsin, arccos, arctan, abs, etc.)
 * 4. Error checking
 * 5. (Least priority) Variables
 * ******************************
 */

#include <cmath> //required for sin, cos(to be implementated) , pow , etc.
#include "Array.h"
#include <string>
#include <iostream>

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
    char operatorList[4];
    Array<double> *numbers;
    Array<char> *operators;
    Array<short> *operatorLocations;
    std::string s;
    int charToInt(char c);
    bool isOperator(char c);
    bool doesSucceedOperator(std::string &s, int index) const;
    double stringToDouble(std::string &s);
    void removeWhiteSpace(std::string &s);
    void populateOperators(std::string &s);
    void populateNumbers(std::string &s);
    double evaluateExpression();
};

#endif // ULMP_H
