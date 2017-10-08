// RemindView.cpp : implementation of the CRemindView class
//
//#include <windows.h>

#include "stdafx.h"
#include "Remind.h"
#include "MainFrm.h"

#include "RemindDoc.h"
#include "RemindView.h"

#include "./library/pop3.h"
#include "./library/StatusBarMsgWnd.h"
#include "./library/picture.h"

#include "public.h"
#include "pronewdlg.h"
#include "msgnewdlg.h"
#include "processdlg.h"
#include "manprocdlg.h"
#include "mailcheckdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CheckMail *maillist;
extern ProgramInfo *proglist;
extern MessageInfo *msglist;
extern ProcessInfo *proclist;
extern char m_sInifilename[128];
extern char m_spath[128];
extern int nBeep;							/*是否蜂鸣提示*/
extern int m_nIspicture;					/*有无背景图片*/
CEvent g_eventman,g_eventmail;
int m_nMailInterval;
/////////////////////////////////////////////////////////////////////////////
// CRemindView

IMPLEMENT_DYNCREATE(CRemindView, CFormView)

BEGIN_MESSAGE_MAP(CRemindView, CFormView)
	ON_MESSAGE(WM_MANPROCESS,OnManProcess)
	ON_MESSAGE(WM_CHECKMAIL,OnCheckMail)
	//{{AFX_MSG_MAP(CRemindView)
	ON_BN_CLICKED(IDC_CKSHUT, OnCkshut)
	ON_BN_CLICKED(IDC_BTNSHUTNOW, OnBtnshutnow)
	ON_COMMAND(ID_EDIT_NEW, OnEditNew)
	ON_COMMAND(ID_EDIT_MOD, OnEditMod)
	ON_COMMAND(ID_EDIT_DEL, OnEditDel)
	ON_COMMAND(ID_OPTION_BEEP, OnOptionBeep)
	ON_UPDATE_COMMAND_UI(ID_OPTION_BEEP, OnUpdateOptionBeep)
	ON_WM_SIZE()
	ON_COMMAND(ID_TOOL_MANPROC, OnToolManproc)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABLIST, OnSelchangeTablist)
	ON_COMMAND(ID_TOOL_MAILCHECK, OnToolMailcheck)
	ON_NOTIFY(NM_DBLCLK, IDC_MSGLIST, OnDblclkMsglist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MSGLIST, OnItemchangedMsglist)
	ON_NOTIFY(NM_DBLCLK, IDC_PROCLIST, OnDblclkProclist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PROCLIST, OnItemchangedProclist)
	ON_NOTIFY(NM_DBLCLK, IDC_PROGLIST, OnDblclkProglist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PROGLIST, OnItemchangedProglist)
	ON_WM_TIMER()
	ON_COMMAND(ID_OPTION_GETPIC, OnOptionGetpic)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemindView construction/destruction

CRemindView::CRemindView()
	: CFormView(CRemindView::IDD)
{
	//{{AFX_DATA_INIT(CRemindView)
	m_bShut = FALSE;
	m_nShutforce = -1;
	m_nShuttype = -1;
	m_dShutdate = COleDateTime::GetCurrentTime();
	m_tShuttime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	//加载位图，为背景图做准备
	//CBitmap bmp;
	//bmp.LoadBitmap(IDB_BM_BACKGROUND);
	//m_brushBackground.CreatePatternBrush(&bmp);
}

CRemindView::~CRemindView()
{
}

void CRemindView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemindView)
	DDX_Control(pDX, IDC_PROGLIST, m_proglist);
	DDX_Control(pDX, IDC_PROCLIST, m_proclist);
	DDX_Control(pDX, IDC_MSGLIST, m_msglist);
	DDX_Control(pDX, IDC_TABLIST, m_tabCtrl);
	DDX_Control(pDX, IDC_CKSHUT, m_cCkshut);
	DDX_Control(pDX, IDC_GROUP, m_cGroup);
	DDX_Control(pDX, IDC_COBTYPE, m_cType);
	DDX_Control(pDX, IDC_DTPSHUTDATE, m_cShutdate);
	DDX_Control(pDX, IDC_DTPSHUTTIME, m_cShuttime);
	DDX_Control(pDX, IDC_COBFORCE, m_cForce);
	DDX_Check(pDX, IDC_CKSHUT, m_bShut);
	DDX_CBIndex(pDX, IDC_COBFORCE, m_nShutforce);
	DDX_CBIndex(pDX, IDC_COBTYPE, m_nShuttype);
	DDX_DateTimeCtrl(pDX, IDC_DTPSHUTDATE, m_dShutdate);
	DDX_DateTimeCtrl(pDX, IDC_DTPSHUTTIME, m_tShuttime);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BTNSHUTNOW, m_btnShutnow);
}

