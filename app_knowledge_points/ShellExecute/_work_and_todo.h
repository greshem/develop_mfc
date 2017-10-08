// _work_and_todo.h : main header file for the _WORK_AND_TODO application
//

#if !defined(AFX__WORK_AND_TODO_H__61C06501_91CC_4733_8F1A_3D9CBFBC5269__INCLUDED_)
#define AFX__WORK_AND_TODO_H__61C06501_91CC_4733_8F1A_3D9CBFBC5269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// C_work_and_todoApp:
// See _work_and_todo.cpp for the implementation of this class
//

class C_work_and_todoApp : public CWinApp
{
public:
	C_work_and_todoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C_work_and_todoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(C_work_and_todoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__WORK_AND_TODO_H__61C06501_91CC_4733_8F1A_3D9CBFBC5269__INCLUDED_)
