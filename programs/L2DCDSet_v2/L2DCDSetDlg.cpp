// L2DCDSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "L2DCDSet.h"
#include "L2DCDSetDlg.h"

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
// CL2DCDSetDlg dialog

CL2DCDSetDlg::CL2DCDSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CL2DCDSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CL2DCDSetDlg)
	m_strOpenTime = _T("");
	m_strCloseTime = _T("");
	m_bBackupDataLine = FALSE;
	m_bBackupMinuteLine = FALSE;
	m_bHKStockExchange = FALSE;
	m_bSpecialStockExchange = FALSE;
	m_strDelayMinute = _T("");
	m_strReadDBFrequency = _T("");
	m_strBackTrendDate = _T("");
	m_strSourceDataPath = _T("");
	m_bStartMode = FALSE;
	m_strL1RequestPort = _T("");
	m_L1SendPacketPort = _T("");
	m_L1UserName = _T("");
	m_strL1Psw = _T("");
	m_strDataFlowSrvAddr = _T("");
	m_strDataFlowProxyPort = _T("");
	m_strDataFlowUserName = _T("");
	m_strDataFlowPwd = _T("");
	m_strL2DataLoginAddr = _T("");
	m_strL2DataLoginPort = _T("");
	m_strL2DataSourcePath = _T("");
	m_strL2DataRequestPort = _T("");
	m_strL2DataPushPort = _T("");
	m_strL2DataUserName = _T("");
	m_strL2DataPsw = _T("");
	m_strServerSetSrvPort = _T("");
	m_strServerSetDealDataCount = _T("");
	m_strServerSetComUnitCount = _T("");
	m_strServerSetMaxLinkCount = _T("");
	m_strMarketCount = _T("");
	m_strMainDataPath = _T("");
	m_iMarketSet = -1;
	m_iDCDSendPacket = -1;
	m_iServerSetComProtocol = -1;
	m_iDataFlowProxy = -1;
	m_iL1MarketSet = -1;
	m_iHKRecvPacket = -1;
	m_iJimiDogMode = -1;
	m_bEnableShort = FALSE;
	m_strBackTrendMinute = _T("");
	m_strNetWorkNumber = _T("");
	m_strNodeAddress = _T("");
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CL2DCDSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CL2DCDSetDlg)
	DDX_Control(pDX, IDC_BUTTON_MAIN_DATA_PATH, m_ButtonMainDataPath);
	DDX_Text(pDX, IDC_EDIT_OPEN_TIME, m_strOpenTime);
	DDX_Text(pDX, IDC_EDIT_CLOSE_TIME, m_strCloseTime);
	DDX_Check(pDX, IDC_CHECK_BACKUP_DATA_LIME, m_bBackupDataLine);
	DDX_Check(pDX, IDC_CHECK_BACKUP_MINUTE_LINE, m_bBackupMinuteLine);
	DDX_Check(pDX, IDC_CHECK_HK_STOCK_EXCHANGE, m_bHKStockExchange);
	DDX_Check(pDX, IDC_CHECK_SPECIAL_STOCK_EXCHANGE, m_bSpecialStockExchange);
	DDX_Text(pDX, IDC_EDIT_DELAY_MINUTE, m_strDelayMinute);
	DDX_Text(pDX, IDC_EDIT_READ_DB_FREQUENCY, m_strReadDBFrequency);
	DDX_Text(pDX, IDC_EDIT_BACK_TREND_DATE, m_strBackTrendDate);
	DDX_Text(pDX, IDC_EDIT_SOURCE_DATA_PATH, m_strSourceDataPath);
	DDX_Check(pDX, IDC_CHECK_START_MODE, m_bStartMode);
	DDX_Text(pDX, IDC_EDIT_L1_REQUEST_PORT, m_strL1RequestPort);
	DDX_Text(pDX, IDC_EDIT_L1_SEND_PACKET_PORT, m_L1SendPacketPort);
	DDX_Text(pDX, IDC_EDIT_L1_USER_NMAE, m_L1UserName);
	DDX_Text(pDX, IDC_EDIT_L1_PSW, m_strL1Psw);
	DDX_Text(pDX, IDC_EDIT_DATA_FLOW_SRV_ADDR, m_strDataFlowSrvAddr);
	DDX_Text(pDX, IDC_EDIT_DATA_FLOW_PROXY_PORT, m_strDataFlowProxyPort);
	DDX_Text(pDX, IDC_EDIT_DATA_FLOW_USER_NAME, m_strDataFlowUserName);
	DDX_Text(pDX, IDC_EDIT_DATA_FLOW_PWD, m_strDataFlowPwd);
	DDX_Text(pDX, IDC_EDIT_L2_DATA_LOGIN_ADDR, m_strL2DataLoginAddr);
	DDX_Text(pDX, IDC_EDIT_L2_DATA_LOGIN_PORT, m_strL2DataLoginPort);
	DDX_Text(pDX, IDC_EDIT_L2_DATA_SOURCE_PATH, m_strL2DataSourcePath);
	DDX_Text(pDX, IDC_EDIT_L2_DATA_REQUEST_PORT, m_strL2DataRequestPort);
	DDX_Text(pDX, IDC_EDIT_L2_DATA_PUSH_PORT, m_strL2DataPushPort);
	DDX_Text(pDX, IDC_EDIT_L2_DATA_USER_NAME, m_strL2DataUserName);
	DDX_Text(pDX, IDC_EDIT_L2_DATA_Psw, m_strL2DataPsw);
	DDX_Text(pDX, IDC_EDIT1_SERVER_SET_SRV_PROT, m_strServerSetSrvPort);
	DDX_Text(pDX, IDC_EDIT_SERVER_SET_DEAL_DATA_COUNT, m_strServerSetDealDataCount);
	DDX_Text(pDX, IDC_EDIT_SERVER_SET_COM_UNIT_COUNT, m_strServerSetComUnitCount);
	DDX_Text(pDX, IDC_EDIT_SERVER_SET_MAX_LINK_COUNT, m_strServerSetMaxLinkCount);
	DDX_Text(pDX, IDC_EDIT_MARKET_COUNT, m_strMarketCount);
	DDX_Text(pDX, IDC_EDIT_MAIN_DATA_PATH, m_strMainDataPath);
	DDX_CBIndex(pDX, IDC_COMBO_MARKET_SET, m_iMarketSet);
	DDX_CBIndex(pDX, IDC_COMBO_DCD_SEND_PACKET, m_iDCDSendPacket);
	DDX_CBIndex(pDX, IDC_COMBO_SERVER_SET_COM_PROTOCOL, m_iServerSetComProtocol);
	DDX_CBIndex(pDX, IDC_COMBO_DATA_FLOW_PROXY, m_iDataFlowProxy);
	DDX_CBIndex(pDX, IDC_COMBO_L1_MARKET_SET, m_iL1MarketSet);
	DDX_CBIndex(pDX, IDC_COMBO_HK_RECV_PACKET, m_iHKRecvPacket);
	DDX_CBIndex(pDX, IDC_COMBO_JIMI_DOG_MODE, m_iJimiDogMode);
	DDX_Check(pDX, IDC_CHECK_ENABLE_SHORT, m_bEnableShort);
	DDX_Text(pDX, IDC_EDIT_BACK_TREND_MINUTE, m_strBackTrendMinute);
	DDX_Text(pDX, IDC_EDIT_NET_WORK_NUMBER, m_strNetWorkNumber);
	DDX_Text(pDX, IDC_EDIT_NODE_ADDRESS, m_strNodeAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CL2DCDSetDlg, CDialog)
	//{{AFX_MSG_MAP(CL2DCDSetDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_OPEN_TIME, OnChangeEditOpenTime)
	ON_EN_CHANGE(IDC_EDIT_CLOSE_TIME, OnChangeEditCloseTime)
	ON_BN_CLICKED(IDC_CHECK_BACKUP_DATA_LIME, OnCheckBackupDataLime)
	ON_BN_CLICKED(IDC_CHECK_BACKUP_MINUTE_LINE, OnCheckBackupMinuteLine)
	ON_CBN_EDITCHANGE(IDC_COMBO_MARKET_SET, OnEditchangeComboMarketSet)
	ON_CBN_DROPDOWN(IDC_COMBO_MARKET_SET, OnDropdownComboMarketSet)
	ON_BN_CLICKED(IDC_CHECK_HK_STOCK_EXCHANGE, OnCheckHkStockExchange)
	ON_BN_CLICKED(IDC_CHECK_SPECIAL_STOCK_EXCHANGE, OnCheckSpecialStockExchange)
	ON_CBN_EDITCHANGE(IDC_COMBO_DCD_SEND_PACKET, OnEditchangeComboDcdSendPacket)
	ON_CBN_DROPDOWN(IDC_COMBO_DCD_SEND_PACKET, OnDropdownComboDcdSendPacket)
	ON_CBN_EDITCHANGE(IDC_COMBO_HK_RECV_PACKET, OnEditchangeComboHkRecvPacket)
	ON_CBN_DROPDOWN(IDC_COMBO_HK_RECV_PACKET, OnDropdownComboHkRecvPacket)
	ON_EN_CHANGE(IDC_EDIT_DELAY_MINUTE, OnChangeEditDelayMinute)
	ON_EN_CHANGE(IDC_EDIT_READ_DB_FREQUENCY, OnChangeEditReadDbFrequency)
	ON_EN_CHANGE(IDC_EDIT_BACK_TREND_DATE, OnChangeEditBackTrendDate)
	ON_CBN_EDITCHANGE(IDC_COMBO_L1_MARKET_SET, OnEditchangeComboL1MarketSet)
	ON_CBN_DROPDOWN(IDC_COMBO_L1_MARKET_SET, OnDropdownComboL1MarketSet)
	ON_EN_CHANGE(IDC_EDIT_SOURCE_DATA_PATH, OnChangeEditSourceDataPath)
	ON_BN_CLICKED(IDC_CHECK_START_MODE, OnCheckStartMode)
	ON_EN_CHANGE(IDC_EDIT_L1_REQUEST_PORT, OnChangeEditL1RequestPort)
	ON_EN_CHANGE(IDC_EDIT_L1_SEND_PACKET_PORT, OnChangeEditL1SendPacketPort)
	ON_EN_CHANGE(IDC_EDIT_L1_USER_NMAE, OnChangeEditL1UserNmae)
	ON_EN_CHANGE(IDC_EDIT_L1_PSW, OnChangeEditL1Psw)
	ON_CBN_EDITCHANGE(IDC_COMBO_DATA_FLOW_PROXY, OnEditchangeComboDataFlowProxy)
	ON_CBN_DROPDOWN(IDC_COMBO_DATA_FLOW_PROXY, OnDropdownComboDataFlowProxy)
	ON_EN_CHANGE(IDC_EDIT_DATA_FLOW_SRV_ADDR, OnChangeEditDataFlowSrvAddr)
	ON_EN_CHANGE(IDC_EDIT_DATA_FLOW_PROXY_PORT, OnChangeEditDataFlowProxyPort)
	ON_EN_CHANGE(IDC_EDIT_DATA_FLOW_USER_NAME, OnChangeEditDataFlowUserName)
	ON_EN_CHANGE(IDC_EDIT_DATA_FLOW_PWD, OnChangeEditDataFlowPwd)
	ON_EN_CHANGE(IDC_EDIT_L2_DATA_LOGIN_ADDR, OnChangeEditL2DataLoginAddr)
	ON_EN_CHANGE(IDC_EDIT_L2_DATA_LOGIN_PORT, OnChangeEditL2DataLoginPort)
	ON_EN_CHANGE(IDC_EDIT_L2_DATA_SOURCE_PATH, OnChangeEditL2DataSourcePath)
	ON_EN_CHANGE(IDC_EDIT_L2_DATA_REQUEST_PORT, OnChangeEditL2DataRequestPort)
	ON_EN_CHANGE(IDC_EDIT_L2_DATA_PUSH_PORT, OnChangeEditL2DataPushPort)
	ON_EN_CHANGE(IDC_EDIT_L2_DATA_USER_NAME, OnChangeEditL2DataUserName)
	ON_EN_CHANGE(IDC_EDIT_L2_DATA_Psw, OnChangeEDITL2DATAPsw)
	ON_EN_CHANGE(IDC_EDIT1_SERVER_SET_SRV_PROT, OnChangeEdit1ServerSetSrvProt)
	ON_EN_CHANGE(IDC_EDIT_SERVER_SET_DEAL_DATA_COUNT, OnChangeEditServerSetDealDataCount)
	ON_EN_CHANGE(IDC_EDIT_SERVER_SET_COM_UNIT_COUNT, OnChangeEditServerSetComUnitCount)
	ON_EN_CHANGE(IDC_EDIT_SERVER_SET_MAX_LINK_COUNT, OnChangeEditServerSetMaxLinkCount)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_DATA_PATH, OnButtonMainDataPath)
	ON_EN_CHANGE(IDC_EDIT_MAIN_DATA_PATH, OnChangeEditMainDataPath)
	ON_CBN_EDITCHANGE(IDC_COMBO_SERVER_SET_COM_PROTOCOL, OnEditchangeComboServerSetComProtocol)
	ON_CBN_DROPDOWN(IDC_COMBO_SERVER_SET_COM_PROTOCOL, OnDropdownComboServerSetComProtocol)
	ON_EN_CHANGE(IDC_EDIT_MARKET_COUNT, OnChangeEditMarketCount)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKET_SET, OnSelchangeComboMarketSet)
	ON_CBN_SELCHANGE(IDC_COMBO_DCD_SEND_PACKET, OnSelchangeComboDcdSendPacket)
	ON_CBN_SELCHANGE(IDC_COMBO_HK_RECV_PACKET, OnSelchangeComboHkRecvPacket)
	ON_CBN_SELCHANGE(IDC_COMBO_L1_MARKET_SET, OnSelchangeComboL1MarketSet)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA_FLOW_PROXY, OnSelchangeComboDataFlowProxy)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER_SET_COM_PROTOCOL, OnSelchangeComboServerSetComProtocol)
	ON_CBN_SELCHANGE(IDC_COMBO_JIMI_DOG_MODE, OnSelchangeComboJimiDogMode)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_SHORT, OnCheckEnableShort)
	ON_EN_CHANGE(IDC_EDIT_BACK_TREND_MINUTE, OnChangeEditBackTrendMinute)
	ON_EN_CHANGE(IDC_EDIT_NET_WORK_NUMBER, OnChangeEditNetWorkNumber)
	ON_EN_CHANGE(IDC_EDIT_NODE_ADDRESS, OnChangeEditNodeAddress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CL2DCDSetDlg message handlers

BOOL CL2DCDSetDlg::OnInitDialog()
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
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MARKET_SET);
	pCombo->ResetContent();
	pCombo->AddString("上交所");
	pCombo->AddString("深交所");
	pCombo->AddString("联交所");
	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_DATA_FLOW_PROXY);
	pCombo->ResetContent();
	pCombo->AddString("不用代理");
	pCombo->AddString("普通代理");
	pCombo->AddString("USB代理");
	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_L1_MARKET_SET);
	pCombo->ResetContent();
	pCombo->AddString("上交所");
	pCombo->AddString("深交所");
	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_SERVER_SET_COM_PROTOCOL);
	pCombo->ResetContent();
	pCombo->AddString("TCP");
	pCombo->AddString("SPX");
	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_HK_RECV_PACKET);
	pCombo->ResetContent();
	pCombo->AddString("播报");
	pCombo->AddString("读库");
	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_DCD_SEND_PACKET);
	pCombo->ResetContent();
	pCombo->AddString("UDP");
	pCombo->AddString("IPX");
	pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_JIMI_DOG_MODE);
	pCombo->ResetContent();
	pCombo->AddString("不指定");
	pCombo->AddString("并口");
	pCombo->AddString("USB");

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAIN_DATA_PATH);
	pEdit->SetReadOnly();
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_MARKET_COUNT);
	pEdit->SetReadOnly();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	LoadDefaultConfig();
