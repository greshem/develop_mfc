// makecab_mfc_gui.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "makecab_mfc_gui.h"
#include "makecab_mfc_guiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable: 4996)
#pragma comment(lib,"./CABINET.lib")


/////////////////////////////////////////////////////////////////////////////
// CMakecab_mfc_guiApp

BEGIN_MESSAGE_MAP(CMakecab_mfc_guiApp, CWinApp)
	//{{AFX_MSG_MAP(CMakecab_mfc_guiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakecab_mfc_guiApp construction

CMakecab_mfc_guiApp::CMakecab_mfc_guiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMakecab_mfc_guiApp object

CMakecab_mfc_guiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMakecab_mfc_guiApp initialization

BOOL CMakecab_mfc_guiApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMakecab_mfc_guiDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
