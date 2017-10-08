// _work_and_todoDlg.h : header file
//

#if !defined(AFX__WORK_AND_TODODLG_H__F871E48F_0399_4CED_816B_84881F32C36B__INCLUDED_)
#define AFX__WORK_AND_TODODLG_H__F871E48F_0399_4CED_816B_84881F32C36B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// C_work_and_todoDlg dialog

class C_work_and_todoDlg : public CDialog
{
// Construction
public:
	C_work_and_todoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(C_work_and_todoDlg)
	enum { IDD = IDD__WORK_AND_TODO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C_work_and_todoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(C_work_and_todoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__WORK_AND_TODODLG_H__F871E48F_0399_4CED_816B_84881F32C36B__INCLUDED_)