//	GetDlgItem(IDC_COMBO_MARKET_SET)->SetWindowText("上交所");
//	GetDlgItem(IDC_COMBO_L1_MARKET_SET)->SetWindowText("上交所");
	return TRUE;  // return TRUE  unless you set the focus to a control
}
int	 CL2DCDSetDlg::LoadDefaultConfig()
{
	MString		strl2dcdIniFileName = "l2dcd.ini";
	//上交所
	char						dftshopentime[50]= {0};				//	开盘时间

	MIniFile	iniFile;
	
	

	if ( iniFile.Open(strl2dcdIniFileName) >= 0 )
	{
		m_iJimiDogMode = iniFile.ReadInteger( "Setting","DogType", 0 );
		m_strMainDataPath = iniFile.ReadString( "PATH","DATA", "" ).c_str();
		m_strMarketCount = "3";
		//收盘设盯
		m_iMarketSet = 0;
		m_strOpenTime = iniFile.ReadString( "MARKET0","STARTTIME", "" ).c_str();
		m_strCloseTime =  iniFile.ReadString( "MARKET0","ENDTIME", "" ).c_str();
		m_bBackupDataLine = bool(iniFile.ReadInteger( "MARKET0","ENABLE_DAY", 0 ));
		m_bBackupMinuteLine = bool(iniFile.ReadInteger( "MARKET0","ENABLE_MIN", 0 ));

		//数据设盯
		m_iDCDSendPacket = iniFile.ReadInteger( "SETTING","USE_IPX", 0 );
		m_iHKRecvPacket = iniFile.ReadInteger( "SETTING","HKMODE", 0 );
		m_bSpecialStockExchange = bool(iniFile.ReadInteger( "SETTING","ENABLE_TBZR", 0 ));
		m_bHKStockExchange = bool(iniFile.ReadInteger( "SETTING","ENABLEHK", 0 ));
		m_strDelayMinute = iniFile.ReadString( "SETTING","hkdelay", "" ).c_str();
		m_strReadDBFrequency = iniFile.ReadString( "SETTING","RecordsOnce", "" ).c_str();
		m_strBackTrendDate = 	iniFile.ReadString( "SETTING","BACKUPDAYS", "" ).c_str();
		m_bEnableShort = bool(iniFile.ReadInteger( "SETTING","EnableShort", 0 ));
		m_strBackTrendMinute = 	iniFile.ReadString( "SETTING","Keep1MinDays", "" ).c_str();
	
		//L1 流设置 上交所
	
		m_iL1MarketSet = 0;
		m_bStartMode = bool(iniFile.ReadInteger( "SHDRV","Enable", 0 ));//启动流方式
		m_strSourceDataPath = iniFile.ReadString( "SHDRV","SERVERIP", "" ).c_str();//数据源地址

		m_strL1RequestPort = iniFile.ReadString( "SHDRV","SERVERPORT", "" ).c_str();//数据源地址
		m_L1SendPacketPort = iniFile.ReadString( "SHDRV","PUSHPORT", "" ).c_str();//推送端口
		m_L1UserName = iniFile.ReadString( "SHDRV","USER", "" ).c_str();//用户名
		m_strL1Psw = iniFile.ReadString( "SHDRV","PSW", "" ).c_str(); //密码
		//数据流代理
		m_iDataFlowProxy = iniFile.ReadInteger( "Proxy","Enable", 0 );
		m_strDataFlowSrvAddr = iniFile.ReadString( "Proxy","IP", "" ).c_str();
		m_strDataFlowProxyPort = iniFile.ReadString( "Proxy","Port", "" ).c_str();
		m_strDataFlowUserName = iniFile.ReadString( "Proxy","User", "" ).c_str();
		m_strDataFlowPwd = iniFile.ReadString( "Proxy","Psw", "" ).c_str();
		//l2数据流
		m_strL2DataLoginAddr = iniFile.ReadString( "SHL2","regserver", "" ).c_str();
		m_strL2DataLoginPort = iniFile.ReadString( "SHL2","regport", "" ).c_str();
		m_strL2DataSourcePath = iniFile.ReadString( "SHL2","SERVERIP", "" ).c_str();
		m_strL2DataRequestPort = iniFile.ReadString( "SHL2","SERVERPORT", "" ).c_str();
		m_strL2DataPushPort = iniFile.ReadString( "SHL2","PUSHPORT", "" ).c_str();
		m_strL2DataUserName = iniFile.ReadString( "SHL2","USER", "" ).c_str();
		m_strL2DataPsw = iniFile.ReadString( "SHL2","PSW", "" ).c_str();
		//服务设定
		m_iServerSetComProtocol = iniFile.ReadInteger( "SERVICE","TCPSPX" ,0);
		m_strServerSetSrvPort = iniFile.ReadString( "SERVICE","PORT", "" ).c_str();
		m_strServerSetDealDataCount = iniFile.ReadString( "SERVICE","DataUnitCount", "" ).c_str();
		m_strServerSetComUnitCount = iniFile.ReadString( "SERVICE","ComUnitCount", "" ).c_str();
		m_strServerSetMaxLinkCount = iniFile.ReadString( "SERVICE","MaxConnect", "" ).c_str();
		iniFile.Close();
	}  
	MString		strl2IniFileName = "..\\syscfg\\cfg\\l2.ini";
	if ( iniFile.Open(strl2IniFileName) >= 0 )
	{
		m_strNetWorkNumber = iniFile.ReadString( "Gateway","NetworkNumber", "" ).c_str();
		m_strNodeAddress = iniFile.ReadString( "Gateway","NodeAddress", "" ).c_str();
		iniFile.Close();

	}


	UpdateData(FALSE);
	return 0;
}
void CL2DCDSetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CL2DCDSetDlg::OnPaint() 
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
HCURSOR CL2DCDSetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CL2DCDSetDlg::OnChangeEditOpenTime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditCloseTime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnCheckBackupDataLime() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnCheckBackupMinuteLine() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnEditchangeComboMarketSet() 
{

	
}
void CL2DCDSetDlg::OnSelchangeComboDcdSendPacket() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_DCD_SEND_PACKET);
	int seln = pCombo->GetCurSel();
	MString		ininame = "l2dcd.ini";
	MIniFile	iniFile; 
	if (seln == 0)
	{	
		
		m_iDCDSendPacket = 0;
	
	}
	else if (seln == 1)
	{
		m_iDCDSendPacket = 1;
	}
	
	UpdateData(FALSE);
	return ;
	
}

