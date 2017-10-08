// DiskCleanDlg.h : header file
//

#if !defined(AFX_DISKCLEANDLG_H__2AE5DB86_71B3_11D6_A3C0_0050BA075140__INCLUDED_)
#define AFX_DISKCLEANDLG_H__2AE5DB86_71B3_11D6_A3C0_0050BA075140__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDiskCleanDlg dialog

class CDiskCleanDlg : public CDialog
{
// Construction
public:
	int m_nDirNum;
	int m_nFileNum;
	CString m_strRootPathName;
	void GetSysDriver();
	int m_nDrvCount;
	//
	CWinThread* m_pThread;
	
	CDiskCleanDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDiskCleanDlg)
	enum { IDD = IDD_DISKCLEAN_DIALOG };
	CListBox	m_ctlListFile1;
	CListBox	m_ctlListFile;
	CComboBox	m_ctlComboDrive;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiskCleanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDiskCleanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelect();
	afx_msg void OnAppAbout();
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	afx_msg LRESULT OnExit(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAnswer(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboDrive();
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISKCLEANDLG_H__2AE5DB86_71B3_11D6_A3C0_0050BA075140__INCLUDED_)
