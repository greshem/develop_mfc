// RichTech_.h : main header file for the TEST application
//

#if !defined(AFX_TEST_H__344E8804_1438_4A8E_9DC2_B7E260C7A48F__INCLUDED_)
#define AFX_TEST_H__344E8804_1438_4A8E_9DC2_B7E260C7A48F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRichTech_App:
// See RichTech_.cpp for the implementation of this class
//

class CRichTech_App : public CWinApp
{
public:
	CRichTech_App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRichTech_App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRichTech_App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_H__344E8804_1438_4A8E_9DC2_B7E260C7A48F__INCLUDED_)