void CL2DCDSetDlg::OnSelchangeComboMarketSet() 
{



	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_MARKET_SET);
	int seln = pCombo->GetCurSel();
	MString		ininame = "l2dcd.ini";
	MIniFile	iniFile; 
	if (seln == 0)
	{	
		if( ( iniFile.Open( ininame) ) >= 0 )
		{
			m_iMarketSet = 0;

			m_strOpenTime = iniFile.ReadString( "MARKET0","STARTTIME", "" ).c_str();
			m_strCloseTime = iniFile.ReadString( "MARKET0","ENDTIME", "" ).c_str();
			m_bBackupDataLine = bool(iniFile.ReadInteger( "MARKET0","ENABLE_DAY", 0 ));
			m_bBackupMinuteLine = bool(iniFile.ReadInteger( "MARKET0","ENABLE_MIN", 0 ));
			iniFile.Close();
		
		}
		else
		{
			CString mcount = "打开l2dcd.ini文件错误";
			return ;
		}
		

	}
	else if (seln == 1)
	{
		if( ( iniFile.Open( ininame) ) >= 0 )
		{
			m_iMarketSet = 1;
			m_strOpenTime = iniFile.ReadString( "MARKET1","STARTTIME", "" ).c_str();
			m_strCloseTime = iniFile.ReadString( "MARKET1","ENDTIME", "" ).c_str();
			m_bBackupDataLine = bool(iniFile.ReadInteger( "MARKET1","ENABLE_DAY", 0 ));
			m_bBackupMinuteLine = bool(iniFile.ReadInteger( "MARKET1","ENABLE_MIN", 0 ));
			iniFile.Close();		
		}
		else
		{
			CString mcount = "打开l2dcd.ini文件错误";
			return ;
		}
	}
	else if(seln == 2)
	{
		if( ( iniFile.Open( ininame) ) >= 0 )
		{
			m_iMarketSet = 2;
			m_strOpenTime = iniFile.ReadString( "MARKET2","STARTTIME", "" ).c_str();
			m_strCloseTime = iniFile.ReadString( "MARKET2","ENDTIME", "" ).c_str();
			m_bBackupDataLine = bool(iniFile.ReadInteger( "MARKET2","ENABLE_DAY", 0 ));
			m_bBackupMinuteLine = bool(iniFile.ReadInteger( "MARKET2","ENABLE_MIN", 0 ));
			iniFile.Close();
		}
		else
		{
			CString mcount = "打开l2dcd.ini文件错误";
			return ;
		}
	}

	UpdateData(FALSE);
	return ;

}

