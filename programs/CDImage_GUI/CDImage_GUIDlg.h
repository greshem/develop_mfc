// CDImage_GUIDlg.h : header file
//

#if !defined(AFX_CDIMAGE_GUIDLG_H__12AEEB68_3E98_4167_80B2_A5DC3E3DDAC5__INCLUDED_)
#define AFX_CDIMAGE_GUIDLG_H__12AEEB68_3E98_4167_80B2_A5DC3E3DDAC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCDImage_GUIDlg dialog

class CCDImage_GUIDlg : public CDialog
{
// Construction
public:
	CCDImage_GUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCDImage_GUIDlg)
	enum { IDD = IDD_CDIMAGE_GUI_DIALOG };
	CString	m_strVolumn;
	BOOL	m_bAllOneTime;
	CString	m_strMtime;
	BOOL	m_bLongName;
	BOOL	m_bCheckWithFileContent;
	BOOL	m_bUpcase;
	CString	m_strIsoDir;
	CString	m_strBootSectFile;
	BOOL	m_bDVD;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDImage_GUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	public:
	int 	ExtractExe();
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCDImage_GUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGen();
	afx_msg void OnCheckMtime();
	afx_msg void OnCheckLongname();
	afx_msg void OnCheckWithAllContent();
	afx_msg void OnCheckUpcase();
	afx_msg void OnButDiretory();
	afx_msg void OnButBootRecord();
	afx_msg void OnChangeVolumn();
	afx_msg void OnCheckDvd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDIMAGE_GUIDLG_H__12AEEB68_3E98_4167_80B2_A5DC3E3DDAC5__INCLUDED_)
