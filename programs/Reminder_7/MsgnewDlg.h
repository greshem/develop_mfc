#if !defined(AFX_MSGNEWDLG_H__38233D3E_FC73_4196_87DB_32082D71BF34__INCLUDED_)
#define AFX_MSGNEWDLG_H__38233D3E_FC73_4196_87DB_32082D71BF34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgnewDlg.h : header file
//
//#include "WinXPButtonST.h"

/////////////////////////////////////////////////////////////////////////////
// CMsgnewDlg dialog

class CMsgnewDlg : public CDialog
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
	CMsgnewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgnewDlg)
	enum { IDD = IDD_DIALOG_MSGNEW };
	CListBox	m_listbox;
	CDateTimeCtrl	m_cDate;
	COleDateTime	m_dDate;
	COleDateTime	m_tTime;
	CString	m_sMsg;
	BOOL	m_bcheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgnewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMsgnewDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCheckdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGNEWDLG_H__38233D3E_FC73_4196_87DB_32082D71BF34__INCLUDED_)