void CL2DCDSetDlg::OnDropdownComboMarketSet() 
{
	// TODO: Add your control notification handler code here


//	pCombo->SelectString(-1,m_strMarketSet);
}

void CL2DCDSetDlg::OnCheckHkStockExchange() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnCheckSpecialStockExchange() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnEditchangeComboDcdSendPacket() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnDropdownComboDcdSendPacket() 
{
	// TODO: Add your control notification handler code here

	
//	pCombo->SelectString(0,m_strDCDSendPacket);
	
}

void CL2DCDSetDlg::OnEditchangeComboHkRecvPacket() 
{
	// TODO: Add your control notification handler code here
	
	
}

void CL2DCDSetDlg::OnDropdownComboHkRecvPacket() 
{
	// TODO: Add your control notification handler code here

	
//	pCombo->SelectString(-1,m_strHKRecvPacket);
	
	
}

void CL2DCDSetDlg::OnChangeEditDelayMinute() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditReadDbFrequency() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditBackTrendDate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnEditchangeComboL1MarketSet() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnDropdownComboL1MarketSet() 
{
	// TODO: Add your control notification handler code here

//	pCombo->AddString("联交所");
//	pCombo->SelectString(-1,m_strL1MarketSet);

	
}

void CL2DCDSetDlg::OnChangeEditSourceDataPath() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnCheckStartMode() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL1RequestPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL1SendPacketPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL1UserNmae() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL1Psw() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnEditchangeComboDataFlowProxy() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnDropdownComboDataFlowProxy() 
{
	// TODO: Add your control notification handler code here

}

