// DiskClean.h : main header file for the DISKCLEAN application
//

#if !defined(AFX_DISKCLEAN_H__2AE5DB84_71B3_11D6_A3C0_0050BA075140__INCLUDED_)
#define AFX_DISKCLEAN_H__2AE5DB84_71B3_11D6_A3C0_0050BA075140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDiskCleanApp:
// See DiskClean.cpp for the implementation of this class
//

class CDiskCleanApp : public CWinApp
{
public:
	CDiskCleanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiskCleanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDiskCleanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISKCLEAN_H__2AE5DB84_71B3_11D6_A3C0_0050BA075140__INCLUDED_)
