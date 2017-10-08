// L2DCDSet.h : main header file for the L2DCDSET application
//

#if !defined(AFX_L2DCDSET_H__BFBDA607_47C2_4779_B117_FF3857350EA2__INCLUDED_)
#define AFX_L2DCDSET_H__BFBDA607_47C2_4779_B117_FF3857350EA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CL2DCDSetApp:
// See L2DCDSet.cpp for the implementation of this class
//

class CL2DCDSetApp : public CWinApp
{
public:
	CL2DCDSetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CL2DCDSetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CL2DCDSetApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_L2DCDSET_H__BFBDA607_47C2_4779_B117_FF3857350EA2__INCLUDED_)
