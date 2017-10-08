// EditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "getFilePath.h"
#include "EditDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EditDialog dialog


EditDialog::EditDialog(CWnd* pParent /*=NULL*/)
	: CDialog(EditDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void EditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditDialog, CDialog)
	//{{AFX_MSG_MAP(EditDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditDialog message handlers

void EditDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString path;
	GetDlgItem(IDC_EDIT1)->GetWindowText(path);
	//::ShellExecute(this->m_hWnd,"open",m_strCata ,NULL,NULL,SW_SHOWNORMAL);
}