void CL2DCDSetDlg::OnChangeEditDataFlowSrvAddr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditDataFlowProxyPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditDataFlowUserName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditDataFlowPwd() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL2DataLoginAddr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL2DataLoginPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL2DataSourcePath() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL2DataRequestPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL2DataPushPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditL2DataUserName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEDITL2DATAPsw() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}



void CL2DCDSetDlg::OnChangeEdit1ServerSetSrvProt() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditServerSetDealDataCount() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditServerSetComUnitCount() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditServerSetMaxLinkCount() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnButtonMainDataPath() 
{
/*// TODO: Add your control notification handler code here
	CString FilePathName;
	CFileDialog dlg(FALSE);///TRUE为OPEN对话框，FALSE为S***E AS对话框
	if (dlg.DoModal() == IDOK)
		FilePathName =dlg.GetPathName();
	GetDlgItem(IDC_EDIT_MAIN_DATA_PATH)->SetWindowText(FilePathName);
	 */


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
//	AfxMessageBox(strFilePath);   
	m_strMainDataPath = strFilePath;
	GetDlgItem(IDC_EDIT_MAIN_DATA_PATH)->SetWindowText(m_strMainDataPath);

}

void CL2DCDSetDlg::OnChangeEditMainDataPath() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnEditchangeComboServerSetComProtocol() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnDropdownComboServerSetComProtocol() 
{
	// TODO: Add your control notification handler code here



	
}

void CL2DCDSetDlg::OnChangeEditMarketCount() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}



void CL2DCDSetDlg::OnSelchangeComboHkRecvPacket() 
{
	// TODO: Add your control notification handler code here

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_HK_RECV_PACKET);
	int seln = pCombo->GetCurSel();
	MString		ininame = "l2dcd.ini";
	MIniFile	iniFile; 
	if (seln == 0)
	{	
		m_iHKRecvPacket = 0;
	}
	else if (seln == 1)
	{
		m_iHKRecvPacket = 1;
	}
	
	UpdateData(FALSE);
	return ;
}

void CL2DCDSetDlg::OnSelchangeComboL1MarketSet() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_L1_MARKET_SET);
	int seln = pCombo->GetCurSel();
	MString		ininame = "l2dcd.ini";
	MIniFile	iniFile;
	if ( iniFile.Open(ininame) >= 0 )
	{
		if (seln == 0)
		{	
			
			m_iL1MarketSet = 0;
			m_bStartMode = bool(iniFile.ReadInteger( "SHDRV","Enable", 0 ));//启动流方式
			m_strSourceDataPath = iniFile.ReadString( "SHDRV","SERVERIP", "" ).c_str();

			m_strL1RequestPort = iniFile.ReadString( "SHDRV","SERVERPORT", "" ).c_str();//数据源地址
			m_L1SendPacketPort = iniFile.ReadString( "SHDRV","PUSHPORT", "" ).c_str();//推送端口
			m_L1UserName = iniFile.ReadString( "SHDRV","USER", "" ).c_str();//用户名
			m_strL1Psw = iniFile.ReadString( "SHDRV","PSW", "" ).c_str(); //密码
			iniFile.Close();
			
		}
		else if (seln == 1)
		{
			m_iL1MarketSet = 1;
			m_bStartMode = bool(iniFile.ReadInteger( "SZDRV","Enable", 0 ));//启动流方式
			m_strSourceDataPath = iniFile.ReadString( "SZDRV","SERVERIP", "" ).c_str();
			m_strL1RequestPort = iniFile.ReadString( "SZDRV","SERVERPORT", "" ).c_str();//数据源地址
			m_L1SendPacketPort = iniFile.ReadString( "SZDRV","PUSHPORT", "" ).c_str();//推送端口
			m_L1UserName = iniFile.ReadString( "SZDRV","USER", "" ).c_str();//用户名
			m_strL1Psw = iniFile.ReadString( "SZDRV","PSW", "" ).c_str(); //密码
			iniFile.Close();
		/*	iniFile.WriteString( "SZDRV","SERVERIP", m_strSourceDataPath.GetBuffer(m_strSourceDataPath.GetLength()) );//数据源地址
			iniFile.WriteString( "SZDRV","SERVERPORT", m_strL1RequestPort.GetBuffer(m_strL1RequestPort.GetLength()) );//数据源地址
			iniFile.WriteString( "SZDRV","PUSHPORT", m_L1SendPacketPort.GetBuffer(m_L1SendPacketPort.GetLength()) );//推送端口
			iniFile.WriteString( "SZDRV","USER", m_L1UserName.GetBuffer(m_L1UserName.GetLength()) );//用户名
			iniFile.WriteString( "SZDRV","PSW", m_strL1Psw.GetBuffer(m_strL1Psw.GetLength()) ); //密码
	*/
		}
	}
	else
	{

	}

	
	UpdateData(FALSE);
	return ;
	
}

