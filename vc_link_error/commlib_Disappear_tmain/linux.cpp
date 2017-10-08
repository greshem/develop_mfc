// ggg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <commLib/CommLib.h> 




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
//int main(int argc, TCHAR* argv[], TCHAR* envp[])
//int tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello= "hello world\n";
		CGlobalFunc global;
        int count= global.GetMonitorCount();
		//strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;
	}

    while(1)
    {
        Sleep(1000);
        OutputDebugString("mfc_in_main_console \\n");

    }
	return nRetCode;
}


