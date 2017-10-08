//#include "stdafx.h"
#include "SdkWriteLog.h"
#include <stdio.h>
#include "windows.h"

BOOL WriteLogFile(const TCHAR *FileName,const TCHAR *buffer,DWORD writelen)
{

	HANDLE hFile = NULL;
	hFile = CreateFile(FileName,
		GENERIC_READ|GENERIC_WRITE, 
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	DWORD dwFileSize = GetFileSize(hFile,NULL);
	SetFilePointer(hFile, 0, NULL, FILE_END);
	DWORD len;
	if(!WriteFile(hFile, buffer, writelen, &len, NULL))
		return FALSE;
	if(writelen!=len)
		return FALSE;
	SetEndOfFile(hFile);
	CloseHandle(hFile);
}

void WriteLog(const TCHAR *lpszFormat, ...)
{
	TCHAR headinfo[64]={0};
	TCHAR buff[2048] = {0};
	TCHAR FileName[MAX_PATH] = {0};
	SYSTEMTIME st;
	GetLocalTime(&st);
	_stprintf(FileName,_T("%.2d_%.2d_%.2d.log"), st.wYear,st.wMonth,st.wDay);
	_stprintf(headinfo,_T("[%.2d:%.2d:%.2d%]:"), st.wHour, st.wMinute, st.wSecond);

	TCHAR szMsg[1024] = {0};   
	va_list   argList;   
	va_start(argList, lpszFormat);   
	_vstprintf(szMsg,lpszFormat, argList);   
	va_end(argList);   
	_stprintf(buff, _T("%s"), headinfo);
	_tcscat(buff,szMsg);
	_tcscat(buff,_T("\r\n"));
	WriteLogFile(FileName,buff,_tcslen(buff)*sizeof(TCHAR));
}