// crashdump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <Dbghelp.h>


 

#pragma auto_inline (off)

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


static DWORD  WINAPI  Fun2( LPVOID lpParameter )
{
	 int *p = NULL;

      *p = 0;

	  return 0;
}

static void Fun3()

{

    __try

    {

       static bool b = false;

       

       if(!b)

       {

           b = true;

           int *p = NULL;

           *p = 0;

        }

       else

       {

           MessageBox(NULL, _T("Here"), _T(""), MB_OK);

       }

    }

    __except( MyUnhandledExceptionFilter( GetExceptionInformation() ) )

    {

    }

}

 

static void Fun()

{
	DWORD threadid;
	HANDLE handle = ::CreateThread( NULL, 0, &Fun2, NULL, 0, &threadid );

	::WaitForSingleObject( handle, INFINITE );

}



int _tmain(const int argc, const _TCHAR* const argv[])
{
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

 

    Fun();

 

    return 1;

}

