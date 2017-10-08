// MailcheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "remind.h"
#include "MailcheckDlg.h"
#include "mailconfigdlg.h"
#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CheckMail *maillist;
extern char m_sInifilename[128];
/////////////////////////////////////////////////////////////////////////////
// CMailcheckDlg dialog

CMailcheckDlg::CMailcheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMailcheckDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMailcheckDlg)
	m_bCkmail = FALSE;
	m_nCheckmail = 0;
	//}}AFX_DATA_INIT
}


void CMailcheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMailcheckDlg)
	DDX_Control(pDX, IDC_LISTCON_MAIL, m_list);
	DDX_Check(pDX, IDC_CKMAIL, m_bCkmail);
	DDX_Text(pDX, IDC_EDTINTERVAL, m_nCheckmail);
	DDV_MinMaxInt(pDX, m_nCheckmail, 1, 10000);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CMailcheckDlg, CDialog)
	//{{AFX_MSG_MAP(CMailcheckDlg)
	ON_BN_CLICKED(IDC_CKMAIL, OnCkmail)
	ON_EN_KILLFOCUS(IDC_EDTINTERVAL, OnKillfocusEdtinterval)
	ON_BN_CLICKED(IDC_BTNAPPEND, OnBtnappend)
	ON_BN_CLICKED(IDC_BTNCHANGE, OnBtnchange)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBtndelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailcheckDlg message handlers

BOOL CMailcheckDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//设置列表显示格式
	DWORD oldStyle = m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(oldStyle|LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
	m_list.SetBkColor(RGB(200,200,200));
	m_list.SetTextBkColor(RGB(200,200,200));

	CSpinButtonCtrl* pSpin =
		(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN1);
	pSpin->SetRange(1, 1000);

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

	m_list.InsertColumn(0,"",LVCFMT_LEFT,16);
	m_list.InsertColumn(1,"邮件地址",LVCFMT_LEFT,150);
	m_list.InsertColumn(2,"POP3服务器",LVCFMT_LEFT,96);

	if(m_nCheckmail<1)
		m_nCheckmail = 5;

	//m_nCount = GetMailListCount();
	m_nCount = GetListCount(&maillist);

	if(m_bCkmail)
		GetDlgItem(IDC_EDTINTERVAL)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_EDTINTERVAL)->EnableWindow(TRUE);

	char sKey[3];
	CheckMail *checkmail;
	checkmail = maillist;
	int i = 1;
	while(checkmail != NULL)
	{
		memset(sKey, 0, sizeof(sKey));
		sprintf(sKey, "%d", i++);
		
		int nItem = m_list.InsertItem(0xffff,sKey,0);
		m_list.SetItem(nItem,1,LVIF_TEXT,checkmail->mail,0,0,0,0);
		m_list.SetItem(nItem,2,LVIF_TEXT,checkmail->host,0,0,0,0);

		checkmail = checkmail->next;
	}

	if(m_nCount<=0)
		m_nCurrent = -1;
	else
		m_nCurrent = 0;
	
	UpdateData(FALSE);
	
	m_list.SetItemState(m_nCurrent,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_list.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMailcheckDlg::OnCkmail() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_bCkmail)
		GetDlgItem(IDC_EDTINTERVAL)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_EDTINTERVAL)->EnableWindow(TRUE);
}

void CMailcheckDlg::OnKillfocusEdtinterval() 
{
	// TODO: Add your control notification handler code here
	char str[128];
	GetDlgItem(IDC_EDTINTERVAL)->GetWindowText(str, 128);
	m_nCheckmail = atoi(str);

	if(m_nCheckmail<1)
	{
		m_nCheckmail = 5;
		UpdateData(FALSE);
	}
}

