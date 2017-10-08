#include "windows.h"
#include "[%name%].h"

[%name%]                ICON    DISCARDABLE     "GENERIC.ICO"

[%name%]  MENU DISCARDABLE 
BEGIN
    POPUP "&File"
    BEGIN
        MENUITEM "E&xit",                             IDM_EXIT
    END
    MENUITEM "&Test!",                                IDM_TEST
    POPUP "&Help"
    BEGIN
        MENUITEM "&About [%name%]_Application...",   IDM_ABOUT
    END
END


ABOUTBOX DIALOG 22, 17, 171, 43
STYLE DS_MODALFRAME | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
CAPTION "[%name%]_Application"
FONT 8, "MS Sans Serif"
{
   CONTROL "[%name%]_MyApp", -1, "STATIC", SS_ICON | WS_CHILD | WS_VISIBLE, 3, 2, 16, 16
   CONTROL "[%name%]_Generic_Application", -1, "STATIC", SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP, 28, 4, 100, 8
   CONTROL "OK", IDOK, "BUTTON", BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_GROUP | WS_TABSTOP, 116, 26, 50, 14
}


