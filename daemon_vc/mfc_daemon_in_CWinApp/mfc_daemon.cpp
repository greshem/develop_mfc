#include <afxwin.h>
//定义一个CWinApp的派生类
class CMinApp:public CWinApp
{
	public:
 		virtual BOOL InitInstance();
};

//重载CWinApp成员函数InitInstance()
BOOL CMinApp::InitInstance()                     //应用程序初始化
{
	while(1)
	{
		system("ipconfig >> c:\test");
		Sleep(1000);
	}
	return TRUE;
};

CMinApp HelloApp;   
