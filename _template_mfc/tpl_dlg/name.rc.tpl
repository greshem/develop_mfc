// Microsoft Visual C++ generated resource script.
//
#include "resource.h"

#define APSTUDIO_READONLY_SYMBOLS
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 2 resource.
//
#include "afxres.h"

/////////////////////////////////////////////////////////////////////////////
#undef APSTUDIO_READONLY_SYMBOLS

#ifdef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// TEXTINCLUDE
//

1 TEXTINCLUDE DISCARDABLE 
BEGIN
    "resource.h\0"
END

2 TEXTINCLUDE DISCARDABLE 
BEGIN
    "#include ""afxres.h""\r\n"
    "\0"
END

3 TEXTINCLUDE DISCARDABLE 
BEGIN
    "#define _AFX_NO_SPLITTER_RESOURCES\r\n"
    "#define _AFX_NO_OLE_RESOURCES\r\n"
    "#define _AFX_NO_TRACKER_RESOURCES\r\n"
    "#define _AFX_NO_PROPERTY_RESOURCES\r\n"
	"\r\n"
	"#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_CHS)\r\n"
	"#ifdef _WIN32\r\n"
	"LANGUAGE 4, 2\r\n"
	"#pragma code_page(936)\r\n"
	"#endif //_WIN32\r\n"
	"#include ""res\\test.rc2""  // non-Microsoft Visual C++ edited resources\r\n"
	"#include ""l.chs\\afxres.rc""  	// Standard components\r\n"
	"#endif\r\n"
    "\0"
END

/////////////////////////////////////////////////////////////////////////////
#endif    // APSTUDIO_INVOKED


/////////////////////////////////////////////////////////////////////////////
//
// Icon
//

// Icon with lowest ID value placed first to ensure application icon
// remains consistent on all systems.
IDR_MAINFRAME           ICON    DISCARDABLE     "res\\test.ico"


#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_CHS)
#ifdef _WIN32
LANGUAGE 4, 2
#pragma code_page(936)
#endif //_WIN32
/////////////////////////////////////////////////////////////////////////////
//
// Dialog
//

IDD_ABOUTBOX DIALOG DISCARDABLE  0, 0, 235, 55
STYLE DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "关于 [%Name%]"
FONT 9, "宋体"
BEGIN
    ICON            IDR_MAINFRAME,IDC_STATIC,11,17,20,20
    LTEXT           "[%Name%] 1.0 版",IDC_STATIC,40,10,119,8,
                    SS_NOPREFIX
    LTEXT           "版权所有 (C) 2011",IDC_STATIC,40,25,119,8
    DEFPUSHBUTTON   "确定",IDOK,178,7, 50,14,WS_GROUP
END

IDD_[%Name%]_DIALOG DIALOGEX  0, 0, 320, 200 
STYLE DS_MODALFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_POPUP |  WS_VISIBLE | WS_CAPTION | WS_SYSMENU
EXSTYLE WS_EX_APPWINDOW
CAPTION "[%Name%]"
FONT 9, "宋体"
BEGIN
    DEFPUSHBUTTON   "确定",IDOK,260,7,50,14
    PUSHBUTTON      "取消",IDCANCEL,260,23,50,14
	LTEXT           "TODO: 在这里设置对话控制。",IDC_STATIC,50,90,200,8
    PUSHBUTTON      "Button1",IDC_BUTTON1,179,131,88,17
END

/////////////////////////////////////////////////////////////////////////////
//
// Version
//

VS_VERSION_INFO     VERSIONINFO
  FILEVERSION       1,0,0,1
  PRODUCTVERSION    1,0,0,1
 FILEFLAGSMASK 0x3fL
#ifdef _DEBUG
 FILEFLAGS 0x1L
#else
 FILEFLAGS 0x0L
#endif
 FILEOS 0x4L
 FILETYPE 0x1L
 FILESUBTYPE 0x0L
BEGIN
	BLOCK "StringFileInfo"
	BEGIN
        BLOCK "080404B0"
		BEGIN 
			VALUE "CompanyName",     "\0"
			VALUE "FileDescription", "[%Name%] Microsoft 基础类应用程序\0"
			VALUE "FileVersion",     "1, 0, 0, 1\0"
			VALUE "InternalName",    "[%Name%]\0"
			VALUE "LegalCopyright",  "版权所有 (C) 2011\0"
			VALUE "LegalTrademarks", "\0"
			VALUE "OriginalFilename","[%Name%].EXE\0"
			VALUE "ProductName",     "[%Name%] 应用程序\0"
			VALUE "ProductVersion",  "1, 0, 0, 1\0"
		END
	END
	BLOCK "VarFileInfo" 
	BEGIN 
		VALUE "Translation", 0x0804, 1200
    END
END

/////////////////////////////////////////////////////////////////////////////
//
// DESIGNINFO
//

#ifdef APSTUDIO_INVOKED
GUIDELINES DESIGNINFO DISCARDABLE 
BEGIN
    IDD_ABOUTBOX, DIALOG
    BEGIN
        LEFTMARGIN, 7
        RIGHTMARGIN, 228
        TOPMARGIN, 7
        BOTTOMMARGIN, 48
    END
    IDD_[%Name%]_DIALOG, DIALOG
    BEGIN
        LEFTMARGIN, 7
        RIGHTMARGIN, 313
        TOPMARGIN, 7
        BOTTOMMARGIN,193 
    END
END
#endif    // APSTUDIO_INVOKED



/////////////////////////////////////////////////////////////////////////////
//
// String Table
//

STRINGTABLE DISCARDABLE 
BEGIN
    IDS_ABOUTBOX            "关于 [%Name%](&A)..."
END
#endif

#ifndef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 3 resource.
//
#define _AFX_NO_SPLITTER_RESOURCES
#define _AFX_NO_OLE_RESOURCES
#define _AFX_NO_TRACKER_RESOURCES
#define _AFX_NO_PROPERTY_RESOURCES

#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_CHS)
#ifdef _WIN32
LANGUAGE 4, 2
#pragma code_page(936)
#endif //_WIN32
#include "res\\test.rc2"  // non-Microsoft Visual C++ edited resources
#include "l.chs\\afxres.rc"  	// Standard components
#endif

/////////////////////////////////////////////////////////////////////////////
#endif    // not APSTUDIO_INVOKED

