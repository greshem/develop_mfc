//
//==============================================================================================
/*
Copyright (c) 2009 Richtech Co.,Ltd. All rights reserved
Module Name: RNFS_Server
Abstract:
Revision History: 2009/08/27
Author:		wangjun
*/
//==============================================================================================
//
#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/socket.h>
#include <wx/thread.h>
#include <windows.h>
#include <Dbghelp.h>
#include <list>
using	namespace	std ;

#include "types.h"
#include "RNFS_Server.h"
//
//==============================================================================================
//
#pragma comment( lib, "DbgHelp" )

static LONG WINAPI MyUnhandledExceptionFilter( struct _EXCEPTION_POINTERS* ExceptionInfo )
{
	const HANDLE lhDumpFile = CreateFile(_T("DumpFile.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL ,NULL);
	MINIDUMP_EXCEPTION_INFORMATION loExceptionInfo;

	loExceptionInfo.ExceptionPointers = ExceptionInfo;
	loExceptionInfo.ThreadId = GetCurrentThreadId();
	loExceptionInfo.ClientPointers = TRUE;
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),lhDumpFile, MiniDumpNormal, &loExceptionInfo, NULL, NULL);
	CloseHandle(lhDumpFile);
	return EXCEPTION_EXECUTE_HANDLER;
}

DWORD	__stdcall	IOCM_StartService() 
{
	DWORD	dwStatus = 0 ;

	wxInitialize() ;

	wxSocketBase::Initialize() ;

	srand( time(NULL) ) ;

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	int a = 5 ;
	int b = 3 ;
	int c = a + b ;

	c = c / ( a - b - 2 ) ;

	printf( "c = %d\n", c ) ;

	return dwStatus ;
}

DWORD	__stdcall	IOCM_StopService() 
{
	DWORD	dwStatus = 0 ;

	// g_bStopService = TRUE ;

	wxUninitialize() ;

	return dwStatus ;
}
