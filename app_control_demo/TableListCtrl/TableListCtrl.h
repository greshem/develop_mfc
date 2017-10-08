// TableListCtrl.h : main header file for the TABLELISTCTRL application
//

#if !defined(AFX_TABLELISTCTRL_H__6523BF12_A5D8_4C68_B755_F2F107937584__INCLUDED_)
#define AFX_TABLELISTCTRL_H__6523BF12_A5D8_4C68_B755_F2F107937584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlApp:
// See TableListCtrl.cpp for the implementation of this class
//

class CTableListCtrlApp : public CWinApp
{
public:
	CTableListCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableListCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTableListCtrlApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLELISTCTRL_H__6523BF12_A5D8_4C68_B755_F2F107937584__INCLUDED_)
