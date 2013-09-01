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

__impl::ULMPCore::ULMPCore()
{
    operatorList[0]='+';
    operatorList[1]='-';
    operatorList[2]='*';
    operatorList[3]='/';
    operatorList[4]='^';

    functionList=new std::vector<std::string>;

    userDefFuncImpl=new std::vector<long double(*)(const std::vector<long double>&)>;
    numOfFunctionParams=new std::vector<unsigned int>;

    /* Inverse functions (as defined in cmath)
    */
    functionList->push_back("asinh");
    numOfFunctionParams->push_back(1);
    functionList->push_back("acosh");
    numOfFunctionParams->push_back(1);
    functionList->push_back("atanh");
    numOfFunctionParams->push_back(1);

    functionList->push_back("asin");
    numOfFunctionParams->push_back(1);
    functionList->push_back("acos");
    numOfFunctionParams->push_back(1);
    functionList->push_back("atan");
    numOfFunctionParams->push_back(1);
    /* Hyperbolic functions (as defined in cmath)
    */
    functionList->push_back("sinh");
    numOfFunctionParams->push_back(1);
    functionList->push_back("cosh");
    numOfFunctionParams->push_back(1);
    functionList->push_back("tanh");
    numOfFunctionParams->push_back(1);
    /* Trignometric functions (as defined in cmath)
    */
    functionList->push_back("sin");
    numOfFunctionParams->push_back(1);
    functionList->push_back("cos");
    numOfFunctionParams->push_back(1);
    functionList->push_back("tan");
    numOfFunctionParams->push_back(1);
    /* Exponential and logarithmic functions (as defined in cmath)
    */
    functionList->push_back("exp");
    numOfFunctionParams->push_back(1);
    functionList->push_back("log");
    numOfFunctionParams->push_back(1);
    functionList->push_back("log10");
    numOfFunctionParams->push_back(1);
    /* Power functions (as defined in cmath)
    */
    functionList->push_back("sqrt");
    numOfFunctionParams->push_back(1);
    functionList->push_back("cbrt");
    numOfFunctionParams->push_back(1);
    functionList->push_back("hypot");
    numOfFunctionParams->push_back(1);
    /* Rounding and remainding functions (as defined in cmath)
    */
    functionList->push_back("ceil");
    numOfFunctionParams->push_back(1);
    functionList->push_back("floor");
    numOfFunctionParams->push_back(1);
    functionList->push_back("mod");
    numOfFunctionParams->push_back(2);
    functionList->push_back("round");
    numOfFunctionParams->push_back(1);
    functionList->push_back("nearbyint");
    numOfFunctionParams->push_back(1);
    functionList->push_back("max");
    numOfFunctionParams->push_back(2);
    functionList->push_back("min");
    numOfFunctionParams->push_back(2);
    functionList->push_back("abs");
    numOfFunctionParams->push_back(1);
}

