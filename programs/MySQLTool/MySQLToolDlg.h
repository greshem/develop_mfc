// MySQLToolDlg.h : header file
//

#if !defined(AFX_MYSQLTOOLDLG_H__DFC76CFD_87AA_4B56_B4EB_12DEEA74C9D5__INCLUDED_)
#define AFX_MYSQLTOOLDLG_H__DFC76CFD_87AA_4B56_B4EB_12DEEA74C9D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMySQLToolDlg dialog
#include <mysql.h>

struct tagRunInfo
{
	int nQueryCount;
	int nSuccessCount;
	int nOpRecCount;
	int nSpendTime;
	int nMinTime;
	int nMaxTime;
};

class CMySQLToolDlg : public CDialog
{
// Construction
public:
	CMySQLToolDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMySQLToolDlg();
// Dialog Data
	//{{AFX_DATA(CMySQLToolDlg)
	enum { IDD = IDD_MYSQLTOOL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySQLToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMySQLToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CString m_strIP;
	int m_nPort;
	CString m_strDBName;
	CString m_strUser;
	CString m_strPsw;

	int m_nSQLCount;
	char **m_arySQL;
	int m_nThreadCount;
	HANDLE *m_aryThread;
	tagRunInfo **m_aryRunInfo;

	bool m_bStop;

protected:
	static CMySQLToolDlg *sm_pDlg;
	static DWORD WINAPI RunThread(void *lpParam);
	bool CreateData(void);
	void FreeData(void);
	void ClearResult(void);
	void ShowResult(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSQLTOOLDLG_H__DFC76CFD_87AA_4B56_B4EB_12DEEA74C9D5__INCLUDED_)
