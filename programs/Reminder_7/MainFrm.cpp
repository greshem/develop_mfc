// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Remind.h"

#include "MainFrm.h"
#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_ICON_NOTIFY WM_USER+10 /*自定义消息*/

extern char m_sInifilename[128];/*INI文件路径*/
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_APP_TERMINATE, OnAppTerminate)
	ON_COMMAND(ID_OPTION_ONTOP, OnOptionOntop)
	ON_UPDATE_COMMAND_UI(ID_OPTION_ONTOP, OnUpdateOptionOntop)
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_OPTION_AUTORUN, OnOptionAutorun)
	ON_UPDATE_COMMAND_UI(ID_OPTION_AUTORUN, OnUpdateOptionAutorun)
	ON_COMMAND(ID_APP_APP, OnAppApp)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ICON_NOTIFY, OnIconNotification)
	//ON_MESSAGE(WM_QUERYENDSESSION, OnQueryEndSession)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	//GetPrivateProfileInt(m_sOptionfield,"Beep",0,m_sInifilename);
	int ret;
	char str[128];
	memset(str, 0, sizeof(str));

	ret = GetRegValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\0", "Remind", str);
	if((ret != 0) && (strlen(str) <= 0))
		m_bAutorun = FALSE;
	else
		m_bAutorun = TRUE;
}

CMainFrame::~CMainFrame()
{
	/*if (m_bmClose.m_hObject)
		m_bmClose.DeleteObject();
	
	if (m_bmInsert.m_hObject)
		m_bmInsert.DeleteObject();
	
	if (m_bmModify.m_hObject)
		m_bmModify.DeleteObject();
	
	if (m_bmDelete.m_hObject)
		m_bmDelete.DeleteObject();
	
	if (m_bmManrpoc.m_hObject)
		m_bmManrpoc.DeleteObject(); */
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//设置窗口形状
	//CRgn   rgnA;
	/*CPoint ptVertex[8];
	ptVertex[0].x = 0;
	ptVertex[0].y = 10;
	ptVertex[1].x = 10;
	ptVertex[1].y = 0;
	ptVertex[2].x = 580;
	ptVertex[2].y = 0;
	ptVertex[3].x = 590;
	ptVertex[3].y = 10;
	ptVertex[4].x = 590;
	ptVertex[4].y = 460;
	ptVertex[5].y = 580;
	ptVertex[5].y = 470;
	ptVertex[6].x = 10;
	ptVertex[6].y = 470;
	ptVertex[7].y = 0;
	ptVertex[7].y = 460;	
	VERIFY(rgnA.CreatePolygonRgn( ptVertex, 8, WINDING));
	SetWindowRgn(rgnA,TRUE);*/
	
	/*//给菜单加位图
	ASSERT(m_bmClose.LoadBitmap(IDB_BMCLOSE));//CBitmap 类型的成员变量
	ASSERT(m_bmInsert.LoadBitmap(IDB_BMINSERT));
	ASSERT(m_bmModify.LoadBitmap(IDB_BMMODIFY));
	ASSERT(m_bmDelete.LoadBitmap(IDB_BMDELETE));
	ASSERT(m_bmManrpoc.LoadBitmap(IDB_BMMANPROC));

	CMenu* pMainMenu = GetMenu();
	CMenu* pSubMenu0 = pMainMenu->GetSubMenu(0);
	CMenu* pSubMenu1 = pMainMenu->GetSubMenu(1);
	CMenu* pSubMenu3 = pMainMenu->GetSubMenu(3);

	ASSERT(pSubMenu0->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bmClose,&m_bmClose));
	ASSERT(pSubMenu1->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bmInsert,&m_bmInsert));
	ASSERT(pSubMenu1->SetMenuItemBitmaps(1,MF_BYPOSITION,&m_bmModify,&m_bmModify));
	ASSERT(pSubMenu1->SetMenuItemBitmaps(2,MF_BYPOSITION,&m_bmDelete,&m_bmDelete));
	ASSERT(pSubMenu3->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bmManrpoc,&m_bmManrpoc));
	*/

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//设置ToolBar的图标列表,可以加入256色的图标
	//m_ilTB.Create(16, 16, TRUE | ILC_COLOR8, 4, 0);
	//HICON hIcon = NULL;
	//hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
	//	MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
	//m_ilTB.Add(hIcon);
	//hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
	//	MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, 0);
	//m_ilTB.Add(hIcon);
	//hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
	//	MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 16, 16, 0);
	//m_ilTB.Add(hIcon);
	//hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
	//	MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 16, 16, 0);
	//m_ilTB.Add(hIcon);
	//m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ilTB);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	//消息通知窗口//自定义消息//提示字符串//图标ID号//弹出菜单ID号 
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_MAINFRAME); 
	if (!m_systemIcon.Create(this,WM_ICON_NOTIFY,"每日提醒",hIcon,IDR_POPUP_MENU))
		return -1;

	nOntop = GetPrivateProfileInt(OPTFIELD,"Ontop",1,m_sInifilename);
	if(nOntop)
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	else
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	//加入系统菜单
	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//pSysMenu->AppendMenu(MF_SEPARATOR);
	//pSysMenu->AppendMenu(MF_STRING, WM_ALWAYSONTOP, "&Always On Top");

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
BOOL CMainFrame::OnQueryEndSession(WPARAM wReserved, LPARAM lEndReason)
{
	OnCloseProg();

    if(lEndReason == ENDSESSION_LOGOFF)
        // user is logging off
		;
    else
        // Windows is going down
		;

    return(TRUE);
}

