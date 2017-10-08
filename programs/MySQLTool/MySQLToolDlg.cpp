// MySQLToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "log.h"
#include "MySQLTool.h"
#include "MySQLToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CMySQLToolDlg dialog

CMySQLToolDlg *CMySQLToolDlg::sm_pDlg = NULL;
CMySQLToolDlg::CMySQLToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySQLToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMySQLToolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nSQLCount		= 0;
	m_arySQL		= NULL;
	m_nThreadCount	= 0;
	m_aryThread		= NULL;
	m_aryRunInfo	= NULL;
	sm_pDlg			= this;
}

CMySQLToolDlg::~CMySQLToolDlg()
{
	FreeData();
}

void CMySQLToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySQLToolDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMySQLToolDlg, CDialog)
	//{{AFX_MSG_MAP(CMySQLToolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySQLToolDlg message handlers

BOOL CMySQLToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
//	log::Instance()->logger("初始化\n");
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
	
	SetDlgItemText(IDC_EDIT_IP, "192.168.1.73");
	SetDlgItemText(IDC_EDIT_PORT, "3306");
	SetDlgItemText(IDC_EDIT_DBNAME, "sf_mirror");
	SetDlgItemText(IDC_EDIT_USER, "root");
	SetDlgItemText(IDC_EDIT_PSW, "tgbygv");
	SetDlgItemText(IDC_EDIT_THREADCOUNT, "30");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMySQLToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMySQLToolDlg::OnPaint() 
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
HCURSOR CMySQLToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMySQLToolDlg::OnOK() 
{
}

void CMySQLToolDlg::OnCancel() 
{
	if (!GetDlgItem(IDC_BTN_START)->IsWindowEnabled())
	{
		return;
	}

	CString strBtnText;
	GetDlgItemText(IDC_BTN_START, strBtnText);
	
	if (strBtnText == "停止")
	{
		OnBtnStart();
	}

	CDialog::OnCancel();
}

void CMySQLToolDlg::ShowResult()
{
	
}

bool CMySQLToolDlg::CreateData(void)
{
	FreeData();

	GetDlgItemText(IDC_EDIT_IP, m_strIP);
	m_nPort = GetDlgItemInt(IDC_EDIT_PORT);
	GetDlgItemText(IDC_EDIT_DBNAME, m_strDBName);
	GetDlgItemText(IDC_EDIT_USER, m_strUser);
	GetDlgItemText(IDC_EDIT_PSW, m_strPsw);

	char szBuf[2048] = {0};
	GetDlgItemText(IDC_EDIT_SQL, szBuf, sizeof(szBuf));

	char seps[] = ";";
	char *token;
	
	int nSQLCount = 0;
	token = strtok(szBuf, seps);
	while (token != NULL) 
	{
		nSQLCount++;
		token = strtok(NULL, seps);
	}

	if (nSQLCount <= 0)
	{
		return false;
	}

	m_arySQL = new char *[nSQLCount];
	if (m_arySQL == NULL)
	{
		return false;
	}

	memset(m_arySQL, 0, sizeof(char *) * nSQLCount);

	GetDlgItemText(IDC_EDIT_SQL, szBuf, sizeof(szBuf));

	int i = 0;
	token = strtok(szBuf, seps);
	while (token != NULL && i < nSQLCount) 
	{
		m_arySQL[i] = new char[strlen(token) + 1];
		
		if (m_arySQL[i] == NULL)
		{
			m_nSQLCount = i;
			return false;
		}

		strcpy(m_arySQL[i], token);
		token = strtok(NULL, seps);
		i++;
	}

	m_nSQLCount = i;

	int nThreadCount = GetDlgItemInt(IDC_EDIT_THREADCOUNT);
	if (nThreadCount <= 0 || nThreadCount > 1024)
	{
		return false;
	}

	m_aryThread = new HANDLE[nThreadCount];
	if (m_aryThread == NULL)
	{
		return false;
	}

	memset(m_aryThread, 0, sizeof(HANDLE) * nThreadCount);
	m_nThreadCount = nThreadCount;

	m_aryRunInfo = new tagRunInfo *[m_nThreadCount];
	if (m_aryRunInfo == NULL)
	{
		return false;
	}

	memset(m_aryRunInfo, 0, sizeof(tagRunInfo *) * m_nThreadCount);
	for (i = 0; i < m_nThreadCount; i++)
	{
		m_aryRunInfo[i] = new tagRunInfo[m_nSQLCount];

		if (m_aryRunInfo[i] == NULL)
		{
			return false;
		}

		memset(m_aryRunInfo[i], 0, sizeof(tagRunInfo) * m_nSQLCount);
	}
		
	return true;
}

void CMySQLToolDlg::FreeData(void)
{
	int i;
	
	if (m_arySQL != NULL)
	{
		for (i = 0; i < m_nSQLCount; i++)
		{
			if (m_arySQL[i] != NULL)
			{
				delete[] m_arySQL[i];
			}
		}
		
		delete[] m_arySQL;
		m_arySQL = NULL;
	}
	
	if (m_aryRunInfo != NULL)
	{
		for (i = 0; i < m_nThreadCount; i++)
		{
			if (m_aryRunInfo[i] != NULL)
			{
				delete[] m_aryRunInfo[i];
			}
		}
		
		delete[] m_aryRunInfo;
		m_aryRunInfo = NULL;
	}

	if (m_aryThread != NULL)
	{
		delete[] m_aryThread;
		m_aryThread = NULL;
	}
	
	m_nSQLCount = 0;
	m_nThreadCount = 0;
}

void CMySQLToolDlg::ClearResult()
{
	SetDlgItemText(IDC_EDIT_RESULT, "");
}

