// DiskCleanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DiskClean.h"
#include "DiskCleanDlg.h"
//#include "SystemInfo.h"
//#include "DiskSerial.h"
#include <dos.h>
#include <direct.h>
//#include "Product.h"
#include "SelectFile.h"
#include <afxmt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD g_dWSel;

CDiskCleanDlg* gpMainWnd;
CString gPath,gPath1;
BOOL gbRuning=FALSE;

#define WM_MYEXIT WM_USER + 1
#define WM_ANSWER WM_USER + 2


UINT ThreadsProc(LPVOID pParam) ;

HANDLE ghThreadExitEvent;
	

void DealRabbishScan(CString path);
void DealWithFile(CString FilePath,CString FileName);
void DeleteZeroFile(CString path);
	

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
	virtual BOOL OnInitDialog();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiskCleanDlg dialog

CDiskCleanDlg::CDiskCleanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiskCleanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiskCleanDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nDrvCount=0;

	g_dWSel=0xFFFFFFFF;
	gpMainWnd=this;
	//
	//
	ghThreadExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		
}

void CDiskCleanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiskCleanDlg)
	DDX_Control(pDX, IDC_LIST2, m_ctlListFile1);
	DDX_Control(pDX, IDC_LIST1, m_ctlListFile);
	DDX_Control(pDX, IDC_COMBO_DRIVE, m_ctlComboDrive);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDiskCleanDlg, CDialog)
	//{{AFX_MSG_MAP(CDiskCleanDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(ID_APP_ABOUT, OnAppAbout)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MYEXIT,OnExit)  
	ON_MESSAGE(WM_ANSWER,OnAnswer)  
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVE, &CDiskCleanDlg::OnCbnSelchangeComboDrive)
	ON_BN_CLICKED(IDC_BUTTON1, &CDiskCleanDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiskCleanDlg message handlers

BOOL CDiskCleanDlg::OnInitDialog()
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

	GetSysDriver();
	m_ctlComboDrive.SetCurSel(0);	
	//for(int i=0;i<26;i++)
	//
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDiskCleanDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDiskCleanDlg::OnPaint() 
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
HCURSOR CDiskCleanDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//得到硬盘驱动器盘符
void CDiskCleanDlg::GetSysDriver()
{
	UINT drvType=0;
	CString drv;
	char ch;
	for(ch='C';drvType!=1;ch++)
	{
		drv="X:\\";
		drv.SetAt(0,ch);
		drvType=GetDriveType(drv);
		if(drvType==DRIVE_FIXED){
			m_ctlComboDrive.AddString(drv);

		}
	}
}

//垃圾文件扫描
void DealRabbishScan(CString path)
{
	if(!gbRuning)return;
	chdir(path);				//更换当前目录
	gPath1=path;
	::SendMessage(gpMainWnd->m_hWnd ,WM_ANSWER, (WPARAM)2, (LPARAM)0);
	if(g_dWSel & 0x1)DealWithFile(path,"*.~*");
	if(g_dWSel & 0x2)DealWithFile(path,"*.ALT");
	if(g_dWSel & 0x4)DealWithFile(path,"*.FIX");
	if(g_dWSel & 0x8)DealWithFile(path,"*.PRV");
	if(g_dWSel & 0x10)DealWithFile(path,"*.SYD");
	if(g_dWSel & 0x20)DealWithFile(path,"*.$$$");
	if(g_dWSel & 0x40)DealWithFile(path,"*.CLN");
	if(g_dWSel & 0x80)DealWithFile(path,"*.GID");
	if(g_dWSel & 0x100)DealWithFile(path,"*.SAV");
	if(g_dWSel & 0x200)DealWithFile(path,"*.tmp");
	if(g_dWSel & 0x400)DealWithFile(path,"*.?~?");
	if(g_dWSel & 0x800)DealWithFile(path,"*.CYP");
	if(g_dWSel & 0x1000)DealWithFile(path,"*.LOO");
	if(g_dWSel & 0x2000)DealWithFile(path,"*.SCO");
	if(g_dWSel & 0x4000)DealWithFile(path,"*.UMB");
	if(g_dWSel & 0x8000)DealWithFile(path,"*.B?K");
	if(g_dWSel & 0x10000)DealWithFile(path,"*.ERR");
	if(g_dWSel & 0x20000)DealWithFile(path,"*.OLD");
	if(g_dWSel & 0x40000)DealWithFile(path,"*.SLK");
	if(g_dWSel & 0x80000)DealWithFile(path,"*.UBK");
	if(g_dWSel & 0x100000)DealWithFile(path,"*.00?");
	if(g_dWSel & 0x200000)DealWithFile(path,"*.ffa");
	if(g_dWSel & 0x400000)DealWithFile(path,"*.ffo");
	if(g_dWSel & 0x800000)DealWithFile(path,"*.ffl");
	if(g_dWSel & 0x1000000)DealWithFile(path,"*.T");
	if(g_dWSel & 0x2000000)DealWithFile(path,"*.ffx");
	//删除单个文件
	if(g_dWSel & 0x4000000)DealWithFile(path,"desktop.ini");
	if(g_dWSel & 0x8000000)DealWithFile(path,"folder.htt");

	//dsp dsw 文件 qzj
	if(g_dWSel & 0x10000000)DealWithFile(path,"*.dsp");
	if(g_dWSel & 0x20000000)DealWithFile(path,"*.dsw");
	//DeleteZeroFile(path);
	BOOL flag;
	CFileFind m_File;
	DWORD dwRes;
	flag=m_File.FindFile(NULL);
	while(flag && gbRuning)
	{
		dwRes=WaitForSingleObject(ghThreadExitEvent,0);
		if(dwRes==WAIT_OBJECT_0)
		{
			gbRuning=FALSE;
			break;
		}
		flag=m_File.FindNextFile();
		if(m_File.IsDirectory())
		{
			if(!m_File.IsDots())
			{

				path=m_File.GetFilePath();	
				//DeleteZeroFile(path);		
				//qzj是目录， 再进去， 递归一下。 
				DealRabbishScan(path);		
			}
		}
	}
	

	
}


//删除垃圾文件
void DealWithFile(CString FilePath,CString FileName)
{
	//((CListBox*)gpMainWnd->GetDlgItem(IDC_LIST1))->AddString(FilePath);
	CFileFind findfile;
	CString tFileName;
	CString Path;
	LV_ITEM lvitem;
	lvitem.mask  = LVIF_TEXT;
	//
	SetCurrentDirectory(FilePath) ;
	if(findfile.FindFile(FileName))
	{

		while(findfile.FindNextFile())
		{
			Path=findfile.GetFilePath();
			gPath=Path;
			tFileName = findfile.GetFileName();
			//DeleteFile(tFileName);
			::SendMessage(gpMainWnd->m_hWnd ,WM_ANSWER, (WPARAM)1, (LPARAM)0);
		}
		Path=findfile.GetFilePath();
		gPath=Path;
		tFileName = findfile.GetFileName();
		//DeleteFile(tFileName);
		::SendMessage(gpMainWnd->m_hWnd ,WM_ANSWER, (WPARAM)1, (LPARAM)0);
	}
}


//处理零字节文件
void DeleteZeroFile(CString path)
{
	//chdir(path);
	CString Path;
	//SetCurrentDirectory(path);
	CString ZeroFilename;
	CFileFind finder;
	BOOL bWorking=finder.FindFile("*.*");
	while(bWorking)
	{
		bWorking=finder.FindNextFile();
		if(!finder.IsDirectory())
		{
			if(finder.GetLength()==0)
			{
				Path=finder.GetFilePath();
				gPath=Path;
				::SendMessage(gpMainWnd->m_hWnd ,WM_ANSWER, (WPARAM)1, (LPARAM)0);
				ZeroFilename=(LPCTSTR)finder.GetFileName();
				//DeleteFile(ZeroFilename);
			}
		}
	}
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	
	//
	return TRUE;	

}


void CDiskCleanDlg::OnSelect() 
{
	CSelectFile dlg;
	dlg.m_dWSel=g_dWSel;
	if(dlg.DoModal()==IDOK)g_dWSel=dlg.m_dWSel;
}

void CDiskCleanDlg::OnAppAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}



