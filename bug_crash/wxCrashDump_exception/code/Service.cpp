//
//==============================================================================================
/*
Copyright (c) 2009 Richtech Co.,Ltd. All rights reserved
Module Name: ServiceSvr
Abstract:
Revision History: 2009/08/27
Author:		wangjun
*/
//==============================================================================================
//
#include <wx/wx.h>
#include <wx/init.h>
#include "types.h"
#include "RNFS_Server.h"

//
//==============================================================================================
//
#ifndef COMPILE_SERVICE

#include <signal.h>

BOOL g_bStop = FALSE;

void SignalHandler(int)
{
	g_bStop = TRUE;
}

int main()
{
	wxInitializer initializer;
	if ( !initializer )
	{
		printf("Failed to initialize the wxWidgets library, aborting.");
		return -1;
	}

#ifndef __WIN32__
	// This is not needed for Windows
	wxLocale locale(wxLANGUAGE_DEFAULT);
#endif

	DWORD dwStatus = IOCM_StartService( ) ;
	if( dwStatus == 0 )
	{
#ifdef    ENABLE_DBG_MESSAGE
		printf( "Start Service successful!\n" ) ;
		printf( "Press Ctrl+C to stop service...\n" ) ;
#endif
	}
	else
	{
		printf( "Start Service failed => %d\n" , (int)dwStatus ) ;
		printf( "Press Ctrl+C to quit...\n" ) ;
	}

	signal(SIGINT, SignalHandler);
	signal(SIGTERM, SignalHandler);
	while (!g_bStop)
	{
		wxSleep(1);
	}

	IOCM_StopService( ) ;

	return 0 ;
}

//
//==============================================================================================
//

#else

//
//==============================================================================================
//
static TCHAR	SERVICE_NAME[] = _T("UCService") ;
static HANDLE	g_hTerminateEvent = NULL ;

SERVICE_STATUS_HANDLE g_SrvStatusHandle ;
BOOL g_bRunningService = FALSE ;

//
//==============================================================================================
//
BOOL SendStatusToSCM (
					  IN DWORD dwCurrentState ,
					  IN DWORD dwWin32ExitCode ,
					  IN DWORD dwServiceSpecificExitCode ,
					  IN DWORD dwCheckPoint ,
					  IN DWORD dwWaitHint )
{
	BOOL bResult = FALSE ;
	SERVICE_STATUS serviceStatus;

	serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	serviceStatus.dwCurrentState = dwCurrentState;

	//
	// If in the process of doing something, then accept
	// no control events, else accept anything
	//
	if( dwCurrentState == SERVICE_START_PENDING )
	{
		serviceStatus.dwControlsAccepted = 0 ;
	}
	else
	{
		serviceStatus.dwControlsAccepted =	SERVICE_ACCEPT_STOP |
			SERVICE_ACCEPT_PAUSE_CONTINUE |
			SERVICE_ACCEPT_SHUTDOWN ;
	}
	//
	// if a specific exit code is defined, set up the win32 exit code properly
	// 
	if( dwServiceSpecificExitCode == 0 )
	{
		serviceStatus.dwWin32ExitCode = dwWin32ExitCode ;
	}
	else
	{
		serviceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR ;
	}

	serviceStatus.dwServiceSpecificExitCode =dwServiceSpecificExitCode ;
	serviceStatus.dwCheckPoint = dwCheckPoint ;
	serviceStatus.dwWaitHint = dwWaitHint ;

	return SetServiceStatus( g_SrvStatusHandle, &serviceStatus ) ;
}

//
//==============================================================================================
//

