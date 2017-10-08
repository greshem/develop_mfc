
#2011_10_21   星期五   add by greshem
1. mfc 的 
int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
函数有问题, 
	CWinThread* pThread = AfxGetThread();
	CWinApp* pApp = AfxGetApp();

	并不判断指针知否为空, 最后 直接调用 

	if (!pThread->InitInstance())
	导致越界访问.
