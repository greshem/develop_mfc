// ManprocDlg.cpp : implementation file
//
#include <stdlib.h>
#include "stdafx.h"
#include "remind.h"
#include "ManprocDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//#include <tlhelp32.h>
#include "./library/psapi.h"
#pragma comment( lib, "psapi" )

/////////////////////////////////////////////////////////////////////////////
// CManprocDlg dialog


CManprocDlg::CManprocDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManprocDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManprocDlg)
	//}}AFX_DATA_INIT
}


void CManprocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManprocDlg)
	DDX_Control(pDX, IDC_LISTTHREAD, m_listthread);
	DDX_Control(pDX, IDC_TAB2, m_tabCtrl);
	DDX_Control(pDX, IDC_LISTMODULE, m_listmodule);
	DDX_Control(pDX, IDC_PROCESSLIST, m_list);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_REFRESH, m_btnRefresh);
	DDX_Control(pDX, IDC_KILLPROC, m_btnKillproc);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CManprocDlg, CDialog)
	//{{AFX_MSG_MAP(CManprocDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PROCESSLIST, OnItemchangedProcesslist)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	ON_BN_CLICKED(IDC_KILLPROC, OnKillproc)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, OnSelchangeTab2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManprocDlg message handlers

BOOL CManprocDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//创建内嵌式TAB
	//pwndPropSheetHolder = GetDlgItem(IDC_THREADHOLDER);
	//m_pManprocSheet = new CManprocSheet(pwndPropSheetHolder);
	//if (!m_pManprocSheet->Create(pwndPropSheetHolder,WS_CHILD | WS_VISIBLE, 0))
	//{
	//	delete m_pManprocSheet;
	//	m_pManprocSheet = NULL;
	//	return FALSE;
	//}

	// fit the property sheet into the place holder window, and show it
	//CRect rectPropSheet;
	//pwndPropSheetHolder->GetWindowRect(rectPropSheet);
	//m_pManprocSheet->SetWindowPos(NULL,0,0,rectPropSheet.Width(),rectPropSheet.Height(),SWP_NOZORDER|SWP_NOACTIVATE);
	
	//添加标签
	TC_ITEM tcItem;
	tcItem.mask=TCIF_TEXT;
	tcItem.pszText="线程";
	m_tabCtrl.InsertItem(0,&tcItem);
	tcItem.pszText="模块";
	m_tabCtrl.InsertItem(1,&tcItem);

	//设置列表显示格式
	DWORD oldStyle = m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(oldStyle|LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
	m_list.SetBkColor(RGB(200,200,200));
	m_list.SetTextBkColor(RGB(200,200,200));

	oldStyle = m_listthread.GetExtendedStyle();
	m_listthread.SetExtendedStyle(oldStyle|LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
	m_listthread.SetBkColor(RGB(200,200,200));
	m_listthread.SetTextBkColor(RGB(200,200,200));

	oldStyle = m_listmodule.GetExtendedStyle();
	m_listmodule.SetExtendedStyle(oldStyle|LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);
	m_listmodule.SetBkColor(RGB(200,200,200));
	m_listmodule.SetTextBkColor(RGB(200,200,200));

	//设置按钮图标等
	m_btnRefresh.SetBitmaps(IDB_REFRESH1,RGB(255,255,255),IDB_REFRESH,RGB(255,255,255));
	m_btnRefresh.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnRefresh.SetRounded(TRUE);
	m_btnRefresh.SetSound(MAKEINTRESOURCE(IDR_WAVEHOVER), ::GetModuleHandle(NULL));
	m_btnRefresh.SetBtnCursor(IDC_HAND);

	m_btnKillproc.SetBitmaps(IDB_KILLPROC1,RGB(255,255,255),IDB_KILLPROC,RGB(255,255,255));
	m_btnKillproc.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnKillproc.SetRounded(TRUE);
	m_btnKillproc.SetSound(MAKEINTRESOURCE(IDR_WAVEHOVER), ::GetModuleHandle(NULL));
	m_btnKillproc.SetBtnCursor(IDC_HAND);

	m_btnCancel.SetBitmaps(IDB_CLOSE1,RGB(255,255,255),IDB_CLOSE,RGB(255,255,255));
	m_btnCancel.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnCancel.SetRounded(TRUE);
	m_btnCancel.SetSound(MAKEINTRESOURCE(IDR_WAVEHOVER), ::GetModuleHandle(NULL));
	m_btnCancel.SetBtnCursor(IDC_HAND);

	//m_list.InsertColumn(0,"序号",LVCFMT_LEFT,36);
	//m_list.InsertColumn(1,"进程名称",LVCFMT_LEFT,156);
	//m_list.InsertColumn(2,"进程ID",LVCFMT_LEFT,50);
	//m_list.InsertColumn(3,"线程数",LVCFMT_LEFT,50);
	//m_list.InsertColumn(4,"进程路径",LVCFMT_LEFT,450);
	m_list.SetHeadings(_T("序号,36;进程名称,156;进程ID,50;父进程ID,60;线程数,50;进程路径,450"));
	m_list.LoadColumnInfo();
	
	m_listthread.SetHeadings(_T("线程,100;特权,100;使用,100"));
	m_listthread.LoadColumnInfo();

	m_listmodule.SetHeadings(_T("内存地址,100;模块,550"));
	m_listmodule.LoadColumnInfo();

	GetDlgItem(IDC_LISTTHREAD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTMODULE)->ShowWindow(SW_HIDE);
	//PROCESSENTRY32* info = new PROCESSENTRY32;
	info = new PROCESSENTRY32;
	m_nCurrent = -1;
    
	ShowProcessList();
	SetDlgItemText(IDC_THREADCOUNT,"");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CManprocDlg::GetProcessPath(DWORD idProcess, char *spath)
{
    HANDLE hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                    FALSE, 
									idProcess );
    if( NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;
        
        if( EnumProcessModules( hProcess, &hMod, sizeof( hMod ), &cbNeeded ) )
        {
			DWORD dw = GetModuleFileNameEx( hProcess, hMod, spath, MAX_PATH );
        }
	    CloseHandle( hProcess );
    }
	return 0;
}

void CManprocDlg::ShowModules(DWORD processID)
{
	HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    // Get a list of all the modules in this process.
    hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );

	m_listmodule.DeleteAllItems();

    if (NULL == hProcess)
        return;

    if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
        {
            char szModName[MAX_PATH];
			char str[16];
            // Get the full path to the module's file.
            if ( GetModuleFileNameEx( hProcess, hMods[i], szModName, sizeof(szModName)))
            {
                // Print the module name and handle value.
                //printf("\t%s (0x%08X)\n", szModName, hMods[i] );
				memset(str, 0, sizeof(str));
				sprintf(str, "0x%08X", hMods[i]);
				//m_pManprocSheet->m_modulePage.m_listModule.InsertItem(0xffff,str,0);
				//m_pManprocSheet->m_modulePage.m_listModule.SetItem(i,1,LVIF_TEXT,szModName,0,0,0,0);
				(void)m_listmodule.AddItem(str,szModName);
            }
        }
    }
    CloseHandle( hProcess );
}

