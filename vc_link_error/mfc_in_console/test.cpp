
#include<afxwin.h>
#include <string>
#include <vector>
#include <Iphlpapi.h>
#include <winsock2.h>
#include <windows.h> 

typedef DWORD(CALLBACK * USERID)();//GetUserID

int logger(CString logstr)
{
	CStdioFile file;
	file.Open("all.log", CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	
	//写入文件
	CString str;
	//str.Format("%s\r\n","hello!I am talkingmute!");
	file.Seek(0,CFile::end);
	file.WriteString( logstr ); 
	file.Close();
	return 1;
}

int main()
{
	
    USERID get_user_id;
	HINSTANCE hInst;//实例句柄
	hInst=LoadLibrary("dklib.dll");
	if(!hInst)
	{
		logger("加载库dklib.dll失败\n");
		return -1;
	}

	//获取函数地址 
	get_user_id =(USERID)GetProcAddress(hInst,"DK_GetUserId");
	int ret = get_user_id();
	CString logstr;
	logstr.Format("获取用户id是: %d\n", ret);
	logger(logstr);
    printf("user_id = %d\n",ret);  
	

    return  0;
}
