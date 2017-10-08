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

	//ֻ����һ��ʵ��
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
	//ʹ�ð�ť�˵�
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
	m_pMainWnd->SetWindowText("ÿ������");

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
"ÿ������ 6.0\t|"
"�������ߣ�Acinonyx\t|"
"E-mail: acinonyx@vip.sina.com\t||"

"�ÿ�����ѡ�ʹ��˵�� ��\t|"

"���˵����������������������������������\t||"

"    ������Ҫϵͳ��ʲôʱ��������Ӧ����Щ\r|"
"ʲô�¡����Զ�����һ�����򡢻��Զ��ر�һ\r|"
"������ʱ�����ǵ��������ڴ�����һ�����ֻ�\r|"
"Ӣ���˯�������𴲶��õ����Զ��رյ����\r|"
"�£���������������;����Щ���������԰�\r|"
"��쵽����д�������ĳ�������Ϊ�ҵļ���\r|"
"�Ƚϲ��������һ��Ӣ��˯�������Ծ�����\r|"
"д������һ������                      \r|"
"    �����������Windows 95/98/NT4/2000/ \r|"
"XP/2003                                 \r||"
"ʹ�÷�����                              \t||"
"1�� �Զ����У�                          \r||"
"    �ó������к����ע�����Run�����һ \r|"
"    ��ֵ������ÿ����������ʱ�����Զ�����\r|"
"    ������ȡ���Զ����У��ɵ��ѡ��˵���\r|"
"    ���Զ����С�������ȡ���Զ����С�    \r||"
"2�� ѡ�                              \r||"
"    ��ѡ��˵����������˵����ɷֱ�����\r|"
"    �Ƿ���÷�����ʾ���Ƿ񽫳���һֱ����\r|"
"    ���ˡ�������������������������������\r||"
"3�� �Զ��ػ������� ������ ��������������\r||"
"    �ŵ�ϵͳ��������״̬ʱ����Ҫѡ�񡰹�\r|"
"    ��������������ע����������Ҫ���á�ǿ\r|"
"    �ơ���ʽ����ϵͳδ��������״̬����\r|"
"    �۲��ú��ַ�ʽ��                  ��\r||"
"    �ơ�Shut down����ť����ֱ�ӡ�ǿ�ơ� \r|"
"    �򡰷�ǿ�ơ����С��ػ�������������ע\r|"
"    ��������������������������          \r||"
"4�� Ӧ�ó������ѣ� ���� ������          \r||"
"    �ſ����Զ�����һ��Ӧ�ó��򡢻�������\r|"
"    ��������.doc��.txt�ļ��ȡ�          \r||"
"    �Ƶ�һ�����Ѵ������ڵ�ʱ���������\r|"
"    �ϴιر�ʱ�䣨�����ǹػ�ʱ���ͱ�����\r|"
"    ��ʱ����������һ�����ѣ����������ʱ\r|"
"    �ͻ�����������ѡ�                  \r|"
"        �������ϴιرձ�������2003-05-18\r|"
"    16:00������һ���������õ�ʱ����     \r|"
"    2003-05-18 17:00�����ҽ������Ͽ���ʱ\r|"
"    ���Զ����ѡ�                        \r|"
"        �����ʱ�������õ���ÿ�����ѵĻ�\r|"
"    ���Ͳ����������ˡ���������          \r||"
"5�� ��Ϣ���ѣ����� ������������         \r||"
"    �ŵ�����һ�����ѣ�ʱ�䵽ʱ���Զ�����\r|"
"    һ���Ի�����ʾ�������ݣ���Ϣ�ĳ���\r|"
"    ���255���ֽڡ�����������         \r||"
"    �Ƶ�һ�����Ѵ������ڵ�ʱ���������\r|"
"    �ϴιر�ʱ�䣨�����ǹػ�ʱ���ͱ�����\r|"
"    ��ʱ����������һ�����ѣ����������ʱ\r|"
"    �ͻ�����������ѡ���������Ӧ�ó���\r|"
"    ������һ���ġ�������    ��          \r||"
"6�� ��ʱ�رս��̣� ���� ������          \r||"
"    �����һ����ʱ�رյ�����ʱ���ᵯ��һ\r|"
"    ���Ի�����ʾϵͳ���е����н��̣���\r|"
"    ��ѡ���κν��̡�����Ȼ��ϵͳ��������\r|"
"    �������ġ���ʵֻҪ����������������\r|"
"    �����Ľ�������Ϳ��Խ�������������\r|"
"    �����ﲻ�ܽ����Ľ�������Ҳ���޷�����\r|"
"    �ģ��ҿɲ���Ū�ô��ϵͳ�������Ǻǡ�\r|"
"    �Ƶ�һ����ʱ�رյ��������к󣬻��Զ�\r|"
"    ɾ���������ѡ����ҵ�����رպ󲻻ᱣ\r|"
"    ���������õ����ѵġ�������          \r||"
"7�� ��ʱ����ʼ��� ���� ������          \r||"
"    �����ö�ʱ����������䣬�������ʼ���\r|"
"    ����ʾ�������ﹲ�ж��ٷ����ʼ������\r|"
"    ����ʽ���ڿɴ�Ĭ���ʼ�����      \r||"
"������������������������Acinonyx��������\r|"
"������������������������2005��11�� �� ��\r|||"
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
