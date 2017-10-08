// Remind.h : main header file for the REMIND application
//

#if !defined(AFX_REMIND_H__9713670B_A3C6_4481_8406_8F4A6DB9920A__INCLUDED_)
#define AFX_REMIND_H__9713670B_A3C6_4481_8406_8F4A6DB9920A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "public.h"

/////////////////////////////////////////////////////////////////////////////
// CRemindApp:
// See Remind.cpp for the implementation of this class
//

class CRemindApp : public CWinApp
{
public:
	CRemindApp();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemindApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRemindApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMIND_H__9713670B_A3C6_4481_8406_8F4A6DB9920A__INCLUDED_)