BOOL CRemindView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CRemindView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	//使程序居中显示
	AfxGetMainWnd()->CenterWindow();

	//添加标签
	TC_ITEM tcItem;
	tcItem.mask=TCIF_TEXT;
	tcItem.pszText="应用程序提醒";
	m_tabCtrl.InsertItem(0,&tcItem);
	tcItem.pszText="消息提醒";
	m_tabCtrl.InsertItem(1,&tcItem);
	tcItem.pszText="关闭进程";
	m_tabCtrl.InsertItem(2,&tcItem);

	//初始化时显示应用程序提醒列表
	m_proglist.SetBkColor(RGB(200,200,200));
	m_proglist.SetTextBkColor(RGB(200,200,200));
	m_proclist.SetBkColor(RGB(200,200,200));
	m_proclist.SetTextBkColor(RGB(200,200,200));
	m_msglist.SetBkColor(RGB(200,200,200));
	m_msglist.SetTextBkColor(RGB(200,200,200));
	m_nActivepage = 0;
	GetDlgItem(IDC_PROGLIST)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MSGLIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PROCLIST)->ShowWindow(SW_HIDE);
	
	//是否蜂鸣提示
	nBeep = GetPrivateProfileInt(OPTFIELD,"Beep",0,m_sInifilename);
	//获取上次关闭程序时间
	COleDateTime dStarttime = COleDateTime::GetCurrentTime();
	memset(sStarttime, 0, sizeof(sStarttime));
	DateTimeToString(dStarttime, sStarttime);
	memset(sLastshuttime, 0, sizeof(sLastshuttime));
	GetPrivateProfileString(SHUTFIELD,"Lastshuttime","",sLastshuttime,MAX_PATH,m_sInifilename);

	//设置按钮图标等,并使其透明
	m_btnShutnow.SetBitmaps(IDB_SHUTNOW1,RGB(255,255,255),IDB_SHUTNOW,RGB(255,255,255));
	m_btnShutnow.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnShutnow.SetRounded(TRUE);
	m_btnShutnow.SetSound(MAKEINTRESOURCE(IDR_WAVEHOVER), ::GetModuleHandle(NULL));
	m_btnShutnow.SetBtnCursor(IDC_HAND);
	m_btnShutnow.DrawTransparent(TRUE);
	m_btnShutnow.SetColor(3,RGB(0,0,255));		//设置按钮字体颜色
	m_btnShutnow.SetColor(1,RGB(255,0,0));

	//显示各列表头
	ShowProgHeader();
	ShowMsgHeader();
	ShowProcHeader();	

	//maillist = NULL;
	proglist = NULL;
	msglist = NULL;
	proclist = NULL;
	InitialListProg();		//启动时开启应用程序提醒
	InitialListMsg();		//启动时开启消息提醒
	InitialTimerShut();		//获取定时关机设置

	m_proglist.SetItemState(m_nCurrentProg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_msglist.SetItemState(m_nCurrentMsg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	m_proglist.SetFocus();

	//启动定时器
	SetTimer(ID_REMIND_TIMER,INTERVAL,NULL);
	SetTimer(ID_SHUT_TIMER,SHUTDOWN,NULL);

	//启动定时检查邮件定时器
	StartCheckMail();
}

/////////////////////////////////////////////////////////////////////////////
// CRemindView printing

BOOL CRemindView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRemindView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRemindView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRemindView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CRemindView diagnostics

#ifdef _DEBUG
void CRemindView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRemindView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CRemindDoc* CRemindView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRemindDoc)));
	return (CRemindDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRemindView message handlers

void CRemindView::OnEditNew() 
{
	// TODO: Add your command handler code here
	COleDateTime dCurrenttime = COleDateTime::GetCurrentTime();
	COleDateTimeSpan dtSpan(0,1,0,0);
	dCurrenttime += dtSpan;
	CPronewDlg pronewdlg;
	CMsgnewDlg msgnewdlg;
	CProcessDlg processdlg;
	switch(m_nActivepage)
	{
	case 0:
		//添加应用程序提醒
		strcpy(pronewdlg.m_sCaption, "添加应用程序提醒");
		pronewdlg.m_nCaption = 0;
		pronewdlg.m_tTime = dCurrenttime;
		if(pronewdlg.DoModal()==IDOK)
		{
			int iCount = GetPrivateProfileInt(PROGFIELD,COUNTKEY,0,m_sInifilename);
			char sKeyname[3];
			memset(sKeyname, 0, sizeof(sKeyname));
			sprintf(sKeyname, "%d", ++iCount);
			//字符串格式：名称25，选择日期7，日期10，时间5，路径。中间以“|”分割
			char str[256];
			memset(str, 0, sizeof(str));

			//添加提醒到CList中
			ProgramInfo *proginfo;
			proginfo = (ProgramInfo*)malloc(sizeof(ProgramInfo));
			memset(proginfo, 0, sizeof(ProgramInfo));
			strcpy(proginfo->Name, pronewdlg.m_sName);
			proginfo->Kind = pronewdlg.m_bcheck;
			TimeToString(pronewdlg.m_tTime, proginfo->Time);
			strcpy(proginfo->Path, pronewdlg.m_sPath);

			if(proginfo->Kind)
			{
				//某日定时
				DateToString(pronewdlg.m_dDate, proginfo->Date);
				strcpy(proginfo->Checkday, "");
				sprintf(str, "%s|1|%s|%s|%s|%s|",proginfo->Name,proginfo->Checkday,proginfo->Date,proginfo->Time,proginfo->Path);
			}
			else
			{
				//一周中选择几天
				strcpy(proginfo->Date, "");
				strcpy(proginfo->Checkday, pronewdlg.m_sCheckday);
				sprintf(str, "%s|0|%s|%s|%s|%s|",proginfo->Name,proginfo->Checkday,proginfo->Date,proginfo->Time,proginfo->Path);
			}
			AddToList(&proglist, proginfo);

			WritePrivateProfileString(PROGFIELD,COUNTKEY,sKeyname,m_sInifilename);
			WritePrivateProfileString(PROGFIELD,sKeyname,str,m_sInifilename);

			char sshowcheckday[20];
			memset(sshowcheckday, 0, sizeof(sshowcheckday));
			NumstringToChnstring(proginfo->Checkday, sshowcheckday);

			int nItem;
			nItem = m_proglist.InsertItem(0xffff,sKeyname,0);
			m_proglist.SetItem(nItem,1,LVIF_TEXT,proginfo->Name,0,0,0,0);
			m_proglist.SetItem(nItem,2,LVIF_TEXT,sshowcheckday,0,0,0,0);
			m_proglist.SetItem(nItem,3,LVIF_TEXT,proginfo->Date,0,0,0,0);
			m_proglist.SetItem(nItem,4,LVIF_TEXT,proginfo->Time,0,0,0,0);
			m_proglist.SetItem(nItem,5,LVIF_TEXT,proginfo->Path,0,0,0,0);

			m_nCurrentProg = nItem;

			m_proglist.SetItemState(m_nCurrentProg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			m_proglist.SetFocus();
		}
		break;
	case 1:
		//添加消息提醒
		strcpy(msgnewdlg.m_sCaption, "添加消息提醒");
		msgnewdlg.m_nCaption = 0;
		msgnewdlg.m_tTime = dCurrenttime;
		if(msgnewdlg.DoModal()==IDOK)
		{
			int iCount = GetPrivateProfileInt(MSGFIELD,COUNTKEY,0,m_sInifilename);
			char sKeyname[3],sMsg[256];
			memset(sKeyname, 0, sizeof(sKeyname));
			sprintf(sKeyname, "%d", ++iCount);
			//字符串格式：日期10，选择日期7，时间5，消息。中间以“|”分割
			char str[256];
			memset(str, 0, sizeof(str));

			//添加提醒到CList中
			MessageInfo *msginfo;
			msginfo = (MessageInfo*)malloc(sizeof(MessageInfo));
			memset(msginfo, 0, sizeof(MessageInfo));
			msginfo->Kind = msgnewdlg.m_bcheck;
			TimeToString(msgnewdlg.m_tTime, msginfo->Time);
			strcpy(msginfo->Msg, msgnewdlg.m_sMsg);

			int npos = 0;
			memset(sMsg, 0, sizeof(sMsg));
			strcpy(sMsg, msginfo->Msg);
			while((npos = strcspn(sMsg, "\r\n")) >= 0 && npos < strlen(sMsg))
			{
				memcpy(sMsg + npos, "&&", 2);
			}

			if(msginfo->Kind)
			{
				//某日定时
				DateToString(msgnewdlg.m_dDate, msginfo->Date);
				strcpy(msginfo->Checkday, "");
				sprintf(str, "1|%s|%s|%s|%s|",msginfo->Checkday,msginfo->Date,msginfo->Time,sMsg);
			}
			else
			{
				//一周中选择几天
				strcpy(msginfo->Date, "");
				strcpy(msginfo->Checkday, msgnewdlg.m_sCheckday);
				sprintf(str, "0|%s|%s|%s|%s|",msginfo->Checkday,msginfo->Date,msginfo->Time,sMsg);
			}
			AddToList(&msglist, msginfo);

			WritePrivateProfileString(MSGFIELD,COUNTKEY,sKeyname,m_sInifilename);
			WritePrivateProfileString(MSGFIELD,sKeyname,str,m_sInifilename);
			
			char sshowcheckday[20];
			memset(sshowcheckday, 0, sizeof(sshowcheckday));
			NumstringToChnstring(msginfo->Checkday, sshowcheckday);

			int nItem;
			nItem = m_msglist.InsertItem(0xffff,sKeyname,0);
			m_msglist.SetItem(nItem,1,LVIF_TEXT,sshowcheckday,0,0,0,0);
			m_msglist.SetItem(nItem,2,LVIF_TEXT,msginfo->Date,0,0,0,0);
			m_msglist.SetItem(nItem,3,LVIF_TEXT,msginfo->Time,0,0,0,0);
			m_msglist.SetItem(nItem,4,LVIF_TEXT,msginfo->Msg,0,0,0,0);

			m_nCurrentMsg = nItem;

			m_msglist.SetItemState(m_nCurrentMsg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			m_msglist.SetFocus();	
		}
		break;
	case 2:
		//定时关闭进程
		strcpy(processdlg.m_sCaption, "添加定时关闭进程");
		processdlg.m_dTime = dCurrenttime;
		if(processdlg.DoModal()==IDOK)
		{
			int iCount = m_proclist.GetItemCount();
			char sKeyname[3];
			memset(sKeyname, 0, sizeof(sKeyname));
			sprintf(sKeyname, "%d", ++iCount);
			//字符串格式：日期10，时间5，名称25，ID。中间以“|”分割
			ProcessInfo *procinfo;
			procinfo = (ProcessInfo*)malloc(sizeof(ProcessInfo));
			memset(procinfo, 0, sizeof(ProcessInfo));

			char str[256];
			memset(str, 0, sizeof(str));
			strcpy(procinfo->Name, processdlg.m_sName);
			strcpy(procinfo->PID , processdlg.m_sID);
			DateToString(processdlg.m_dDate, procinfo->Date);
			TimeToString(processdlg.m_dTime, procinfo->Time);

			AddToList(&proclist, procinfo);

			int nItem;
			nItem = m_proclist.InsertItem(0xffff,sKeyname,0);
			m_proclist.SetItem(nItem,1,LVIF_TEXT,procinfo->PID,0,0,0,0);
			m_proclist.SetItem(nItem,2,LVIF_TEXT,procinfo->Name,0,0,0,0);
			m_proclist.SetItem(nItem,3,LVIF_TEXT,procinfo->Date,0,0,0,0);
			m_proclist.SetItem(nItem,4,LVIF_TEXT,procinfo->Time,0,0,0,0);

			m_nCurrentTerm = nItem;

			m_proclist.SetItemState(m_nCurrentTerm,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			m_proclist.SetFocus();
		}
		break;
	default:
		break;
	}
}

void CRemindView::OnEditMod() 
{
	// TODO: Add your command handler code here
	char str[256];
	if(m_nActivepage==0)
	{
		m_nCurrentProg = ::SendMessage(m_proglist,(UINT) LVM_GETNEXTITEM,-1,LVNI_SELECTED);
		//修改应用程序提醒
		if(m_nCurrentProg<0)
		{
			return;
		}
		//从列表取得数据
		char sKeyname[3];
		memset(sKeyname, 0, sizeof(sKeyname));
		strcpy(sKeyname, m_proglist.GetItemText(m_nCurrentProg,0));

		ProgramInfo *proginfo;
		proginfo = GetListNode(&proglist, m_nCurrentProg);

		//修改窗口初始化
		CPronewDlg pronewdlg;
		strcpy(pronewdlg.m_sCaption, "修改应用程序提醒");
		pronewdlg.m_nCaption = 1;
		pronewdlg.m_nKind = proginfo->Kind;
		pronewdlg.m_sName = proginfo->Name;
		if(proginfo->Kind==0)
		{
			//一周中选择几天
			pronewdlg.m_dDate.SetStatus(COleDateTime::null);
			pronewdlg.m_bcheck = FALSE;
			CheckStringToIntArray(proginfo->Checkday,pronewdlg.array);
		}
		else
		{
			//某日定时
			int nReturn = StrToDate(proginfo->Date,&pronewdlg.m_dDate);
			pronewdlg.m_bcheck = TRUE;
			if(nReturn<0)
			{
				ShowStrFormatError();
				return;
			}
		}
		int nReturn = StrToTime(proginfo->Time,&pronewdlg.m_tTime);
		if(nReturn<0)
		{
			ShowStrFormatError();
			return;
		}
		pronewdlg.m_sPath = proginfo->Path;
		if(pronewdlg.DoModal()==IDOK)
		{
			//字符串格式：名称25，选择日期7，日期10，时间5，路径。中间以“|”分割
			strcpy(proginfo->Name, pronewdlg.m_sName);
			TimeToString(pronewdlg.m_tTime, proginfo->Time);
			strcpy(proginfo->Path, pronewdlg.m_sPath);
			proginfo->Kind = pronewdlg.m_bcheck;
			if(pronewdlg.m_bcheck)
			{
				DateToString(pronewdlg.m_dDate, proginfo->Date);
				strcpy(proginfo->Checkday, "");
				memset(str, 0, sizeof(str));
				sprintf(str, "%s|1|%s|%s|%s|%s|",proginfo->Name,proginfo->Checkday,proginfo->Date,proginfo->Time,proginfo->Path);
			}
			else
			{
				strcpy(proginfo->Date, "");
				strcpy(proginfo->Checkday, pronewdlg.m_sCheckday);
				memset(str, 0, sizeof(str));
				sprintf(str, "%s|0|%s|%s|%s|%s|",proginfo->Name,proginfo->Checkday,proginfo->Date,proginfo->Time,proginfo->Path);
			}

			WritePrivateProfileString(PROGFIELD,sKeyname,str,m_sInifilename);

			char sshowcheckday[20];
			memset(sshowcheckday, 0, sizeof(sshowcheckday));
			NumstringToChnstring(proginfo->Checkday, sshowcheckday);

			m_proglist.SetItem(m_nCurrentProg,1,LVIF_TEXT,proginfo->Name,0,0,0,0);
			m_proglist.SetItem(m_nCurrentProg,2,LVIF_TEXT,sshowcheckday,0,0,0,0);
			m_proglist.SetItem(m_nCurrentProg,3,LVIF_TEXT,proginfo->Date,0,0,0,0);
			m_proglist.SetItem(m_nCurrentProg,4,LVIF_TEXT,proginfo->Time,0,0,0,0);
			m_proglist.SetItem(m_nCurrentProg,5,LVIF_TEXT,proginfo->Path,0,0,0,0);

			m_proglist.SetItemState(m_nCurrentProg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			m_proglist.SetFocus();
		}
	}
	else if(m_nActivepage==1)
	{
		m_nCurrentMsg = ::SendMessage(m_msglist,(UINT) LVM_GETNEXTITEM,-1,LVNI_SELECTED);
		//修改消息提醒
		if(m_nCurrentMsg<0)
		{
			return;
		}
		//从列表取得数据
		char sKeyname[3];
		memset(sKeyname, 0, sizeof(sKeyname));
		strcpy(sKeyname, m_msglist.GetItemText(m_nCurrentMsg,0));

		MessageInfo *msginfo;
		msginfo = GetListNode(&msglist, m_nCurrentMsg);

		//修改窗口初始化
		CMsgnewDlg msgnewdlg;
		strcpy(msgnewdlg.m_sCaption, "修改消息提醒");
		msgnewdlg.m_nCaption = 1;
		msgnewdlg.m_nKind = msginfo->Kind;
		
		//某日定时还是一周中选择几天
		if(msginfo->Kind==0)
		{
			msgnewdlg.m_dDate.SetStatus(COleDateTime::null);
			msgnewdlg.m_bcheck = FALSE;
			CheckStringToIntArray(msginfo->Checkday,msgnewdlg.array);
		}
		else
		{
			int nReturn = StrToDate(msginfo->Date,&msgnewdlg.m_dDate);
			msgnewdlg.m_bcheck = TRUE;
			if(nReturn<0)
			{
				ShowStrFormatError();
				return;
			}
		}

		int nReturn = StrToTime(msginfo->Time,&msgnewdlg.m_tTime);
		if(nReturn<0)
		{
			ShowStrFormatError();
			return;
		}
		msgnewdlg.m_sMsg = msginfo->Msg;
		if(msgnewdlg.DoModal()==IDOK)
		{
			//字符串格式：日期10，时间5，消息。中间以“|”分割
			char sMsg[256];
			TimeToString(msgnewdlg.m_tTime, msginfo->Time);
			strcpy(msginfo->Msg, msgnewdlg.m_sMsg);

			memset(str, 0, sizeof(str));

			int npos = 0;
			memset(sMsg, 0, sizeof(sMsg));
			strcpy(sMsg, msginfo->Msg);
			while((npos = strcspn(sMsg, "\r\n")) >= 0 && npos < strlen(sMsg))
			{
				memcpy(sMsg + npos, "&&", 2);
			}

			//某日定时还是一周中选择几天
			if(msgnewdlg.m_bcheck)
			{
				DateToString(msgnewdlg.m_dDate, msginfo->Date);
				strcpy(msginfo->Checkday, "");
				sprintf(str, "1|%s|%s|%s|%s|",msginfo->Checkday,msginfo->Date,msginfo->Time,sMsg);
			}
			else
			{
				strcpy(msginfo->Date, "");
				strcpy(msginfo->Checkday, msgnewdlg.m_sCheckday);
				sprintf(str,"0|%s|%s|%s|%s|",msginfo->Checkday,msginfo->Date,msginfo->Time,sMsg);
			}

			WritePrivateProfileString(MSGFIELD,sKeyname,str,m_sInifilename);

			char sshowcheckday[20];
			memset(sshowcheckday, 0, sizeof(sshowcheckday));
			NumstringToChnstring(msginfo->Checkday, sshowcheckday);

			m_msglist.SetItem(m_nCurrentMsg,1,LVIF_TEXT,sshowcheckday,0,0,0,0);
			m_msglist.SetItem(m_nCurrentMsg,2,LVIF_TEXT,msginfo->Date,0,0,0,0);
			m_msglist.SetItem(m_nCurrentMsg,3,LVIF_TEXT,msginfo->Time,0,0,0,0);
			m_msglist.SetItem(m_nCurrentMsg,4,LVIF_TEXT,msginfo->Msg,0,0,0,0);

			m_msglist.SetItemState(m_nCurrentMsg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			m_msglist.SetFocus();
		}
	}
	else if(m_nActivepage==2)
	{
		m_nCurrentTerm = ::SendMessage(m_proclist,(UINT) LVM_GETNEXTITEM,-1,LVNI_SELECTED);
		//修改定时关闭进程
		if(m_nCurrentTerm<0)
		{
			return;
		}
		//从列表取得数据

		ProcessInfo *procinfo;
		procinfo = GetListNode(&proclist, m_nCurrentTerm);
		
		//修改窗口初始化
		CProcessDlg processdlg;
		strcpy(processdlg.m_sCaption, "修改关闭进程");
		strcpy(processdlg.m_sName, procinfo->Name);
		int nReturn = StrToDate(procinfo->Date,&processdlg.m_dDate);
		if(nReturn<0)
		{
			ShowStrFormatError();
			return;
		}
		nReturn = StrToTime(procinfo->Time,&processdlg.m_dTime);
		if(nReturn<0)
		{
			ShowStrFormatError();
			return;
		}
		strcpy(processdlg.m_sID, procinfo->PID);

		if(processdlg.DoModal()==IDOK)
		{
			//字符串格式：日期10，时间5，名称25，ID。中间以“|”分割
			strcpy(procinfo->Name, processdlg.m_sName);
			DateToString(processdlg.m_dDate, procinfo->Date);
			TimeToString(processdlg.m_dTime, procinfo->Time);
			strcpy(procinfo->PID, processdlg.m_sID);

			m_proclist.SetItem(m_nCurrentTerm,1,LVIF_TEXT,procinfo->PID,0,0,0,0);
			m_proclist.SetItem(m_nCurrentTerm,2,LVIF_TEXT,procinfo->Name,0,0,0,0);
			m_proclist.SetItem(m_nCurrentTerm,3,LVIF_TEXT,procinfo->Date,0,0,0,0);
			m_proclist.SetItem(m_nCurrentTerm,4,LVIF_TEXT,procinfo->Time,0,0,0,0);
		}
	}
}

void CRemindView::OnEditDel() 
{
	// TODO: Add your command handler code here
	if(m_nActivepage==0)
	{
		//删除应用程序提醒
		int iCount = GetPrivateProfileInt(PROGFIELD,COUNTKEY,0,m_sInifilename);
		if(iCount<1)
			return;
		if(MessageBox("确定要删除这条提醒吗？","提示",MB_YESNO+MB_ICONQUESTION)==IDNO)
			return;

		//从CList中删除当前的提醒
		m_nCurrentProg = ::SendMessage(m_proglist,(UINT) LVM_GETNEXTITEM,-1,LVNI_SELECTED);
		DelListNode(&proglist, m_nCurrentProg);

		m_proglist.DeleteItem(m_nCurrentProg);
		--iCount;
		if(m_nCurrentProg==iCount)
		{
			//如果选择的是最后一行
			--m_nCurrentProg;
		}
		else
		{
			char sKeyname[3], sKeyname1[3];
			for(int i=m_nCurrentProg;i<iCount;i++)
			{
				//修改列表显示
				char cstr[MAX_PATH];
				memset(sKeyname, 0, sizeof(sKeyname));
				memset(sKeyname1, 0, sizeof(sKeyname1));
				sprintf(sKeyname, "%d", i+1);
				sprintf(sKeyname1, "%d", i+2);
				m_proglist.SetItem(i,0,LVIF_TEXT,sKeyname,0,0,0,0);
				//修改INI文件
				GetPrivateProfileString(PROGFIELD,sKeyname1,"",cstr,MAX_PATH,m_sInifilename);
				WritePrivateProfileString(PROGFIELD,sKeyname,cstr,m_sInifilename);
			}
		}
		//删除最后一条键值
		char slastkey[3],sCount[3];
		memset(slastkey, 0, sizeof(slastkey));
		memset(sCount, 0, sizeof(sCount));
		sprintf(slastkey, "%d", iCount+1);
		sprintf(sCount, "%d", iCount);
		WritePrivateProfileString(PROGFIELD,slastkey,NULL,m_sInifilename);
		WritePrivateProfileString(PROGFIELD,COUNTKEY,sCount,m_sInifilename);
		
		m_proglist.SetItemState(m_nCurrentProg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_proglist.SetFocus();
	}
	else if(m_nActivepage==1)
	{
		//删除消息提醒
		int iCount = GetPrivateProfileInt(MSGFIELD,COUNTKEY,0,m_sInifilename);
		if(iCount<1)
			return;
		if(MessageBox("确定要删除这条提醒吗？","提示",MB_YESNO+MB_ICONQUESTION)==IDNO)
			return;

		//从CList中删除当前的提醒
		m_nCurrentMsg = ::SendMessage(m_msglist,(UINT) LVM_GETNEXTITEM,-1,LVNI_SELECTED);
		DelListNode(&msglist, m_nCurrentMsg);

		m_msglist.DeleteItem(m_nCurrentMsg);
		--iCount;
		if(m_nCurrentMsg==iCount)
		{
			//如果选择的是最后一行
			--m_nCurrentMsg;
		}
		else
		{
			char sKeyname[3], sKeyname1[3];
			for(int i=m_nCurrentMsg;i<iCount;i++)
			{
				//修改列表显示
				char cstr[MAX_PATH];
				memset(sKeyname, 0, sizeof(sKeyname));
				memset(sKeyname1, 0, sizeof(sKeyname1));
				sprintf(sKeyname, "%d", i+1);
				sprintf(sKeyname1, "%d", i+2);
				m_msglist.SetItem(i,0,LVIF_TEXT,sKeyname,0,0,0,0);
				//修改INI文件				
				GetPrivateProfileString(MSGFIELD,sKeyname1,"",cstr,MAX_PATH,m_sInifilename);
				WritePrivateProfileString(MSGFIELD,sKeyname,cstr,m_sInifilename);
			}
		}
		//删除最后一条键值
		char slastkey[3],sCount[3];
		memset(slastkey, 0, sizeof(slastkey));
		memset(sCount, 0, sizeof(sCount));
		sprintf(slastkey, "%d", iCount+1);
		sprintf(sCount, "%d", iCount);
		WritePrivateProfileString(MSGFIELD,slastkey,NULL,m_sInifilename);
		WritePrivateProfileString(MSGFIELD,COUNTKEY,sCount,m_sInifilename);

		m_msglist.SetItemState(m_nCurrentMsg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_msglist.SetFocus();
	}
	else if(m_nActivepage==2)
	{
		//删除定时关闭进程
		int iCount = m_proclist.GetItemCount();
		if(iCount<1 || m_nCurrentTerm<0)
			return;
		if(MessageBox("确定要删除这条信息吗？","提示",MB_YESNO+MB_ICONQUESTION)==IDNO)
			return;

		//从CList中删除当前的提醒
		m_nCurrentTerm = ::SendMessage(m_proclist,(UINT) LVM_GETNEXTITEM,-1,LVNI_SELECTED);
		DelListNode(&proclist, m_nCurrentTerm);

		m_proclist.DeleteItem(m_nCurrentTerm);
		--iCount;
		if(m_nCurrentTerm==iCount)
		{
			//如果选择的是最后一行
			--m_nCurrentTerm;
		}
		else
		{			
			char sKeyname[3];
			for(int i=m_nCurrentTerm;i<iCount;i++)
			{
				//修改列表显示
				memset(sKeyname, 0, sizeof(sKeyname));
				sprintf(sKeyname, "%d", i+1);
				m_proclist.SetItem(i,0,LVIF_TEXT,sKeyname,0,0,0,0);
			}
		}
		m_proclist.SetItemState(m_nCurrentTerm,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_proclist.SetFocus();
	}
}

void CRemindView::OnCkshut() 
{
	// TODO: Add your control notification handler code here
	//写入定时关机的信息
	//字符串格式：是否关机1，日期10，时间5，类型1，是否强制1。中间以“|”分割
	UpdateData(TRUE);
	if(m_nShuttype==-1)
		m_nShuttype = 9;
	if(m_nShutforce==-1)
		m_nShutforce = 9;
	if((m_nShuttype==9 || m_nShutforce==9) && m_bShut)
	{
		MessageBox("请选择关机类型！","提示",MB_OK+MB_ICONINFORMATION);
		m_bShut = FALSE;
		UpdateData(FALSE);
		return;
	}
	if(m_bShut && (MessageBox("确定要设定定时关机吗？","提示",MB_YESNO+MB_ICONQUESTION)==IDNO))
	{
		m_bShut = FALSE;
		UpdateData(FALSE);
		return;
	}
	char sShut[2],sDate[11],sTime[6],sType[20],sForce[20],str[256];
	memset(sShut, 0, sizeof(sShut));
	memset(sDate, 0, sizeof(sDate));
	memset(sTime, 0, sizeof(sTime));
	memset(sType, 0, sizeof(sType));
	memset(sForce, 0, sizeof(sForce));
	memset(str, 0, sizeof(str));
	if(m_bShut)
	{
		//关机状态信息写入INI文件
		strcpy(sShut, "T");
		DateToString(m_dShutdate, sDate);
		if(strlen(sDate) <= 0)
			strcpy(sDate, "          ");
		TimeToString(m_tShuttime, sTime);
		sprintf(str, "%s|%s|%s|%d|%d|",sShut,sDate,sTime,m_nShuttype,m_nShutforce);
		WritePrivateProfileString(SHUTFIELD,SHUTKEY,str,m_sInifilename);

		m_cShutdate.EnableWindow(FALSE);
		m_cShuttime.EnableWindow(FALSE);
		m_cType.EnableWindow(FALSE);
		m_cForce.EnableWindow(FALSE);

		//栏状态显示消息
		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CStatusBar* pStatus = &pFrame->m_wndStatusBar;
		if(pStatus)
		{
			pStatus->SetPaneText(1,"定时关机");
		}
	}
	else
	{
		//关机状态信息写入INI文件
		strcpy(sShut, "F");
		DateToString(m_dShutdate, sDate);
		if(strlen(sDate) <= 0)
			strcpy(sDate, "          ");
		TimeToString(m_tShuttime, sTime);
		sprintf(str, "%s|%s|%s|%d|%d|",sShut,sDate,sTime,m_nShuttype,m_nShutforce);
		WritePrivateProfileString(SHUTFIELD,SHUTKEY,str,m_sInifilename);

		m_cShutdate.EnableWindow(TRUE);
		m_cShuttime.EnableWindow(TRUE);
		m_cType.EnableWindow(TRUE);
		m_cForce.EnableWindow(TRUE);
	}
}

void CRemindView::ShutdownSystem(int nType, int nForce)
{
	//Power off your computer.
	//格式化日期时间字符串
	COleDateTime dShuttime = COleDateTime::GetCurrentTime();
	char sDatetime[20];
	memset(sDatetime, 0, sizeof(sDatetime));
	DateTimeToString(dShuttime, sDatetime);
	WritePrivateProfileString(SHUTFIELD,"Lastshuttime",sDatetime,m_sInifilename);

	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	
	// Get a token for this process. 
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		ERROR("OpenProcessToken"); 
	
	// Get the LUID for the shutdown privilege. 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get the shutdown privilege for this process. 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 
	
	// Cannot test the return value of AdjustTokenPrivileges. 
	if (GetLastError() != ERROR_SUCCESS) 
		ERROR("AdjustTokenPrivileges"); 
	
	// Shut down the system and force all applications to close. 
	switch(nType)
	{
	case 0:	/*关机*/
		if(nForce==0)	//强制关机	
		{
			if (!ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0))
				ERROR("ExitWindowsEx");
		}
		else			//非强制关机
		{
			if (!ExitWindowsEx(EWX_POWEROFF, 0))
				ERROR("ExitWindowsEx");
		}
		break;
	case 1:	/*重启*/
		if(nForce==0)	//强制重启	
		{
			if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0))
				ERROR("ExitWindowsEx");
		}
		else			//非强制重启
		{
			if (!ExitWindowsEx(EWX_REBOOT, 0))
				ERROR("ExitWindowsEx");
		}
		break;
	case 2:	/*注销*/
		if(nForce==0)	//强制注销	
		{
			if (!ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0))
				ERROR("ExitWindowsEx");
		}
		else			//非强制注销
		{
			if (!ExitWindowsEx(EWX_LOGOFF, 0))
				ERROR("ExitWindowsEx");
		}
		break;
	}
}

void CRemindView::OnBtnshutnow() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_nShuttype==-1 || m_nShutforce==-1)
	{
		MessageBox("请选择关机类型！","提示",MB_OK+MB_ICONINFORMATION);
		return;
	}

	char aType[3][16] = {"关闭机器","重新启动","注销登陆"};
	char aForce[2][8] = {"强制",""};
	char sMsg[128];
	memset(sMsg, 0, sizeof(sMsg));
	sprintf(sMsg, "确定要%s%s吗？", aForce[m_nShutforce], aType[m_nShuttype]);
	if(MessageBox(sMsg,"提示",MB_YESNO+MB_ICONQUESTION)==IDYES)
		ShutdownSystem(m_nShuttype,m_nShutforce);
}

void CRemindView::OnOptionBeep() 
{
	// TODO: Add your command handler code here
	//蜂鸣提示
	if(nBeep)
	{
		nBeep = 0;
	}
	else
	{
		nBeep = 1;
	}
	char m_sBeep[2];
	sprintf(m_sBeep, "%d", nBeep);
	WritePrivateProfileString(OPTFIELD,"Beep",m_sBeep,m_sInifilename);
}

void CRemindView::OnUpdateOptionBeep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(nBeep);
}

void CRemindView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	//随窗口的大小变化而变化
	CRect rect;	
	GetClientRect(&rect);
	//ClientToScreen(rect);
	if(m_tabCtrl.m_hWnd!=NULL)
	{
		//改变控件位置和大小
		m_tabCtrl.MoveWindow(6,6,rect.right-12,rect.bottom-69);
		m_proglist.MoveWindow(12,32,rect.right-24,rect.bottom-102);
		m_msglist.MoveWindow(12,32,rect.right-24,rect.bottom-102);
		m_proclist.MoveWindow(12,32,rect.right-24,rect.bottom-102);
		m_cGroup.MoveWindow(6,rect.bottom-63,rect.right-12,56);

		//m_cGroup.SetWindowPos(NULL,6,rect.bottom-63,0,0,SWP_NOSIZE);
		m_cCkshut.SetWindowPos(NULL,19,rect.bottom-38,0,0,SWP_NOSIZE);
		m_cShutdate.SetWindowPos(NULL,68,rect.bottom-42,0,0,SWP_NOSIZE);
		m_cShuttime.SetWindowPos(NULL,226,rect.bottom-42,0,0,SWP_NOSIZE);
		m_cType.SetWindowPos(NULL,320,rect.bottom-41,0,0,SWP_NOSIZE);
		m_cForce.SetWindowPos(NULL,424,rect.bottom-41,0,0,SWP_NOSIZE);
		m_btnShutnow.SetWindowPos(NULL,517,rect.bottom-41,0,0,SWP_NOSIZE);

		//在窗口四角设置一个弧形
		CRgn   rgnA;	
		VERIFY(rgnA.CreateRoundRectRgn(0,0,rect.right+12,rect.bottom+92,20,20));
		AfxGetMainWnd()->SetWindowRgn(rgnA,TRUE);
	}
}

void CRemindView::OnToolManproc() 
{
	// TODO: Add your command handler code here
	AfxBeginThread(ThreadManProc,GetSafeHwnd());
}

LRESULT CRemindView::OnManProcess(WPARAM wParam,LPARAM lParam)
{
	CManprocDlg manprocdlg;
	manprocdlg.DoModal();
	g_eventman.SetEvent();
	return 0;
}

UINT CRemindView::ThreadManProc(LPVOID pParam)
{
	::PostMessage((HWND)pParam,WM_MANPROCESS,0,0);
	::WaitForSingleObject(g_eventman, INFINITE);
	return 0;
}

void CRemindView::ShowProgHeader()
{
	//显示应用程序提醒内容
	//::SendMessage(m_proglist.m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	DWORD oldStyle = m_proglist.GetExtendedStyle();
	m_proglist.SetExtendedStyle(oldStyle|LVS_EX_FULLROWSELECT|LVS_EX_TRACKSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);

	m_proglist.InsertColumn(0,"序号",LVCFMT_LEFT,36);
	m_proglist.InsertColumn(1,"名称",LVCFMT_LEFT,164);
	m_proglist.InsertColumn(2,"选择日期",LVCFMT_LEFT,100);
	m_proglist.InsertColumn(3,"日期",LVCFMT_LEFT,72);
	m_proglist.InsertColumn(4,"时间",LVCFMT_LEFT,48);
	m_proglist.InsertColumn(5,"路径",LVCFMT_LEFT,288);
}

void CRemindView::ShowMsgHeader()
{
	//显示消息提醒内容
	//::SendMessage(m_cMsglist.m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	DWORD oldStyle = m_msglist.GetExtendedStyle();
	m_msglist.SetExtendedStyle(oldStyle|LVS_EX_FULLROWSELECT|LVS_EX_TRACKSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);

	m_msglist.InsertColumn(0,"序号",LVCFMT_LEFT,36);
	m_msglist.InsertColumn(1,"选择日期",LVCFMT_LEFT,100);
	m_msglist.InsertColumn(2,"日期",LVCFMT_LEFT,80);
	m_msglist.InsertColumn(3,"时间",LVCFMT_LEFT,48);
	m_msglist.InsertColumn(4,"消息",LVCFMT_LEFT,382);
}

void CRemindView::ShowProcHeader()
{
	//显示定时关闭进程内容
	//::SendMessage(m_cProclist.m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	DWORD oldStyle = m_proclist.GetExtendedStyle();
	m_proclist.SetExtendedStyle(oldStyle|LVS_EX_FULLROWSELECT|LVS_EX_TRACKSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_INFOTIP);

	m_proclist.InsertColumn(0,"序号",LVCFMT_LEFT,36);
	m_proclist.InsertColumn(1,"进程ID",LVCFMT_LEFT,80);
	m_proclist.InsertColumn(2,"进程",LVCFMT_LEFT,180);
	m_proclist.InsertColumn(3,"日期",LVCFMT_LEFT,100);
	m_proclist.InsertColumn(4,"时间",LVCFMT_LEFT,60);
}

void CRemindView::OnItemchangedProglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->uNewState&LVIS_SELECTED)
	{
		UpdateData(TRUE);
		m_nCurrentProg = pNMListView->iItem;
	}

	*pResult = 0;
}

