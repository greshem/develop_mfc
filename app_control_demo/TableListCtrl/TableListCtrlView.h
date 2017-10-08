// TableListCtrlView.h : interface of the CTableListCtrlView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLELISTCTRLVIEW_H__58259DD4_6B9F_41A3_A4A7_70298BAC88C7__INCLUDED_)
#define AFX_TABLELISTCTRLVIEW_H__58259DD4_6B9F_41A3_A4A7_70298BAC88C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTableListCtrlView : public CListView
{
protected: // create from serialization only
	CTableListCtrlView();
	DECLARE_DYNCREATE(CTableListCtrlView)

// Attributes
public:
	CTableListCtrlDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableListCtrlView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTableListCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTableListCtrlView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl m_TabCtrl;
};

#ifndef _DEBUG  // debug version in TableListCtrlView.cpp
inline CTableListCtrlDoc* CTableListCtrlView::GetDocument()
   { return (CTableListCtrlDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLELISTCTRLVIEW_H__58259DD4_6B9F_41A3_A4A7_70298BAC88C7__INCLUDED_)
