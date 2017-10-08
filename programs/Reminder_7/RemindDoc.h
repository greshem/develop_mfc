// RemindDoc.h : interface of the CRemindDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REMINDDOC_H__37E181E7_EB1F_4257_BE78_F7022FA89781__INCLUDED_)
#define AFX_REMINDDOC_H__37E181E7_EB1F_4257_BE78_F7022FA89781__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./library/picture.h"

class CRemindDoc : public CDocument
{
protected: // create from serialization only
	CRemindDoc();
	DECLARE_DYNCREATE(CRemindDoc)

// Attributes
public:

// Operations
public:
	CPicture* GetPicture() {
		return &m_pict;
	}
	CPicture	m_pict; // the picture

protected:
	//CPicture	m_pict; // the picture
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemindDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRemindDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRemindDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMINDDOC_H__37E181E7_EB1F_4257_BE78_F7022FA89781__INCLUDED_)
