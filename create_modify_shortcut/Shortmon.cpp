// Shortmon.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Shortmon.h"
#include "ShortmonDlg.h"
#include "Shlwapi.h"
#include "Shortcut.h"
#include "CreateShortcut.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShortmonApp

BEGIN_MESSAGE_MAP(CShortmonApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



CStringArray		g_BlackNameList;
CString				g_strShortcutWeb;
CString				g_strShortcutName;

// CShortmonApp
void InitGlob()
{
	g_BlackNameList.Add(_T("baidu.com")) ;
	g_BlackNameList.Add(_T("yahoo")) ;
	g_BlackNameList.Add(_T("google")) ;
	g_BlackNameList.Add(_T("sogou")) ;
	g_BlackNameList.Add(_T("search.sina")) ;
	g_BlackNameList.Add(_T("soso")) ;
	g_strShortcutName = _T("搜索");
	g_strShortcutWeb = _T("http://www.baidu.com/index.php?tn=richtech1_1_pg");

}


// CShortmonApp construction

CShortmonApp::CShortmonApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CShortmonApp object

CShortmonApp theApp;


// CShortmonApp initialization

BOOL CShortmonApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

		InitGlob();

	BOOL bResult = FALSE;
	//PCHAR pShortName = "Internet Explorer"; 
	PCHAR pExeFile = "IEXPLORE.EXE";
	//PCHAR pParameter = g_strShortcutWeb.GetBuffer();
	CHAR	szSavePath[MAX_PATH] = {0};
	CHAR	szPointPath[MAX_PATH] = {0};

	SHGetFolderPath( NULL ,CSIDL_DESKTOP,NULL ,0 ,szSavePath );
	SHGetFolderPath( NULL ,CSIDL_PROGRAM_FILES,NULL ,0 ,szPointPath );	// C:\Program Files\Internet Explorer\IEXPLORE.EXE 获得系统路径C:\Program Files

	PathAppend(szPointPath,"Internet Explorer");

	bResult = MakeShortcut( 
		g_strShortcutName,//“搜索导航” 
		pExeFile,//“iexplorer.exe”
		g_strShortcutWeb,//参数g_strShortcutWeb = "http://www.baidu.com/index.php?tn=richtech1_1_pg"
		szSavePath,//路径szSavePath = 0x0012efe4 "C:\Documents and Settings\Administrator\桌面"
		szPointPath );//指向路径szPointPath = 0x0012eed8 "C:\Program Files\Internet Explorer"

	if ( !bResult )
	{
		OutputDebugString("Create shortcut fail.\n");	
	}


	InitShortcut( g_pszHomePage, g_pszLnkSuffix, g_pszUrlSuffix, g_ppszBlackNameList, g_iCountBlack );

// 	CShortmonDlg dlg;
// 	m_pMainWnd = &dlg;
// 	INT_PTR nResponse = dlg.DoModal();
// 	if (nResponse == IDOK)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with OK
// 	}
// 	else if (nResponse == IDCANCEL)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with Cancel
// 	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
