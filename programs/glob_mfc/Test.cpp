// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test.h"
#include "log.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "resource.h"
//#include <Baselib.hpp>
#include "MyDlg.h"
#include <vector>
#include <string>
using namespace std;
// 唯一的应用程序对象
//#pragma comment( linker, "/subsystem:\"windows \" /entry:\"mainCRTStartup\"" )  // 设置连接器选项
//#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )  // 设置连接器选项

//CWinApp theApp;

BOOL   TransDirectory(LPCTSTR   DirName, vector<string> &out)
{
	CFileFind   tempFind;   //file://声明一个CFileFind类变量，以用来搜索
	char   tempFileFind[1024];   //file://用于定义搜索格式
	sprintf(tempFileFind, "%s\\*.*",DirName);
	log::Instance()->logger("FILE: %s \n", tempFileFind);
	//file://匹配格式为*.*,即该目录下的所有文件  

	BOOL   IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
	if(IsFinded)
	{
		printf("找到了\n");
		log::Instance()->logger("找到了\n");
	}
	else
	{
		printf("%s\n", tempFileFind);
		printf("没有找到\n");
	}
	//file://查找第一个文件
	while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();   //file://递归搜索其他的文件  
		if(!tempFind.IsDots())  // file://如果不是 ". "目录
		{
			char   foundFileName[1024];
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(1024));
			if(tempFind.IsDirectory())  // file://如果是目录，则递归地调用
			{   //file://DeleteDirectory
				char   tempDir[200];
				sprintf(tempDir, "%s\\%s",DirName,foundFileName);
				printf("DIR: %s\n", tempDir);
				TransDirectory(tempDir, out);
			}
			else
			{   //file://如果是文件则直接删除之
				char   tempFileName[1024];
				sprintf(tempFileName, "%s\\%s ",DirName,foundFileName);
				//printf("%s\n", tempFileName);
				out.push_back(string(tempFileName));
				//DeleteFile(tempFileName);
			}
		}
	}
	tempFind.Close();

	return   TRUE;
} 


using namespace std;

int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("致命错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	if(argc != 2)
	{
		printf("Usage: %s dir", argv[0]);
		exit(-1);
	}
	vector<string> files;
	log::Instance()->logger("开始 执行TransDirectory \n");
	TransDirectory(argv[1], files);
	//CMyDlg dlg;
	//dlg.DoModal();

	for(vector<string>::iterator it=files.begin(); it!= files.end(); it++)
	{	
		cout<<*it<<endl;
	}



	
	return nRetCode;
}
