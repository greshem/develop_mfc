#include <afxwin.h>
//定义一个CWinApp的派生类
extern int logger(CString logstr);
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
		CString logstr;
		logstr.Format("这是日志\n");
		logger(logstr);	
		Sleep(1000);
	}
	return TRUE;
};

CMinApp HelloApp;   
