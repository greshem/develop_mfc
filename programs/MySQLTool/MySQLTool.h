// MySQLTool.h : main header file for the MYSQLTOOL application
//

#if !defined(AFX_MYSQLTOOL_H__FBBCDB92_1468_4D43_A9E6_ACFB5E5D9613__INCLUDED_)
#define AFX_MYSQLTOOL_H__FBBCDB92_1468_4D43_A9E6_ACFB5E5D9613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMySQLToolApp:
// See MySQLTool.cpp for the implementation of this class
//

class CMySQLToolApp : public CWinApp
{
public:
	CMySQLToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySQLToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMySQLToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSQLTOOL_H__FBBCDB92_1468_4D43_A9E6_ACFB5E5D9613__INCLUDED_)
