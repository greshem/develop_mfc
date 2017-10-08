// ProcessDlg.cpp : implementation file
//
#include "stdafx.h"
#include "remind.h"
#include "ProcessDlg.h"
//#include "afxmt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//#include <tlhelp32.h>

//CEvent g_eventkill;		//creates autoreset event
/////////////////////////////////////////////////////////////////////////////
// CProcessDlg dialog
//UINT ThreadFunc(LPVOID pParam)
//{
//	while(1)
//	{
//		//每过一秒钟发送一次消息
//		Sleep(1000);
//		::PostMessage((HWND)pParam,WM_SHOWPROCESS,0,0);
//		if(::WaitForSingleObject(g_eventkill,0)==WAIT_OBJECT_0)
//			break;
//	}
//	return 0;
//}

CProcessDlg::CProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessDlg)
	m_dDate = COleDateTime::GetCurrentTime();
	m_dTime = COleDateTime::GetCurrentTime();
	m_sCount = _T("");
	//}}AFX_DATA_INIT
}


void CProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessDlg)
	DDX_Control(pDX, IDC_LISTC_PROC, m_list);
	DDX_DateTimeCtrl(pDX, IDC_DTPDATE, m_dDate);
	DDX_DateTimeCtrl(pDX, IDC_DTPTIME, m_dTime);
	DDX_Text(pDX, IDC_COUNT, m_sCount);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_REFRESH, m_btnRefresh);
}


BEGIN_MESSAGE_MAP(CProcessDlg, CDialog)
	ON_MESSAGE(WM_SHOWPROCESS,OnShowprocess)
	//{{AFX_MSG_MAP(CProcessDlg)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg message handlers

BOOL CProcessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_sCaption);
	// TODO: Add extra initialization here
	//m_cProclist.ModifyStyle(0,LVS_REPORT);
	//::SendMessage(m_cProclist.m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	DWORD oldStyle = m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(oldStyle|LVS_EX_FULLROWSELECT|LVS_EX_TRACKSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);

	//m_cProclist.InsertColumn(0,"进程名称",LVCFMT_LEFT,156);
	//m_cProclist.InsertColumn(1,"进程ID",LVCFMT_LEFT,50);
	//m_cProclist.InsertColumn(2,"线程数",LVCFMT_LEFT,50);
	m_list.SetHeadings(_T("进程名称,156;进程ID,50;线程数,50"));
	m_list.LoadColumnInfo();
	//m_cProclist.InsertColumn(3,"   ",LVCFMT_LEFT,50);
	
	//PROCESSENTRY32* info = new PROCESSENTRY32;
	info = new PROCESSENTRY32;
	
	//int nItem = 0;
	m_nCurrent = -1;
	PostMessage(WM_SHOWPROCESS);
	
	//创建线程
	//AfxBeginThread(ThreadFunc,GetSafeHwnd());
	//设置按钮图标等
	m_btnRefresh.SetBitmaps(IDB_REFRESH1,RGB(255,255,255),IDB_REFRESH,RGB(255,255,255));
	m_btnRefresh.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnRefresh.SetRounded(TRUE);
	m_btnRefresh.SetSound(MAKEINTRESOURCE(IDR_WAVEHOVER), ::GetModuleHandle(NULL));
	m_btnRefresh.SetBtnCursor(IDC_HAND);

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

LRESULT CProcessDlg::OnShowprocess(WPARAM wParam,LPARAM lParam)
{
	m_list.DeleteAllItems();
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	
    info->dwSize = sizeof(PROCESSENTRY32);
    int nItem = 0;
	char sExefile[32], sID[5], sThread[5];
	if(Process32First(handle,info))
	{
		if(GetLastError()==ERROR_NO_MORE_FILES )
		{
			AfxMessageBox("No More Process");
		}
		else
		{
			do
			{
				memset(sExefile, 0, sizeof(sExefile));
				memset(sID, 0, sizeof(sID));
				memset(sThread, 0, sizeof(sThread));
				sprintf(sExefile, "%s", info->szExeFile);
				sprintf(sID, "%d", info->th32ProcessID);
				sprintf(sThread, "%d", info->cntThreads);
				(void)m_list.AddItem(sExefile,sID,sThread);
				if(stricmp(m_sID, sID) == 0)
					m_nCurrent = nItem;
				nItem++;
			}
			while(Process32Next(handle,info)!=FALSE);
		}
	}
	CloseHandle(handle);

	if(m_nCurrent>=0)
	{
		CSize size1;
		size1 = m_list.ApproximateViewRect();

		//向下滚动
		CSize size;
		size.cx = 0;
		size.cy = m_nCurrent*(size1.cy/m_list.GetItemCount());
		m_list.Scroll(size);
		m_list.SetItemState(m_nCurrent,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_list.SetFocus();
	}

	m_sCount.Format("进程总数：%d",m_list.GetItemCount());
	SetDlgItemText(IDC_COUNT,m_sCount);

	return 0;
}

void CProcessDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	m_nCurrent = ::SendMessage(				// returns LRESULT in lResult
			m_list,							// handle to destination control
			(UINT) LVM_GETNEXTITEM,			// message ID
			-1,								// = (WPARAM) (int) iStart
			LVNI_SELECTED					// = (LPARAM) MAKELPARAM ((UINT) flags, 0)
        );
	if(m_nCurrent<0)
	{
		MessageBox("请选择一个将要结束的进程！","提示",MB_OK+MB_ICONINFORMATION);
		return;
	}
	memset(m_sName, 0, sizeof(m_sName));
	memset(m_sID, 0, sizeof(m_sID));
	strcpy(m_sName, m_list.GetItemText(m_nCurrent, 0));
	strcpy(m_sID, m_list.GetItemText(m_nCurrent, 1));

	delete info;
	CDialog::OnOK();
}

void CProcessDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//点击窗口任何地方可移动窗口
	SendMessage(WM_SYSCOMMAND,SC_MOVE|HTCAPTION,0);
	//PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y));
	//SendMessage(WM_SYSCOMMAND,0xF012,0);
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CProcessDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//通知结束进程
	//g_eventkill.SetEvent();
	delete info;
	CDialog::OnCancel();
}

void CProcessDlg::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	PostMessage(WM_SHOWPROCESS);
}
