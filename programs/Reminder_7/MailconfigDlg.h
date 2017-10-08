#if !defined(AFX_MAILCONFIGDLG_H__13483E09_A87E_4227_A454_4FCC66F260AD__INCLUDED_)
#define AFX_MAILCONFIGDLG_H__13483E09_A87E_4227_A454_4FCC66F260AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailconfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMailconfigDlg dialog

class CMailconfigDlg : public CDialog
{
protected:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;

// Construction
public:
	CMailconfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMailconfigDlg)
	enum { IDD = IDD_DIALOG_MAILCONFIG };
	CString	m_sHost;
	CString	m_sMail;
	CString	m_sPass;
	CString	m_sUser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailconfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMailconfigDlg)
	afx_msg void OnChangeEdtmail();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILCONFIGDLG_H__13483E09_A87E_4227_A454_4FCC66F260AD__INCLUDED_)