int __impl::ULMPCore::charToInt(char c)   //Looks simple, but does error checking :)
{
    switch(c)
    {
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case '0':
        return 0;
    default:
        return 10; //error code
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

long double __impl::ULMPCore::stringToDouble(std::string str)
{
    unsigned int divisorForDecimal=1;
    unsigned short c;
    long double answer=0.0;
    int negate=1;
    for(unsigned int i=0; i<str.length(); i++)
    {
        if(str.at(i)=='.')
        {
            str.erase(i,1);
            divisorForDecimal=pow(10,str.length()-i);
            break;
        }
    }
    for(unsigned int i=0; i<str.length(); i++)
    {
        if(str.at(i)=='-')
        {
            str.erase(i,1);
            negate*=-1;
            i--;
            continue;
        }
        if(str.at(i)=='+')
        {
            str.erase(i,1);
            i--;
        }
    }
    for(unsigned int i=0; i<str.length(); i++)
    {
        c=charToInt(str.at(i));
        if(c==10)
        {
            std::cout <<"The string at this time was " << s << std::endl;
            std::cout << "The argument was " << str << std::endl;
            std::string errMsg= "Undefined token in expression: " ;
            errMsg.push_back(str.at(i));
            throw ULMPError(errMsg); //if we find a 10, it means a non-number character was found, so throw an error
        }
        answer=answer+(c*pow(10,str.length()-i-1));
    }
    return (answer*negate)/divisorForDecimal;
}
std::string __impl::ULMPCore::doubleToString (long double d)
{
    return std::to_string(d);
}

bool __impl::ULMPCore::isOperator(char c)
{
    for(unsigned int i=0; i<sizeof(operatorList) ; i++)
    {
        if(c==operatorList[i])
            return true;
    }
    return false;
}

bool __impl::ULMPCore::doesSucceedOperator(int index) const
{
    if(index==0)
        return true;
    for(unsigned int i=0; i<sizeof(operatorList); i++ )
    {
        if(s.at(index-1)==operatorList[i])   //if previous element of string is a character return true
        {
            return true;
        }
    }
    return false; // else false
}

int __impl::ULMPCore::findNextOperator(int index)
{
    for(unsigned int i=0; i<operatorLocations.size()-1; i++)
    {
        if(operatorLocations.at(i)<index && index< operatorLocations.at(i+1))
        {
            return operatorLocations.at(i+1);
        }
    }
    return -1; //will never reach here
}

bool __impl::ULMPCore::solveFunctions()
{
    multiFunc=false;
    std::size_t funcIndex;
    long double answer;
    std::vector<long double> args;
    unsigned int startOfFunc, lengthOfFunc, endOfFunc;
    std::size_t commaIndex=0, prevCI=-1;
    for(unsigned int i=0; i<s.length(); i++)
    {
        if(s.at(i)==',')   //if we find this is a function with more than one parameter, do the special parse
            //(we are assured that we get commas only in functions)
        {
            specialParse(s); //this modifies the string BTW
            multiFunc=true;
            return multiFunc; //we are done. this was called from another instance of ULMPCore class, and so we are just partially parsing the string }
        }
    }
    // *****************************************************************************
    //                          FUNCTION CRUNCHING UNIT
    // This is reached, only when string is of form, e.g. mod2.000|3.000 * sin2.3000
    for(unsigned int i=0; i<functionList->size(); i++)   // NOTE: i is the function no in functionList array
    {
        funcIndex=s.find(functionList->at(i));
        if(funcIndex!=std::string::npos && isNumber(s.at(funcIndex+functionList->at(i).length())) && (funcIndex==0 || isOperator(s.at(funcIndex-1)) ) )
        {
            args.clear();
            //continue performing operations
            startOfFunc=funcIndex+(functionList->at(i).length()); //we want to get to '2' in sin20.000
            prevCI=startOfFunc-1; // used in multi-param functions.
            lengthOfFunc=findNextOperator(startOfFunc)-startOfFunc;// = 6
            endOfFunc=findNextOperator(startOfFunc);
            if(numOfFunctionParams->at(i)==1)
            {
                args.push_back(stringToDouble(s.substr(startOfFunc, lengthOfFunc)));
            }
            else
            {
                for(;;)
                {
                    commaIndex=s.find('|',prevCI+1);
                    if(commaIndex==std::string::npos || endOfFunc<commaIndex)
                    {
                        args.push_back(stringToDouble(s.substr(prevCI+1, startOfFunc+lengthOfFunc-prevCI-1))); 
                        break;
                    }
                    args.push_back(stringToDouble(s.substr(prevCI+1, commaIndex-prevCI-1)));
                    prevCI=commaIndex;
                }
            }
            answer=computeFunction(i, args);
            s.replace(startOfFunc-functionList->at(i).length() , lengthOfFunc+functionList->at(i).length() , doubleToString(answer) );
            i--; //in case more of the same function is present.
            populateOperators();
        }
    }
    return multiFunc;
}

long double __impl::ULMPCore::computeFunction(int index, const std::vector<long double>& args) throw (ULMPError)
{
    const long double oneDegree=0.0174532925;
    if(numOfFunctionParams->at(index)!=args.size())
    {
        std::string errMsg;
        errMsg = functionList->at(index) + " expects " + std::to_string(numOfFunctionParams->at(index)) + " parameters";
        throw ULMPError(errMsg);
    }
    switch(index)
    {
    case 0:
        return asinh(args.at(0)*oneDegree);
    case 1:
        return acosh(args.at(0)*oneDegree);
    case 2:
        return atanh(args.at(0)*oneDegree);
    case 3:
        return asin(args.at(0)*oneDegree);
    case 4:
        return acos(args.at(0)*oneDegree);
    case 5:
        return atan(args.at(0)*oneDegree);
    case 6:
        return sinh(args.at(0)*oneDegree);
    case 7:
        return cosh(args.at(0)*oneDegree);
    case 8:
        return tanh(args.at(0)*oneDegree);
    case 9:
        return sin(args.at(0)*oneDegree);
    case 10:
        return cos(args.at(0)*oneDegree);
    case 11:
        return tan(args.at(0)*oneDegree);
    case 12:
        return exp(args.at(0));
    case 13:
        return log(args.at(0));
    case 14:
        return log10(args.at(0));
    case 15:
        return sqrt(args.at(0));
    case 16:
        return cbrt(args.at(0));
    case 17:
        return hypot(args.at(0), args.at(1));
    case 18:
        return ceil(args.at(0));
    case 19:
        return floor(args.at(0));
    case 20:
        return fmod(args.at(0), args.at(1));
    case 21:
        return round(args.at(0));
    case 22:
        return nearbyint(args.at(0));
    case 23:
        return fmax(args.at(0), args.at(1));
    case 24:
        return fmin(args.at(0), args.at(1));
    case 25:
        return fabs(args.at(0));
    }
    if(index >= 26)
    {
        return userDefFuncImpl->at(index-26)(args);
    }
    return -1; //will never reach here
}

void __impl::ULMPCore::populateOperators()
{
    operatorLocations.clear();
    operators.clear();
    operatorLocations.push_back(-1);
    for(unsigned int i=0; i<s.length(); i++)
    {
        if(isOperator( s.at(i) ) && !doesSucceedOperator(i) )   //if s at i is an operator and it does not succeed any other operator
        {
            operators.push_back(s.at(i)); // add it to operators array
            operatorLocations.push_back(i);
        }
    }
    operatorLocations.push_back(s.length());
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
void __impl::ULMPCore::populateNumbers()
{
    numbers->clear();
    std::string num;
    for(unsigned int i=0; i<operatorLocations.size()-1; i++)
    {
        num=s.substr(operatorLocations.at(i)+1, operatorLocations.at(i+1) - (operatorLocations.at(i)+1) ) ;
        numbers->push_back( stringToDouble(num) );
    }
}

std::string& __impl::ULMPCore::getProcessedString()
{
    return s;
}

void __impl::ULMPCore::checkForBrackets()
{
    std::stack<unsigned int> brackets;
    std::string sub;
    for(unsigned int j=0; j<s.length(); j++)
    {
        if(s.at(j)=='(')
        {
            brackets.push(j);
        }
        if(s.at(j)==')')
        {
            unsigned int start=brackets.top();
            brackets.pop();
            unsigned int end=j;
            sub=s.substr(start+1, end-start-1);
            ULMPCore u;
            long double b = u.parseString(sub);
            if(!u.checkIfMultiFunc())
            {
                sub=doubleToString(b);
                s.erase(start, (end-start) +1);
                s.insert(start,sub);
                j=start;
            }
            else
            {
                sub=u.getProcessedString();
                s.erase(start, (end-start)+1 );
                s.insert(start,sub);
            }
        }
    }
}

bool __impl::ULMPCore::checkIfMultiFunc()
{
    return multiFunc;
}

void __impl::ULMPCore::specialParse(std::string &expression)   //we are certain we will not come here if there is only one parameter
{
    std::size_t commaIndex, prevCI=-1;
    ULMPCore u;
    std::string temp;

    for(;;)
    {
        commaIndex=s.find(',');
        if(commaIndex==std::string::npos)
        {
            // example string here is 2.00000|3
            temp=doubleToString(u.parseString(expression.substr(prevCI+1, expression.length()-1-prevCI)));
            expression.replace(prevCI+1,expression.length()-prevCI, temp);
            break;
        }
        temp=doubleToString(u.parseString(expression.substr(prevCI+1, commaIndex-prevCI-1)));
        expression.replace(prevCI+1,commaIndex-prevCI-1, temp);
        prevCI=s.find(",");
        expression.replace(prevCI,1,"|");
    }
}

long double __impl::ULMPCore::parseString(std::string expression)
{
    multiFunc=false;
    s=expression;
    checkForBrackets();
    populateOperators();
    if(solveFunctions())
    {
        multiFunc=true;
        return -1;
    };
    numbers=new std::vector<long double>();
    populateNumbers();
    long double answer = evaluateExpression();
    delete numbers;
    return answer;
}

long double __impl::ULMPCore::evaluateExpression()
{
    long double temp=0;
    bool linearAdd=false, linearMul=false;
    bool powPresent=false;
    for(unsigned int i=0; i<operators.size(); i++)
    {
        if(operators.at(i)=='+' || operators.at(i)=='-') linearAdd=true;
        if(operators.at(i)=='*' || operators.at(i)=='/') linearMul=true;
        if(operators.at(i)=='^') powPresent=true;
    }
    if(!(linearAdd && linearMul) && !powPresent)   //if both addition/subtraction and multiplication/division are not present, do linear calculation
    {
        if(linearAdd)
        {
            for(unsigned int i=0; i<operators.size(); i++)
            {
                if(operators.at(i) == '+')
                {
                    temp=numbers->at(i)+numbers->at(i+1);
                }
                else temp=numbers->at(i)-numbers->at(i+1);
                numbers->at(i)=temp;
                numbers->erase(numbers->begin()+i+1);
                operators.erase(operators.begin()+i);
                i=-1;
            }
        }
        if(linearMul)
        {
            for(unsigned int i=0; i<operators.size(); i++)
            {
                if(operators.at(i) == '*')
                {
                    temp=numbers->at(i)*numbers->at(i+1);
                }
                else temp=numbers->at(i)/numbers->at(i+1);
                numbers->at(i)=temp;
                numbers->erase(numbers->begin()+i+1);
                operators.erase(operators.begin()+i);
                i=-1;
            }
        }
    }
    for(unsigned int i=0; i<operators.size(); i++)
    {
        if(operators.at(i) == '^')
        {
            temp=pow(numbers->at(i),numbers->at(i+1));
            numbers->at(i)=temp;
            numbers->erase(numbers->begin()+i+1);
            operators.erase(operators.begin()+i);
            i=-1;
        }
    }
    for(unsigned int i=0; i<operators.size(); i++)
    {
        if(operators.at(i) == '/')
        {
            temp=numbers->at(i)/numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(numbers->begin()+i+1);
            operators.erase(operators.begin()+i);
            i=-1;
        }
    }
    for(unsigned int i=0; i<operators.size(); i++)
    {
        if(operators.at(i) == '*')
        {
            temp=numbers->at(i)*numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(numbers->begin()+i+1);
            operators.erase(operators.begin()+i);
            i=-1;
        }
    }
    for(unsigned int i=0; i<operators.size(); i++)
    {
        if(operators.at(i) == '+')
        {
            temp=numbers->at(i)+numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(numbers->begin()+i+1);
            operators.erase(operators.begin()+i);
            i=-1;
        }
    }
    for(unsigned int i=0; i<operators.size(); i++)
    {
        if(operators.at(i) == '-')
        {
            temp=numbers->at(i)-numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(numbers->begin()+i+1);
            operators.erase(operators.begin()+i);
            i=-1;
        }
    }
    return numbers->at(0);
}

void __impl::ULMPCore::defineFunction(std::string funcName, long double (*func)(const std::vector<long double>& args), unsigned int num)
{
    functionList->push_back(funcName);
    userDefFuncImpl->push_back(func);
    numOfFunctionParams->push_back(num);
}
bool __impl::ULMPCore::isNumber(char c)
{
    if(( ( (int) c ) >= ( (int) '0' ) ) && ( ( (int) c ) <=( (int) '9' )) ) //if ascii code of given char is between those of '0' and '9' then we are good
        return true;
    else
        return false;
}

__impl::ULMPCore::~ULMPCore()
{
    delete userDefFuncImpl; //array of function pointers
    delete numOfFunctionParams;
    delete functionList;
}
// END OF ULMPCore Class
/* ***********************************************************/

// BEGIN of ULMPError Class
/*************************************************************/
ULMPError::ULMPError(std::string errorMessage)
{
    erMesg=errorMessage;
}

std::string ULMPError::getErrorMessage()
{
    return erMesg;
}

// END of ULMPError Class
/**************************************************************/
ULMP::ULMP()
{
    constants=new std::vector<std::string>;
    constantsValues=new std::vector<long double>;
    //add some common constants
    constants->push_back("pi");
    constants->push_back("e");
    constantsValues->push_back(3.14159265359);
    constantsValues->push_back(2.71828182846);
    u=new __impl::ULMPCore;
}

void ULMP::removeWhiteSpace()
{
    for(unsigned int i=0; i<s.length(); i++)
    {
        if(s.at(i)==' ')
        {
            s.erase(i,1);
            i--; //to erase consecutive spaces
        }
    }
}

void ULMP::defineFunction(std::string funcName, long double(*func)(const std::vector<long double>&), unsigned int num)
{
    for(unsigned int i=0; i<s.length(); i++)
    {
        std::cout << s.at(i) << std::endl;
        if(!isALetter(s.at(i)) || s.at(i)!='_')
        {
            throw ULMPError("Function cannot have numbers or special characters");
        }
    }
    u->defineFunction(funcName, func, num);
}

void ULMP::checkForErrors()
{

    /* This function is only going to check for integrity of the available operators.
     * The test for unknown operators is in the charToInt function */
    /* ***************************************************************/
    /* Test for illegal operator order */
    //All the below code is saying is that if two consecutive operators are present, and the second is not a + or a -, then it's an error
    for(unsigned int i=0; i<s.size()-1; i++)
    {
        for(unsigned int j=0; j<5; j++)
        {
            if(u->isOperator(s.at(i)) && u->isOperator(s.at(i+1)))
            {
                if(s.at(i+1)!='-')
                {
                    if(s.at(i+1)=='+') break; //doesn't matter, its the unary + operator, so ignore
                    std::string temp = "Illegal operator at index ";
                    temp.append(std::to_string(i+1));
                    throw ULMPError(temp);
                }
            }
        }
    }
    /* *****************************************************************/
    // Test for mismatched brackets
    // This one is really simple, just loop through the string, count the number of opening and closing brackets, if they don't match, or ) comes before (, throw an error
    unsigned int opening=0, closing = 0, firstOpened = 0;
    bool opened=false;
    for(unsigned int i=0; i<s.size(); i++)
    {
        if(s.at(i)=='(')
        {
            opening++;
            if(opened==false)
            {
                opened=true;
                firstOpened=i;
            }
        }
        if(s.at(i)==')')
        {
            if(opening<=closing)
            {
                std::string temp = "Illegal Bracket at index ";
                temp.append(std::to_string(i));
                throw ULMPError(temp);
            }
            closing++;
        }
    }
    if(opening!=closing)
    {
        std::string temp = "Bracket at index " + std::to_string(firstOpened) + " doesn't have a matching closing parenthesis";
        throw ULMPError(std::string(temp));
    }
    /* *****************************************************************/
    /* Test for illegal use of decimal, e.g. 2./2 */
    for(unsigned int i=0; i<s.size(); i++)
    {
        if(s.at(i)=='.' && !u->isNumber(s.at(i+1)))
        {
            std::string temp="Illegal Decimal at index ";
            temp.append(std::to_string(i));
            throw ULMPError(temp);
        }
    }
}

void ULMP::preProcess()
{
    std::size_t constIndex=-1, endOfConstant;
    for(unsigned int i=0; i<constants->size(); i++)   //this part is about replacing constants
    {
        constIndex=s.find(constants->at(i),constIndex+1);
        if(constIndex!=std::string::npos)
        {
            endOfConstant=constIndex+constants->at(i).size() - 1;
            bool isConstInBeginning=constIndex==0;
            bool isConstInEnd=endOfConstant==s.length()-1;
            if((isConstInBeginning && isConstInEnd) || (isConstInBeginning && (u->isOperator(s.at(endOfConstant+1)) || s.at(endOfConstant+1)=='(' || s.at(endOfConstant+1)==')')) || (isConstInEnd && (u->isOperator(s.at(constIndex-1)) || s.at(constIndex-1)=='(' || s.at(constIndex-1)==')' )) || ((!isConstInEnd && !isConstInBeginning) && (u->isOperator(s.at(constIndex-1)) || s.at(constIndex-1)=='(' || s.at(constIndex+1)==')') && (u->isOperator(s.at(endOfConstant+1)) || s.at(endOfConstant+1)=='(' || s.at(endOfConstant+1)==')')) )
            {
                s.insert(constIndex, 1, '(');
                constIndex++;
                s.insert(constIndex+constants->at(i).size(),1,')'); //adding brackets around the constant
                std::string temp = std::to_string(constantsValues->at(i));
                s.replace(constIndex, constants->at(i).size(), temp);
                i--;
            }
            if(s.rfind(constants->at(i)) != constIndex) i--;
        }
    }
    for(unsigned int i=1; i<s.length()-1; i++)   //why do we care about the first element?
    {
        if(s.at(i)=='(' && (u->isNumber(s.at(i-1)) || s.at(i-1)==')' ))
        {
            s.insert(i,1,'*');
            i++;
            break;
        }
        if(s.at(i)==')' && (!u->isOperator(s.at(i+1)) && s.at(i+1)!=')') )
        {
            s.insert(i+1,1,'*');
            i++;
        }
        if(isALetter(s.at(i)) && u->isNumber(s.at(i-1)))
        {
            s.insert(i,1,'*');
        }
    }
}

bool ULMP::isALetter(char c)
{
    if( ((int) c >= 65 && (int) c <= 90) || ((int) c >= 97 && (int) c <= 122) ) // 65 = 'A' 90 = 'Z' 97 = 'a' 122 = 'z'
        return true;
    else
        return false;
}

void ULMP::defineConstant(std::string constantName, long double constantValue)
{
    for(unsigned int i=0; i<u->functionList->size(); i++)
    {
        if(constantName == u->functionList->at(i)) throw ULMPError("Constant name already taken.");
    }
    for(unsigned int i=0; i<constants->size(); i++)
    {
        if(constantName == constants->at(i)) throw ULMPError("Constant name already taken.");
    }
    for(unsigned int i=0; i<constantName.length(); i++)
    {
        if(!isALetter(constantName.at(i))) throw ULMPError("There cannot be special characters or numbers in the constant");
    }

    constants->push_back(constantName);
    constantsValues->push_back(constantValue);
}

long double ULMP::parseString(std::string expr)
{
    s=expr;
    removeWhiteSpace();
    checkForErrors();
    preProcess();
    double answer= u->parseString(s);
    return answer;
}

ULMP::~ULMP()
{
    delete u;
    delete constantsValues;
    delete constants;
}
