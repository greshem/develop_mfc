// 倪梓鹏 
//------------------------------------------------------------------------------
//该程序是一个在win2000下用sdk写简单的系统进程管理器，
//由于进程路径，dll模块还有线程显示部分是后来补上的，所以跟前面部分用链表存储进程信息格格不入。
//再者由于本人水平太差，不懂得如何用<tlhelp32.h>获得进程路径以及dll模块，因
//而出现了既用<tlhelp32.h>，又用<psapi.h>奇怪的现象。
//该程序设计原先的设计思想是用链表存储有关于系统进程的一切要显示的信息，当杀死某进程时，对链表
//节点进行删除，并重新显示进程信息，以及用定时器定时扫描系统进程，如有新进程则插入新节点，以及
//允许用户导出进程信息文件.
//但当发现非个人能力所及，已是木已成舟，呜呼～～～～～～～～，奈何！！！
//所以最后链表存储的只有进程的基本信息，进程的线程，调用的dll也没有插入到链表中，也没有用到定
//时器，文件导出就更不用说啦！
//进程每调用一次showprocess就重新扫描系统进程，并添加节点，显示进程信息完毕后又清空链表（无奈！！！）
//每点击主listview（进程信息列表）的每一项，就可以获得该进程的id，从而显示该进程的有关dll以及线程。
//最后还有一点要注意的就是杀死进程前，我提升了进程的权限（ KillProcess()中的函数UpdateProcessPrivilege）
//可以杀死系统的大把进程，死机或是系统崩溃可与我无关喔（重启可恢复），如果想要保持像任务管理器那样
//安全有限制的杀死进程，请把KillProcess()函数中包含UpdateProcessPrivilege（该函数的具体实现在
//"ProcessInformation.h"中）的那一行删除。经测试在win2k下，最多可删剩3个进程.
//把进程smss杀了，其他进程没显示的路径就可以显示出来。这是为什么我到现在还不清楚，那位高手告诉我阿，
//拜托！拜托！zpni@21nc.com
//-------------------------------------------------------------------------------
//整个程序主要包含两个文件"ProcessInformation.h"（链表实现文件）以及ProcessManage.cpp（
//功能实现文件）其他的就无关要紧，PSAPI.h，PSAPI.lib文件是库文件
//-------------------------------------------------------------------------------
#include <windows.h>
#include <tlhelp32.h>
#include "resource.h"
#include "ProcessInformation.h"
#include "psapi.h"
#include <commctrl.h>              //使用扩展的一些就要用这个头文件
#pragma comment(lib,"comctl32.lib")//编译时增加comctl32.lib，里面有扩展控件的接口
#pragma comment(lib,"./psapi.lib")//编译时增加comctl32.lib，里面有扩展控件的接口
//---------------------  控件值   ------------------------------------------------
#define IDKILL 1000  
#define IDSTATIC1 1000
#define IDSTATIC2 1001
#define IDCLIST 3000 
#define IDCDLLLIST 3001
#define IDCTHREADLIST 3002
//--------------------------------------------------------------------------------
#define iColMax 6    // listview的column的项目数
//---------------------------------------------------------------------------------
HINSTANCE hAppInstance = NULL; //实例(程序自身)句柄
HWND hListView = NULL,//控件ListView句柄
     hThreadListView = NULL,
     hDllListView = NULL,
     hMainWindow = NULL,//主窗口句柄
     hBtnOK = NULL,//按键"列举进程"句柄
     hBtnKill = NULL,
     hBtnExit = NULL;

static TCHAR szAppName[] = TEXT ("ListProcess") ; //程序名
TCHAR Buffer[256]; //缓冲区
//----------------------------------------------------------------------------------
BOOL AddItem(HWND hWndListView, int iItem,int iSubItem, LPSTR lpstr); //对控件ListView添加项目
BOOL InitListViewColumns(HWND hWndListView, int iCol, int iWidth, LPSTR lpstr) ;//初始化控件ListView表头
BOOL GetSelectItem(HWND hWhichListView, DWORD &dwProcessId);
//---------------------------------------------------------------------------------
BOOL ShowProcess(LinkList &head); //显示刷新进程列表
BOOL KillProcess(); //结束选中进程
//---------------------------------------------------------------------------------
BOOL ShowThreadList () ;
BOOL GetThreadInfo(DWORD dwProcessId);
BOOL ShowDll();
BOOL GetDllInfo(DWORD dwProcessId);
//---------------------------------------------------------------------------------
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;//窗口过程函数
//-----------------------------------------------------------------------------------
//===================================================================================
//listview控件添加项目,iItem为纵向列数,iSubItem为横向列数,lpstr为显示内容
BOOL  AddItem(HWND hWndListView, int iItem, int iSubItem, LPSTR lpstr)
{
	if( 0 == iSubItem)
	{
		LV_ITEM lvi;	
		lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
		lvi.stateMask = 0;
		lvi.state = 0;
        lvi.iItem =  iItem;
		lvi.iSubItem = iSubItem;
		lvi.pszText = lpstr; // sends an LVN_GETDISPINFO
		if( ListView_InsertItem(hWndListView,(LPARAM)&lvi) == -1)
			return FALSE;
	}
	else if( 0 < iSubItem)
		ListView_SetItemText(hWndListView, iItem, iSubItem ,lpstr);
    return TRUE;
	
}

