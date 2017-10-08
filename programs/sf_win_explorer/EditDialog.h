#if !defined(AFX_EDITDIALOG_H__2D8D3358_052D_49C9_9BFC_5880C6ABD11E__INCLUDED_)
#define AFX_EDITDIALOG_H__2D8D3358_052D_49C9_9BFC_5880C6ABD11E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EditDialog dialog

class EditDialog : public CDialog
{
// Construction
public:
	EditDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EditDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditDialog)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDIALOG_H__2D8D3358_052D_49C9_9BFC_5880C6ABD11E__INCLUDED_)
