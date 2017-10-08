// makecab_mfc_guiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cabinet.h"
#include "makecab_mfc_gui.h"
#include "makecab_mfc_guiDlg.h"

#pragma warning(disable: 4097 4100 4121 4127 4146 4244 4245 4511 4512 4701 4800 4996 4786)

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



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
		IsFinded=(BOOL)tempFind.FindNextFile();   
		if(!tempFind.IsDots())  // file://如果不是 ". "目录
		{
			char   foundFileName[1024];
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(1024));
			if(tempFind.IsDirectory() && (tempFind.GetFileName() != ".svn") )  
			{   
				char   tempDir[200];
				sprintf(tempDir, "%s\\%s",DirName,foundFileName);
				//printf("DIR: %s\n", tempDir);
				out.push_back(string(tempDir));
				TransDirectory(tempDir, out);
			}
			else
			{   
				//char   tempFileName[1024];
				//sprintf(tempFileName, "%s\\%s ",DirName,foundFileName);
				//out.push_back(string(tempFileName));
				
			}
		}
	}
	tempFind.Close();
	
	return   TRUE;
} 


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CMakecab_mfc_guiDlg dialog

CMakecab_mfc_guiDlg::CMakecab_mfc_guiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMakecab_mfc_guiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakecab_mfc_guiDlg)
	m_strPath = _T("E:\\PartImage\\Ethernet_drv");
	//m_strPath = "E:\\PartImage\\Ethernet_drv";
	m_strCatOutput = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMakecab_mfc_guiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakecab_mfc_guiDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strPath);
	DDX_Text(pDX, IDC_EDIT2, m_strCatOutput);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMakecab_mfc_guiDlg, CDialog)
	//{{AFX_MSG_MAP(CMakecab_mfc_guiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_GEN_CAB_CONF, OnGenCabConf)
	ON_BN_CLICKED(IDC_GEN_CAB, OnGenCab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakecab_mfc_guiDlg message handlers

BOOL CMakecab_mfc_guiDlg::OnInitDialog()
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
	if(m_strPath!="")
	{
		//	TransDirectory(m_strPath, m_fileList);
		ShowAllFile();
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMakecab_mfc_guiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMakecab_mfc_guiDlg::OnPaint() 
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
HCURSOR CMakecab_mfc_guiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMakecab_mfc_guiDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
		CCabinet cab;
	/*
	cab.CreateCabinet ("c:\\AUTOEXEC.cab");
	cab.AddFile2Cab ("c:\\AUTOEXEC.BAT");
	cab.AddFile2Cab ("c:\\boot.ini");
	cab.FlushCab ();
	*/
	//cab.Compress ("fci.lib", NULL);
	//cab.Decompress ("E:\\test.cab",NULL);


	if(m_strCatOutput=="")
	{
		MessageBox("cab 输出文件为空\n");
		return ;
	}
	CEdit *ptrEdit=(CEdit *)GetDlgItem(IDC_EDIT2);
	char buffer[1024];
	ptrEdit->GetWindowText(buffer, sizeof(buffer));
//	ptrEdit->GetLine(0, buffer, sizeof())
//	MessageBox()
	if(cab.CreateCabinet (buffer) == FALSE)
	{
		MessageBox("生成cab 文件失败");
		return ;
	}



	for(vector<string>::iterator it=m_fileList.begin(); it!= m_fileList.end(); it++)
	{
		cab.AddFile2Cab((char *)(*it).c_str());	
	}

	if(cab.FlushCab ())
	{
		MessageBox("生成cab成功\n");
	}
	GenMakecabConf();
}

void CMakecab_mfc_guiDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
	char   strFilePath[225]; //CSIDL_DESKTOPDIRECTORY   
	LPITEMIDLIST   pidlBeginAt,   pidlDestination;   
	SHGetSpecialFolderLocation(HWND_DESKTOP,   CSIDL_DRIVES,   &pidlBeginAt);//   取得开始菜单或桌面的PIDL   
	BROWSEINFO   BrInfo;   
	ZeroMemory(&BrInfo,   sizeof(BrInfo));   
	BrInfo.hwndOwner =   HWND_DESKTOP;//可不用   
	BrInfo.pidlRoot =   pidlBeginAt;   
	BrInfo.lpszTitle =   "请选择一个文件夹：";   
	pidlDestination =   SHBrowseForFolder(&BrInfo);//浏览文件夹   
	if(NULL   ==   pidlDestination)//用户选择了取消按钮   
		return;   
	SHGetPathFromIDList(pidlDestination,   strFilePath);//   把PIDL转换为路径名   
	//替换掉(IDC_EDIT_MAIN_DATA_PATH)
	GetDlgItem(IDC_EDIT1)->SetWindowText(strFilePath);
	UpdateData();
	m_fileList.clear();
	//TransDirectory(strFilePath, m_fileList);
	ShowAllFile();

}

void CMakecab_mfc_guiDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(FALSE, "cab");
	if(dlg.DoModal()==IDOK)
	{
		CString tmp=dlg.GetPathName();
		GetDlgItem(IDC_EDIT2)->SetWindowText(tmp);
	}
}


void CMakecab_mfc_guiDlg::GenMakecabConf() 
{
	//CFile file;
	//file.Open("output.txt", CFile::modeReadWrite);
	//CFile::modeWrite|CFile::modeCreate
	CFile file("output.txt", CFile::modeWrite|CFile::modeCreate);

	CString log;

	for(vector<string>::iterator it=m_fileList.begin(); it!= m_fileList.end(); it++)
	{

		file.Write((*it).c_str(), (*it).size());
		file.Write("\r\n", 2);

	}
	//file.Write("qianqian", 8);
	file.Flush();
	file.Close();
}



