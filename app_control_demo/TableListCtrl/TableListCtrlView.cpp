// TableListCtrlView.cpp : implementation of the CTableListCtrlView class
//

#include "stdafx.h"
#include "TableListCtrl.h"

#include "TableListCtrlDoc.h"
#include "TableListCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlView

IMPLEMENT_DYNCREATE(CTableListCtrlView, CListView)

BEGIN_MESSAGE_MAP(CTableListCtrlView, CListView)
	//{{AFX_MSG_MAP(CTableListCtrlView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlView construction/destruction

CTableListCtrlView::CTableListCtrlView()
{
	// TODO: add construction code here

}

CTableListCtrlView::~CTableListCtrlView()
{
}

BOOL CTableListCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlView drawing

void CTableListCtrlView::OnDraw(CDC* pDC)
{
	CTableListCtrlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CTableListCtrlView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	CRect rectCtrl(10,10,500,300);
	GetClientRect(&rectCtrl);
    m_TabCtrl.Create(TCS_TABS | TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE,rectCtrl, this, 0x1006);

	m_TabCtrl.InsertItem(0,_T("dddsd"),100);
	m_TabCtrl.InsertItem(1,_T("dddsd"),100);
	m_TabCtrl.InsertItem(2,_T("dddsd"),100);

}

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlView printing

BOOL CTableListCtrlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTableListCtrlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTableListCtrlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlView diagnostics

#ifdef _DEBUG
void CTableListCtrlView::AssertValid() const
{
	CListView::AssertValid();
}

void CTableListCtrlView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CTableListCtrlDoc* CTableListCtrlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTableListCtrlDoc)));
	return (CTableListCtrlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTableListCtrlView message handlers

void CTableListCtrlView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
	
	//add 
	if(m_TabCtrl)
	{
		m_TabCtrl.MoveWindow(0,0,cx,cy);
	}
	
}