//初始化表头,iCol为横向列序数,iWidth为某列宽度,lpstr为显示内容
BOOL InitListViewColumns(HWND hWndListView, int iCol, int iWidth, LPSTR lpstr)
{ 
	if ( iCol <= iColMax )
	{
		LVCOLUMN lvc; 
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
		// Add the columns. 
        lvc.iSubItem = iCol;
        lvc.pszText = lpstr;	
        lvc.cx = iWidth;             // width of column in pixels
		lvc.fmt = LVCFMT_LEFT;       // left-aligned column		
		if (ListView_InsertColumn(hWndListView, iCol, &lvc) == -1) 
			return FALSE; 
		return TRUE; 
	}
	else 
		return FALSE;   	
} 
//hwichlistview 是listview 控件句柄，dwProcessId是选中某项后得到进程id
BOOL GetSelectItem(HWND hWhichListView,DWORD &dwProcessId)
{
	int ipos;//ipos返回选中项的索引
	ipos = ListView_GetNextItem(hWhichListView, -1, LVIS_SELECTED);
	if( -1 == ipos)
	{   
		dwProcessId = 0;
		return FALSE;
	}
    ListView_GetItemText(hWhichListView,ipos,0,Buffer,10);
    dwProcessId = atol(Buffer);
	return TRUE;
}
//----------------------------------------------------------------------------------
//以上部分是有关对控件listview的操作
//-----------------------------------------------------------------------------------

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{

	MSG          msg ;
	WNDCLASS     wndclass ;
    InitCommonControls();
    
	hAppInstance = hInstance;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) (COLOR_BTNFACE+1) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;
	
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}
	hMainWindow = CreateWindow(
		               szAppName,
		               "系统进程管理器",
					   WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
					   CW_USEDEFAULT,
					   CW_USEDEFAULT,
					   650,460,
					   NULL,
					   NULL,
					   hInstance,
					   NULL
					   );
	
	ShowWindow (hMainWindow, iCmdShow) ;
	UpdateWindow (hMainWindow) ;
    
	while (GetMessage (&msg, NULL, 0, 0))
	{
		if (!IsWindow(hMainWindow) || !IsDialogMessage(hMainWindow, &msg))
		{
			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;
		}
	}
	return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LinkList L,Head;
	Head = InitList(L);//创建存储进程信息的链表，返回头节点
	switch (message)
	{
	case WM_CREATE:
		//创建ListView列表框
		 hListView = CreateWindow("SysListView32" , NULL,WS_BORDER | WS_CHILD | WS_VISIBLE 
			                      | WS_TABSTOP | WS_VSCROLL| LVS_REPORT| LVS_SHOWSELALWAYS,
			                      20, 20, 510, 205, hwnd, (HMENU)IDCLIST,
								  hAppInstance, NULL);
		 hDllListView = CreateWindow("SysListView32" , NULL,WS_BORDER | WS_CHILD | WS_VISIBLE 
			                          | WS_TABSTOP | WS_VSCROLL| LVS_REPORT|LVS_SHOWSELALWAYS,
			                          20, 250, 280, 150, hwnd, (HMENU)IDCDLLLIST,
			                          hAppInstance, NULL);
		 hThreadListView = CreateWindow("SysListView32", NULL,WS_BORDER | WS_CHILD | WS_VISIBLE 
			                            | WS_TABSTOP | WS_VSCROLL| LVS_REPORT|LVS_SHOWSELALWAYS|LVS_NOLABELWRAP ,
			                            300, 250, 220, 150, hwnd, (HMENU)IDCTHREADLIST,
			                            hAppInstance, NULL);
		

		 hBtnOK=CreateWindow("BUTTON",   //建立按钮"列举进程"
							"列举进程",
							WS_CHILD | WS_VISIBLE,
							550,30,
							70,30,
							hwnd,
							(HMENU) IDOK,
							hAppInstance,
							NULL);

		hBtnKill=CreateWindow("BUTTON",   //建立按钮"杀死进程"
	                    	"杀死进程",
		                    WS_CHILD | WS_VISIBLE,
		                    550,80,
	                    	70,30,
	                     	hwnd,
	                    	(HMENU) IDKILL,
	                    	hAppInstance,
	                    	NULL); 
		
		hBtnExit =CreateWindow("BUTTON",   //建立按钮"退出"
			                "退出",
			                WS_CHILD | WS_VISIBLE,
			                550,130,
			                70,30,
			                hwnd,
			                (HMENU) IDCANCEL,
			                hAppInstance,
		                	NULL); 
		//为控件listview添加表头
//---------------------------------------------------------------------
		InitListViewColumns(hListView, 0, 50, "ID");	
		InitListViewColumns(hListView, 1, 100, "进程映像名");
		InitListViewColumns(hListView, 2, 60, "父进程ID");	
		InitListViewColumns(hListView, 3, 50, "线程数");
		InitListViewColumns(hListView, 4, 50, "优先级");
	//	InitListViewColumns(hListView, 5, 180 , "模块ID");
		InitListViewColumns(hListView, 5, 180 , "路径");
//---------------------------------------------------------------------
		InitListViewColumns(hDllListView, 0, 180, " 模块信息 ");	
		InitListViewColumns(hDllListView, 1, 80, " 基地址");
//----------------------------------------------------------------------
		InitListViewColumns(hThreadListView, 0, 60, "序号");
		InitListViewColumns(hThreadListView, 1, 50, "线程ID");	
		InitListViewColumns(hThreadListView, 2, 55, "优先级");
//----------------------------------------------------------------------	
		ListView_SetExtendedListViewStyle(hListView,LVS_EX_FULLROWSELECT);
		ListView_SetExtendedListViewStyle(hDllListView,LVS_EX_FULLROWSELECT);
		ListView_SetExtendedListViewStyle(hThreadListView,LVS_EX_FULLROWSELECT);
    	ShowProcess(Head);
		break;
	case WM_COMMAND:		
		switch(LOWORD(wParam))
		{
		case  IDOK:
			 ShowProcess(Head);
			break;			
		case  IDKILL:
			if( IDYES == MessageBox(hMainWindow, "确认删除该进程", "ListProcess", MB_YESNO))	
			{
				KillProcess();
	    	    ShowProcess(Head);
			}
			break;
        case  IDCANCEL:
		    DelList(Head);//彻底解除链表
			DestroyWindow(hwnd);
			break;
		}//end switch
        break;
	case WM_NOTIFY:
			switch(	((LPNMHDR) lParam)->code)
			{
			case NM_CLICK:
				ShowThreadList();
				ShowDll();
				break;
			}
			break;

		
    case WM_DESTROY:
		DelList(Head);//彻底解除链表
		PostQuitMessage (0) ;
		return 0 ;
			
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
//----------------------------------------------------------------------------
//以下部分是功能的具体实现
//-----------------------------------------------------------------------------
//显示进程信息
//参数head是系统所有的进程组成的链表（见文件"ProcessInformation.h")的头指针
BOOL ShowProcess(LinkList &head)
{
	int i = 0;
	LinkList L;
	ListView_DeleteAllItems(hListView); //清空列表
	EnumProcessesInfo(L,head);
	//由提供的链条头节点，构造进程信息（id，父进程，名字，优先级，路径）链表，该函数在
	//"ProcessInformation.h"中，链表的实现也在该头文件中

	L = head->next ;
	ListView_DeleteAllItems(hListView); //清空主列表
	ListView_DeleteAllItems(hThreadListView); //清空线程列表
	ListView_DeleteAllItems(hDllListView); //清空dll模块列表
	while( NULL !=  L)
	{
		ltoa(L->dwProcessId, Buffer, 10); 
		AddItem(hListView, i, 0 ,Buffer);//添加进程id
		
		AddItem(hListView, i, 1, L->szProcessName); //进程名
		
		ltoa(L->dwParentProcessID, Buffer, 10);
		AddItem(hListView, i, 2,Buffer ); //进程的父进程id
		
		ltoa(L->dwCountOFThread, Buffer, 10);
		AddItem(hListView, i, 3,Buffer ); // 线程数
		
		ltoa(L->lPRIProcess, Buffer, 10);
		AddItem(hListView, i, 4, Buffer );//进程的优先级
		
		AddItem(hListView, i, 5, Buffer);
		AddItem(hListView, i, 5, L->szPrcessPatch);//进程路径
		i++;
		L = L->next;
	}   
	CleanList(head);
	return TRUE;
	
}
//-------------------------------------
//杀死进程
BOOL KillProcess()
{	
	DWORD dwProcessId;
	HANDLE hProcessHandle = NULL;
	int  success = 1;
	if( GetSelectItem(hListView,dwProcessId))//获得要杀死的进程的ID保存在dwProcessId中
	{
		UpdateProcessPrivilege( GetCurrentProcess(), SE_DEBUG_NAME );
       //危险动作，提高进程到特权模式，可以杀死很多运行在内核模式下的进程，该函数在"ProcessInformation.h"中  
	    hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwProcessId);
	    if (hProcessHandle != NULL)
		{
			success =TerminateProcess(hProcessHandle, 0); //结束选中进程，若成功返回0
	    	Sleep(500);
		    return TRUE;
		}
	}
	if( 1== success)
		MessageBox(hMainWindow,"不能结束该进程" ,"ListProcess",16);
	CloseHandle(hProcessHandle);
	return FALSE;
}

