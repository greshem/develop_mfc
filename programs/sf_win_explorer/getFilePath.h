// getFilePath.h : main header file for the GETFILEPATH application
//

#if !defined(AFX_GETFILEPATH_H__17C76E5F_0EF9_4AE6_82FF_9144FE2AC491__INCLUDED_)
#define AFX_GETFILEPATH_H__17C76E5F_0EF9_4AE6_82FF_9144FE2AC491__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetFilePathApp:
// See getFilePath.cpp for the implementation of this class
//

class CGetFilePathApp : public CWinApp
{
public:
	CGetFilePathApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetFilePathApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetFilePathApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETFILEPATH_H__17C76E5F_0EF9_4AE6_82FF_9144FE2AC491__INCLUDED_)
