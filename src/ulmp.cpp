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
#include "ulmp.hpp"
#include <cstdio>
ULMPCore::ULMPCore()
{
    operatorList[0]='+';
    operatorList[1]='-';
    operatorList[2]='*';
    operatorList[3]='/';
    operatorList[4]='^';

    functionList=new Array<std::string>;

    /* Inverse functions (as defined in cmath)
     */
    functionList->push_back("asinh");
    functionList->push_back("acosh");
    functionList->push_back("atanh");

    functionList->push_back("asin");
    functionList->push_back("acos");
    functionList->push_back("atan");
    /* Hyperbolic functions (as defined in cmath)
    */
    functionList->push_back("sinh");
    functionList->push_back("cosh");
    functionList->push_back("tanh");
    /* Trignometric functions (as defined in cmath)
    */
    functionList->push_back("sin");
    functionList->push_back("cos");
    functionList->push_back("tan");
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
int ULMPCore::charToInt(char c) { //Looks simple, but does error checking :)
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
        return 10; //error code
        break;
    }
}
/* stringToDouble to convert a string to a long double
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

long double ULMPCore::stringToDouble(std::string str) {
    unsigned int divisorForDecimal=1;
    unsigned short c;
    long double answer=0.0;
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
            break;
        }
        if(str.at(i)=='+') {
            str.erase(i,1);
            i=-1;
        }
    }
    for(unsigned int i=0; i<str.length(); i++) {
        c=charToInt(str.at(i));
        if(c==10) throw ULMPError(ULMPUnknownToken, std::string("Undefined tokens in expression")); //if we find a 10, it means a non-number character was found, so throw an error
        answer=answer+(c*pow10(str.length()-i-1));
    }
    return (answer*negate)/divisorForDecimal;
}
std::string ULMPCore::doubleToString (long double d) {
    return std::to_string(d);
}

bool ULMPCore::isOperator(char c)  {
    for(unsigned int i=0; i<sizeof(operatorList) ; i++) {
        if(c==operatorList[i])
            return true;
    }
    return false;
}


bool ULMPCore::doesSucceedOperator(int index) const {
    if(index==0)
        return true;
    for(unsigned int i=0; i<sizeof(operatorList); i++ ) {
        if(s.at(index-1)==operatorList[i]) { //if previous element of string is a character return true
            return true;
        }
    }
    return false; // else false

}

int ULMPCore::findNextOperator(int index) {
    for(int i=0; i<operatorLocations->size()-1; i++) {
        if(operatorLocations->at(i)<index && index< operatorLocations->at(i+1)) {
            return operatorLocations->at(i+1);
        }
    }
    return -2; //will never reach here
}
bool ULMPCore::checkIfFuncIndexIsMultiFunc(unsigned int index) {
    switch(index) {
    case 17:
        return true;
    case 20:
        return true;
    case 23:
        return true;
    case 24:
        return true;
    default:
        return false;
    }
}
bool ULMPCore::solveFunctions() {
    multiFunc=false;
    bool multiParam=false;
    std::size_t funcIndex;
    long double *funcArg=0, *funcArg2=0, answer;// = 6
    unsigned int startOfFunc, lengthOfFunc;
    std::size_t commaIndex=0;
    for(unsigned int i=0; i<s.length(); i++) {
        if(s.at(i)==',') { //if we find this is a function with more than one parameter, do the special parse
            specialParse(s); //this modifies the string BTW
            multiFunc=true;
            return multiFunc; //we are done. this was called from another instance of ULMPCore class, and so we are just partially parsing the string
        }
    }
    // ****************************************
    // This is reached, only when string is of form, e.g. mod2.000|3.000 * sin2.3000
    commaIndex=s.find('|');
    for(int i=0; i<functionList->size(); i++) { // NOTE: i is the function no in functionList array
        funcIndex=s.find(functionList->at(i));
        if(funcIndex!=std::string::npos) {
            //continue performing operations
            startOfFunc=funcIndex+(functionList->at(i).length()); //we want to get to '2' in sin20.000
            lengthOfFunc=findNextOperator(startOfFunc)-startOfFunc;// = 6
            multiParam=checkIfFuncIndexIsMultiFunc(i);
            if(multiParam) {
                funcArg=new long double(stringToDouble(s.substr(startOfFunc, commaIndex-startOfFunc) ));

                funcArg2=new long double(stringToDouble(s.substr(commaIndex+1, lengthOfFunc-commaIndex-1)));
            } else {
                funcArg=new long double(stringToDouble(s.substr(startOfFunc, lengthOfFunc)));
            }
            answer=computeFunction(i, funcArg, funcArg2);
            s.replace(startOfFunc-functionList->at(i).length() , lengthOfFunc+functionList->at(i).length() , doubleToString(answer) );
            populateOperators();
        }
    }
    return multiFunc;
}
long double ULMPCore::computeFunction(int index, long double *fArg, long double *fArg2) throw (ULMPError) {
    const long double oneDegree=0.0174532925;
    switch(index) {
    case 0:
        return asinh(*fArg*oneDegree);
    case 1:
        return acosh(*fArg*oneDegree);
    case 2:
        return atanh(*fArg*oneDegree);
    case 3:
        return acos(*fArg*oneDegree);
    case 4:
        return asin(*fArg*oneDegree);
    case 5:
        return atan(*fArg*oneDegree);
    case 6:
        return sinh(*fArg*oneDegree);
    case 7:
        return cosh(*fArg*oneDegree);
    case 8:
        return tanh(*fArg*oneDegree);
    case 9:
        return sin(*fArg*oneDegree);
    case 10:
        return cos(*fArg*oneDegree);
    case 11:
        return tan(*fArg*oneDegree);
    case 12:
        return exp(*fArg);
    case 13:
        return log(*fArg);
    case 14:
        return log10(*fArg);
    case 15:
        return sqrt(*fArg);
    case 16:
        return cbrt(*fArg);
    case 17:
        if(fArg2!=0)
            return hypot(*fArg, *fArg2);
        else throw ULMPError(ULMPNoFunctionParameter, "hypot expects two parameters but only one received");
    case 18:
        return ceil(*fArg);
    case 19:
        return floor(*fArg);
    case 20:
        if(fArg2!=0)
            return fmod(*fArg, *fArg2);
        else throw ULMPError(ULMPNoFunctionParameter, "mod expects two parameters but only one received");
    case 21:
        return round(*fArg);
    case 22:
        return nearbyint(*fArg);
    case 23:
        if(fArg2!=0)
            return fmax(*fArg, *fArg2);
        else throw ULMPError(ULMPNoFunctionParameter, "max expects two parameters but only one received");
    case 24:
        if(fArg2!=0)
            return fmin(*fArg, *fArg2);
        else throw ULMPError(ULMPNoFunctionParameter, "min expects two parameters but only one received");
    case 25:
        return fabs(*fArg);

    }
    return -1; //will never reach here
}


void ULMPCore::populateOperators() {
    operatorLocations->clear();
    operators->clear();
    operatorLocations->push_back(-1);
    for(int i=0; i<s.length(); i++) {
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
void ULMPCore::populateNumbers() {
    std::string num;
    for(int i=0; i<operatorLocations->size()-1; i++) {
        num=s.substr(operatorLocations->at(i)+1, operatorLocations->at(i+1) - (operatorLocations->at(i)+1) ) ;
        numbers->push_back( stringToDouble(num) );
    }
}
std::string& ULMPCore::getProcessedString() {
    return s;
}
void ULMPCore::checkForBrackets() {
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
            ULMPCore u;
            long double b = u.parseString(sub);
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

bool ULMPCore::checkIfMultiFunc() {
    return multiFunc;
}

void ULMPCore::specialParse(std::string &expression) {
    std::size_t commaIndex=s.find(',');
    ULMPCore u;
    std::string temp=doubleToString(u.parseString(expression.substr(0, commaIndex) ) );
    expression.replace(0,commaIndex, temp);
    commaIndex=s.find(',');
    ULMPCore v;
    temp=doubleToString(v.parseString(expression.substr(commaIndex+1, expression.length()-commaIndex-1)));
    expression.replace(commaIndex+1, expression.length()-commaIndex-1, temp);

    commaIndex=s.find(',');
    expression.replace(commaIndex,1,"|");
}

long double ULMPCore::parseString(std::string expression) {
    s=expression;
    checkForBrackets();
    operatorLocations=new Array<int>();
    operators=new Array<char>();
    populateOperators();
    if(solveFunctions()) {
        multiFunc=true;
        return -1;
    };
    numbers=new Array<long double>();
    populateNumbers();
    delete operatorLocations;
    long double answer = evaluateExpression();
    delete operators;
    delete numbers;
    return answer;
}

long double ULMPCore::evaluateExpression() {
    long double temp=0;
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
// END OF ULMPCore Class
/* ***********************************************************/

