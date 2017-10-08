// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__84C7924A_51ED_4C1E_8055_F1C4C32806C4__INCLUDED_)
#define AFX_MAINFRM_H__84C7924A_51ED_4C1E_8055_F1C4C32806C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./library/systemicon.h"
#include "./library/BCMenu.h"

class CMainFrame : public CFrameWnd
{
public:
	BCMenu m_menu;
	CSystemIcon m_systemIcon;	/*定义对象*/
	int nOntop;					/*是否置于顶端*/
	BOOL m_bAutorun;			/*是否自动运行*/
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;

public:
	HMENU NewMenu();
	CStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnAppTerminate();
	afx_msg void OnOptionOntop();
	afx_msg void OnUpdateOptionOntop(CCmdUI* pCmdUI);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnOptionAutorun();
	afx_msg void OnUpdateOptionAutorun(CCmdUI* pCmdUI);
	afx_msg void OnAppApp();
	//}}AFX_MSG
	afx_msg LRESULT OnIconNotification(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnQueryEndSession(WPARAM wReserved, LPARAM lEndReason);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__84C7924A_51ED_4C1E_8055_F1C4C32806C4__INCLUDED_)