UINT ThreadsProc(LPVOID pParam) 
{
	CString path;
	//
	CComboBox* pComboBox=(CComboBox*)gpMainWnd->GetDlgItem(IDC_COMBO_DRIVE);
	pComboBox->GetLBText(pComboBox->GetCurSel(),path);
	//
	DealRabbishScan(path);		//清除该目录的垃圾文件
	//DeleteZeroFile(path);		//清除该目录下长度为零的文件
	//
	if(gbRuning)::SendMessage(gpMainWnd->m_hWnd ,WM_MYEXIT, (WPARAM)0, (LPARAM)0);
	return 0;
}

LRESULT CDiskCleanDlg::OnExit(WPARAM wParam, LPARAM lParam)
{
	
	
	AfxMessageBox("处理完毕!",MB_OK |MB_ICONINFORMATION   );	
	//
	GetDlgItem(IDC_START)->EnableWindow(TRUE);	
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);	
	gbRuning=FALSE;
	//
	return 0;
}

LRESULT CDiskCleanDlg::OnAnswer(WPARAM wParam, LPARAM lParam)
{
	int nSel;
	int count;
	//
	nSel=(int)wParam;
	if(nSel==1){
		//count=m_ctlListFile.GetCount();
		//if(count>=5)m_ctlListFile.DeleteString(0);
		m_nFileNum++;
		CString str;
		str.Format("处理文件数: %d",m_nFileNum) ;
		GetDlgItem(IDC_STATICFILENUM)->SetWindowText(str);
		//
		m_ctlListFile.AddString(gPath);
	
	}
	else {
		m_nDirNum++;
		CString str;
		str.Format("检查目录数: %d",m_nDirNum) ;
		GetDlgItem(IDC_STATICDIRNUM)->SetWindowText(str);
		//
		count=m_ctlListFile1.GetCount();
		if(count>=5)m_ctlListFile1.DeleteString(0);
		m_ctlListFile1.AddString(gPath1);
		
	}
	
	return 0;
}


