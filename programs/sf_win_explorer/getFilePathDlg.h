// getFilePathDlg.h : header file
//

#if !defined(AFX_GETFILEPATHDLG_H__83A6DDB7_B331_44BF_9239_3203C7F6E640__INCLUDED_)
#define AFX_GETFILEPATHDLG_H__83A6DDB7_B331_44BF_9239_3203C7F6E640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetFilePathDlg dialog

class CGetFilePathDlg : public CDialog
{
// Construction
public:
	int m_nIndex;
	CString m_strPath;
	CGetFilePathDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetFilePathDlg)
	enum { IDD = IDD_GETFILEPATH_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetFilePathDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetFilePathDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETFILEPATHDLG_H__83A6DDB7_B331_44BF_9239_3203C7F6E640__INCLUDED_)