VOID RTIO_Handler( 
				  IN DWORD controlCode )
{
	DWORD currentState = 0 ;
	BOOL bResult ;

	switch( controlCode )
	{ 
	case SERVICE_CONTROL_STOP:  // Stop the service
		{
			bResult = SendStatusToSCM(  
				SERVICE_STOP_PENDING ,
				NO_ERROR , 0 , 1 , 5000 ) ;


			g_bRunningService = FALSE ;

			SetEvent( g_hTerminateEvent ) ;
		}

		return;

	case SERVICE_CONTROL_PAUSE :		// Pause the service
	case SERVICE_CONTROL_CONTINUE :		// Resume from a pause            
	case SERVICE_CONTROL_INTERROGATE:	// Update current status
	case SERVICE_CONTROL_SHUTDOWN:
		return ;

	default :
		break ;
	}

	SendStatusToSCM( currentState, NO_ERROR, 0, 0, 0 );
}

//
//==============================================================================================
//

VOID ServiceMain( DWORD argc, LPTSTR *argv )
{
	BOOL		bSuccess ;
	DWORD		dwStatus = 0 ;
	//	TCHAR		tszInfo[256] ;

	if (!wxInitialize())
		return;

	__try
	{

		g_SrvStatusHandle = RegisterServiceCtrlHandler(
			SERVICE_NAME , 
			( LPHANDLER_FUNCTION )RTIO_Handler ) ;
		if( !g_SrvStatusHandle ) 
		{
			dwStatus = GetLastError( ) ;
			__leave ;
		}

		bSuccess = SendStatusToSCM( 
			SERVICE_START_PENDING, 
			NO_ERROR, 0 , 1 , 5000 ) ;								
		if (!bSuccess) 
		{
			dwStatus = GetLastError( ) ;
			__leave ;
		}

		g_hTerminateEvent = CreateEvent( 0 , TRUE , FALSE , 0 ) ;
		if( NULL == g_hTerminateEvent ) 
		{
			dwStatus = GetLastError( ) ;
			__leave ;
		}

		bSuccess = SendStatusToSCM(	
			SERVICE_START_PENDING ,
			NO_ERROR , 0 , 2 , 1000 ) ;
		if( !bSuccess ) 
		{
			dwStatus = GetLastError( ) ;
			__leave ;
		}

		bSuccess = SendStatusToSCM(	
			SERVICE_START_PENDING ,
			NO_ERROR , 0 , 3 , 5000 ) ; 
		if( !bSuccess ) 
		{
			dwStatus = GetLastError( ) ;
			__leave ;
		}
#if 0    
		OutputDebugString( "******* Start RTIoService! ******* \n" ) ;
#endif
		dwStatus = IOCM_StartService() ;
		if( 0 != dwStatus )
		{
#if 0
			_stprintf( tszInfo , 
				_T("RTIOServer: Start IOService failed : %d\n" ) , dwStatus ) ;
			OutputDebugString( tszInfo ) ;
#endif
			__leave ;
		}

		bSuccess = SendStatusToSCM(	
			SERVICE_RUNNING ,
			NO_ERROR , 0 , 0 , 0 ) ;
		if( !bSuccess ) 
		{
			dwStatus = GetLastError( ) ;
			__leave ;
		}

		g_bRunningService = TRUE ;

		WaitForSingleObject( g_hTerminateEvent, INFINITE ) ;
		IOCM_StopService( ) ;

#if 0
		OutputDebugString( "======= Exit RTIoService! ======= \n" ) ;
#endif
	}
	__finally
	{
		if( g_hTerminateEvent )  
		{
			CloseHandle( g_hTerminateEvent ) ;
		}

		if( g_SrvStatusHandle )
		{
			SendStatusToSCM( SERVICE_STOPPED, dwStatus , 0 , 0 , 0 ) ;
		}

	}
	wxUninitialize();
}

//
//==============================================================================================
//

VOID main( VOID )
{
	BOOL bResult ;    
	SERVICE_TABLE_ENTRY serviceTable[] =
	{
		{ SERVICE_NAME , ( LPSERVICE_MAIN_FUNCTION )ServiceMain } ,
		{ NULL, NULL }
	};

	bResult = StartServiceCtrlDispatcher( serviceTable ) ;
	if( !bResult )
	{
#if 0
		OutputDebugString( "StartServiceCtrlDispatcher failed\n" ) ;
#endif
	}
}
//
//==============================================================================================
//
#endif