void CRemindView::OnItemchangedMsglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->uNewState&LVIS_SELECTED)
	{
		UpdateData(TRUE);
		m_nCurrentMsg = pNMListView->iItem;
	}

	*pResult = 0;
}

void CRemindView::OnItemchangedProclist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->uNewState&LVIS_SELECTED)
	{
		UpdateData(TRUE);
		m_nCurrentTerm = pNMListView->iItem;
	}

	*pResult = 0;
}

void CRemindView::OnSelchangeTablist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_nActivepage = m_tabCtrl.GetCurSel();		//所选标签号
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	if(pStatus)
	{
		switch(m_nActivepage)
		{
		case 0:
			GetDlgItem(IDC_PROGLIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_MSGLIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PROCLIST)->ShowWindow(SW_HIDE);
			m_proglist.SetItemState(m_nCurrentProg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			m_proglist.SetFocus();
			pStatus->SetPaneText(0,"应用程序提醒");
			break;
		case 1:
			GetDlgItem(IDC_PROGLIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_MSGLIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_PROCLIST)->ShowWindow(SW_HIDE);
			m_msglist.SetItemState(m_nCurrentMsg,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			m_msglist.SetFocus();
			pStatus->SetPaneText(0,"消息提醒");
			break;
		case 2:
			GetDlgItem(IDC_PROGLIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_MSGLIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PROCLIST)->ShowWindow(SW_SHOW);
			m_proclist.SetItemState(m_nCurrentTerm,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
			m_proclist.SetFocus();
			pStatus->SetPaneText(0,"定时关闭进程");
		default:
			break;
		}
	}

	*pResult = 0;
}

void CRemindView::OnDblclkMsglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnEditMod();
	*pResult = 0;
}

void CRemindView::OnDblclkProclist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnEditMod();
	*pResult = 0;
}