void CL2DCDSetDlg::OnSelchangeComboDataFlowProxy() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_DATA_FLOW_PROXY);
	int seln = pCombo->GetCurSel();
	MString		ininame = "l2dcd.ini";
	MIniFile	iniFile; 


	if (seln == 0)
	{	
		
		m_iDataFlowProxy = 0;
		pCombo= (CComboBox*)GetDlgItem(IDC_EDIT_DATA_FLOW_USER_NAME);
		::EnableWindow(pCombo->GetSafeHwnd(), TRUE);
		pCombo= (CComboBox*)GetDlgItem(IDC_EDIT_DATA_FLOW_PWD);
		::EnableWindow(pCombo->GetSafeHwnd(), TRUE);
		
	}
	else if (seln == 1)
	{
		m_iDataFlowProxy = 1;
		pCombo= (CComboBox*)GetDlgItem(IDC_EDIT_DATA_FLOW_USER_NAME);
		::EnableWindow(pCombo->GetSafeHwnd(), TRUE);
		pCombo= (CComboBox*)GetDlgItem(IDC_EDIT_DATA_FLOW_PWD);
		::EnableWindow(pCombo->GetSafeHwnd(), TRUE);
	}else if (seln == 2)
	{
		m_iDataFlowProxy = 2;
		pCombo= (CComboBox*)GetDlgItem(IDC_EDIT_DATA_FLOW_USER_NAME);
		::EnableWindow(pCombo->GetSafeHwnd(), TRUE);
		pCombo= (CComboBox*)GetDlgItem(IDC_EDIT_DATA_FLOW_PWD);
		::EnableWindow(pCombo->GetSafeHwnd(), TRUE);
	}else if (seln == 3)
	{
		m_iDataFlowProxy = 3;
		pCombo= (CComboBox*)GetDlgItem(IDC_EDIT_DATA_FLOW_USER_NAME);
		::EnableWindow(pCombo->GetSafeHwnd(), FALSE);
		pCombo= (CComboBox*)GetDlgItem(IDC_EDIT_DATA_FLOW_PWD);
		::EnableWindow(pCombo->GetSafeHwnd(), FALSE);
	}

	UpdateData(FALSE);
	return ;
	
}

void CL2DCDSetDlg::OnSelchangeComboServerSetComProtocol() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_SERVER_SET_COM_PROTOCOL);
	int seln = pCombo->GetCurSel();
	MString		ininame = "l2dcd.ini";
	MIniFile	iniFile; 
	if (seln == 0)
	{	
		
		m_iServerSetComProtocol = 0;
		
	}
	else if (seln == 1)
	{
		m_iServerSetComProtocol = 1;
	}
	
	UpdateData(FALSE);
	return ;
	
}

void CL2DCDSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	int ret = 0;
	UpdateData(TRUE);
	ret = SaveL2DCDCfg();
	if (ret != 0)
	{
		AfxMessageBox("保存设定失败!"); 
	}
	else
	{
		AfxMessageBox("保存设定成功!"); 
	}