//======================================================
//显示选中的进程的线程情况
BOOL ShowThreadList () 
{ 
	DWORD dwProcessId;
	if(GetSelectItem(hListView, dwProcessId))//获得选中的进程的ID保存在dwProcessId中
		GetThreadInfo(dwProcessId);
	else FALSE;
	return TRUE;
}
//由某进程dwProcessId获得该进程的线程的具体情况
BOOL GetThreadInfo(DWORD dwProcessId)
{
    HANDLE        hThreadSnap = NULL; 
    BOOL          bRet        = FALSE; 
    THREADENTRY32 te32        = {0}; 	
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
    if (hThreadSnap == INVALID_HANDLE_VALUE) 
        return (FALSE); 	
    te32.dwSize = sizeof(THREADENTRY32); 
	int i = 0 ;
    if (Thread32First(hThreadSnap, &te32)) 
    { 
		ListView_DeleteAllItems(hThreadListView); //清空列表
        do 
        { 
            if (te32.th32OwnerProcessID == dwProcessId) 
            { 
				itoa (i, Buffer,10);
				AddItem(hThreadListView, i, 0, Buffer );
				
				ltoa(te32.th32ThreadID,Buffer,10);
				AddItem(hThreadListView, i, 1,Buffer );

				ltoa(te32.tpBasePri,Buffer,10);
				AddItem(hThreadListView, i, 2, Buffer );
			    i++;
            } 			
        } 
        while (Thread32Next(hThreadSnap, &te32)); 
        bRet = TRUE; 
    } 
    else 
        bRet = FALSE;         	
    CloseHandle (hThreadSnap); 	
    return (bRet); 
} 

