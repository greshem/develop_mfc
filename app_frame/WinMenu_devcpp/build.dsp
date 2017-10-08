# Microsoft Developer Studio Project File - Name="build" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WinMenu_devcpp - Win32 Default
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "build.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "build.mak" CFG="WinMenu_devcpp - Win32 Default"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinMenu_devcpp - Win32 Default" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinMenu_devcpp - Win32 Default"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release\WinMenu_devcpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release\WinMenu_devcpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /W1 /GR /EHsc /DWINDOWSCODE /D_AFXDLL /D_MBCS /MDd /DWIN32 /D_DEBUG /D_WINDOWS /DNOPCH /D "WIN32" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /W1 /GR /EHsc /DWINDOWSCODE /D_AFXDLL /D_MBCS /MDd /DWIN32 /D_DEBUG /D_WINDOWS /DNOPCH /D "WIN32" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d _WINDOWS
# ADD RSC /l 0x409 /d _WINDOWS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib comctl32.lib rpcrt4.lib wsock32.lib odbc32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbccp32.lib /nologo /machine:i386 /out:"Release\WinMenu_devcpp.exe" /subsystem:windows /libpath:"D:\usr\lib" /INCREMENTAL:NO /NOLOGO /NODEFAULTLIB:LIBCMTD.lib /DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86
# ADD LINK32 winmm.lib comctl32.lib rpcrt4.lib wsock32.lib odbc32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbccp32.lib /nologo /machine:i386 /out:"Release\WinMenu_devcpp.exe" /subsystem:windows /libpath:"D:\usr\lib" /INCREMENTAL:NO /NOLOGO /NODEFAULTLIB:LIBCMTD.lib /DEBUG /SUBSYSTEM:WINDOWS /MACHINE:X86

!ENDIF

# Begin Target

# Name "WinMenu_devcpp - Win32 Default"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WinMenu_private.rc
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Group
# End Target
# End Project

