/*
   The MIT License (MIT)

   Copyright (c) 2013 Sumanth v

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

#include "ulmp.hpp"

ULMP::ULMP()
{
    operatorList[0]='+';
    operatorList[1]='-';
    operatorList[2]='*';
    operatorList[3]='/';
    operatorList[4]='^';

    functionList=new Array<std::string>;
    /* Trignometric functions (as defined in cmath)
    */
    functionList->push_back("sin");
    functionList->push_back("cos");
    functionList->push_back("tan");
    functionList->push_back("asin");
    functionList->push_back("acos");
    functionList->push_back("atan");
    /* Hyperbolic functions (as defined in cmath)
    */
    functionList->push_back("sinh");
    functionList->push_back("cosh");
    functionList->push_back("tanh");
    functionList->push_back("asinh");
    functionList->push_back("acosh");
    functionList->push_back("atanh");
    /* Exponential and logarithmic functions (as defined in cmath)
    */
    functionList->push_back("exp");
    functionList->push_back("log");
    functionList->push_back("log10");
    /* Power functions (as defined in cmath)
    */
    functionList->push_back("sqrt");
    functionList->push_back("cbrt");
    functionList->push_back("hypot");
    /* Rounding and remainding functions (as defined in cmath)
    */
    functionList->push_back("ceil");
    functionList->push_back("floor");
    functionList->push_back("mod");
    functionList->push_back("round");
    functionList->push_back("nearbyint");
    functionList->push_back("max");
    functionList->push_back("min");
    functionList->push_back("abs");
}


int ULMP::charToInt(char c) {
    switch(c) {
    case '1':
        return 1;
        break;
    case '2':
        return 2;
        break;
    case '3':
        return 3;
        break;
    case '4':
        return 4;
        break;
    case '5':
        return 5;
        break;
    case '6':
        return 6;
        break;
    case '7':
        return 7;
        break;
    case '8':
        return 8;
        break;
    case '9':
        return 9;
        break;
    case '0':
        return 0;
        break;
    default:
        return -1;
        break;
    }
}
/* stringToDouble to convert a string to a double
 * Example number: 235.53
 * decPosition will be 3
 * s.length() after erasure of decimal will be 5
 * We should divide 23553 by 10^2 to get 235.53
 * So the power to which 10 is to be raised is 5-3, or length-decPosition
 *
 * Algorithm for determining numbers:
 * Example number: 23553
 * length=5
 * 2 should be multiplied by 10^4 to get 20000
 * 3 should be multiplied by 10^3 to get 3000
 * 5 should be multiplied by 10^2 to get 500
 * 5 should be multiplied by 10^1 to get 50
 * 3 should be multiplied by 10^0 to get 3
 *
 * Therefore, s.at(i) should be multiplied by 10^len-1
 * and added to the previous result
 */

double ULMP::stringToDouble(std::string str) {
    unsigned int divisorForDecimal=1;
    unsigned short c;
    double answer=0.0;
    int negate=1;

    for(unsigned int i=0; i<str.length(); i++) {
        if(str.at(i)=='.') {
            str.erase(i,1);
            divisorForDecimal=pow10(str.length()-i);
            break;
        }
    }

    for(int i=0; i<str.length(); i++) {
        if(str.at(i)=='-') {
            str.erase(i,1);
            negate*=-1;
            i=-1;
        }
    }

    for(unsigned int i=0; i<str.length(); i++) {
        c=charToInt(str.at(i));
        answer=answer+(c*pow10(str.length()-i-1));
    }
    return (answer*negate)/divisorForDecimal;
}
std::string ULMP::doubleToString (double d) {
    return std::to_string(d);
}

bool ULMP::isOperator(char c)  {
    for(unsigned int i=0; i<sizeof(operatorList) ; i++) {
        if(c==operatorList[i])
            return true;
    }
    return false;
}

bool ULMP::doesSucceedOperator(int index) const {
    if(index==0)
        return true;
    for(unsigned int i=0; i<sizeof(operatorList); i++ ) {
        if(s.at(index-1)==operatorList[i]) { //if previous element of string is a character return true
            return true;
        }
    }
    return false; // else false

}
int ULMP::findNextOperator(int index) {
    for(int i=0; i<operatorLocations->size()-1; i++) {
        if(operatorLocations->at(i)<index && index< operatorLocations->at(i+1)) {
            return operatorLocations->at(i+1);
        }
    }
}

