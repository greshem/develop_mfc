#include<windows.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string>
//#include <wstring>
int main()
{
	char u[2];
	u[1]=':';
	for(char d='C';d<='Z';d++)//遍历C到Z
	{
		u[0]=d;
//		std::wstring strTest((char *)"C:\\");
        //这里传入的需要是 unicode 的字符串， 假如输入的是NULL ， 获取当前目录的root目录，  
		int ret= GetDriveType(NULL);
		if(ret ==DRIVE_REMOVABLE)//判断是不是可移动的盘
		{
			printf("%c is 读盘 \n", d);
        }                                                      
		else if ( ret== DRIVE_REMOTE)
		{
			printf("%c is 网络磁盘 \n", d);
		}
		else if( ret== DRIVE_CDROM)
		{
			printf("%c is 光驱 \n", d);
		}
		else if(ret== DRIVE_RAMDISK)
		{
			printf("%c is 内存盘 \n", d);
		}
		else if(ret== DRIVE_FIXED)
		{
            printf("%c is 硬盘\n", d); 
        }
        else
        {
         printf("%c 不存在\n", d); 
        }
                                                            
	}
	//getchar();
}
BOOL FindU(TCHAR *u)
{
	u[1]=':';
	for(char d='C';d<='Z';d++)//遍历C到Z
	{
		u[0]=d;
		if(GetDriveType(u)==DRIVE_REMOVABLE)//判断是不是可移动的盘
				return TRUE;
	}
	return FALSE;
} 