void CRemindView::OnDblclkProglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnEditMod();
	*pResult = 0;
}

void CRemindView::ShowStrFormatError()
{
	MessageBox("字符串格式错误！\n请检查Remind.ini文件","警告",MB_OK+MB_ICONEXCLAMATION);
}

BOOL CRemindView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	///CView::OnEraseBkgnd(pDC);
}

void CRemindView::InitialListProg()
{
	//启动时开启应用程序提醒
	//字符串格式：名称25，类型1，选择日期7，日期10，时间5，路径。中间以“|”分割
	int iCountprog = GetPrivateProfileInt(PROGFIELD,COUNTKEY,0,m_sInifilename);
	if(iCountprog>0)
	{
		m_nCurrentProg = 0;
		char sKind[2];
		char s[3];
		char cstr[MAX_PATH];
		int nItem;
		for(int i=1; i<=iCountprog; i++)
		{
			memset(s, 0, sizeof(s));
			sprintf(s, "%d", i);
			GetPrivateProfileString(PROGFIELD,s,"",cstr,MAX_PATH,m_sInifilename);
			char sNum[3];
			if(strlen(cstr) > 0)
			{
				//往列表添加内容
				ProgramInfo *proginfo;
				proginfo = (ProgramInfo*)malloc(sizeof(ProgramInfo));
				memset(proginfo, 0, sizeof(ProgramInfo));
				
				getfld(cstr, proginfo->Name, 0);
				getfld(cstr, sKind, 1);
				proginfo->Kind = atoi(sKind);
				getfld(cstr, proginfo->Checkday, 2);
				getfld(cstr, proginfo->Date, 3);
				getfld(cstr, proginfo->Time, 4);
				getfld(cstr, proginfo->Path, 5);

				AddToList(&proglist, proginfo);
				
				memset(sNum, 0, sizeof(sNum));
				sprintf(sNum, "%d", i);

				char scheckday[20];
				memset(scheckday, 0, sizeof(scheckday));
				NumstringToChnstring(proginfo->Checkday, scheckday);

				nItem = m_proglist.InsertItem(0xffff,sNum,0);
				m_proglist.SetItem(nItem,1,LVIF_TEXT,proginfo->Name,0,0,0,0);
				m_proglist.SetItem(nItem,2,LVIF_TEXT,scheckday,0,0,0,0);
				m_proglist.SetItem(nItem,3,LVIF_TEXT,proginfo->Date,0,0,0,0);
				m_proglist.SetItem(nItem,4,LVIF_TEXT,proginfo->Time,0,0,0,0);
				m_proglist.SetItem(nItem,5,LVIF_TEXT,proginfo->Path,0,0,0,0);

				//运行从上次关机到本次开始中设置定时运行的程序
				if(proginfo->Kind == 1)
				{
					char sRuntime[20];
					memset(sRuntime, 0, sizeof(sRuntime));
					sprintf(sRuntime, "%s %s", proginfo->Date, proginfo->Time);
					if(stricmp(sRuntime, sLastshuttime)>=0 && stricmp(sRuntime, sStarttime)<=0)
					{
						BeepPrompt(nBeep);
						ShellExecute(m_hWnd,NULL,proginfo->Path,NULL,NULL,SW_SHOWNORMAL);
					}
				}
			}
		}
	}
	else
	{
		m_nCurrentProg = -1;
	}
}

