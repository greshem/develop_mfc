
#include <windows.h>
#include <stdio.h>
#include <stdlib.h> 
//�鿴����ΪGetDiskFreeSpaceEx():

//OK,�����ϴ�������:

 
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

//���DDX����.

//������,��ʣ��ռ侫ȷ��С�����2λ,��WindowsXP����ȷ,��ʵ��ȫ�����Լ�����.

//���DDX����.

//������,��ʣ��ռ侫ȷ��С�����2λ,��WindowsXP����ȷ,��ʵ��ȫ�����Լ�����.
}
