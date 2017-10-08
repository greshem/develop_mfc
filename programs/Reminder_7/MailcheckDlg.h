#if !defined(AFX_MAILCHECKDLG_H__B6DAA81F_2863_430B_B327_15688E0DB907__INCLUDED_)
#define AFX_MAILCHECKDLG_H__B6DAA81F_2863_430B_B327_15688E0DB907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailcheckDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMailcheckDlg dialog

class CMailcheckDlg : public CDialog
{
protected:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	int m_nCount;			//设置的邮件总数
	int m_nCurrent;

// Construction
public:
	CMailcheckDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMailcheckDlg)
	enum { IDD = IDD_DIALOG_MAILCHECK };
	CListCtrl	m_list;
	BOOL	m_bCkmail;
	int		m_nCheckmail;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailcheckDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMailcheckDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCkmail();
	afx_msg void OnKillfocusEdtinterval();
	afx_msg void OnBtnappend();
	afx_msg void OnBtnchange();
	afx_msg void OnBtndelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILCHECKDLG_H__B6DAA81F_2863_430B_B327_15688E0DB907__INCLUDED_)