void CRemindView::InitialListMsg()
{
	//启动时开启消息提醒
	//字符串格式：类型1，选择日期7，日期10，时间5，消息。中间以“|”分割
	int iCountmsg = GetPrivateProfileInt(MSGFIELD,COUNTKEY,0,m_sInifilename);
	if(iCountmsg>0)
	{
		m_nCurrentMsg = 0;
		char sKind[2];
		char s[3];
		char cstr[MAX_PATH];
		int nItem;
		for(int i=1; i<=iCountmsg; i++)
		{
			sprintf(s, "%d", i);
			GetPrivateProfileString(MSGFIELD,s,"",cstr,MAX_PATH,m_sInifilename);
			char sNum[5];
			if(strlen(cstr) > 0)
			{
				memset(sKind, 0, sizeof(sKind));
				MessageInfo *msginfo;
				msginfo = (MessageInfo*)malloc(sizeof(MessageInfo));
				memset(msginfo, 0, sizeof(MessageInfo));

				getfld(cstr, sKind, 0);
				msginfo->Kind = atoi(sKind);
				getfld(cstr, msginfo->Checkday, 1);
				getfld(cstr, msginfo->Date, 2);
				getfld(cstr, msginfo->Time, 3);
				getfld(cstr, msginfo->Msg, 4);
				
				int npos = 0;
				while((npos = strcspn(msginfo->Msg, "&&")) >= 0 && npos < strlen(msginfo->Msg))
				{
					memcpy(msginfo->Msg + npos, "\r\n", 2);
				}				
				AddToList(&msglist, msginfo);

				char scheckday[1024];
				memset(sNum, 0, sizeof(sNum));
				memset(scheckday, 0, sizeof(scheckday));
				sprintf(sNum, "%d", i);
				NumstringToChnstring(msginfo->Checkday, scheckday);

				nItem = m_msglist.InsertItem(0xffff,sNum,0);
				m_msglist.SetItem(nItem,1,LVIF_TEXT,scheckday,0,0,0,0);
				m_msglist.SetItem(nItem,2,LVIF_TEXT,msginfo->Date,0,0,0,0);
				m_msglist.SetItem(nItem,3,LVIF_TEXT,msginfo->Time,0,0,0,0);
				m_msglist.SetItem(nItem,4,LVIF_TEXT,msginfo->Msg,0,0,0,0);

				//运行从上次关机到本次开始中设置的定时提醒
				if(msginfo->Kind == 1)
				{
					char sRuntime[20];
					memset(sRuntime, 0, sizeof(sRuntime));
					sprintf(sRuntime, "%s %s", msginfo->Date, msginfo->Time);
					if((stricmp(sRuntime, sLastshuttime) >= 0) && (stricmp(sRuntime, sStarttime) <= 0))
					{
						BeepPrompt(nBeep);
						MessageBox(msginfo->Msg,"消息提醒",MB_OK+MB_ICONINFORMATION);
					}
				}
			}
		}
	}
	else
	{
		m_nCurrentMsg = -1;
	}
}