/*BOOL CDiskCleanDlg::DestroyWindow() 
{
	delete ghThreadExitEvent;
	//
	return CDialog::DestroyWindow();
}*/

void CDiskCleanDlg::OnStart() 
{
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
	//
	gbRuning=TRUE;
	m_nFileNum=0;
	CString str;
	str.Format("处理文件数: %d",m_nFileNum) ;
	GetDlgItem(IDC_STATICFILENUM)->SetWindowText(str);
	//
	m_nDirNum=0;
	str.Format("检查目录数: %d",m_nDirNum) ;
	GetDlgItem(IDC_STATICDIRNUM)->SetWindowText(str);
	//
	m_ctlListFile.ResetContent();
	m_ctlListFile1.ResetContent();
	//
	ResetEvent(ghThreadExitEvent);	
	m_pThread=AfxBeginThread(&ThreadsProc, 
					(LPVOID)NULL, THREAD_PRIORITY_NORMAL);
	
	
}

void CDiskCleanDlg::OnStop() 
{
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	//
	SetEvent(ghThreadExitEvent);	
}

void CDiskCleanDlg::OnCbnSelchangeComboDrive()
{
	// TODO: Add your control notification handler code here
}

void CDiskCleanDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	//第二种方式
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
	GetDlgItem(IDC_COMBO_DRIVE)->SetWindowText(strFilePath);


}
