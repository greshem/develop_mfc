// MsgnewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "remind.h"
#include "MsgnewDlg.h"
#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgnewDlg dialog


CMsgnewDlg::CMsgnewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgnewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMsgnewDlg)
	m_dDate = COleDateTime::GetCurrentTime();
	m_tTime = COleDateTime::GetCurrentTime();
	m_sMsg = _T("");
	m_bcheck = FALSE;
	//}}AFX_DATA_INIT
}


void CMsgnewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgnewDlg)
	DDX_Control(pDX, IDC_LISTBOX_MSG, m_listbox);
	DDX_Control(pDX, IDC_DTPDATE, m_cDate);
	DDX_DateTimeCtrl(pDX, IDC_DTPDATE, m_dDate);
	DDX_DateTimeCtrl(pDX, IDC_DTPTIME, m_tTime);
	DDX_Text(pDX, IDC_EDTMSG, m_sMsg);
	DDV_MaxChars(pDX, m_sMsg, 512);
	DDX_Check(pDX, IDC_CHECKDATE, m_bcheck);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CMsgnewDlg, CDialog)
	//{{AFX_MSG_MAP(CMsgnewDlg)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECKDATE, OnCheckdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgnewDlg message handlers

void CMsgnewDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	if(m_sMsg.GetLength()<=0)
	{
		MessageBox("请输入消息！","提示",MB_OK+MB_ICONINFORMATION);
		//CEdit* pEditname = (CEdit*)GetDlgItem(IDC_EDTMSG);
		//pEditname->SetFocus();
		GetDlgItem(IDC_EDTMSG)->SetFocus();
		return;
	}

	if(!m_bcheck)
	{
		int nCount = m_listbox.GetSelCount();
		if(!m_bcheck && nCount<1)
		{
			MessageBox("请选择需要提醒的日期！","提示",MB_OK+MB_ICONINFORMATION);
			//CEdit* pEditpath = (CEdit*)GetDlgItem(IDC_EDTPATH);
			//pEditpath->SetFocus();
			GetDlgItem(IDC_EDTPATH)->SetFocus();
			return;
		}
		else
		{
			//获得选中天数的字符串
			CArray<int,int> aryListBoxSel;
			aryListBoxSel.SetSize(nCount);
			m_listbox.GetSelItems(nCount, aryListBoxSel.GetData());
			int *arr = (int*)aryListBoxSel.GetData();
			FormatCheckedString(arr, nCount, m_sCheckday);
		}
	}

	CDialog::OnOK();
}

BOOL CMsgnewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(m_sCaption);

	m_listbox.InsertString(0,"Sun");
	m_listbox.InsertString(1,"Mon");
	m_listbox.InsertString(2,"Tue");
	m_listbox.InsertString(3,"Wed");
	m_listbox.InsertString(4,"Thu");
	m_listbox.InsertString(5,"Fri");
	m_listbox.InsertString(6,"Sat");

	//CDateTimeCtrl* pDatetime = (CDateTimeCtrl*)GetDlgItem(IDC_DTPDATE);
	//if(m_nCaption==0)
	//{
	//	::SendMessage(pDatetime->m_hWnd,DTM_SETSYSTEMTIME,GDT_NONE,NULL);
	//}
	//else
	//{
	//	if(m_dDate.GetStatus() == COleDateTime::null)
	//		::SendMessage(pDatetime->m_hWnd,DTM_SETSYSTEMTIME,GDT_NONE,NULL);
	//	else
	//		::SendMessage(pDatetime->m_hWnd,DTM_SETSYSTEMTIME,GDT_VALID,NULL);
	//}
	CDateTimeCtrl* pDatetime = (CDateTimeCtrl*)GetDlgItem(IDC_DTPDATE);
	if(m_nCaption==0)
	{
		//::SendMessage(pDatetime->m_hWnd,DTM_SETSYSTEMTIME,GDT_NONE,NULL);
		pDatetime->EnableWindow(FALSE);
		m_listbox.EnableWindow(TRUE);

		m_listbox.SetSel(1);
		m_listbox.SetSel(2);
		m_listbox.SetSel(3);
		m_listbox.SetSel(4);
		m_listbox.SetSel(5);
	}
	else 
	{
		//if(m_dDate.GetStatus() == COleDateTime::null)
		//m_nKind为一时不指定特定日期
		if(!m_nKind)
		{
			//::SendMessage(pDatetime->m_hWnd,DTM_SETSYSTEMTIME,GDT_NONE,NULL);
			pDatetime->EnableWindow(FALSE);
			m_listbox.EnableWindow(TRUE);

			for(int i=0;i<7;i++)
			{
				if(array[i]!=0)
					m_listbox.SetSel(array[i]-1);
			}
		}
		else
		{
			//::SendMessage(pDatetime->m_hWnd,DTM_SETSYSTEMTIME,GDT_VALID,NULL);
			pDatetime->EnableWindow(TRUE);
			m_listbox.EnableWindow(FALSE);
		}
	}

	//CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDTMSG);
	//pEdit->SetFocus();
	GetDlgItem(IDC_EDTMSG)->SetFocus();

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

void CMsgnewDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SendMessage(WM_SYSCOMMAND,SC_MOVE|HTCAPTION,0);
	//PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y));
	//SendMessage(WM_SYSCOMMAND,0xF012,0);

	CDialog::OnLButtonDown(nFlags, point);
}

void CMsgnewDlg::OnCheckdate() 
{
	// TODO: Add your control notification handler code here
	m_bcheck = !m_bcheck;

	if(m_bcheck)
	{
		m_cDate.EnableWindow(TRUE);
		m_listbox.EnableWindow(FALSE);
	}
	else
	{
		m_cDate.EnableWindow(FALSE);
		m_listbox.EnableWindow(TRUE);
		if(m_listbox.GetSelCount()<=0)
		{
			m_listbox.SetSel(1);
			m_listbox.SetSel(2);
			m_listbox.SetSel(3);
			m_listbox.SetSel(4);
			m_listbox.SetSel(5);
		}
	}
}
