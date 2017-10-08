# Microsoft Developer Studio Project File - Name="Remind" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Remind - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Remind.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Remind.mak" CFG="Remind - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Remind - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Remind - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Remind - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 library/psapi.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Remind - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 library/psapi.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Remind - Win32 Release"
# Name "Remind - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\library\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\library\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\library\CreditStatic.CPP
# End Source File
# Begin Source File

SOURCE=.\library\EnumThreads.cpp
# End Source File
# Begin Source File

SOURCE=.\library\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\MailcheckDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MailconfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ManprocDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\library\MARS.CPP
# End Source File
# Begin Source File

SOURCE=.\MsgnewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\library\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\library\Pop3.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PronewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Public.cpp
# End Source File
# Begin Source File

SOURCE=.\Remind.cpp
# End Source File
# Begin Source File

SOURCE=.\Remind.rc
# End Source File
# Begin Source File

SOURCE=.\RemindDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\RemindView.cpp
# End Source File
# Begin Source File

SOURCE=.\library\SortHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\library\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\library\StatusBarMsgWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\library\SystemIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\library\WinXPButtonST.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\library\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\library\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\library\CreditStatic.H
# End Source File
# Begin Source File

SOURCE=.\library\EnumThreads.h
# End Source File
# Begin Source File

SOURCE=.\library\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\MailcheckDlg.h
# End Source File
# Begin Source File

SOURCE=.\MailconfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ManprocDlg.h
# End Source File
# Begin Source File

SOURCE=.\library\MARS.H
# End Source File
# Begin Source File

SOURCE=.\MsgnewDlg.h
# End Source File
# Begin Source File

SOURCE=.\library\Picture.h
# End Source File
# Begin Source File

SOURCE=.\library\Pop3.h
# End Source File
# Begin Source File

SOURCE=.\ProcessDlg.h
# End Source File
# Begin Source File

SOURCE=.\PronewDlg.h
# End Source File
# Begin Source File

SOURCE=.\library\PSAPI.H
# End Source File
# Begin Source File

SOURCE=.\Public.h
# End Source File
# Begin Source File

SOURCE=.\Remind.h
# End Source File
# Begin Source File

SOURCE=.\RemindDoc.h
# End Source File
# Begin Source File

SOURCE=.\RemindView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\library\SortHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\library\SortListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\library\StatusBarMsgWnd.h
# End Source File
# Begin Source File

SOURCE=.\library\std_defs2.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\library\SystemIcon.h
# End Source File
# Begin Source File

SOURCE=.\library\WinXPButtonST.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ABORT.BMP
# End Source File
# Begin Source File

SOURCE=.\res\ARROW1D.BMP
# End Source File
# Begin Source File

SOURCE=".\res\Bald Eagle.ico"
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmcancel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmkillpr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmok1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmrefres.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CANCEL.BMP
# End Source File
# Begin Source File

SOURCE=.\res\cancel1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CLOCK.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Close.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Close1.BMP
# End Source File
# Begin Source File

SOURCE=.\res\CRDFILE3.BMP
# End Source File
# Begin Source File

SOURCE=.\res\CUT.BMP
# End Source File
# Begin Source File

SOURCE=.\res\DELETE.BMP
# End Source File
# Begin Source File

SOURCE=.\res\DOOROPEN.BMP
# End Source File
# Begin Source File

SOURCE=.\res\DOORSHUT.BMP
# End Source File
# Begin Source File

SOURCE=".\res\folder users.ico"
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\Insert.BMP
# End Source File
# Begin Source File

SOURCE=.\res\killproc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\killproc1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LED1ON.BMP
# End Source File
# Begin Source File

SOURCE=.\res\LED2ON.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Modify.BMP
# End Source File
# Begin Source File

SOURCE=.\res\OK.BMP
# End Source File
# Begin Source File

SOURCE=.\res\ok1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\refresh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\refresh1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Remind.ico
# End Source File
# Begin Source File

SOURCE=.\res\Remind.rc2
# End Source File
# Begin Source File

SOURCE=.\res\RemindDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\shutnow.BMP
# End Source File
# Begin Source File

SOURCE=.\res\shutnow1.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toucan.ico
# End Source File
# Begin Source File

SOURCE=.\res\User.ico
# End Source File
# Begin Source File

SOURCE=".\res\w-travel070_salzburg1.jpg"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\REMINDER.WAV
# End Source File
# Begin Source File

SOURCE=.\res\stone.wav
# End Source File
# End Target
# End Project
