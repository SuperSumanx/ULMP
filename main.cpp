/* ULMP
 * Ultra Light Math Parser
 * Developed By Sumanth in 2013
 **/
/* This is an example program written to demonstrate the ULMP class
 * which handles all the mathematical expresssions
 */

#include "ulmp.h"
#include "Array.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define CLOCKS_PER_MILLISECOND CLOCKS_PER_SEC/1000

using namespace std;


int main()
{
    ULMP u;
    cout.precision(15);
    u.setString("2345.234/53246*356 +354.215+---65456054.286");
    cout << "The answer is " << u.parseString() << endl;
    return 0;
}

