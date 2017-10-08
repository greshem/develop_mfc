#include <string>
#include <afxwin.h>
#include <windows.h> 
#include <iostream>

//using namespace std;
typedef DWORD(CALLBACK * USERID)();//GetUserID

int logger(CString logstr)
{
	CStdioFile file;
	file.Open("all.log", CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	
	//写入文件
	CString str;
	file.Seek(0,CFile::end);
	file.WriteString( logstr ); 
	file.Close();
	return 1;
}

int main()
{
    USERID get_user_id;
	HINSTANCE hInst;//实例句柄
	CString dll_name;
	for(int i= 1; i<5000; i++)
	{
		dll_name.Format("%d.dll",i);
		hInst=LoadLibrary(dll_name);
		if(!hInst)
		{
			//logger("加载库dklib.dll失败\n");
//			cout<<"加载库"<<dll_name<<"失败"<<endl;
			printf("加载库%s失败\n",dll_name.GetBuffer(0));

			int err = GetLastError();
			printf("Error= %d",err);
			Sleep(1000000);
			//return -1;
		}
		else
		{
			printf("加载库%s成功\n",dll_name.GetBuffer(0));
		}
	}

			Sleep(1000000);
/*
	//获取函数地址 
	get_user_id =(USERID)GetProcAddress(hInst,"DK_GetUserId");
	if(get_user_id == NULL)
	{
		logger("获取get_user_id地址失败\n");
	}
	int ret = get_user_id();
	CString logstr;
	logstr.Format("获取用户id是: %d\n", ret);
	logger(logstr);
    printf("user_id = %d\n",ret);  
*/
    return  0;
}
