#include<windows.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string>
//#include <wstring>
int main()
{
	char u[2];
	u[1]=':';
	for(char d='C';d<='Z';d++)//����C��Z
	{
		u[0]=d;
//		std::wstring strTest((char *)"C:\\");
        //���ﴫ�����Ҫ�� unicode ���ַ����� �����������NULL �� ��ȡ��ǰĿ¼��rootĿ¼��  
		int ret= GetDriveType(NULL);
		if(ret ==DRIVE_REMOVABLE)//�ж��ǲ��ǿ��ƶ�����
		{
			printf("%c is ���� \n", d);
        }                                                      
		else if ( ret== DRIVE_REMOTE)
		{
			printf("%c is ������� \n", d);
		}
		else if( ret== DRIVE_CDROM)
		{
			printf("%c is ���� \n", d);
		}
		else if(ret== DRIVE_RAMDISK)
		{
			printf("%c is �ڴ��� \n", d);
		}
		else if(ret== DRIVE_FIXED)
		{
            printf("%c is Ӳ��\n", d); 
        }
        else
        {
         printf("%c ������\n", d); 
        }
                                                            
	}
	//getchar();
}
BOOL FindU(TCHAR *u)
{
	u[1]=':';
	for(char d='C';d<='Z';d++)//����C��Z
	{
		u[0]=d;
		if(GetDriveType(u)==DRIVE_REMOVABLE)//�ж��ǲ��ǿ��ƶ�����
				return TRUE;
	}
	return FALSE;
} 
