#!/usr/bin/perl
#2011_03_28_14:15:34   星期一   add by greshem
# 默认的输出目录是 Debug/

#==========================================================================
#cl.exe /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"Debug/" /Fp"Debug/bbb.pch" /Yu"stdafx.h" /Fo"Debug/" /Fd"Debug/" /FD /GZ   *.cpp
#pch文件去掉, 不会根据头文件产生 pch 文件. 
#/Yu 选项 /Fo 选项. 

#==========================================================================
#只编译 不链接.  /c 选项. 
#cl.exe /c /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"Debug/"  /Fo"Debug/" /Fd"Debug/" /FD /GZ   *.cpp
#cl.exe /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"Debug/"  /Fo"Debug/" /Fd"Debug/" /FD /GZ   *.cpp
print <<EOF
cl.exe /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"Debug/"  /Fo"Debug/" /Fd"Debug/" /FD /GZ   *.cpp
EOF
;
########################################################################
print <<EOF
rc.exe /l 0x804 /fo"Debug\getFilePath.res" /d "NDEBUG" /d "_AFXDLL" 
EOF
;

########################################################################
print <<EOF
link.exe  /nologo /incremental:no /debug /machine:I386  /SUBSYSTEM:windows  /nologo /subsystem:windows /incremental:yes  /debug /machine:I386 /out:"Debug/mfc_test.exe" /pdbtype:sept  Debug/*.obj Debug/*.res version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrt.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 
EOF
;
