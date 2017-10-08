// [%Name%]Dlg.h : header file
//

#if !defined(AFX_[%Name%]DLG_H__1FC1EE1C_A463_4CD8_B242_B245CE73AB6D__INCLUDED_)
#define AFX_[%Name%]DLG_H__1FC1EE1C_A463_4CD8_B242_B245CE73AB6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// C[%Name%]Dlg dialog

class C[%Name%]Dlg : public CDialog
{
// Construction
public:
	C[%Name%]Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(C[%Name%]Dlg)
	enum { IDD = IDD_[%Name%]_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C[%Name%]Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(C[%Name%]Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_[%Name%]DLG_H__1FC1EE1C_A463_4CD8_B242_B245CE73AB6D__INCLUDED_)