void CRemindView::InitialTimerShut()
{
	//获取定时关机设置
	//字符串格式：是否关机1，日期10，时间5，类型1，是否强制1。中间以“|”分割
	char sShut[2],sShutdate[11],sShuttime[6],sShuttype[2],sShutforce[2];
	char cstr[MAX_PATH];
	GetPrivateProfileString(SHUTFIELD,SHUTKEY,"",cstr,MAX_PATH,m_sInifilename);
	if(strlen(cstr) > 0)
	{
		memset(sShut, 0, sizeof(sShut));
		memset(sShutdate, 0, sizeof(sShutdate));
		memset(sShuttime, 0, sizeof(sShuttime));
		memset(sShuttype, 0, sizeof(sShuttype));
		memset(sShutforce, 0, sizeof(sShutforce));
		getfld(cstr, sShut, 0);
		getfld(cstr, sShutdate, 1);
		getfld(cstr, sShuttime, 2);
		getfld(cstr, sShuttype, 3);
		getfld(cstr, sShutforce, 4);

		char temp[2];
		//是否自动关机
		if(strcmp(sShut,"T") == 0)
			m_bShut = TRUE;
		else
			m_bShut = FALSE;
		//每天定时关机还是某一天某时
		if(sShutdate=="          ")
			m_dShutdate.SetStatus(COleDateTime::null);
		else
		{
			int nReturn = StrToDate(sShutdate, &m_dShutdate);
			if(nReturn<0)
			{
				ShowStrFormatError();
				return;
			}
		}
		int nReturn = StrToTime(sShuttime,&m_tShuttime);
		if(nReturn<0)
			{
				ShowStrFormatError();
				return;
			}
		//自动关机类型
		strcpy(temp, sShuttype);
		m_nShuttype = atoi(temp);
		if(m_nShuttype>2)
			m_nShuttype = -1;
		strcpy(temp,sShutforce);
		m_nShutforce = atoi(temp);
		if(m_nShutforce>1)
			m_nShutforce = -1;

		UpdateData(FALSE);

		m_cShutdate.EnableWindow(!m_bShut);
		m_cShuttime.EnableWindow(!m_bShut);
		m_cType.EnableWindow(!m_bShut);
		m_cForce.EnableWindow(!m_bShut);
	}
}

