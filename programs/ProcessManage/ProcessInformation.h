
#ifndef ProcessInformationH
#define ProcessInformationH
#include "psapi.h"
//----------------------------------------------------------------------------------
typedef struct LNodeProcessInfo
{ 
	DWORD dwProcessId;    //进程ID
	DWORD dwCountOFThread;  //线程数
	DWORD dwParentProcessID; //父进程ID
	LONG  lPRIProcess;    //进程优先级
	DWORD dwModuleId;
	TCHAR szProcessName[MAX_PATH];//进程映像名
	TCHAR szPrcessPatch[MAX_PATH]; //进程路径	
	struct LNodeProcessInfo* next;
}LNodeProcessInfo, *LinkList;

//----------------------------------------------------------------------------------
LNodeProcessInfo* InitList(LinkList &L);
bool CleanList(LinkList &Head);
bool DelList(LinkList &Head);
bool ListInsert(LinkList &L,PROCESSENTRY32  *e); //插入结点
bool InfoFormToolHelp(LinkList &LinkListProcess); //该函数由toolhelp获得的ID，进程名，父进程ID，优先级
bool EnumProcessesInfo(LinkList &LinkListProcess, LinkList head);//获取进程信息列表
BOOL UpdateProcessPrivilege( HANDLE hProcess, LPCTSTR lpPrivilegeName );
//-----------------------------------------------------------------------------------
//构造链表返回头结点
LNodeProcessInfo* InitList(LinkList &L)
{	
    LinkList Head = new LNodeProcessInfo; //生成进程信息结点
	Head->dwCountOFThread = -1;
	Head->dwParentProcessID = -1;
	Head->dwProcessId = -1;
	Head->lPRIProcess = -1;
	Head->dwModuleId = -1;
	lstrcpy(Head->szPrcessPatch,"");
	lstrcpy(Head->szProcessName, "");
	L = Head ;
	L->next = NULL;
	return Head;
}
//删除链表只剩下头节点释放空间
bool CleanList(LinkList &Head)
{
	if(NULL != Head)
	{
		LinkList p,L;
	    L = Head ;
	    while( NULL != L->next)
		{
		   p= L->next;
		   L->next =L->next->next;
		   delete p;
		}
		Head = L;
	    return true;
	}
	else 
		return false;
}
bool DelList(LinkList &Head)
{
	if( NULL!= Head )
	{
		if( NULL != Head->next)
		    CleanList(Head);
		delete Head;
		return true;
	}
	else 
		return false;
}
//插入节点
bool ListInsert(LinkList &L, PROCESSENTRY32   *e)
{
       LinkList ProcessInfo = new LNodeProcessInfo; //生成进程信息结点
	   ProcessInfo->dwProcessId =  e->th32ProcessID;
	   lstrcpy(ProcessInfo->szProcessName,e->szExeFile);
	   ProcessInfo->dwCountOFThread = e->cntThreads;
	   ProcessInfo->lPRIProcess = e->pcPriClassBase;
	   ProcessInfo->dwParentProcessID = e->th32ParentProcessID;
	   ProcessInfo->dwModuleId = e->th32ModuleID; 
	   TCHAR d[234];
	   ltoa(e->th32ModuleID,d,10);
	   if( NULL != L)
	   {
		   ProcessInfo ->next = NULL;
	       L->next = ProcessInfo;
	   }
	   else
      
		   return false;
	   L= L->next;
	return true;
}

//该函数由toolhelp获得的ID，进程名，父进程ID，优先级
bool InfoFormToolHelp(LinkList &LinkListProcess) 
{
    if( -1 != LinkListProcess->dwProcessId) //确定linklistprocess指向头指针
		return false;
	else
	{
		HANDLE handle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
        PROCESSENTRY32* information = new PROCESSENTRY32;
	    information->dwSize = sizeof(PROCESSENTRY32);
	    if(Process32First(handle,information))
		{
		   ListInsert(LinkListProcess,information);
		   while(Process32Next(handle,information)!=FALSE)
		   {
		    	ListInsert(LinkListProcess, information);
		   }
		}
		delete information;
		CloseHandle(handle);
		return true;
	}	
}
//从该函数获取其它信息
bool InfoFormModule(LinkList &LinkListProcess)
{
	if( -1 != LinkListProcess->dwProcessId) //确定linklistprocess指向头指针
		return false;
	HANDLE hProcess = NULL;
	HMODULE	hModule = NULL;
	DWORD		dwSize;
	while(NULL != LinkListProcess)
	{
		if( !lstrcmp(LinkListProcess->szProcessName, "System") || !lstrcmp(LinkListProcess->szProcessName,"[System Process]") )
			lstrcpy(LinkListProcess->szPrcessPatch, " ");     
        else 
		{                                        
			hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, LinkListProcess->dwProcessId);	   
			if(NULL != hProcess)
			{
				if( EnumProcessModules( hProcess, &hModule,	sizeof(hModule), &dwSize ) )
				{ 	
					GetModuleFileNameExA(hProcess,hModule, LinkListProcess->szPrcessPatch, MAX_PATH );
					
				}
			}
			else  lstrcpy(LinkListProcess->szPrcessPatch, "");
		}		
		LinkListProcess = LinkListProcess->next;
		
	}
	CloseHandle( hProcess ) ;
	return true;
}

//获取进程信息列表
bool EnumProcessesInfo(LinkList &LinkListProcess, LinkList head )
{
	LinkListProcess = head;
	InfoFormToolHelp(LinkListProcess); //该函数由toolhelp获得的ID，进程名，父进程ID，优先级
	LinkListProcess = head;
	InfoFormModule(LinkListProcess);
	return true;
}

//---------------------------------------------------------------------------------
//提升进程权限
BOOL UpdateProcessPrivilege( HANDLE hProcess, LPCTSTR lpPrivilegeName = SE_DEBUG_NAME )
// hProcess  : 要提升的进程，目标进程
// lpPrivilegeName : 要提升到的特权，目标特权
// 返回值 : TRUE : 成功; FALSE : 失败
{
	HANDLE hToken;
	if ( OpenProcessToken( hProcess, TOKEN_ALL_ACCESS, &hToken ) ) {
		
		LUID destLuid;
		if ( LookupPrivilegeValue( NULL, lpPrivilegeName, &destLuid ) ) {
			
			TOKEN_PRIVILEGES TokenPrivileges;
			TokenPrivileges.PrivilegeCount = 1;
			TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			TokenPrivileges.Privileges[0].Luid = destLuid;
			int iResult;
			if ( iResult = AdjustTokenPrivileges( hToken, FALSE, &TokenPrivileges, 
				0, NULL, NULL ) ) {
				
				return TRUE;				
			}
		}
	}
	
	return FALSE;
}
#endif