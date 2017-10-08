#if !defined(AFX_SELECTFILE_H__F3459B98_F7A8_11D6_A3C1_444553540000__INCLUDED_)
#define AFX_SELECTFILE_H__F3459B98_F7A8_11D6_A3C1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectFile dialog

class CSelectFile : public CDialog
{
// Construction
public:
	DWORD m_dWSel;
	CSelectFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectFile)
	enum { IDD = IDD_SELECTFILE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectFile)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTFILE_H__F3459B98_F7A8_11D6_A3C1_444553540000__INCLUDED_)