void CRemindView::OnToolMailcheck() 
{
	// TODO: Add your command handler code here
	//修改邮箱设置，定时检测设置
	CMailcheckDlg maildlg;

	maildlg.m_bCkmail = GetPrivateProfileInt(MAILFIELD,MAILCHECKKEY,0,m_sInifilename);
	maildlg.m_nCheckmail = m_nMailInterval;
	
	if(maildlg.DoModal()==IDOK)
	{
		char sInternal[5];
		memset(sInternal, 0, sizeof(sInternal));
		sprintf(sInternal, "%d", maildlg.m_nCheckmail);
		WritePrivateProfileString(MAILFIELD,MAILINTERVALKEY,sInternal,m_sInifilename);
		if(maildlg.m_bCkmail)
		{
			WritePrivateProfileString(MAILFIELD,MAILCHECKKEY,"1",m_sInifilename);
			if(m_nMailInterval!=maildlg.m_nCheckmail)
			{
				m_nMailInterval = maildlg.m_nCheckmail;
				KillTimer(ID_CHECKMAIL_TIMER);
				SetTimer(ID_CHECKMAIL_TIMER, m_nMailInterval*60000, NULL);
			}
		}
		else
		{
			WritePrivateProfileString(MAILFIELD,MAILCHECKKEY,"0",m_sInifilename);
			KillTimer(ID_CHECKMAIL_TIMER);
		}
	}
}

UINT CRemindView::ThreadCheckMail(LPVOID pParam)
{
	::PostMessage((HWND)pParam,WM_CHECKMAIL,0,0);
	::WaitForSingleObject(g_eventmail, INFINITE);
	return 0;
}

LRESULT CRemindView::OnCheckMail(WPARAM wParam,LPARAM lParam)
{
	//检查邮箱里邮件数，并提醒
	KillTimer(ID_CHECKMAIL_TIMER);
	int nCount = GetListCount(&maillist);
	char password[128];
	if(nCount>0)
	{
		CheckMail *checkmail = maillist;
		char sMsg[512], strtemp[128];
		memset(sMsg, 0, sizeof(sMsg));
		while(checkmail != NULL)
		{
			memset(password, 0, sizeof(password));
			Endecrypt_Mars(checkmail->password, password, 0);
			
			CPop3 PopServer;
			
			if(PopServer.Connect(checkmail->host,checkmail->user,password)==FALSE)
			{
				memset(strtemp, 0, sizeof(strtemp));
				sprintf(strtemp, "无法连接%s的邮件服务器......\r\n", checkmail->mail);
				strcat(sMsg, strtemp);
			}
			else if(PopServer.Statistics()==FALSE)
			{
				//Beep(32767,1000);	// produce Beep sound 
				//m_Error = 2;
			}
			else
			{
				m_NoMail = PopServer.GetNumberOfMails();
				if(m_NoMail>0)
				{
					memset(strtemp, 0, sizeof(strtemp));
					sprintf(strtemp, "您的邮箱%s里总共有 %d 封邮件！\r\n", checkmail->mail,m_NoMail);
					strcat(sMsg, strtemp);				
				}
			}
			checkmail = checkmail->next;
		}
		
		if(strlen(sMsg) > 0)
		{
			char msgtemp[512];
			memset(msgtemp, 0, sizeof(msgtemp));
			sprintf(msgtemp, "Remind:%s", sMsg);
			CStatusBarMsgWnd* t_MsgWnd = CStatusBarMsgWnd::CreateObject(
				msgtemp, 
				180, 
				100, 
				6000, 
				10,
				CRect(10, 10, 160, 160),
				this);
			t_MsgWnd->PopMsg();
		}
	}
	
	SetTimer(ID_CHECKMAIL_TIMER, m_nMailInterval*60000, NULL);
	
	g_eventmail.SetEvent();
	return 0;
}

void CRemindView::StartCheckMail()
{
	//启动定时检查邮件定时器
	maillist = NULL;

	int nCheckmail = GetPrivateProfileInt(MAILFIELD,MAILCHECKKEY,0,m_sInifilename);
	int nCount = GetPrivateProfileInt(MAILFIELD,COUNTKEY,0,m_sInifilename);
	if(nCheckmail && nCount)
	{
		m_nMailInterval = GetPrivateProfileInt(MAILFIELD,MAILINTERVALKEY,5,m_sInifilename);
		SetTimer(ID_CHECKMAIL_TIMER,m_nMailInterval*60000,NULL);
	}

	char cstr[MAX_PATH];
	char sKey[3];
	for(int i=0;i<nCount;i++)
	{
		memset(sKey, 0, sizeof(sKey));
		sprintf(sKey, "%d", i+1);
		GetPrivateProfileString(MAILFIELD,sKey,"",cstr,MAX_PATH,m_sInifilename);

		CheckMail *checkmail;
		checkmail = (CheckMail*)malloc(sizeof(CheckMail));
		memset(checkmail, 0, sizeof(CheckMail));

		getfld(cstr, checkmail->mail, 0);
		getfld(cstr, checkmail->host, 1);
		getfld(cstr, checkmail->user, 2);
		getfld(cstr, checkmail->password, 3);

		AddToList(&maillist, checkmail);
	}
}

