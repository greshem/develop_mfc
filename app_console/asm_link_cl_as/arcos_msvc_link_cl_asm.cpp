
//#2012_02_28_12:02:30 add by greshem
//come from /usr/include/OGRE/asm_math.h,   only compile in msvc compiler.
#include <fstream>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  


float asm_arccos( float r ) 
{

    float asm_one = 1.f;
    float asm_half_pi = (3.14159/2);
    __asm {
        fld r // r0 = r
        fld r // r1 = r0, r0 = r
        fmul r // r0 = r0 * r
        fsubr asm_one // r0 = r0 - 1.f
        fsqrt // r0 = sqrtf( r0 )
        fchs // r0 = - r0
        fdiv // r0 = r1 / r0
        fld1 // {{ r0 = atan( r0 )
        fpatan // }}
        fadd asm_half_pi // r0 = r0 + pi / 2
    } // returns r0
}

using namespace std;
int main(int argc, char *argv[])
{
	printf("%f", asm_arccos(333));
	return 0;
}
