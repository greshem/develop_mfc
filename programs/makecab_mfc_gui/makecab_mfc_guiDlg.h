// makecab_mfc_guiDlg.h : header file
//

#if !defined(AFX_MAKECAB_MFC_GUIDLG_H__1D6B06E8_DD3A_49DA_999B_63B2926C6D55__INCLUDED_)
#define AFX_MAKECAB_MFC_GUIDLG_H__1D6B06E8_DD3A_49DA_999B_63B2926C6D55__INCLUDED_

#include <string>
#include <vector>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMakecab_mfc_guiDlg dialog

class CMakecab_mfc_guiDlg : public CDialog
{
// Construction
public:
	vector<string> m_fileList;;
	CMakecab_mfc_guiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMakecab_mfc_guiDlg)
	enum { IDD = IDD_MAKECAB_MFC_GUI_DIALOG };
	CString	m_strPath;
	CString	m_strCatOutput;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakecab_mfc_guiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMakecab_mfc_guiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton6();
	afx_msg void OnGenCabConf();
	afx_msg void OnGenCab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void GenMakecabConf();
	void ShowAllFile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKECAB_MFC_GUIDLG_H__1D6B06E8_DD3A_49DA_999B_63B2926C6D55__INCLUDED_)
