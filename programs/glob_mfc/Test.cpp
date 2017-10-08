// Test.cpp : �������̨Ӧ�ó������ڵ㡣
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
// Ψһ��Ӧ�ó������
//#pragma comment( linker, "/subsystem:\"windows \" /entry:\"mainCRTStartup\"" )  // ����������ѡ��
//#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )  // ����������ѡ��

//CWinApp theApp;

BOOL   TransDirectory(LPCTSTR   DirName, vector<string> &out)
{
	CFileFind   tempFind;   //file://����һ��CFileFind�����������������
	char   tempFileFind[1024];   //file://���ڶ���������ʽ
	sprintf(tempFileFind, "%s\\*.*",DirName);
	log::Instance()->logger("FILE: %s \n", tempFileFind);
	//file://ƥ���ʽΪ*.*,����Ŀ¼�µ������ļ�  

	BOOL   IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
	if(IsFinded)
	{
		printf("�ҵ���\n");
		log::Instance()->logger("�ҵ���\n");
	}
	else
	{
		printf("%s\n", tempFileFind);
		printf("û���ҵ�\n");
	}
	//file://���ҵ�һ���ļ�
	while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();   //file://�ݹ������������ļ�  
		if(!tempFind.IsDots())  // file://������� ". "Ŀ¼
		{
			char   foundFileName[1024];
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(1024));
			if(tempFind.IsDirectory())  // file://�����Ŀ¼����ݹ�ص���
			{   //file://DeleteDirectory
				char   tempDir[200];
				sprintf(tempDir, "%s\\%s",DirName,foundFileName);
				printf("DIR: %s\n", tempDir);
				TransDirectory(tempDir, out);
			}
			else
			{   //file://������ļ���ֱ��ɾ��֮
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

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("��������: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	if(argc != 2)
	{
		printf("Usage: %s dir", argv[0]);
		exit(-1);
	}
	vector<string> files;
	log::Instance()->logger("��ʼ ִ��TransDirectory \n");
	TransDirectory(argv[1], files);
	//CMyDlg dlg;
	//dlg.DoModal();

	for(vector<string>::iterator it=files.begin(); it!= files.end(); it++)
	{	
		cout<<*it<<endl;
	}



	
	return nRetCode;
}
