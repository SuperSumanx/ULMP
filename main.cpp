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

