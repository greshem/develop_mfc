// SelectFile.cpp : implementation file
//

#include "stdafx.h"
#include "DiskClean.h"
#include "SelectFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectFile dialog


CSelectFile::CSelectFile(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectFile)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectFile, CDialog)
	//{{AFX_MSG_MAP(CSelectFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectFile message handlers

BOOL CSelectFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_dWSel & 0x1)((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1);
	if(m_dWSel & 0x2)((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(1);
	if(m_dWSel & 0x4)((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(1);
	if(m_dWSel & 0x8)((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(1);
	if(m_dWSel & 0x10)((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(1);
	if(m_dWSel & 0x20)((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(1);
	if(m_dWSel & 0x40)((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(1);
	if(m_dWSel & 0x80)((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(1);
	if(m_dWSel & 0x100)((CButton*)GetDlgItem(IDC_CHECK9))->SetCheck(1);
	if(m_dWSel & 0x200)((CButton*)GetDlgItem(IDC_CHECK10))->SetCheck(1);
	if(m_dWSel & 0x400)((CButton*)GetDlgItem(IDC_CHECK11))->SetCheck(1);
	if(m_dWSel & 0x800)((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(1);
	if(m_dWSel & 0x1000)((CButton*)GetDlgItem(IDC_CHECK13))->SetCheck(1);
	if(m_dWSel & 0x2000)((CButton*)GetDlgItem(IDC_CHECK14))->SetCheck(1);
	if(m_dWSel & 0x4000)((CButton*)GetDlgItem(IDC_CHECK15))->SetCheck(1);
	if(m_dWSel & 0x8000)((CButton*)GetDlgItem(IDC_CHECK16))->SetCheck(1);
	if(m_dWSel & 0x10000)((CButton*)GetDlgItem(IDC_CHECK17))->SetCheck(1);
	if(m_dWSel & 0x20000)((CButton*)GetDlgItem(IDC_CHECK18))->SetCheck(1);
	if(m_dWSel & 0x40000)((CButton*)GetDlgItem(IDC_CHECK19))->SetCheck(1);
	if(m_dWSel & 0x80000)((CButton*)GetDlgItem(IDC_CHECK20))->SetCheck(1);
	if(m_dWSel & 0x100000)((CButton*)GetDlgItem(IDC_CHECK21))->SetCheck(1);
	if(m_dWSel & 0x200000)((CButton*)GetDlgItem(IDC_CHECK22))->SetCheck(1);
	if(m_dWSel & 0x400000)((CButton*)GetDlgItem(IDC_CHECK23))->SetCheck(1);
	if(m_dWSel & 0x800000)((CButton*)GetDlgItem(IDC_CHECK24))->SetCheck(1);
	if(m_dWSel & 0x1000000)((CButton*)GetDlgItem(IDC_CHECK25))->SetCheck(1);
	if(m_dWSel & 0x2000000)((CButton*)GetDlgItem(IDC_CHECK26))->SetCheck(1);
	if(m_dWSel & 0x4000000)((CButton*)GetDlgItem(IDC_CHECK27))->SetCheck(1);
	if(m_dWSel & 0x8000000)((CButton*)GetDlgItem(IDC_CHECK28))->SetCheck(1);
	//qzj
	if(m_dWSel & 0x10000000)((CButton*)GetDlgItem(IDC_CHECK29))->SetCheck(1);
	if(m_dWSel & 0x20000000)((CButton*)GetDlgItem(IDC_CHECK30))->SetCheck(1);
	//
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
