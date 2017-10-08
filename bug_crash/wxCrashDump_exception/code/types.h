//
//==============================================================================================
/*
Copyright (c) 2009 Richtech Co.,Ltd. All rights reserved
Module Name: types
Abstract:
Revision History: 2009/08/27
Author:		wangjun
*/
//==============================================================================================
//
#ifndef _TYPES_H_
#define _TYPES_H_
//
//==============================================================================================
//
#ifndef __WIN32__  
#define IN
#define OUT

#define SOCKET_ERROR		(-1)
#define INVALID_SOCKET  0

#define	VOID void
typedef void* PVOID;
typedef void* LPVOID;
typedef long  LONG;
typedef	unsigned long	ULONG;
typedef	unsigned long	DWORD;
typedef	DWORD*	PDWORD;
typedef	unsigned short	WORD;
typedef	WORD*	PWORD;
typedef	unsigned char	BYTE;
typedef	BYTE*	PBYTE;
typedef	int BOOL;
typedef	char	CHAR;
typedef	char*	PCHAR;
typedef int	INT;
typedef unsigned long UINT;
typedef	float	FLOAT;
typedef	int	SOCKET ;


typedef union _LARGE_INTEGER 
{
	struct 
	{
		DWORD LowPart;
		LONG HighPart;
	};
	struct
	{
		DWORD LowPart;
		LONG HighPart;
	} u;
	wxULongLong_t QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER* PLARGE_INTEGER;

typedef wxLongLong_t INT64 ;
typedef	wxULongLong_t DWORD64 ;
typedef DWORD64*   PDWORD64;

#define MAX_PATH					260

#define __stdcall

#define ERROR_SUCCESS				0

#define IPPROTO_TCP					6
#define TCP_NODELAY					1

#define stricmp		strcasecmp
#define strnicmp	strncasecmp

#endif
//
//==============================================================================================
//
#endif