void CMailcheckDlg::OnBtnappend() 
{
	// TODO: Add your control notification handler code here
	//m_nCount = GetPrivateProfileInt(MAILFIELD,"Count",0,m_sInifilename);
	if(m_nCount>=5)
	{
		MessageBox("已经达到最大邮件设置个数！","提示",MB_OK+MB_ICONINFORMATION);
		return;
	}

	CMailconfigDlg dlg;

	if(dlg.DoModal()==IDOK)
	{
		CheckMail *checkmail;
		checkmail = (CheckMail*)malloc(sizeof(CheckMail));
		memset(checkmail, 0, sizeof(CheckMail));
		char sCount[3];
		char str[256];
		memset(sCount, 0, sizeof(sCount));
		memset(str, 0, sizeof(str));
		sprintf(sCount, "%d", ++m_nCount);
		strcpy(checkmail->mail, dlg.m_sMail);
		strcpy(checkmail->host, dlg.m_sHost);
		strcpy(checkmail->user, dlg.m_sUser);
		char pwd[128];
		memset(pwd, 0, sizeof(pwd));
		strcpy(pwd, dlg.m_sPass);
		Endecrypt_Mars(pwd, checkmail->password);

		AddToList(&maillist, checkmail);

		sprintf(str, "%s|%s|%s|%s|", dlg.m_sMail, dlg.m_sHost, dlg.m_sUser, checkmail->password);
		WritePrivateProfileString(MAILFIELD,COUNTKEY,sCount,m_sInifilename);
		WritePrivateProfileString(MAILFIELD,sCount,str,m_sInifilename);

		int nItem = m_list.InsertItem(0xffff,sCount,0);
		m_list.SetItem(nItem,1,LVIF_TEXT,dlg.m_sMail,0,0,0,0);
		m_list.SetItem(nItem,2,LVIF_TEXT,dlg.m_sHost,0,0,0,0);

		m_nCurrent = m_nCount - 1;
		m_list.SetItemState(m_nCurrent,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_list.SetFocus();
	}
}

void CMailcheckDlg::OnBtnchange() 
{
	// TODO: Add your control notification handler code here
	m_nCurrent = ::SendMessage(m_list,(UINT) LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if(m_nCurrent<0)
	{
		return;
	}

	CMailconfigDlg dlg;

	char str[256];
	char sKey[3];
	char password[128];

	memset(sKey, 0, sizeof(sKey));
	strcpy(sKey, m_list.GetItemText(m_nCurrent,0));
	CheckMail *checkmail = GetListNode(&maillist, m_nCurrent);
	dlg.m_sMail = checkmail->mail;
	dlg.m_sHost = checkmail->host;
	dlg.m_sUser = checkmail->user;
	memset(password, 0, sizeof(password));
	Endecrypt_Mars(checkmail->password, password, 0);
	dlg.m_sPass = password;

	if(dlg.DoModal()==IDOK)
	{
		strcpy(checkmail->mail, dlg.m_sMail);
		strcpy(checkmail->host, dlg.m_sHost);
		strcpy(checkmail->user, dlg.m_sUser);
		char pwd[128];
		memset(pwd, 0, sizeof(pwd));
		strcpy(pwd, dlg.m_sPass);
		Endecrypt_Mars(pwd, checkmail->password);

		memset(str, 0, sizeof(str));

		sprintf(str,"%s|%s|%s|%s|",dlg.m_sMail,dlg.m_sHost,dlg.m_sUser,checkmail->password);
		WritePrivateProfileString(MAILFIELD,sKey,str,m_sInifilename);

		(void)m_list.SetItemText(m_nCurrent,1,dlg.m_sMail);
		(void)m_list.SetItemText(m_nCurrent,2,dlg.m_sHost);

		m_list.SetItemState(m_nCurrent,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_list.SetFocus();
	}
}

void CMailcheckDlg::OnBtndelete() 
{
	// TODO: Add your control notification handler code here
	m_nCurrent = ::SendMessage(m_list,(UINT) LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if(m_nCurrent < 0)
		return;
	
	if(MessageBox("确定要删除这条记录吗？","提示",MB_YESNO+MB_ICONQUESTION)==IDYES)
	{
		DelListNode(&maillist, m_nCurrent);

		m_list.DeleteItem(m_nCurrent);
		--m_nCount;
		if(m_nCurrent==m_nCount)
		{
			//如果选择的是最后一行
			--m_nCurrent;
		}
		else
		{
			char sKeyname[3], sKeyname1[3];
			for(int i=m_nCurrent;i<m_nCount;i++)
			{
				//修改列表显示
				memset(sKeyname, 0, sizeof(sKeyname));
				memset(sKeyname1, 0, sizeof(sKeyname1));

				sprintf(sKeyname, "%d", i+1);
				m_list.SetItem(i,0,LVIF_TEXT,sKeyname,0,0,0,0);
				//修改INI文件
				char cstr[MAX_PATH];
				sprintf(sKeyname1, "%d", i+2);
				GetPrivateProfileString(MAILFIELD,sKeyname1,"",cstr,MAX_PATH,m_sInifilename);
				WritePrivateProfileString(MAILFIELD,sKeyname,cstr,m_sInifilename);
			}
		}
		//删除最后一条键值
		char slastkey[3],sCount[3];
		sprintf(slastkey, "%d", m_nCount+1);
		WritePrivateProfileString(MAILFIELD,slastkey,NULL,m_sInifilename);
		
		sprintf(sCount,"%d",m_nCount);
		WritePrivateProfileString(MAILFIELD,COUNTKEY,sCount,m_sInifilename);
	}
	m_list.SetItemState(m_nCurrent,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_list.SetFocus();
}
