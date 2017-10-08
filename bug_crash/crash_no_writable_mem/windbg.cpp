//#include "stdafx.h" 
#include <windows.h>
#include <stdlib.h> 
#include <stdio.h>
 
char* getcharBuffer() 
{ 
  return "6969,3p3p"; 
} 
 
void changeto4p(char * buffer) 
{ 
  while(*buffer) 
  { 
    if(*buffer == '3') 
      *buffer='4'; 
    buffer++; 
  }   
} 
//int _tmain(int argc, char * argv[]) 
int main(int argc, char * argv[]) 
{ 
  printf("%s\n","Any key continue..."); 
  //getchar(); 
  char *str=getcharBuffer(); 
  changeto4p(str); 
  printf("%s",str); 
  return 0; 
} 
