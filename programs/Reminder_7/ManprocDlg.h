#if !defined(AFX_MANPROCDLG_H__0F9ACD45_4809_43CD_BA03_E42CB7B8FA6A__INCLUDED_)
#define AFX_MANPROCDLG_H__0F9ACD45_4809_43CD_BA03_E42CB7B8FA6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManprocDlg.h : header file
//
#include <tlhelp32.h>
#include "./library/SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CManprocDlg dialog

class CManprocDlg : public CDialog
{
protected:
	//CManprocSheet* m_pManprocSheet;			/*属性页*/
	//CWnd* pwndPropSheetHolder;				/*存放propertysheet的地方*/
	int m_nCurrent;							/*当前行*/
	PROCESSENTRY32* info;
	char m_sID[8], m_sName[32];					/*当前选中行的process ID，名称*/

	CWinXPButtonST m_btnRefresh;
	CWinXPButtonST m_btnKillproc;
	CWinXPButtonST m_btnCancel;

// Construction
public:
	CManprocDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CManprocDlg)
	enum { IDD = IDD_DIALOG_MANAGE_PROCESS };
	CSortListCtrl	m_listthread;
	CTabCtrl	m_tabCtrl;
	CSortListCtrl	m_listmodule;
	CSortListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManprocDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ShowThreads(DWORD processID);
	void ShowProcessList();
	int GetProcessCount();
	void ShowModules(DWORD processID);
	int GetProcessPath(DWORD idProcess, char *spath);

	// Generated message map functions
	//{{AFX_MSG(CManprocDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedProcesslist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRefresh();
	afx_msg void OnKillproc();
	afx_msg void OnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANPROCDLG_H__0F9ACD45_4809_43CD_BA03_E42CB7B8FA6A__INCLUDED_)
