// RemindDoc.cpp : implementation of the CRemindDoc class
//

#include "stdafx.h"
#include "Remind.h"

#include "RemindDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char m_sInifilename[128];
extern int m_nIspicture;					/*ÓÐÎÞ±³¾°Í¼Æ¬*/
/////////////////////////////////////////////////////////////////////////////
// CRemindDoc

IMPLEMENT_DYNCREATE(CRemindDoc, CDocument)

BEGIN_MESSAGE_MAP(CRemindDoc, CDocument)
	//{{AFX_MSG_MAP(CRemindDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemindDoc construction/destruction

CRemindDoc::CRemindDoc()
{
	// TODO: add one-time construction code here

}

CRemindDoc::~CRemindDoc()
{
}

BOOL CRemindDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	char picpath[128];
	memset(picpath, 0, sizeof(picpath));
	GetPrivateProfileString(OPTFIELD,BKGPICKEY,"",picpath,128,m_sInifilename);
	m_nIspicture = m_pict.Load(picpath);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CRemindDoc serialization

void CRemindDoc::Serialize(CArchive& ar)
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
// CRemindDoc diagnostics

#ifdef _DEBUG
void CRemindDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRemindDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRemindDoc commands