DWORD WINAPI CMySQLToolDlg::RunThread(void *lpParam)
{
	tagRunInfo *aryRunInfo = (tagRunInfo *)lpParam;
	CMySQLToolDlg *pDlg = sm_pDlg;

	MYSQL *mysql = mysql_init(NULL);
	if (mysql == NULL)
	{
		return 0;
	}
	
	my_bool bReconnect = true;
	mysql_options(mysql, MYSQL_OPT_RECONNECT, (const char*)&bReconnect);
	
	if (mysql_real_connect(mysql, pDlg->m_strIP, pDlg->m_strUser, pDlg->m_strPsw, 
		pDlg->m_strDBName, pDlg->m_nPort, NULL, 0) == NULL)
	{
		mysql_close(mysql);
		return 0;
	}
	
	srand(GetTickCount());

	while (!pDlg->m_bStop)
	{
		int nIndex = rand() % pDlg->m_nSQLCount;
		int nOldTime = GetTickCount();

		if (mysql_query(mysql, pDlg->m_arySQL[nIndex]) == 0)
		{
			MYSQL_RES *results = mysql_store_result(mysql);
			if (results != NULL)
			{
				aryRunInfo[nIndex].nOpRecCount += (int)mysql_num_rows(results);
				
				MYSQL_ROW record;
				while((record = mysql_fetch_row(results))) 
				{      
				} 
				
				mysql_free_result(results);
			}

			aryRunInfo[nIndex].nSuccessCount++;
		}

		int nSpendTime = abs(GetTickCount()-nOldTime);

		if (aryRunInfo[nIndex].nMinTime == 0)
		{
			aryRunInfo[nIndex].nMinTime = nSpendTime;
		}
		else
		{
			aryRunInfo[nIndex].nMinTime = min(aryRunInfo[nIndex].nMinTime, nSpendTime);
		}
		
		aryRunInfo[nIndex].nMaxTime = max(aryRunInfo[nIndex].nMaxTime, nSpendTime); 
		aryRunInfo[nIndex].nSpendTime += nSpendTime;

		aryRunInfo[nIndex].nQueryCount++;

		Sleep(30 + rand() % 10);
	}
	
	mysql_close(mysql);

	return 0;
}

void CMySQLToolDlg::OnBtnStart() 
{
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	
	CString strBtnText;
	GetDlgItemText(IDC_BTN_START, strBtnText);

	if (strBtnText == "开始")
	{
		if (!CreateData())
		{
			FreeData();
			GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
			return;
		}

		ClearResult();

		m_bStop = false;

		DWORD dwThreadId;

		int i;
		for (i = 0; i < m_nThreadCount; i++)
		{
			m_aryThread[i] = CreateThread(NULL, 1024 * 10, RunThread, m_aryRunInfo[i], 0, &dwThreadId);
		}

		SetDlgItemText(IDC_BTN_START, "停止");
	}
	else
	{
		CString strResult;
		CString strText;

		m_bStop = true;

		int i, j;
		for (i = 0; i < m_nThreadCount; i++)
		{
			if (m_aryThread[i] == NULL)
			{
				strText.Format("线程[%d] 没有执行！\r\n\r\n", i + 1);
				strResult += strText;
				continue;
			}

			MSG msg;
			int nTime = 0;
			bool bNorExit = true;
			
			while (WaitForSingleObject(m_aryThread[i], 50) != WAIT_OBJECT_0)
			{
				// 超时20秒, 则认为该线程已僵死.
				if (++nTime > 400)
				{
					TerminateThread(m_aryThread[i], 1);
					bNorExit = false;
					break;
				}

				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			CloseHandle(m_aryThread[i]);

			if (bNorExit)
			{
				strText.Format("线程[%d]\r\n", i + 1);
			}
			else
			{
				strText.Format("线程[%d] 已经僵死！\r\n", i + 1);
			}

			strResult += strText;

			for (j = 0; j < m_nSQLCount; j++)
			{
				strText.Format("语句[%d]\r\n", j + 1);
				strResult += strText;
				strText.Format("总的执行次数:%d次\r\n", m_aryRunInfo[i][j].nQueryCount);
				strResult += strText;
				strText.Format("成功执行次数:%d次\r\n", m_aryRunInfo[i][j].nSuccessCount);
				strResult += strText;
				strText.Format("总的耗费时间:%dms\r\n", m_aryRunInfo[i][j].nSpendTime);
				strResult += strText;
				strText.Format("最短一次时间:%dms\r\n", m_aryRunInfo[i][j].nMinTime);
				strResult += strText;
				strText.Format("最长一次时间:%dms\r\n", m_aryRunInfo[i][j].nMaxTime);
				strResult += strText;

				int nAveRecCount = 0;
				if (m_aryRunInfo[i][j].nQueryCount > 0)
				{
					nAveRecCount = m_aryRunInfo[i][j].nOpRecCount / m_aryRunInfo[i][j].nQueryCount;
				}

				strText.Format("平均记录条数:%d条\r\n", nAveRecCount);
				strResult += strText;

				int nAveTime = 0;
				if (m_aryRunInfo[i][j].nQueryCount > 0)
				{
					nAveTime = m_aryRunInfo[i][j].nSpendTime / m_aryRunInfo[i][j].nQueryCount;
				}
				
				strText.Format("平均花费时间:%dms\r\n", nAveTime);
				strResult += strText;

				if (j == m_nSQLCount-1)
				{
					strResult += "\r\n";
				}
			}
		}

		SetDlgItemText(IDC_EDIT_RESULT, strResult);

		FreeData();

		SetDlgItemText(IDC_BTN_START, "开始");
	}

	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
}
