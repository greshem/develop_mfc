
#2011_10_21   ������   add by greshem
1. mfc �� 
int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
����������, 
	CWinThread* pThread = AfxGetThread();
	CWinApp* pApp = AfxGetApp();

	�����ж�ָ��֪��Ϊ��, ��� ֱ�ӵ��� 

	if (!pThread->InitInstance())
	����Խ�����.
