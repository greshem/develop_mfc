// MailconfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "remind.h"
#include "MailconfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailconfigDlg dialog


CMailconfigDlg::CMailconfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMailconfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMailconfigDlg)
	m_sHost = _T("");
	m_sMail = _T("");
	m_sPass = _T("");
	m_sUser = _T("");
	//}}AFX_DATA_INIT
}


void CMailconfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMailconfigDlg)
	DDX_Text(pDX, IDC_EDTHOST, m_sHost);
	DDV_MaxChars(pDX, m_sHost, 100);
	DDX_Text(pDX, IDC_EDTMAIL, m_sMail);
	DDV_MaxChars(pDX, m_sMail, 100);
	DDX_Text(pDX, IDC_EDTPASS, m_sPass);
	DDV_MaxChars(pDX, m_sPass, 16);
	DDX_Text(pDX, IDC_EDTUSER, m_sUser);
	DDV_MaxChars(pDX, m_sUser, 50);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CMailconfigDlg, CDialog)
	//{{AFX_MSG_MAP(CMailconfigDlg)
	ON_EN_CHANGE(IDC_EDTMAIL, OnChangeEdtmail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailconfigDlg message handlers

void CMailconfigDlg::OnChangeEdtmail() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char sMail[128], sHost[32];
	int npos = 0;
	memset(sMail, 0, sizeof(sMail));
	memset(sHost, 0, sizeof(sHost));
	GetDlgItem(IDC_EDTMAIL)->GetWindowText(sMail, 128);
	//int nfind = sMail.Find('@');
	if((npos = strcspn(sMail, "@")) >0 && npos < strlen(sMail))
	{
		GetDlgItem(IDC_EDTHOST)->SetWindowText(sMail + npos + 1);
		(strrchr(sMail,'@'))[0] = 0;
	}

		GetDlgItem(IDC_EDTUSER)->SetWindowText(sMail);
	//else
	//{
	//	GetDlgItem(IDC_EDTUSER)->SetWindowText(sMail.Mid(0,nfind));
	//}
}

BOOL CMailconfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//设置按钮图标等
	//m_btnOk.SetIcon(IDI_ICON2);
	m_btnOk.SetBitmaps(IDB_OK1,RGB(255,255,255),IDB_OK,RGB(255,255,255));
	m_btnOk.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnOk.SetRounded(TRUE);
	m_btnOk.SetSound(MAKEINTRESOURCE(IDR_WAVEHOVER), ::GetModuleHandle(NULL));
	m_btnOk.SetBtnCursor(IDC_HAND);

	//m_btnCancel.SetIcon(IDI_ICON3);
	m_btnCancel.SetBitmaps(IDB_CANCEL1,RGB(255,255,255),IDB_CANCEL,RGB(255,255,255));
	m_btnCancel.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnCancel.SetRounded(TRUE);
	m_btnCancel.SetSound(MAKEINTRESOURCE(IDR_WAVEHOVER), ::GetModuleHandle(NULL));
	m_btnCancel.SetBtnCursor(IDC_HAND);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
