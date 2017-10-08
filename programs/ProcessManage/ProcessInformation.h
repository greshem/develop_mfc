
#ifndef ProcessInformationH
#define ProcessInformationH
#include "psapi.h"
//----------------------------------------------------------------------------------
typedef struct LNodeProcessInfo
{ 
	DWORD dwProcessId;    //����ID
	DWORD dwCountOFThread;  //�߳���
	DWORD dwParentProcessID; //������ID
	LONG  lPRIProcess;    //�������ȼ�
	DWORD dwModuleId;
	TCHAR szProcessName[MAX_PATH];//����ӳ����
	TCHAR szPrcessPatch[MAX_PATH]; //����·��	
	struct LNodeProcessInfo* next;
}LNodeProcessInfo, *LinkList;

//----------------------------------------------------------------------------------
LNodeProcessInfo* InitList(LinkList &L);
bool CleanList(LinkList &Head);
bool DelList(LinkList &Head);
bool ListInsert(LinkList &L,PROCESSENTRY32  *e); //������
bool InfoFormToolHelp(LinkList &LinkListProcess); //�ú�����toolhelp��õ�ID����������������ID�����ȼ�
bool EnumProcessesInfo(LinkList &LinkListProcess, LinkList head);//��ȡ������Ϣ�б�
BOOL UpdateProcessPrivilege( HANDLE hProcess, LPCTSTR lpPrivilegeName );
//-----------------------------------------------------------------------------------
//����������ͷ���
LNodeProcessInfo* InitList(LinkList &L)
{	
    LinkList Head = new LNodeProcessInfo; //���ɽ�����Ϣ���
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
//ɾ������ֻʣ��ͷ�ڵ��ͷſռ�
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
//����ڵ�
bool ListInsert(LinkList &L, PROCESSENTRY32   *e)
{
       LinkList ProcessInfo = new LNodeProcessInfo; //���ɽ�����Ϣ���
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

//�ú�����toolhelp��õ�ID����������������ID�����ȼ�
bool InfoFormToolHelp(LinkList &LinkListProcess) 
{
    if( -1 != LinkListProcess->dwProcessId) //ȷ��linklistprocessָ��ͷָ��
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
//�Ӹú�����ȡ������Ϣ
bool InfoFormModule(LinkList &LinkListProcess)
{
	if( -1 != LinkListProcess->dwProcessId) //ȷ��linklistprocessָ��ͷָ��
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

//��ȡ������Ϣ�б�
bool EnumProcessesInfo(LinkList &LinkListProcess, LinkList head )
{
	LinkListProcess = head;
	InfoFormToolHelp(LinkListProcess); //�ú�����toolhelp��õ�ID����������������ID�����ȼ�
	LinkListProcess = head;
	InfoFormModule(LinkListProcess);
	return true;
}

//---------------------------------------------------------------------------------
//��������Ȩ��
BOOL UpdateProcessPrivilege( HANDLE hProcess, LPCTSTR lpPrivilegeName = SE_DEBUG_NAME )
// hProcess  : Ҫ�����Ľ��̣�Ŀ�����
// lpPrivilegeName : Ҫ����������Ȩ��Ŀ����Ȩ
// ����ֵ : TRUE : �ɹ�; FALSE : ʧ��
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