void CMakecab_mfc_guiDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	char tmp[1024];
	GetCurrentDirectory(sizeof(tmp), tmp);
	MessageBox(tmp);

}

void CMakecab_mfc_guiDlg::OnGenCabConf() 
{
	// TODO: Add your control notification handler code here
	unsigned long  ret;
	//CFile file("output.txt", CFile::modeWrite|CFile::modeCreate);
//	CFile cabCmd("tmp.cmp", CFile::modeWrite|CFile::modeCreate);
//	ofstream cabCmd("tmp.cmp", ios::out||ios::trunc);
	ofstream cabCmd("tmp.cmd");

	if(cabCmd.bad())
	{
		MessageBox("tmp.cmd没有生成\n");
	}
	AllocConsole();//打开控制台窗口
	HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);//得到控制台句
	//20101029
	//greshem, 这里比较重要， printf cout cin 发挥作用，需要重新绑定一下 stdout stdin 到WINDOWS 的句柄， 
	freopen("CONOUT$","w+t",stdout);
	freopen("CONIN$","r+t",stdin); 

	WriteFile(hOutput,"hello",strlen("hello"),&ret,0);
	//////////////////////////////////////////////////////////////////////////
	cout<<".OPTION EXPLICIT"<<endl;
	cout<<".Set CabinetNameTemplate=.\\Package_drives.cab"<<endl;
	cout<<".set DiskDirectoryTemplate=."<<endl;
	cout<<".Set CompressionType=MSZIP"<<endl;
	cout<<".Set MaxCabinetSize=0"<<endl;
	cout<<".Set MaxDiskFileCount=0"<<endl;
	cout<<".Set MaxDiskSize=0"<<endl;
	cout<<".Set UniqueFiles=\"OFF\""<<endl;
	cout<<".Set Cabinet=On"<<endl;

	cout<<".Set DiskDirectory1="<<m_strPath.GetBuffer(1024)<<endl;
	cout<<".Set DestinationDir=\"\""<<endl;


	//////////////////////////////////////////////////////////////////////////
	cabCmd<<".OPTION EXPLICIT"<<endl;
	cabCmd<<".Set CabinetNameTemplate=.\\Package_drives.cab"<<endl;
	cabCmd<<".set DiskDirectoryTemplate=."<<endl;
	cabCmd<<".Set CompressionType=MSZIP"<<endl;
	cabCmd<<".Set MaxCabinetSize=0"<<endl;
	cabCmd<<".Set MaxDiskFileCount=0"<<endl;
	cabCmd<<".Set MaxDiskSize=0"<<endl;
	cabCmd<<".Set UniqueFiles=\"OFF\""<<endl;
	cabCmd<<".Set Cabinet=On"<<endl;
	
	cabCmd<<".Set DiskDirectory1="<<m_strPath.GetBuffer(1024)<<endl;
	cabCmd<<".Set DestinationDir=\"\""<<endl;

	//历遍所有的目录
	for(vector<string>::iterator it=m_fileList.begin(); it!= m_fileList.end(); it++)
	{
	//	cout<<(*it)<<endl;

		string tmp(*it);
		tmp+="\"\r\n";
		//WriteFile(hOutput, tmp.c_str(), tmp.size(),&ret, 0);
		tmp.replace(tmp.begin(), tmp.begin()+m_strPath.GetLength()+1, "");

		printf("\n.Set DestinationDir %s", tmp.c_str());
		cabCmd<<"\n.Set DestinationDir=\"" << tmp;

		CFileFind find;
		string pattern(*it);
		pattern+="\\*";
		find.FindFile(pattern.c_str());
		while(find.FindNextFile()  ) 
		{
			if(! find.IsDots() && !find.IsDirectory())
			{
				
				printf("\"%s\\%s\"\n",(*it).c_str(),  find.GetFileName());
				cabCmd<<"\""<<(*it)<<"\\"<<find.GetFileName().GetBuffer(1024)<<"\"\n";
				//WriteFile(hOutput, (*it).c_str(), (*it).size(), &ret, 0);
				//WriteFile(hOutput, find.GetFileName().GetBuffer(1024), find.GetFileName().GetLength(), &ret, 0);
				//WriteFile(hOutput, "\r\n", 2, &ret, 0);
			}
		}
		//while(FineNextFile) 会漏掉最后一个文件， 这里做一下处理 
		if(! find.IsDirectory()) 
		{
			printf("\"%s\\%s\"\n",(*it).c_str(),  find.GetFileName());
			cabCmd<<"\""<<(*it)<<"\\"<<find.GetFileName().GetBuffer(1024)<<"\"\n";
		}
		find.Close();
	}
	printf("已经生成conf, 按任意按钮,继续生成cab......");
	getchar();
	FreeConsole();

	WinExec("makecab.exe /f tmp.cmd", TRUE);

}


void CMakecab_mfc_guiDlg::ShowAllFile()
{
	TransDirectory(m_strPath, m_fileList);
	CListBox *ptrListbox=(CListBox *)GetDlgItem(IDC_LIST1);
	ptrListbox->ResetContent();
	for(vector<string>::iterator it=m_fileList.begin(); it!= m_fileList.end(); it++)
	{
		ptrListbox->AddString((*it).c_str()) ;
	}
}

void CMakecab_mfc_guiDlg::OnGenCab() 
{
	// TODO: Add your control notification handler code here

}
