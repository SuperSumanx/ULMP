#include "ulmp.h"

ULMP::ULMP()
{
    operatorList[0]='+';
    operatorList[1]='-';
    operatorList[2]='*';
    operatorList[3]='/';
}

ULMP::ULMP(std::string expression)
{
    operatorList[0]='+';
    operatorList[1]='-';
    operatorList[2]='*';
    operatorList[3]='/';
    s=expression;
}

void ULMP::setString(const char* expression){
    s=expression;
}

int ULMP::charToInt(char c){
    switch(c){
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

double ULMP::stringToDouble(std::string &s) {
    unsigned int divisorForDecimal=1;
    unsigned short c;
    double answer=0.0;
    int negate=1;

    for(unsigned int i=0; i<s.length(); i++) {
        if(s.at(i)=='.') {
            s.erase(i,1);
            divisorForDecimal=pow10(s.length()-i);
            break;
        }
    }

    for(int i=0; i<s.length(); i++) {
        if(s.at(i)=='-') {
            s.erase(i,1);
            negate*=-1;
            i=-1;
        }
    }

    for(unsigned int i=0; i<s.length(); i++){
        c=charToInt(s.at(i));
        answer=answer+(c*pow10(s.length()-i-1));
    }
    return (answer*negate)/divisorForDecimal;
}

bool ULMP::isOperator(char c)  {
    for(unsigned int i=0; i<sizeof(operatorList) ; i++) {
        if(c==operatorList[i])
            return true;
    }
    return false;
}

bool ULMP::doesSucceedOperator(std::string &s, int index) const {
    for(unsigned int i=0; i<sizeof(operatorList); i++ ) {
        if(s.at(index-1)==operatorList[i]) { //if previous element of string is a character return true
            return true;
        }
    }
    return false; // else false

}

void ULMP::removeWhiteSpace(std::string &s) {
    for(unsigned int i=0; i<s.length(); i++) {
        if(s.at(i)==' ') {
            s.erase(i,1);
            i=-1;
            continue;
        }
    }
}

void ULMP::populateOperators(std::string &s) {
    operatorLocations->push_back(-1);
    for(unsigned int i=0; i<s.length(); i++) {
        if( isOperator( s.at(i) ) && !doesSucceedOperator(s, i) ) { //if s at i is an operator and it does not succeed any other operator
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
void ULMP::populateNumbers(std::string &s) {
    std::string num;
    for(int i=0; i<operatorLocations->size()-1; i++) {
        num=s.substr(operatorLocations->at(i)+1, operatorLocations->at(i+1) - (operatorLocations->at(i)+1) ) ;
        numbers->push_back( stringToDouble(num) );
    }
}

double ULMP::parseString(){
    removeWhiteSpace(s);

    operatorLocations=new Array<short>();
    operators=new Array<char>();

    populateOperators(s);
    numbers=new Array<double>();
    populateNumbers(s);
    delete operatorLocations;
    double answer = evaluateExpression();
    delete operators;
    delete numbers;
    return answer;
}

double ULMP::parseString(std::string expression) {
    s=expression;
    removeWhiteSpace(s);

    operatorLocations=new Array<short>();
    operators=new Array<char>();

    populateOperators(s);
    numbers=new Array<double>();
    populateNumbers(s);
    delete operatorLocations;
    double answer = evaluateExpression();
    delete operators;
    delete numbers;
    return answer;
}

double ULMP::parseString(char* expression) {
    s=expression;
    removeWhiteSpace(s);

    operatorLocations=new Array<short>();
    operators=new Array<char>();

    populateOperators(s);
    numbers=new Array<double>();
    populateNumbers(s);
    delete operatorLocations;
    double answer = evaluateExpression();
    delete operators;
    delete numbers;
    return answer;
}

double ULMP::evaluateExpression(){
    double temp=0;
    for(int i=0; i<operators->size(); i++){
        if(operators->at(i) == '/'){
            temp=numbers->at(i)/numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }     
    }
    for(int i=0; i<operators->size(); i++){
        if(operators->at(i) == '*'){
            temp=numbers->at(i)*numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }
    }
    for(int i=0; i<operators->size(); i++){
        if(operators->at(i) == '+'){
            temp=numbers->at(i)+numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }
    }
    for(int i=0; i<operators->size(); i++){
        if(operators->at(i) == '-'){
            temp=numbers->at(i)-numbers->at(i+1);
            numbers->at(i)=temp;
            numbers->erase(i+1);
            operators->erase(i);
            i=-1;
        }
    }
    return numbers->at(0);
}