//===================================================================
//显示选中进程调用的Dll的具体情况
BOOL ShowDll()
{
	DWORD dwProcessId = 0;
	DWORD dwModuleId = 0;
	DWORD cbMe32 = 0;
	if(GetSelectItem(hListView, dwProcessId))
	{   
        GetDllInfo(dwProcessId);       
		return TRUE;
	}
	return FALSE;
}
//由某进程dwProcessId获得该进程调用的dll
BOOL GetDllInfo (DWORD dwPID) 
{ 
	
	HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;
	char szModName[MAX_PATH];
	ListView_DeleteAllItems(hDllListView); //清空列表
    hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |PROCESS_VM_READ,FALSE, dwPID);
    if( hProcess &&  EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for ( i = 0; i <=(cbNeeded / sizeof(HMODULE)); i++ )
        {        			
            if ( GetModuleFileNameEx( hProcess, hMods[i], szModName,
				sizeof(szModName)))
            {
				AddItem(hDllListView, i,0, szModName);
				wsprintf(Buffer,"0x%08x",hMods[i]);
				AddItem(hDllListView, i,1, Buffer);
				if( 0 == i)
				{
					AddItem(hDllListView, ++i, 0, "=====================");
				    AddItem(hDllListView, i, 1, "========");
				}
            }
        }
		CloseHandle( hProcess );
		return TRUE;
    }
	else  
	{
		CloseHandle( hProcess );
		return FALSE;
    }
}


