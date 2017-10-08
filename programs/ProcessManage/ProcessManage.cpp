// ������ 
//------------------------------------------------------------------------------
//�ó�����һ����win2000����sdkд�򵥵�ϵͳ���̹�������
//���ڽ���·����dllģ�黹���߳���ʾ�����Ǻ������ϵģ����Ը�ǰ�沿��������洢������Ϣ����롣
//�������ڱ���ˮƽ̫������������<tlhelp32.h>��ý���·���Լ�dllģ�飬��
//�������˼���<tlhelp32.h>������<psapi.h>��ֵ�����
//�ó������ԭ�ȵ����˼����������洢�й���ϵͳ���̵�һ��Ҫ��ʾ����Ϣ����ɱ��ĳ����ʱ��������
//�ڵ����ɾ������������ʾ������Ϣ���Լ��ö�ʱ����ʱɨ��ϵͳ���̣������½���������½ڵ㣬�Լ�
//�����û�����������Ϣ�ļ�.
//�������ַǸ�����������������ľ�ѳ��ۣ��غ��������������������κΣ�����
//�����������洢��ֻ�н��̵Ļ�����Ϣ�����̵��̣߳����õ�dllҲû�в��뵽�����У�Ҳû���õ���
//ʱ�����ļ������͸�����˵����
//����ÿ����һ��showprocess������ɨ��ϵͳ���̣�����ӽڵ㣬��ʾ������Ϣ��Ϻ�������������Σ�������
//ÿ�����listview��������Ϣ�б���ÿһ��Ϳ��Ի�øý��̵�id���Ӷ���ʾ�ý��̵��й�dll�Լ��̡߳�
//�����һ��Ҫע��ľ���ɱ������ǰ���������˽��̵�Ȩ�ޣ� KillProcess()�еĺ���UpdateProcessPrivilege��
//����ɱ��ϵͳ�Ĵ�ѽ��̣���������ϵͳ�����������޹�ร������ɻָ����������Ҫ�������������������
//��ȫ�����Ƶ�ɱ�����̣����KillProcess()�����а���UpdateProcessPrivilege���ú����ľ���ʵ����
//"ProcessInformation.h"�У�����һ��ɾ������������win2k�£�����ɾʣ3������.
//�ѽ���smssɱ�ˣ���������û��ʾ��·���Ϳ�����ʾ����������Ϊʲô�ҵ����ڻ����������λ���ָ����Ұ���
//���У����У�zpni@21nc.com
//-------------------------------------------------------------------------------
//����������Ҫ���������ļ�"ProcessInformation.h"������ʵ���ļ����Լ�ProcessManage.cpp��
//����ʵ���ļ��������ľ��޹�Ҫ����PSAPI.h��PSAPI.lib�ļ��ǿ��ļ�
//-------------------------------------------------------------------------------
#include <windows.h>
#include <tlhelp32.h>
#include "resource.h"
#include "ProcessInformation.h"
#include "psapi.h"
#include <commctrl.h>              //ʹ����չ��һЩ��Ҫ�����ͷ�ļ�
#pragma comment(lib,"comctl32.lib")//����ʱ����comctl32.lib����������չ�ؼ��Ľӿ�
#pragma comment(lib,"./psapi.lib")//����ʱ����comctl32.lib����������չ�ؼ��Ľӿ�
//---------------------  �ؼ�ֵ   ------------------------------------------------
#define IDKILL 1000  
#define IDSTATIC1 1000
#define IDSTATIC2 1001
#define IDCLIST 3000 
#define IDCDLLLIST 3001
#define IDCTHREADLIST 3002
//--------------------------------------------------------------------------------
#define iColMax 6    // listview��column����Ŀ��
//---------------------------------------------------------------------------------
HINSTANCE hAppInstance = NULL; //ʵ��(��������)���
HWND hListView = NULL,//�ؼ�ListView���
     hThreadListView = NULL,
     hDllListView = NULL,
     hMainWindow = NULL,//�����ھ��
     hBtnOK = NULL,//����"�оٽ���"���
     hBtnKill = NULL,
     hBtnExit = NULL;

