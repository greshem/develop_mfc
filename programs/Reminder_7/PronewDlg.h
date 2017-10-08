#if !defined(AFX_PRONEWDLG_H__8DA93902_8836_4085_A7E6_A1FDDDE4167B__INCLUDED_)
#define AFX_PRONEWDLG_H__8DA93902_8836_4085_A7E6_A1FDDDE4167B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PronewDlg.h : header file
//
//#include "WinXPButtonST.h"

/////////////////////////////////////////////////////////////////////////////
// CPronewDlg dialog

class CPronewDlg : public CDialog
{
public:
	char m_sCaption[32];
	int m_nCaption;
	char m_sCheckday[20];	//选择需要提醒的日期
	int m_nKind;			//选择每日提醒还是只提醒一次
	int array[7];			//选中的日期	

protected:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;

// Construction
public:
	CPronewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPronewDlg)
	enum { IDD = IDD_DIALOG_PRONEW };
	CListBox	m_listbox;
	CDateTimeCtrl	m_cDate;
	COleDateTime	m_tTime;
	COleDateTime	m_dDate;
	CString	m_sName;
	CString	m_sPath;
	BOOL	m_bcheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPronewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPronewDlg)
	afx_msg void OnBtngetpath();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCheckdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRONEWDLG_H__8DA93902_8836_4085_A7E6_A1FDDDE4167B__INCLUDED_)