bool ULMP::solveFunctions() {
    multiFunc=false;
    std::size_t funcIndex;
    double funcArg, funcArg2, answer;
    unsigned int startOfFunc, lengthOfFunc;
    std::size_t commaIndex=0;
    for(unsigned int i=0; i<s.length(); i++) {
        if(s.at(i)==',') {
            specialParse(s);
            multiFunc=true;
            return multiFunc;
        }
    }
    commaIndex=s.find('|');
    for(int i=0; i<functionList->size(); i++) {
        funcIndex=s.find(functionList->at(i));
        if(funcIndex!=std::string::npos) {
            //continue performing operations
            startOfFunc=funcIndex+(functionList->at(i).length());
            lengthOfFunc=findNextOperator(startOfFunc)-startOfFunc;
            if(commaIndex!=std::string::npos) {
                funcArg=stringToDouble(s.substr(startOfFunc, commaIndex-startOfFunc) );
                funcArg2=stringToDouble(s.substr(commaIndex+1, lengthOfFunc-commaIndex-1));
            } else {
                funcArg=stringToDouble(s.substr(startOfFunc, lengthOfFunc));
            }
            answer=computeFunction(i, funcArg, funcArg2);
            s.replace(startOfFunc-functionList->at(i).length() , lengthOfFunc+functionList->at(i).length() , doubleToString(answer) );
            populateOperators();
        }
    }
    return multiFunc;
}
double ULMP::computeFunction(int index, double fArg, double fArg2) {
    const double oneDegree=0.0174532925;
    switch(index) {
    case 0:
        return sin(fArg*oneDegree);
    case 1:
        return cos(fArg*oneDegree);
    case 2:
        return tan(fArg*oneDegree);
    case 3:
        return asin(fArg*oneDegree);
    case 4:
        return acos(fArg*oneDegree);
    case 5:
        return atan(fArg*oneDegree);
    case 6:
        return sinh(fArg*oneDegree);
    case 7:
        return cosh(fArg*oneDegree);
    case 8:
        return tanh(fArg*oneDegree);
    case 9:
        return asinh(fArg*oneDegree);
    case 10:
        return acosh(fArg*oneDegree);
    case 11:
        return atanh(fArg*oneDegree);
    case 12:
        return exp(fArg);
    case 13:
        return log(fArg);
    case 14:
        return log10(fArg);
    case 15:
        return sqrt(fArg);
    case 16:
        return cbrt(fArg);
    case 17:
        return hypot(fArg, fArg2);
    case 18:
        return ceil(fArg);
    case 19:
        return floor(fArg);
    case 20:
        return fmod(fArg, fArg2);
    case 21:
        return round(fArg);
    case 22:
        return nearbyint(fArg);
    case 23:
        return fmax(fArg, fArg2);
    case 24:
        return fmin(fArg, fArg2);
    case 25:
        return fabs(fArg);

    }

}
void ULMP::removeWhiteSpace() {
    for(unsigned int i=0; i<s.length(); i++) {
        if(s.at(i)==' ') {
            s.erase(i,1);
            i=-1;
            continue;
        }
    }
}

void ULMP::populateOperators() {
    operatorLocations->clear();
    operators->clear();
    operatorLocations->push_back(-1);
    for(unsigned int i=0; i<s.length(); i++) {
        if( isOperator( s.at(i) ) && !doesSucceedOperator(i) ) { //if s at i is an operator and it does not succeed any other operator
            operators->push_back(s.at(i)); // add it to operators array
            operatorLocations->push_back(i);
        }
    }
    operatorLocations->push_back(s.length());
}

/* populateNumbers
 * Used to seperate numbers from operators and add them to numbers array
 * Consider expression : 25234.5+53.63
 * 25234.5 starts at 0 and has a length of 7
 * operatorLocations.at(0)+1=0 and operatorLocations.at(1)=7
 * 53.63 starts at 8 and has a length of 5
 * operatorLocations.at(1)+1=8 and operatorLocations.at(2)=13
 * Therefore substr(operatorLocations.at(i)+1, operatorLocations.at(i+1) - operatorLocations.at(i)+1)
 */