//	CDialog::OnOK();
}
int CL2DCDSetDlg::SaveL2DCDCfg()
{
	MString		strl2dcdIniFileName = "l2dcd.ini";
	//上交所
	char						dftshopentime[50]= {0};				//	开盘时间
	
	MIniFile	iniFile;
	MFile		file;
	if( !MFile::IsExist(strl2dcdIniFileName))
	{
		file.Create(strl2dcdIniFileName);
	}
	if ( iniFile.Open(strl2dcdIniFileName) >= 0 )
	{
		//	strcpy(dftshopentime,iniFile.ReadString( "MARKET0","STARTTIME", "" ).c_str());
		
		
		iniFile.WriteString( "PATH","DATA",m_strMainDataPath.GetBuffer(m_strMainDataPath.GetLength()) );
		if ( m_iMarketSet == 0)
		{
			if (m_bBackupDataLine == 1)
			{
				iniFile.WriteString( "MARKET0","ENABLE_DAY", "1");
				
			}
			else
			{
				iniFile.WriteString( "MARKET0","ENABLE_DAY", "0");
				
			}
			if (m_bBackupMinuteLine)
			{
				iniFile.WriteString( "MARKET0","ENABLE_MIN", "1" );
				
			}
			else
			{
				iniFile.WriteString( "MARKET0","ENABLE_MIN", "0" );
			}
		
			
			iniFile.WriteString( "MARKET0","STARTTIME", m_strOpenTime.GetBuffer(m_strOpenTime.GetLength()));
			iniFile.WriteString( "MARKET0","ENDTIME", m_strCloseTime.GetBuffer(m_strCloseTime.GetLength()) );
	
		}
		if (m_iMarketSet == 1)
		{
			if (m_bBackupDataLine)
			{
				iniFile.WriteString( "MARKET1","ENABLE_DAY", "1");
				
			}
			else
			{
				iniFile.WriteString( "MARKET1","ENABLE_DAY", "0");
				
			}
			if (m_bBackupMinuteLine)
			{
				iniFile.WriteString( "MARKET1","ENABLE_MIN", "1" );
				
			}
			else
			{
				iniFile.WriteString( "MARKET1","ENABLE_MIN", "0" );
			}
			
			iniFile.WriteString( "MARKET1","STARTTIME", m_strOpenTime.GetBuffer(m_strOpenTime.GetLength()));
			iniFile.WriteString( "MARKET1","ENDTIME", m_strCloseTime.GetBuffer(m_strCloseTime.GetLength()) );
		}

		if (m_iMarketSet == 2)
		{
			if (m_bBackupDataLine)
			{
				iniFile.WriteString( "MARKET2","ENABLE_DAY", "1");
				
			}
			else
			{
				iniFile.WriteString( "MARKET2","ENABLE_DAY", "0");
				
			}
			if (m_bBackupMinuteLine)
			{
				iniFile.WriteString( "MARKET2","ENABLE_MIN", "1" );
				
			}
			else
			{
				iniFile.WriteString( "MARKET1","ENABLE_MIN", "0" );
			}
			
			iniFile.WriteString( "MARKET2","STARTTIME", m_strOpenTime.GetBuffer(m_strOpenTime.GetLength()));
			iniFile.WriteString( "MARKET2","ENDTIME", m_strCloseTime.GetBuffer(m_strCloseTime.GetLength()) );
		}

		if (m_bSpecialStockExchange)
		{
			iniFile.WriteString( "SETTING","ENABLE_TBZR", "1" );
		}
		else
		{
			iniFile.WriteString( "SETTING","ENABLE_TBZR", "0" );
			
		}
		
		if (m_bHKStockExchange)
		{
			iniFile.WriteString( "SETTING","ENABLEHK", "1" );
		}
		else
		{
			iniFile.WriteString( "SETTING","ENABLEHK", "0" );
			
		}

		if (m_bEnableShort)
		{
			iniFile.WriteString( "SETTING","EnableShort", "1" );
		}
		else
		{
			iniFile.WriteString( "SETTING","EnableShort", "0" );
			
		}

		if (m_iDCDSendPacket == 0)
		{
			iniFile.WriteString( "SETTING","USE_IPX", "0" );
		}

		if (m_iDCDSendPacket == 1)
		{
			iniFile.WriteString( "SETTING","USE_IPX", "1" );

		}
		if (m_iHKRecvPacket == 1)
		{
			iniFile.WriteString( "SETTING","HKMODE", "1" );
		}
		
		if (m_iHKRecvPacket == 0)
		{
			iniFile.WriteString( "SETTING","HKMODE", "0" );
			
		}
		iniFile.WriteString( "SETTING","hkdelay", m_strDelayMinute.GetBuffer(m_strDelayMinute.GetLength()) );
		iniFile.WriteString( "SETTING","RecordsOnce", m_strReadDBFrequency.GetBuffer(m_strReadDBFrequency.GetLength()) );
		iniFile.WriteString( "SETTING","BACKUPDAYS", m_strBackTrendDate.GetBuffer(m_strBackTrendDate.GetLength()));
		iniFile.WriteString( "SETTING","Keep1MinDays", m_strBackTrendMinute.GetBuffer(m_strBackTrendMinute.GetLength()));


		//L1 流设置 上交所	

		if (m_iL1MarketSet == 0)
		{
			if (m_bStartMode)
			{
				iniFile.WriteString( "SHDRV","Enable", "1" );//启动流方式
			}
			else
			{
				iniFile.WriteString( "SHDRV","Enable", "0" );//启动流方式
			}
			iniFile.WriteString( "SHDRV","SERVERIP", m_strSourceDataPath.GetBuffer(m_strSourceDataPath.GetLength()) );//数据源地址
			iniFile.WriteString( "SHDRV","SERVERPORT", m_strL1RequestPort.GetBuffer(m_strL1RequestPort.GetLength()) );//数据源地址
			iniFile.WriteString( "SHDRV","PUSHPORT", m_L1SendPacketPort.GetBuffer(m_L1SendPacketPort.GetLength()) );//推送端口
			iniFile.WriteString( "SHDRV","USER", m_L1UserName.GetBuffer(m_L1UserName.GetLength()) );//用户名
			iniFile.WriteString( "SHDRV","PSW", m_strL1Psw.GetBuffer(m_strL1Psw.GetLength()) ); //密码
		}
		
		if (m_iL1MarketSet == 1)
		{
			if (m_bStartMode)
			{
				iniFile.WriteString( "SZDRV","Enable", "1" );//启动流方式
			}
			else
			{
				iniFile.WriteString( "SZDRV","Enable", "0" );//启动流方式
			}
			iniFile.WriteString( "SZDRV","SERVERIP", m_strSourceDataPath.GetBuffer(m_strSourceDataPath.GetLength()) );//数据源地址
			iniFile.WriteString( "SZDRV","SERVERPORT", m_strL1RequestPort.GetBuffer(m_strL1RequestPort.GetLength()) );//数据源地址
			iniFile.WriteString( "SZDRV","PUSHPORT", m_L1SendPacketPort.GetBuffer(m_L1SendPacketPort.GetLength()) );//推送端口
			iniFile.WriteString( "SZDRV","USER", m_L1UserName.GetBuffer(m_L1UserName.GetLength()) );//用户名
			iniFile.WriteString( "SZDRV","PSW", m_strL1Psw.GetBuffer(m_strL1Psw.GetLength()) ); //密码

		}	
		//数据流代理
		if (m_iDataFlowProxy == 0)
		{
			iniFile.WriteString( "Proxy","Enable", "0" );
			iniFile.WriteString( "Proxy","IP", m_strDataFlowSrvAddr.GetBuffer(m_strDataFlowSrvAddr.GetLength()) );
			iniFile.WriteString( "Proxy","Port", m_strDataFlowProxyPort.GetBuffer(m_strDataFlowProxyPort.GetLength()) );
			iniFile.WriteString( "Proxy","User", m_strDataFlowUserName.GetBuffer(m_strDataFlowUserName.GetLength()) );
			iniFile.WriteString( "Proxy","Psw", m_strDataFlowPwd.GetBuffer(m_strDataFlowPwd.GetLength()) );
		}
		if (m_iDataFlowProxy == 1)
		{
			iniFile.WriteString( "Proxy","Enable", "1" );
			iniFile.WriteString( "Proxy","IP", m_strDataFlowSrvAddr.GetBuffer(m_strDataFlowSrvAddr.GetLength()) );
			iniFile.WriteString( "Proxy","Port", m_strDataFlowProxyPort.GetBuffer(m_strDataFlowProxyPort.GetLength()) );
			iniFile.WriteString( "Proxy","User", m_strDataFlowUserName.GetBuffer(m_strDataFlowUserName.GetLength()) );
			iniFile.WriteString( "Proxy","Psw", m_strDataFlowPwd.GetBuffer(m_strDataFlowPwd.GetLength()) );
		}
		if (m_iDataFlowProxy == 2)
		{
			iniFile.WriteString( "Proxy","Enable", "2" );
			iniFile.WriteString( "Proxy","IP", m_strDataFlowSrvAddr.GetBuffer(m_strDataFlowSrvAddr.GetLength()) );
			iniFile.WriteString( "Proxy","Port", m_strDataFlowProxyPort.GetBuffer(m_strDataFlowProxyPort.GetLength()) );
			iniFile.WriteString( "Proxy","User", m_strDataFlowUserName.GetBuffer(m_strDataFlowUserName.GetLength()) );
			iniFile.WriteString( "Proxy","Psw", m_strDataFlowPwd.GetBuffer(m_strDataFlowPwd.GetLength()) );
		}	
		if (m_iDataFlowProxy == 3)
		{
			iniFile.WriteString( "Proxy","Enable", "3" );
			
			iniFile.WriteString( "Proxy","IPAddr", m_strDataFlowSrvAddr.GetBuffer(m_strDataFlowSrvAddr.GetLength()) );
			iniFile.WriteString( "Proxy","Port", m_strDataFlowProxyPort.GetBuffer(m_strDataFlowProxyPort.GetLength()) );
		}
	
		//l2数据流

		iniFile.WriteString( "SHL2","regserver", m_strL2DataLoginAddr.GetBuffer(m_strL2DataLoginAddr.GetLength()) );
		iniFile.WriteString( "SHL2","regport", m_strL2DataLoginPort.GetBuffer(m_strL2DataLoginPort.GetLength()) );
		iniFile.WriteString( "SHL2","SERVERIP", m_strL2DataSourcePath.GetBuffer(m_strL2DataSourcePath.GetLength()));
		iniFile.WriteString( "SHL2","SERVERPORT", m_strL2DataRequestPort.GetBuffer(m_strL2DataRequestPort.GetLength()) );
		iniFile.WriteString( "SHL2","PUSHPORT", m_strL2DataPushPort.GetBuffer(m_strL2DataPushPort.GetLength()) );
		iniFile.WriteString( "SHL2","USER", m_strL2DataUserName.GetBuffer(m_strL2DataUserName.GetLength()) );
		iniFile.WriteString( "SHL2","PSW", m_strL2DataPsw.GetBuffer(m_strL2DataPsw.GetLength()) );
		//服务设定
		if (m_iServerSetComProtocol == 0 )
		{
			 
			iniFile.WriteString( "SERVICE","TCPSPX","0");

		}
		if (m_iServerSetComProtocol == 1)
		{
			iniFile.WriteString( "SERVICE","TCPSPX","1");

		}
		iniFile.WriteString( "SERVICE","PORT", m_strServerSetSrvPort.GetBuffer(m_strServerSetSrvPort.GetLength()));
		iniFile.WriteString( "SERVICE","DataUnitCount", m_strServerSetDealDataCount.GetBuffer(m_strServerSetDealDataCount.GetLength()) );
		iniFile.WriteString( "SERVICE","ComUnitCount", m_strServerSetComUnitCount.GetBuffer(m_strServerSetComUnitCount.GetLength()) );
		iniFile.WriteString( "SERVICE","MaxConnect", m_strServerSetMaxLinkCount.GetBuffer(m_strServerSetMaxLinkCount.GetLength()) );
		//加密狗
		iniFile.WriteInteger( "Setting","DogType", m_iJimiDogMode);
		iniFile.Close();
	} 
	MString		strl2IniFileName = "..\\syscfg\\cfg\\l2.ini";
	MString     strl2IniFileDir = "..\\syscfg\\cfg";
	if( !MFile::IsExist(strl2IniFileName))
	{
		MFile::CreateDirectoryTree(strl2IniFileDir);
		file.Create(strl2IniFileName);
	}
	if ( iniFile.Open(strl2IniFileName) >= 0 )
	{
		iniFile.WriteString( "Gateway","NetworkNumber", m_strNetWorkNumber.GetBuffer(m_strNetWorkNumber.GetLength()));
		iniFile.WriteString( "Gateway","NodeAddress", m_strNodeAddress.GetBuffer(m_strNodeAddress.GetLength()));
		iniFile.Close();
	}
	UpdateData(FALSE);
	return 0;
}

void CL2DCDSetDlg::OnSelchangeComboJimiDogMode() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_JIMI_DOG_MODE);
	int seln = pCombo->GetCurSel();
	
	if (seln == 0)
	{	
		
		m_iJimiDogMode = 0;
	}
	else if (seln == 1)
	{
		m_iJimiDogMode = 1;
		
	}else if (seln == 2)
	{
		m_iJimiDogMode = 2;
	}
	
	UpdateData(FALSE);
	return ;
}

void CL2DCDSetDlg::OnCheckEnableShort() 
{
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditBackTrendMinute() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditNetWorkNumber() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CL2DCDSetDlg::OnChangeEditNodeAddress() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
