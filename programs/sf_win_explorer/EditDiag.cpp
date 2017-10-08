// EditDiag.cpp : implementation file
//

#include "stdafx.h"
#include "getFilePath.h"
#include "EditDiag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EditDiag dialog


EditDiag::EditDiag(CWnd* pParent /*=NULL*/)
	: CDialog(EditDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditDiag)
	m_strCata = _T("");
	m_strNumber = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void EditDiag::DoDataExchange(CDataExchange* pDX)
{

	//{{AFX_DATA_MAP(EditDiag)
	DDX_Text(pDX, IDC_CATA, m_strCata);
	DDX_Text(pDX, IDC_NUMBER, m_strNumber);
	DDX_Text(pDX, IDC_NAME, m_strName);
	CDialog::DoDataExchange(pDX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditDiag, CDialog)
	//{{AFX_MSG_MAP(EditDiag)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditDiag message handlers

void EditDiag::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString path;
//	GetDlgItem(IDC_EDIT1)->GetWindowText(path);
	//MessageBox(m_strCata);
	::ShellExecute(this->m_hWnd,"open",m_strCata,NULL,NULL,SW_SHOWNORMAL);
}
