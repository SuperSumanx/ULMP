/* ULMP
 * Ultra Light Math Parser
 * Developed By Sumanth in 2013
 **/
/* This is an example program written to demonstrate the ULMP class
 * which handles all the mathematical expresssions
 */

#include "ulmp.hpp"
#include "Array.hpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    ULMP u;
    cout.precision(15);

    u.setString("((245 6+ 2 *23  45 . 234)/5 324 6*3 56+ 32*(235 65+3 54.2 15)+---654 560 54.28 6+2^2 .5)");
    cout << "The string was " <<" ( (2456+2*2345.234)/53246*356+32*(23565+354.215)+---65456054.286+2^2.5) "<< endl;
    cout << "The answer is " << u.parseString() << endl;
    return 0;
}

