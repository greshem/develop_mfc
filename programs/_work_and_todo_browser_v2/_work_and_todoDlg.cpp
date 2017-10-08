// _work_and_todoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "_work_and_todo.h"
#include "_work_and_todoDlg.h"
#include <io.h>
#include <stdlib.h>
#include <stdio.h> 
#include <vector>
#include <string>
using namespace std;

//#include <unistd.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
BOOL   TransDirectory(LPCTSTR   DirName, vector<string> &out)
{
	CFileFind   tempFind;   //file://声明一个CFileFind类变量，以用来搜索
	char   tempFileFind[1024];   //file://用于定义搜索格式
	sprintf(tempFileFind, "%s\\*.*",DirName);
	//file://匹配格式为*.*,即该目录下的所有文件  
	
	BOOL   IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
	if(IsFinded)
	{
		printf("找到了\n");
	}
	else
	{
		printf("%s\n", tempFileFind);
		printf("没有找到\n");
	}
	//file://查找第一个文件
	while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();   //file://递归搜索其他的文件  
		if(!tempFind.IsDots())  // file://如果不是 ". "目录
		{
			char   foundFileName[1024];
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(1024));
			if(tempFind.IsDirectory())  // file://如果是目录，则递归地调用
			{   //file://DeleteDirectory
				char   tempDir[200];
				sprintf(tempDir, "%s\\%s",DirName,foundFileName);
				printf("DIR: %s\n", tempDir);
				TransDirectory(tempDir, out);
			}
			else
			{   //file://如果是文件则直接删除之
				char   tempFileName[1024];
				sprintf(tempFileName, "%s\\%s ",DirName,foundFileName);
				//printf("%s\n", tempFileName);
				out.push_back(string(tempFileName));
				//DeleteFile(tempFileName);
			}
		}
	}
	tempFind.Close();
	
	return   TRUE;
} 

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C_work_and_todoDlg dialog

C_work_and_todoDlg::C_work_and_todoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C_work_and_todoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C_work_and_todoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C_work_and_todoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C_work_and_todoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(C_work_and_todoDlg, CDialog)
	//{{AFX_MSG_MAP(C_work_and_todoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C_work_and_todoDlg message handlers

BOOL C_work_and_todoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void C_work_and_todoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void C_work_and_todoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR C_work_and_todoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void C_work_and_todoDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	vector<string> daily;
	//char path[1024]="c:\\_work_and_todo_keyword";
	char path[1024]="c:\\_pre_cache";
	for(int i=0; i<=26; i++)
	{
		path[0]++;
		if(_access(path, 0) == -1 )
		{

		}
		else
		{
		//	MessageBox(CString("日记目录在")+path) ; 
			TransDirectory(path, daily);
		}
	}
	CString pattern;// GetText(IDC_EDIT1);
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(pattern);
	CListBox *ptr;
	ptr =(CListBox*)GetDlgItem(IDC_LIST1);
	//MessageBox(pattern);
	for(vector<string>::iterator it=daily.begin(); it!= daily.end(); it++)
	{
		if(strstr((*it).c_str(), pattern))
		{
			ptr->AddString((*it).c_str());
		}
	}
}

void C_work_and_todoDlg::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	CListBox *ptr;
	char path[1024];
	ptr =(CListBox*)GetDlgItem(IDC_LIST1);
	int cur=ptr->GetCurSel();
	ptr->GetText(cur, path);

//	::ShellExecute(this->GetSafeHwnd(),"explore",path,NULL,path,SW_SHOW);

	ShellExecute(NULL,_T("open"),path,NULL,NULL,SW_SHOW);
//	ShellExecute(NULL,_T("explore"),path,NULL,NULL,SW_SHOW);	


//	MessageBox(path);
	
}
