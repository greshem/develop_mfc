// makecab_mfc_gui.h : main header file for the MAKECAB_MFC_GUI application
//

#if !defined(AFX_MAKECAB_MFC_GUI_H__C5E0BF9F_630A_4953_801B_762C23582192__INCLUDED_)
#define AFX_MAKECAB_MFC_GUI_H__C5E0BF9F_630A_4953_801B_762C23582192__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMakecab_mfc_guiApp:
// See makecab_mfc_gui.cpp for the implementation of this class
//

class CMakecab_mfc_guiApp : public CWinApp
{
public:
	CMakecab_mfc_guiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakecab_mfc_guiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMakecab_mfc_guiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKECAB_MFC_GUI_H__C5E0BF9F_630A_4953_801B_762C23582192__INCLUDED_)