void CRemindView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	char sSystemdatetime[20],sSystemtime[20];
	char sDatetime[20];
	memset(sSystemdatetime, 0, sizeof(sSystemdatetime));
	memset(sSystemtime, 0, sizeof(sSystemtime));

	COleDateTime dCurrenttime = COleDateTime::GetCurrentTime();
	DateTimeToString(dCurrenttime, sSystemdatetime);
	strcpy(sSystemtime, sSystemdatetime + 11);

	switch(nIDEvent)
	{
	case ID_REMIND_TIMER:
		//应用程序提醒
		//字符串格式：名称25，日期10，时间5，路径。中间以“|”分割
		int nCountprog;
		nCountprog = GetListCount(&proglist);
		if(nCountprog>0)
		{
			ProgramInfo *proginfo;
			proginfo = proglist;
			while(proginfo != NULL)
			{	
				if(proginfo->Kind==0)
				{
					//没有日期
					int ndayofweek = dCurrenttime.GetDayOfWeek();						
					int arr[7];
					CheckStringToIntArray(proginfo->Checkday,arr);
					//查找当天是一周中的那一天并与ini文件中数据查找匹配的，如果匹配，则执行
					for(int i=0;i<7;i++)
					{
						if(arr[i]==ndayofweek)
						{	
							if(stricmp(sSystemtime, proginfo->Time)==0)
							{
								BeepPrompt(nBeep);
								ShellExecute(m_hWnd,NULL,(LPCTSTR)proginfo->Path,NULL,NULL,SW_SHOWNORMAL);
							}
						}
					}					
				}
				else
				{
					//时间日期日期齐全
					memset(sDatetime, 0, sizeof(sDatetime));
					sprintf(sDatetime, "%s %s", proginfo->Date, proginfo->Time);
					if(stricmp(sDatetime, sSystemdatetime)==0)
					{
						BeepPrompt(nBeep);
						ShellExecute(m_hWnd,NULL,(LPCTSTR)proginfo->Path,NULL,NULL,SW_SHOWNORMAL);
					}
				}
				proginfo = proginfo->next;
			}
		}
		//break;
	//case ID_MESSAGE_TIMER:
		//消息提醒
		//字符串格式：日期10，时间5，消息。中间以“|”分割
		int nCountmsg;
		nCountmsg = GetListCount(&msglist);
		if(nCountmsg>0)
		{
			MessageInfo *msginfo;
			msginfo = msglist;
			while(msginfo != NULL)
			{
				//查找当天是一周中的那一天并与ini文件中数据查找匹配的，如果匹配，则执行
				if(msginfo->Kind==0)
				{
					//没有日期
					int ndayofweek = dCurrenttime.GetDayOfWeek();						
					int arr[7];
					CheckStringToIntArray(msginfo->Checkday,arr);
					for(int i=0;i<7;i++)
					{
						if(arr[i]==ndayofweek)
						{	
							if(stricmp(sSystemtime, msginfo->Time)==0)
							{
								BeepPrompt(nBeep);
								MessageBox(msginfo->Msg,"消息提醒",MB_OK+MB_ICONINFORMATION);
							}
						}
					}
				}
				else
				{
					//时间日期日期齐全
					memset(sDatetime, 0, sizeof(sDatetime));
					sprintf(sDatetime, "%s %s", msginfo->Date, msginfo->Time);
					if(stricmp(sDatetime, sSystemdatetime)==0)
					{
						BeepPrompt(nBeep);
						MessageBox(msginfo->Msg,"消息提醒",MB_OK+MB_ICONINFORMATION);
					}
				}
				msginfo = msginfo->next;
			}
		}
		//break;
	//case ID_TERMINATE_TIMER:
		//关闭进程
		//字符串格式：日期10，时间5，名称25，ID。中间以“|”分割
		int nCountterm;
		nCountterm = GetListCount(&proclist);
		if(nCountterm>0)
		{
			int i = 1;
			ProcessInfo *procinfo;
			procinfo = proclist;
			while(procinfo != NULL)
			{
				//时间日期日期齐全
				memset(sDatetime, 0, sizeof(sDatetime));
				sprintf(sDatetime, "%s %s", procinfo->Date, procinfo->Time);
				if(stricmp(sDatetime, sSystemdatetime) == 0)
				{
					HANDLE handle=OpenProcess(PROCESS_ALL_ACCESS,TRUE,(DWORD)atoi(procinfo->PID));
					if(handle!=NULL)
					{
						//关闭进程，删除当前节点
						TerminateProcess(handle,0);

						procinfo = procinfo->next;
						DelListNode(&proclist, i - 1);				

						m_proclist.DeleteItem(i-1);
						--nCountterm;
						if(i==nCountterm+1)
						{
							//如果执行的是最后一行
							if(m_nCurrentTerm==nCountterm)
								--m_nCurrentTerm;
						}
					}
				}
				else
				{
					i++;
					procinfo = procinfo->next;
				}
			}
		}
		break;
	case ID_SHUT_TIMER:
		//定时关机
		if(m_bShut)
		{
			char sDate[11],sTime[9];
			memset(sDate, 0, sizeof(sDate));
			memset(sTime, 0, sizeof(sTime));
			memset(sDatetime, 0, sizeof(sDatetime));
			DateToString(m_dShutdate, sDate);
			TimeToString(m_tShuttime, sTime);
			sprintf(sDatetime, "%s %s", sDate, sTime);
			if(m_dShutdate.GetStatus() == COleDateTime::null)
			{
				//没有日期
				if(stricmp(sTime, sSystemtime)==0)
				{
					TRACE("Shutting down now!\n");
					ShutdownSystem(m_nShuttype,m_nShutforce);
				}
			}
			else
			{
				//时间日期日期齐全
				if(stricmp(sDatetime, sSystemdatetime)==0)
				{
					TRACE("Shutting down now!\n");
					ShutdownSystem(m_nShuttype,m_nShutforce);
				}
			}
		}
		break;
	case ID_CHECKMAIL_TIMER:
		AfxBeginThread(ThreadCheckMail,GetSafeHwnd());
		break;
	}

	CFormView::OnTimer(nIDEvent);
}

void CRemindView::GetImageRect(CRect &rc)
{
	//获得显示背景图的区域
	CRemindDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CPicture* ppic = pDoc->GetPicture();
	ASSERT(ppic);
	if (!ppic || !*ppic) 
	{
		rc.SetRect(0,0,0,0);
	} 
	else
	{
		GetClientRect(&rc);
	}
}

void CRemindView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	//设置背景图
	if(m_nIspicture)
	{
		CRect rect;	
		GetClientRect(rect);
		pDC->FillRect(rect,&m_brushBackground);
		CRemindDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		CPicture* ppic = pDoc->GetPicture();
		ASSERT(ppic);
		if (*ppic) 
		{
			CRect rc;
			GetImageRect(rc);
			ppic->Render(pDC,rc);
		}
	}
}

void CRemindView::OnOptionGetpic() 
{
	// TODO: Add your command handler code here
	char szFilters[] = "Picture Files (*.jpg)|*.jpg|";
	CFileDialog fileDlg(TRUE, "jpg", "*.jpg",OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	if(fileDlg.DoModal()==IDOK)
	{
		char picpath[128];
		CDC *pDC;

		memset(picpath, 0, sizeof(picpath));
		strcpy(picpath, fileDlg.GetPathName());
		WritePrivateProfileString(OPTFIELD,BKGPICKEY,picpath,m_sInifilename);
		CRemindDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		m_nIspicture = pDoc->m_pict.Load(picpath);
		pDC = GetDC();
		OnDraw(pDC);
		CFormView::OnInitialUpdate();
		RefreshView();
	}
}

int CRemindView::RefreshView()
{
	m_btnShutnow.DrawTransparent(TRUE);
	return 0;
}
