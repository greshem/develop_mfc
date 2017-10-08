#include <stdlib.h>
#include <iostream>
#include <string> 
#include <fstream>
#include <iterator>  
#include <vector> 
#include <iostream> 
#include <commLib/CommLib.h> 
using namespace std;
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s file_list \n", argv[0]);
		//exit(-1);
	}
	printf("%s\n", "linux2.cpp");

  	CString tmp=CGlobalFunc::GetAppExe();

	string  str("linux2.cpp");
	cout<<str.c_str()<<endl;
	return 0;
}
