// CDImage_GUI.h : main header file for the CDIMAGE_GUI application
//

#if !defined(AFX_CDIMAGE_GUI_H__078273B3_53E7_423A_BB59_0EA9D768B3F2__INCLUDED_)
#define AFX_CDIMAGE_GUI_H__078273B3_53E7_423A_BB59_0EA9D768B3F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCDImage_GUIApp:
// See CDImage_GUI.cpp for the implementation of this class
//

class CCDImage_GUIApp : public CWinApp
{
public:
	CCDImage_GUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDImage_GUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCDImage_GUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDIMAGE_GUI_H__078273B3_53E7_423A_BB59_0EA9D768B3F2__INCLUDED_)