void ULMP::populateNumbers() {
    std::string num;
    for(int i=0; i<operatorLocations->size()-1; i++) {
        num=s.substr(operatorLocations->at(i)+1, operatorLocations->at(i+1) - (operatorLocations->at(i)+1) ) ;
        numbers->push_back( stringToDouble(num) );
    }
}
std::string& ULMP::getProcessedString() {
    return s;
}
void ULMP::checkForBrackets() {
    std::stack<unsigned int> brackets;
    std::string sub;
    for(int j=0; j<s.length(); j++) {
        if(s.at(j)=='(') {
            brackets.push(j);
        }
        if(s.at(j)==')') {
            unsigned int start=brackets.top();
            brackets.pop();
            unsigned int end=j;
            sub=s.substr(start+1, end-start-1);
            ULMP u;
            double b = u.parseString(sub);
            if(!u.checkIfMultiFunc()) {
                sub=doubleToString(b);
                s.erase(start, (end-start) +1);
                s.insert(start,sub);
                j=-1;
            }
            else {
                sub=u.getProcessedString();
                s.erase(start, (end-start)+1 );
                s.insert(start,sub);
            }
        }
    }
}

bool ULMP::checkIfMultiFunc() {
    return multiFunc;
}

void ULMP::specialParse(std::string &expression) {
    std::size_t commaIndex=s.find(',');
    ULMP u;
    std::string temp=doubleToString(u.parseString(expression.substr(0, commaIndex) ) );
    expression.replace(0,commaIndex, temp);
    commaIndex=s.find(',');
    ULMP v;
    temp=doubleToString(v.parseString(expression.substr(commaIndex+1, expression.length()-commaIndex-1)));
    expression.replace(commaIndex+1, expression.length()-commaIndex-1, temp);

    commaIndex=s.find(',');
    expression.replace(commaIndex,1,"|");
}
double ULMP::parseString(std::string expression) {
    s=expression;
    removeWhiteSpace();
    checkForBrackets();
    operatorLocations=new Array<int>();
    operators=new Array<char>();

    populateOperators();
    if(solveFunctions()) {
        multiFunc=true;
        return -1;
    };
    populateOperators();
    numbers=new Array<double>();
    populateNumbers();
    delete operatorLocations;
    double answer = evaluateExpression();
    delete operators;
    delete numbers;
    return answer;
}

double ULMP::evaluateExpression() {
    double temp=0;
    bool linearAdd=false, linearMul=false;
    for(unsigned int i=0; i<operators->size(); i++) {
        if(operators->at(i)=='+' || operators->at(i)=='-') linearAdd=true;
        if(operators->at(i)=='*' || operators->at(i)=='/') linearMul=true;
    }
    if(!(linearAdd && linearMul)) { //if both addition/subtraction and multiplication/division are not present, do linear calculation
        if(linearAdd) {
            for(int i=0; i<operators->size(); i++) {
                if(operators->at(i) == '+') {
                    temp=numbers->at(i)+numbers->at(i+1);
                } else temp=numbers->at(i)-numbers->at(i+1);
                numbers->at(i)=temp;
                numbers->erase(i+1);
                operators->erase(i);
                i=-1;
            }
        }
        if(linearMul) {
            for(int i=0; i<operators->size(); i++) {
                if(operators->at(i) == '*') {
                    temp=numbers->at(i)*numbers->at(i+1);
                } else temp=numbers->at(i)/numbers->at(i+1);
                numbers->at(i)=temp;
                numbers->erase(i+1);
                operators->erase(i);
                i=-1;
            }
        }
    }
    for(int i=0; i<operators->size(); i++) {
        if(operators->at(i) == '^') {
            temp=pow(numbers->at(i),numbers->at(i+1));
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }
    }
    for(int i=0; i<operators->size(); i++) {
        if(operators->at(i) == '/') {
            temp=numbers->at(i)/numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }
    }
    for(int i=0; i<operators->size(); i++) {
        if(operators->at(i) == '*') {
            temp=numbers->at(i)*numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }
    }
    for(int i=0; i<operators->size(); i++) {
        if(operators->at(i) == '+') {
            temp=numbers->at(i)+numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }
    }
    for(int i=0; i<operators->size(); i++) {
        if(operators->at(i) == '-') {
            temp=numbers->at(i)-numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }
    }
    return numbers->at(0);
}
