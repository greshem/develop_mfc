// Remind.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "Remind.h"

#include "MainFrm.h"
#include "RemindDoc.h"
#include "RemindView.h"

#include "./library/HyperLink.h"
#include "./library/CreditStatic.h"
#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define one "0xbe8e2ce1, 0xdab6, 0x11d6, 0xad, 0xd0, 0x0, 0xe0, 0x4c, 0x53, 0xf6, 0xe6"
//HANDLE handle;

extern CheckMail *maillist;
extern char m_sInifilename[128];
extern char m_spath[128];
/////////////////////////////////////////////////////////////////////////////
// CRemindApp

BEGIN_MESSAGE_MAP(CRemindApp, CWinApp)
	//{{AFX_MSG_MAP(CRemindApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemindApp construction

CRemindApp::CRemindApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRemindApp object

CRemindApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRemindApp initialization

BOOL CRemindApp::InitInstance()
{
	char path[MAX_PATH];
	char progname[32];

	memset(path, 0, sizeof(path));
	memset(progname, 0, sizeof(progname));
	GetModuleFileName(NULL,path,MAX_PATH);

	strcpy(progname, strrchr(path,'\\') + 1);
	(strrchr(path,'\\'))[1] = 0;
	strcpy(m_spath, path);

	//只运行一个实例
	HANDLE handle;
	handle=::CreateMutex(NULL, FALSE, progname);
	if(GetLastError()==ERROR_ALREADY_EXISTS)	
	{
		return FALSE;
	}

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	sprintf(m_sInifilename, "%sremind.ini", m_spath);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CRemindDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CRemindView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	
	// Dispatch commands specified on the command line
	//使用按钮菜单
	CMenu* pMenu = m_pMainWnd->GetMenu();
	if (pMenu)pMenu->DestroyMenu();
	HMENU hMenu = ((CMainFrame*) m_pMainWnd)->NewMenu();
	pMenu = CMenu::FromHandle( hMenu );
	m_pMainWnd->SetMenu(pMenu);
	((CMainFrame*)m_pMainWnd)->m_hMenuDefault = hMenu;

	// The one and only window has been initialized, so show and update it.
	//m_pMainWnd->ShowWindow(SW_SHOW);
	//m_pMainWnd->ShowWindow(SW_HIDE);
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->SetWindowText("每日提醒");

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	CCreditStatic m_static;

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_sHelp;
	CHyperLink	m_ctrlMail;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_sHelp = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDTHELP, m_sHelp);
	DDX_Control(pDX, IDC_TXTMAIL, m_ctrlMail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CRemindApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CRemindApp message handlers


int CRemindApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	OnCloseProg();	    
	//CloseHandle(handle);
	return CWinApp::ExitInstance();
}

char *pArrCredit = {
"每日提醒 6.0\t|"
"软件设计者：Acinonyx\t|"
"E-mail: acinonyx@vip.sina.com\t||"

"★“每日提醒”使用说明 ★\t|"

"软件说明：　　　　　　　　　　　　　　　\t||"

"    当你需要系统在什么时候提醒你应该作些\r|"
"什么事、或自动运行一个程序、或自动关闭一\r|"
"个进程时、或是当你想躺在床上听一下音乐或\r|"
"英语后睡觉懒得起床而让电脑自动关闭的情况\r|"
"下，这个软件就有了用途。这些事它都可以帮\r|"
"你办到。我写这个程序的初衷是因为我的记性\r|"
"比较差，而且想听一下英语睡觉，所以就想着\r|"
"写了这样一个程序。                      \r|"
"    本软件适用于Windows 95/98/NT4/2000/ \r|"
"XP/2003                                 \r||"
"使用方法：                              \t||"
"1、 自动运行：                          \r||"
"    该程序运行后会在注册表里Run下添加一 \r|"
"    键值，这样每次启动机器时都会自动运行\r|"
"    ，若想取消自动运行，可点击选项菜单下\r|"
"    “自动运行”，即可取消自动运行。    \r||"
"2、 选项：                              \r||"
"    “选项”菜单下有两个菜单，可分别设置\r|"
"    是否采用蜂鸣提示、是否将程序一直处于\r|"
"    顶端。　　　　　　　　　　　　　　　\r||"
"3、 自动关机：　　 　　　 　　　　　　　\r||"
"    ⑴当系统处于锁定状态时，若要选择“关\r|"
"    机”“重启”“注销”，则需要采用“强\r|"
"    制”方式。若系统未处于锁定状态，则不\r|"
"    论采用何种方式。                  　\r||"
"    ⑵“Shut down”按钮用于直接“强制” \r|"
"    或“非强制”进行“关机”“重启”“注\r|"
"    销”。　　　　　　　　　　          \r||"
"4、 应用程序提醒： 　　 　　　          \r||"
"    ⑴可以自动运行一个应用程序、或其他文\r|"
"    件，比如.doc、.txt文件等。          \r||"
"    ⑵当一个提醒带有日期的时候，如果你在\r|"
"    上次关闭时间（可以是关机时）和本次启\r|"
"    动时间中设置了一个提醒，则程序启动时\r|"
"    就会运行这个提醒。                  \r|"
"        比如我上次关闭本程序是2003-05-18\r|"
"    16:00，我有一个提醒设置的时间是     \r|"
"    2003-05-18 17:00，则我今天早上开机时\r|"
"    会自动提醒。                        \r|"
"        但如果时间里设置的是每天提醒的话\r|"
"    ，就不是这样的了。　　　　          \r||"
"5、 消息提醒：　　 　　　　　　         \r||"
"    ⑴当设置一个提醒，时间到时会自动弹出\r|"
"    一个对话框，显示提醒内容，消息的长度\r|"
"    最长是255个字节。　　　　　         \r||"
"    ⑵当一个提醒带有日期的时候，如果你在\r|"
"    上次关闭时间（可以是关机时）和本次启\r|"
"    动时间中设置了一个提醒，则程序启动时\r|"
"    就会运行这个提醒。这个情况和应用程序\r|"
"    提醒是一样的。　　　    　          \r||"
"6、 定时关闭进程： 　　 　　　          \r||"
"    ⑴添加一个定时关闭的提醒时，会弹出一\r|"
"    个对话框，显示系统运行的所有进程，可\r|"
"    以选择任何进程。（当然：系统进程是无\r|"
"    法结束的。其实只要是任务管理器里可以\r|"
"    结束的进程这里就可以结束，如果任务管\r|"
"    理器里不能结束的进程这里也是无法结束\r|"
"    的，我可不想弄得大家系统崩溃。呵呵。\r|"
"    ⑵当一个定时关闭的提醒运行后，会自动\r|"
"    删除本条提醒。而且当程序关闭后不会保\r|"
"    存您所设置的提醒的。　　　          \r||"
"7、 定时检查邮件： 　　 　　　          \r||"
"    可设置定时检查您的邮箱，如有新邮件则\r|"
"    会提示您邮箱里共有多少封新邮件。点击\r|"
"    弹出式窗口可打开默认邮件程序。      \r||"
"　　　　　　　　　　　　Acinonyx　　　　\r|"
"　　　　　　　　　　　　2005年11月 　 　\r|||"
};

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlMail.SetURL("mailto:acinonyx@vip.sina.com");

	m_static.SubclassDlgItem(IDC_EDTHELP,this);
	m_static.SetCredits(pArrCredit,'|');
	m_static.SetColor(BACKGROUND_COLOR, RGB(0,0,0));
	m_static.SetTransparent();
	m_static.StartScrolling();

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