static TCHAR szAppName[] = TEXT ("ListProcess") ; //������
TCHAR Buffer[256]; //������
//----------------------------------------------------------------------------------
BOOL AddItem(HWND hWndListView, int iItem,int iSubItem, LPSTR lpstr); //�Կؼ�ListView�����Ŀ
BOOL InitListViewColumns(HWND hWndListView, int iCol, int iWidth, LPSTR lpstr) ;//��ʼ���ؼ�ListView��ͷ
BOOL GetSelectItem(HWND hWhichListView, DWORD &dwProcessId);
//---------------------------------------------------------------------------------
BOOL ShowProcess(LinkList &head); //��ʾˢ�½����б�
BOOL KillProcess(); //����ѡ�н���
//---------------------------------------------------------------------------------
BOOL ShowThreadList () ;
BOOL GetThreadInfo(DWORD dwProcessId);
BOOL ShowDll();
BOOL GetDllInfo(DWORD dwProcessId);
//---------------------------------------------------------------------------------
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;//���ڹ��̺���
//-----------------------------------------------------------------------------------
//===================================================================================
//listview�ؼ������Ŀ,iItemΪ��������,iSubItemΪ��������,lpstrΪ��ʾ����
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

//��ʼ����ͷ,iColΪ����������,iWidthΪĳ�п��,lpstrΪ��ʾ����
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
//hwichlistview ��listview �ؼ������dwProcessId��ѡ��ĳ���õ�����id
BOOL GetSelectItem(HWND hWhichListView,DWORD &dwProcessId)
{
	int ipos;//ipos����ѡ���������
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
//���ϲ������йضԿؼ�listview�Ĳ���
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
		               "ϵͳ���̹�����",
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
	Head = InitList(L);//�����洢������Ϣ����������ͷ�ڵ�
	switch (message)
	{
	case WM_CREATE:
		//����ListView�б��
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
		

		 hBtnOK=CreateWindow("BUTTON",   //������ť"�оٽ���"
							"�оٽ���",
							WS_CHILD | WS_VISIBLE,
							550,30,
							70,30,
							hwnd,
							(HMENU) IDOK,
							hAppInstance,
							NULL);

		hBtnKill=CreateWindow("BUTTON",   //������ť"ɱ������"
	                    	"ɱ������",
		                    WS_CHILD | WS_VISIBLE,
		                    550,80,
	                    	70,30,
	                     	hwnd,
	                    	(HMENU) IDKILL,
	                    	hAppInstance,
	                    	NULL); 
		
		hBtnExit =CreateWindow("BUTTON",   //������ť"�˳�"
			                "�˳�",
			                WS_CHILD | WS_VISIBLE,
			                550,130,
			                70,30,
			                hwnd,
			                (HMENU) IDCANCEL,
			                hAppInstance,
		                	NULL); 
		//Ϊ�ؼ�listview��ӱ�ͷ
//---------------------------------------------------------------------
		InitListViewColumns(hListView, 0, 50, "ID");	
		InitListViewColumns(hListView, 1, 100, "����ӳ����");
		InitListViewColumns(hListView, 2, 60, "������ID");	
		InitListViewColumns(hListView, 3, 50, "�߳���");
		InitListViewColumns(hListView, 4, 50, "���ȼ�");
	//	InitListViewColumns(hListView, 5, 180 , "ģ��ID");
		InitListViewColumns(hListView, 5, 180 , "·��");
//---------------------------------------------------------------------
		InitListViewColumns(hDllListView, 0, 180, " ģ����Ϣ ");	
		InitListViewColumns(hDllListView, 1, 80, " ����ַ");
//----------------------------------------------------------------------
		InitListViewColumns(hThreadListView, 0, 60, "���");
		InitListViewColumns(hThreadListView, 1, 50, "�߳�ID");	
		InitListViewColumns(hThreadListView, 2, 55, "���ȼ�");
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
			if( IDYES == MessageBox(hMainWindow, "ȷ��ɾ���ý���", "ListProcess", MB_YESNO))	
			{
				KillProcess();
	    	    ShowProcess(Head);
			}
			break;
        case  IDCANCEL:
		    DelList(Head);//���׽������
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
		DelList(Head);//���׽������
		PostQuitMessage (0) ;
		return 0 ;
			
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
//----------------------------------------------------------------------------
//���²����ǹ��ܵľ���ʵ��
//-----------------------------------------------------------------------------
//��ʾ������Ϣ
//����head��ϵͳ���еĽ�����ɵ��������ļ�"ProcessInformation.h")��ͷָ��
BOOL ShowProcess(LinkList &head)
{
	int i = 0;
	LinkList L;
	ListView_DeleteAllItems(hListView); //����б�
	EnumProcessesInfo(L,head);
	//���ṩ������ͷ�ڵ㣬���������Ϣ��id�������̣����֣����ȼ���·���������ú�����
	//"ProcessInformation.h"�У������ʵ��Ҳ�ڸ�ͷ�ļ���

	L = head->next ;
	ListView_DeleteAllItems(hListView); //������б�
	ListView_DeleteAllItems(hThreadListView); //����߳��б�
	ListView_DeleteAllItems(hDllListView); //���dllģ���б�
	while( NULL !=  L)
	{
		ltoa(L->dwProcessId, Buffer, 10); 
		AddItem(hListView, i, 0 ,Buffer);//��ӽ���id
		
		AddItem(hListView, i, 1, L->szProcessName); //������
		
		ltoa(L->dwParentProcessID, Buffer, 10);
		AddItem(hListView, i, 2,Buffer ); //���̵ĸ�����id
		
		ltoa(L->dwCountOFThread, Buffer, 10);
		AddItem(hListView, i, 3,Buffer ); // �߳���
		
		ltoa(L->lPRIProcess, Buffer, 10);
		AddItem(hListView, i, 4, Buffer );//���̵����ȼ�
		
		AddItem(hListView, i, 5, Buffer);
		AddItem(hListView, i, 5, L->szPrcessPatch);//����·��
		i++;
		L = L->next;
	}   
	CleanList(head);
	return TRUE;
	
}
//-------------------------------------
//ɱ������
BOOL KillProcess()
{	
	DWORD dwProcessId;
	HANDLE hProcessHandle = NULL;
	int  success = 1;
	if( GetSelectItem(hListView,dwProcessId))//���Ҫɱ���Ľ��̵�ID������dwProcessId��
	{
		UpdateProcessPrivilege( GetCurrentProcess(), SE_DEBUG_NAME );
       //Σ�ն�������߽��̵���Ȩģʽ������ɱ���ܶ��������ں�ģʽ�µĽ��̣��ú�����"ProcessInformation.h"��  
	    hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwProcessId);
	    if (hProcessHandle != NULL)
		{
			success =TerminateProcess(hProcessHandle, 0); //����ѡ�н��̣����ɹ�����0
	    	Sleep(500);
		    return TRUE;
		}
	}
	if( 1== success)
		MessageBox(hMainWindow,"���ܽ����ý���" ,"ListProcess",16);
	CloseHandle(hProcessHandle);
	return FALSE;
}

//======================================================
//��ʾѡ�еĽ��̵��߳����
BOOL ShowThreadList () 
{ 
	DWORD dwProcessId;
	if(GetSelectItem(hListView, dwProcessId))//���ѡ�еĽ��̵�ID������dwProcessId��
		GetThreadInfo(dwProcessId);
	else FALSE;
	return TRUE;
}
//��ĳ����dwProcessId��øý��̵��̵߳ľ������
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
		ListView_DeleteAllItems(hThreadListView); //����б�
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
//��ʾѡ�н��̵��õ�Dll�ľ������
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
//��ĳ����dwProcessId��øý��̵��õ�dll
BOOL GetDllInfo (DWORD dwPID) 
{ 
	
	HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;
	char szModName[MAX_PATH];
	ListView_DeleteAllItems(hDllListView); //����б�
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