LRESULT CMainFrame::OnIconNotification(WPARAM wParam, LPARAM lParam) 
{ 
	return m_systemIcon.OnIconNotification(wParam, lParam); 
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
	//CFrameWnd::OnClose();
}

void CMainFrame::OnAppTerminate() 
{
	// TODO: Add your command handler code here
	//删除图标，退出程序
	m_systemIcon.DeleteIcon();
	CFrameWnd::OnClose();
	//exit(1);
}

void CMainFrame::OnOptionOntop() 
{
	// TODO: Add your command handler code here
	//置于顶端
	if(nOntop)
	{
		nOntop = 0;
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	else
	{
		nOntop = 1;
		SetWindowPos(&wndTopMost, 0, 0, 0, 0,SWP_NOSIZE | SWP_NOMOVE);
	}
	char m_sOntop[2];
	memset(m_sOntop, 0, sizeof(m_sOntop));
	sprintf(m_sOntop,"%d",nOntop);
	WritePrivateProfileString(OPTFIELD,"Ontop",m_sOntop,m_sInifilename);
}

void CMainFrame::OnUpdateOptionOntop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(nOntop);
}

HMENU CMainFrame::NewMenu()
{
	// Load the menu from the resources
	m_menu.LoadMenu(IDR_MAINFRAME);  // ****replace IDR_MAINFRAME with your menu ID****
	m_menu.ModifyODMenu(NULL,ID_APP_TERMINATE,IDB_CLOSE);
	// Use ModifyODMenu to add a bitmap to a menu options.The first parameter
	// is the menu option text string.If it's NULL, keep the current text
	// string.The second option is the ID of the menu option to change.
	// The third option is the resource ID of the bitmap.This can also be a
	// toolbar ID in which case the class searches the toolbar for the
	// appropriate bitmap.Only Bitmap and Toolbar resources are supported.
	// m_menu.ModifyODMenu(NULL,ID_ZOOM,IDB_ZOOM);
	
	// Another method for adding bitmaps to menu options is through the
	// LoadToolbar member function.This method allows you to add all
	// the bitmaps in a toolbar object to menu options (if they exist).
	// The function parameter is an the toolbar id.
	// There is also a function called LoadToolbars that takes an
	// array of id's.
	m_menu.LoadToolbar(IDR_MAINFRAME);
	
	return(m_menu.Detach());	
}

void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	//This handler ensure that the popup menu items are drawn correctly	BOOL setflag=FALSE;
	BOOL setflag=FALSE;
	if(lpMeasureItemStruct->CtlType==ODT_MENU){
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID)){
			CMenu* cmenu=CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
			if(BCMenu::IsMenu(cmenu))
			{
				m_menu.MeasureItem(lpMeasureItemStruct);
				setflag = TRUE;
			}
		}
	}
	if(!setflag)		
		CFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	//This handler ensures that keyboard shortcuts work
	LRESULT lresult;
	if(BCMenu::IsMenu(pMenu))
		lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
		lresult=CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
	return(lresult);
	
	//return CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	//This handler updates the menus from time to time
	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: Add your message handler code here
	if(!bSysMenu){
		if(BCMenu::IsMenu(pPopupMenu))BCMenu::UpdateMenu(pPopupMenu);
	}	
}

void CMainFrame::OnOptionAutorun() 
{
	// TODO: Add your command handler code here
	int ret;

	if(m_bAutorun==FALSE)
	{
		//将此应用程序加入注册表，随系统自动启动
		char spath[MAX_PATH];
		GetModuleFileName(NULL,spath,MAX_PATH);
		ret = SetRegValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\0", REGKEYNAME, spath);
		if(ret != 0)
		{
			MessageBox("写注册表失败！","提示",MB_OK+MB_ICONINFORMATION);
			return;
		}
		m_bAutorun = TRUE;
	}
	else
	{
		//取消自动启动
		ret = DelRegKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\0", REGKEYNAME);
		if(ret != 0)
		{
			MessageBox("删除注册表值失败！","提示",MB_OK+MB_ICONINFORMATION);
			return;
		}
		m_bAutorun = FALSE;
	}
}

void CMainFrame::OnUpdateOptionAutorun(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bAutorun);
}

void CMainFrame::OnAppApp() 
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->ShowWindow(SW_SHOW);
}
