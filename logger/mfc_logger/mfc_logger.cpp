#include <afxwin.h>
//����һ��CWinApp��������
extern int logger(CString logstr);
class CMinApp:public CWinApp
{
	public:
 		virtual BOOL InitInstance();
};

//����CWinApp��Ա����InitInstance()
BOOL CMinApp::InitInstance()                     //Ӧ�ó����ʼ��
{
	while(1)
	{
		CString logstr;
		logstr.Format("������־\n");
		logger(logstr);	
		Sleep(1000);
	}
	return TRUE;
};

CMinApp HelloApp;   
