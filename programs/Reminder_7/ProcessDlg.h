#if !defined(AFX_PROCESSDLG_H__033362CD_D7ED_47DB_AD22_1F1086A6A969__INCLUDED_)
#define AFX_PROCESSDLG_H__033362CD_D7ED_47DB_AD22_1F1086A6A969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessDlg.h : header file
//
#include <tlhelp32.h>
#include "./library/SortListCtrl.h"
//#include "WinXPButtonST.h"

#define WM_SHOWPROCESS WM_USER+5
/////////////////////////////////////////////////////////////////////////////
// CProcessDlg dialog

class CProcessDlg : public CDialog
{
public:
	char m_sCaption[32];		//显示标题
	int m_nCurrent;			//当前行
	char m_sName[32], m_sID[8];	//线程名称、ID

protected:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	CWinXPButtonST m_btnRefresh;

private:
	PROCESSENTRY32* info;

// Construction
public:
	CProcessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProcessDlg)
	enum { IDD = IDD_DIALOG_PROCESS };
	CSortListCtrl	m_list;
	COleDateTime	m_dDate;
	COleDateTime	m_dTime;
	CString	m_sCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProcessDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnCancel();
	afx_msg void OnRefresh();
	//}}AFX_MSG
	afx_msg LRESULT OnShowprocess(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSDLG_H__033362CD_D7ED_47DB_AD22_1F1086A6A969__INCLUDED_)
