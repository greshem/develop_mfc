#include <stdlib.h>
#include <iostream>
#include <string> 
#include <fstream>
#include <iterator>  
#include <vector> 
#include <iostream> 

#ifndef WINDOWSCODE
#include <unistd.h>
#endif


//2011_09_26 by greshem. 

using namespace std;

string   my_string();
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s file_list \n", argv[0]);
	}
	printf("%s\n", "string_not_return.cpp");


	string  str= my_string();
	string b=str;
	
	return 0;
}

string   my_string()
{
    if(1==1)
    {
    }
    else
    {
        return "this is a string";    
    }
}
