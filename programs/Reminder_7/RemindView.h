// RemindView.h : interface of the CRemindView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REMINDVIEW_H__DDD4B47E_6D8C_4507_AFEE_E25515896983__INCLUDED_)
#define AFX_REMINDVIEW_H__DDD4B47E_6D8C_4507_AFEE_E25515896983__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "WinXPButtonST.h"
#include "public.h"

#define WM_MANPROCESS WM_USER+9
#define WM_CHECKMAIL WM_USER+8

class CRemindView : public CFormView
{
protected:
	int m_nCurrentProg,m_nCurrentMsg,m_nCurrentTerm;	/*当前所在行*/
	int m_nActivepage;

	CWinXPButtonST m_btnShutnow;
	CBrush m_brushBackground;					//背景画刷
	char sStarttime[20], sLastshuttime[20];		/*本次启动时间、上次关闭时间*/

private:
	int m_Error;
	int m_NoMail;

protected: // create from serialization only
	CRemindView();
	DECLARE_DYNCREATE(CRemindView)

public:
	//{{AFX_DATA(CRemindView)
	enum { IDD = IDD_REMIND_FORM };
	CListCtrl	m_proglist;
	CListCtrl	m_proclist;
	CListCtrl	m_msglist;
	CTabCtrl	m_tabCtrl;
	CButton	m_cCkshut;
	CButton	m_cGroup;
	CComboBox	m_cType;
	CDateTimeCtrl	m_cShutdate;
	CDateTimeCtrl	m_cShuttime;
	CComboBox	m_cForce;
	BOOL	m_bShut;
	int		m_nShutforce;
	int		m_nShuttype;
	COleDateTime	m_dShutdate;
	COleDateTime	m_tShuttime;
	//}}AFX_DATA

// Attributes
public:
	CRemindDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemindView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	static UINT ThreadCheckMail(LPVOID pParam);
	void ShowProcHeader();
	static UINT ThreadManProc(LPVOID pParam);
	virtual ~CRemindView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int RefreshView();
	void StartCheckMail();
	void GetImageRect(CRect& rc);
	void InitialTimerShut();
	void InitialListMsg();
	void InitialListProg();
	void ShowProgHeader();
	void ShowMsgHeader();
	void ShowStrFormatError();
	void ShutdownSystem(int nType, int nForce);
	//{{AFX_MSG(CRemindView)
	afx_msg void OnCkshut();
	afx_msg void OnBtnshutnow();
	afx_msg void OnEditNew();
	afx_msg void OnEditMod();
	afx_msg void OnEditDel();
	afx_msg void OnOptionBeep();
	afx_msg void OnUpdateOptionBeep(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnToolManproc();
	afx_msg void OnSelchangeTablist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolMailcheck();
	afx_msg void OnDblclkMsglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedMsglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkProclist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedProclist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkProglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedProglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOptionGetpic();
	//}}AFX_MSG
	afx_msg LRESULT OnManProcess(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnCheckMail(WPARAM wParam,LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RemindView.cpp
inline CRemindDoc* CRemindView::GetDocument()
   { return (CRemindDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMINDVIEW_H__DDD4B47E_6D8C_4507_AFEE_E25515896983__INCLUDED_)
