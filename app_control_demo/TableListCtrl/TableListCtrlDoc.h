// TableListCtrlDoc.h : interface of the CTableListCtrlDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLELISTCTRLDOC_H__42DFE4B6_1137_4F96_BD39_104FBF859710__INCLUDED_)
#define AFX_TABLELISTCTRLDOC_H__42DFE4B6_1137_4F96_BD39_104FBF859710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTableListCtrlDoc : public CDocument
{
protected: // create from serialization only
	CTableListCtrlDoc();
	DECLARE_DYNCREATE(CTableListCtrlDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableListCtrlDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTableListCtrlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTableListCtrlDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLELISTCTRLDOC_H__42DFE4B6_1137_4F96_BD39_104FBF859710__INCLUDED_)