void CManprocDlg::OnItemchangedProcesslist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->uNewState&LVIS_SELECTED)
	{
		m_nCurrent = pNMListView->iItem;
		DWORD processID;
		memset(m_sID, 0, sizeof(m_sID));
		memset(m_sName, 0, sizeof(m_sName));
		strcpy(m_sID, m_list.GetItemText(m_nCurrent,2));
		strcpy(m_sName, m_list.GetItemText(m_nCurrent,1));
		processID = _ttoi(m_sID);

		ShowThreads(processID);
		ShowModules(processID);
		
		char strCount[128];
		sprintf(strCount, "当前进程线程总数：%d  引用模块总数：%d", m_listthread.GetItemCount(), m_listmodule.GetItemCount());
		SetDlgItemText(IDC_THREADCOUNT,strCount);
	}
	*pResult = 0;
}

int CManprocDlg::GetProcessCount()
{
	//获取进程总数
	DWORD aProcesses[1024], cbNeeded, cProcesses;
    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return 0;
    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);
	return cProcesses;
}

void CManprocDlg::ShowProcessList()
{
	int nItem = 0;
	char sExefile[32], sID[8], sparentid[8], sThread[5], sPath[256], sNum[5];

	m_list.DeleteAllItems();
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	info->dwSize = sizeof(PROCESSENTRY32);
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
				memset(sparentid, 0, sizeof(sparentid));
				memset(sThread, 0, sizeof(sThread));
				memset(sPath, 0, sizeof(sPath));
				memset(sNum, 0, sizeof(sNum));

				sprintf(sNum, "%d", nItem);
				sprintf(sExefile, "%s", info->szExeFile);
				sprintf(sID, "%d", info->th32ProcessID);
				sprintf(sparentid, "%d", info->th32ParentProcessID);
				sprintf(sThread, "%d", info->cntThreads);
				GetProcessPath(info->th32ProcessID, sPath);
				(void)m_list.AddItem(sNum,sExefile,sID,sparentid,sThread,sPath);
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
		//向下滚动
		CSize size;
		size.cx = 0;
		size.cy = m_nCurrent*7;
		m_list.Scroll(size);
		m_list.SetItemState(m_nCurrent,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_list.SetFocus();
	}

	char strCount[5];
	memset(strCount, 0, sizeof(strCount));
	sprintf(strCount,"进程总数：%d",GetProcessCount());
	SetDlgItemText(IDC_PROCESSCOUNT,strCount);	
}

