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
#include <string>
#include <ctime>
int main(int argc, char **argv) {
    std::string expr="2/3+2";
    double a;
    /* This is a benchmark */
    clock_t start= clock();
    for(int i=0; i<100000; i++) { 
        ULMPParse("sin(cosh(sin(cos(sin(cos(20) * sinh(20))*cos(20))*tan(20))*acos(1.5234)))"); //using the C-API, which is yet to be polished
    }
    clock_t endTime= clock();
    //This test gives me approx. 30 seconds on my Core 2 Duo E4300 running Linux Mint 15
    std::cout << "Time taken for parse = " <<(double) (endTime - start)/CLOCKS_PER_SEC << std::endl;
    
    return 0;
}

