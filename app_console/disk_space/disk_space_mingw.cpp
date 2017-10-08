
#include <windows.h>
#include <stdio.h>
#include <stdlib.h> 
//查看函数为GetDiskFreeSpaceEx():

//OK,基本上代码如下:

 
int main()
{
ULARGE_INTEGER uliUserFree,uliTotal,uliRealFree;
   
//        UpdateData(TRUE);

  GetDiskFreeSpaceEx("c:\\",&uliUserFree,&uliTotal,&uliRealFree);
  printf("c:\\ %0.2fGB      %0.2fGB     %0.2fGB \n",(double)(LONGLONG)uliTotal.QuadPart/(1024*1024*1024),
                                             (double)(LONGLONG)uliUserFree.QuadPart/(1024*1024*1024),
               (double)(LONGLONG)uliRealFree.QuadPart/(1024*1024*1024));
  
  
  GetDiskFreeSpaceEx("d:\\",&uliUserFree,&uliTotal,&uliRealFree);
  printf("d:\\ %0.2fGB    %0.2fGB    %0.2fGB\n",(double)(LONGLONG)uliTotal.QuadPart/(1024*1024*1024),
                                             (double)(LONGLONG)uliUserFree.QuadPart/(1024*1024*1024),
               (double)(LONGLONG)uliRealFree.QuadPart/(1024*1024*1024));
    
  GetDiskFreeSpaceEx("e:\\",&uliUserFree,&uliTotal,&uliRealFree);
   printf("e:\\ %0.2fGB    %0.2fGB    %0.2fGB\n",(double)(LONGLONG)uliTotal.QuadPart/(1024*1024*1024),
                                             (double)(LONGLONG)uliUserFree.QuadPart/(1024*1024*1024),
               (double)(LONGLONG)uliRealFree.QuadPart/(1024*1024*1024));
  
  GetDiskFreeSpaceEx("f:\\",&uliUserFree,&uliTotal,&uliRealFree);
  printf("f:\\ %0.2fGB    %0.2fGB    %0.2fGB\n",(double)(LONGLONG)uliTotal.QuadPart/(1024*1024*1024),
                                             (double)(LONGLONG)uliUserFree.QuadPart/(1024*1024*1024),
               (double)(LONGLONG)uliRealFree.QuadPart/(1024*1024*1024));
  
  GetDiskFreeSpaceEx("g:\\",&uliUserFree,&uliTotal,&uliRealFree);
   printf("g:\\ %0.2fGB    %0.2fGB    %0.2fGB\n",(double)(LONGLONG)uliTotal.QuadPart/(1024*1024*1024),
                                             (double)(LONGLONG)uliUserFree.QuadPart/(1024*1024*1024),
               (double)(LONGLONG)uliRealFree.QuadPart/(1024*1024*1024));
  
  GetDiskFreeSpaceEx("h:\\",&uliUserFree,&uliTotal,&uliRealFree);
   printf("h:\\ %0.2fGB    %0.2fGB    %0.2fGB\n",(double)(LONGLONG)uliTotal.QuadPart/(1024*1024*1024),
                                             (double)(LONGLONG)uliUserFree.QuadPart/(1024*1024*1024),
               (double)(LONGLONG)uliRealFree.QuadPart/(1024*1024*1024));
  
  GetDiskFreeSpaceEx("i:\\",&uliUserFree,&uliTotal,&uliRealFree);
 printf("i:\\ %0.2fGB    %0.2fGB    %0.2fGB\n",(double)(LONGLONG)uliTotal.QuadPart/(1024*1024*1024),
                                             (double)(LONGLONG)uliUserFree.QuadPart/(1024*1024*1024),
               (double)(LONGLONG)uliRealFree.QuadPart/(1024*1024*1024));

//外加DDX变量.

//就这样,将剩余空间精确到小数点后2位,比WindowsXP还精确,其实完全可以自己控制.

//外加DDX变量.

//就这样,将剩余空间精确到小数点后2位,比WindowsXP还精确,其实完全可以自己控制.
}