void CManprocDlg::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	ShowProcessList();
}

void CManprocDlg::OnKillproc() 
{
	// TODO: Add your control notification handler code here
	if(m_nCurrent<0)
		return;
	
	char strmsg[256];
	
	HANDLE handle=OpenProcess(PROCESS_ALL_ACCESS,TRUE,(DWORD)atoi(m_sID));
	if(handle!=NULL)
	{
		memset(strmsg, 0, sizeof(strmsg));
		sprintf(strmsg,"确定要结束%s这一进程吗？",m_sName);
		if(MessageBox(strmsg,"提示",MB_YESNO+MB_ICONQUESTION)==IDYES)
		{
			//关闭进程
			if(TerminateProcess(handle,0)==0)
			{
				memset(strmsg, 0, sizeof(strmsg));
				sprintf(strmsg,"无法结束%s这一进程！",m_sName);
				MessageBox(strmsg,"提示",MB_YESNO+MB_ICONEXCLAMATION);
			}
			else
			{
				int nCount = m_list.GetItemCount();
				m_list.DeleteItem(m_nCurrent);

				if(m_nCurrent==nCount-1)
					--m_nCurrent;
				
				m_list.SetItemState(m_nCurrent,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
				m_list.SetFocus();

				DWORD processID;
				memset(m_sID, 0, sizeof(m_sID));
				memset(m_sName, 0, sizeof(m_sName));
				strcpy(m_sID, m_list.GetItemText(m_nCurrent,2));
				strcpy(m_sName, m_list.GetItemText(m_nCurrent,1));
				processID = _ttoi(m_sID);
				
				ShowThreads(processID);
				ShowModules(processID);
				//m_nCurrent = -1;
				//int m_nActivepage;		//当前显示线程还是模块
				//m_nActivepage = m_pManprocSheet->GetActiveIndex();
				//if(m_nActivepage==0)
				//{
				//	m_listthread.DeleteAllItems();
				//}
				//else
				//{
				//	m_listmodule.DeleteAllItems();
				//}				
			}
		}
	}
	else
	{
		memset(strmsg, 0, sizeof(strmsg));
		sprintf(strmsg,"%s为关键系统进程，无法结束该进程！",m_sName);
		MessageBox(strmsg,"提示",MB_OK+MB_ICONEXCLAMATION);
	}
}

void CManprocDlg::ShowThreads(DWORD processID)
{
	m_listthread.DeleteAllItems();

    HANDLE        hThreadSnap = NULL; 
    THREADENTRY32 thread32    = {0}; 
 
    // Take a snapshot of all modules in the specified process. 
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
    if (hThreadSnap == INVALID_HANDLE_VALUE) 
        return; 
 
    // Fill the size of the structure before using it. 
    thread32.dwSize = sizeof(THREADENTRY32); 
 
    // Walk the module list of the process, and find the module of 
    // interest. Then copy the information to the buffer pointed 
    // to by lpMe32 so that it can be returned to the caller. 
	int nItem = 0;
	char sid[16], sPri[8], sUser[8];
    if (Thread32First(hThreadSnap, &thread32)) 
    {
        do 
        { 
			if (thread32.th32OwnerProcessID==processID)
			{				
				sprintf(sid, "%08X", thread32.th32ThreadID);
				sprintf(sPri, "%d", thread32.tpBasePri);
				sprintf(sUser, "%d", thread32.cntUsage);
				(void)m_listthread.AddItem(sid,sPri,sUser);
				nItem++;
			}
        } 
        while (Thread32Next(hThreadSnap, &thread32)); 
 
        //bRet = bFound;   // if this sets bRet to FALSE, dwModuleID 
                         // no longer exists in specified process 
    } 
    // Do not forget to clean up the snapshot object. 
    CloseHandle (hThreadSnap);  
}

void CManprocDlg::OnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int m_nActivepage = m_tabCtrl.GetCurSel();
	if(m_nActivepage==0)
	{
		GetDlgItem(IDC_LISTTHREAD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTMODULE)->ShowWindow(SW_HIDE);		
	}
	else
	{
		GetDlgItem(IDC_LISTTHREAD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTMODULE)->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
}