// BEGIN of ULMPError Class
/*************************************************************/
ULMPError::ULMPError(ULMPErrorEnum errorType, std::string errorMessage) {
    er=errorType;
    erMesg=errorMessage;
}
ULMPErrorEnum ULMPError::getErrorType() {
    return er;
}
std::string& ULMPError::getErrorMessage() {
    return erMesg;
}
// END of ULMPError Class
/**************************************************************/
ULMP::ULMP() {}
void ULMP::removeWhiteSpace() {
    for(int i=0; i<s.length(); i++) {
        if(s.at(i)==' ') {
            s.erase(i,1);
            i=-1; //to erase consecutive spaces
        }
    }
}

bool ULMP::isNumber(char c) {
    if(( ( (int) c ) >= ( (int) '0' ) ) && ( ( (int) c ) <=( (int) '9' )) ) //if ascii code of given char is between those of '0' and '9' then we are good
        return true;
    else
        return false;
}
void ULMP::checkForErrors() {
    /* This function is only going to check for integrity of the available operators.
     * The test for unknown operators is in the charToInt function */
    /* ***************************************************************/
    /* Test for illegal operator order */
    ULMPCore u; //temporary ULMPCore class used as reference
    //All the below code is saying is that if two consecutive operators are present, and the second is not a + or a -, then it's an error
    for(unsigned int i=0; i<s.size()-1; i++) {
        for(unsigned int j=0; j<5; j++) {
            if(u.isOperator(s.at(i)) && u.isOperator(s.at(i+1))) {
                if(s.at(i+1)!='-') {
                    if(s.at(i+1)=='+') break; //doesn't matter, its the unary + operator, so ignore
                    std::string temp = "Illegal operator at index ";
                    temp.append(std::to_string(i+1));
                    throw ULMPError(ULMPIllegalOperator, temp);
                }
            }
        }
    }
    /* *****************************************************************/
    // Test for mismatched brackets
    // This one is really simple, just loop through the string, count the number of opening and closing brackets, if they don't match, or ) comes before (, throw an error
    unsigned int opening=0, closing = 0, firstOpened = 0;
    bool opened=false;
    for(unsigned int i=0; i<s.size(); i++) {
        if(s.at(i)=='(') {
            opening++;
            if(opened==false) {
                opened=true;
                firstOpened=i;
            }
        }
        if(s.at(i)==')') {
            if(opening<=closing) {
                std::string temp = "Illegal Bracket at index ";
                temp.append(std::to_string(i));
                throw ULMPError(ULMPIllegalBracket, temp);
            }
            closing++;
        }
    }
    if(opening!=closing) {
        std::string temp = "Bracket at index " + std::to_string(firstOpened) + " doesn't have a matching closing parenthesis";
        throw ULMPError(ULMPBracketMismatch, std::string(temp));
    }
    /* *****************************************************************/
    /* Test for illegal use of decimal, e.g. 2./2 */
    for(unsigned int i=0; i<s.size(); i++) {
        if(s.at(i)=='.' && !isNumber(s.at(i+1))) {
            std::string temp="Illegal Decimal at index ";
            temp.append(std::to_string(i));
            throw ULMPError(ULMPIllegalDecimal, temp);
        }
    }
}

long double ULMP::parseString(std::string expr) {
    s=expr;
    removeWhiteSpace();
    checkForErrors();
    ULMPCore u;
    return u.parseString(s);
}

extern "C" long double ULMPParse(const char *expr)
{
    ULMP u;
    try {
        return u.parseString(expr);
    } catch(ULMPError e) {
        printf("Error of type: %s \n", e.getErrorMessage().c_str());
    }
}

