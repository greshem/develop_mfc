#include <afxwin.h>
//����һ��CWinApp��������
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
		system("ipconfig >> c:\test");
		Sleep(1000);
	}
	return TRUE;
};

CMinApp HelloApp;   
