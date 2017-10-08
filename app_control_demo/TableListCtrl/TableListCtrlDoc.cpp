// TableListCtrlDoc.cpp : implementation of the CTableListCtrlDoc class
//

#include "stdafx.h"
#include "TableListCtrl.h"

#include "TableListCtrlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlDoc

IMPLEMENT_DYNCREATE(CTableListCtrlDoc, CDocument)

BEGIN_MESSAGE_MAP(CTableListCtrlDoc, CDocument)
	//{{AFX_MSG_MAP(CTableListCtrlDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlDoc construction/destruction

CTableListCtrlDoc::CTableListCtrlDoc()
{
	// TODO: add one-time construction code here

}

CTableListCtrlDoc::~CTableListCtrlDoc()
{
}

BOOL CTableListCtrlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlDoc serialization

void CTableListCtrlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlDoc diagnostics

#ifdef _DEBUG
void CTableListCtrlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTableListCtrlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlDoc commands
