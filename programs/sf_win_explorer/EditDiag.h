#if !defined(AFX_EDITDIAG_H__783007CC_3E40_4602_BAFC_38182D62FF14__INCLUDED_)
#define AFX_EDITDIAG_H__783007CC_3E40_4602_BAFC_38182D62FF14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDiag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditDiag dialog

class EditDiag : public CDialog
{
// Construction
public:

	EditDiag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EditDiag)
	enum { IDD = IDD_DIALOG1 };
	CString	m_strCata;
	CString	m_strNumber;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditDiag)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDIAG_H__783007CC_3E40_4602_BAFC_38182D62FF14__INCLUDED_)
