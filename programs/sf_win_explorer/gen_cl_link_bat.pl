#!/usr/bin/perl
#2011_03_28_14:15:34   ����һ   add by greshem
# Ĭ�ϵ����Ŀ¼�� Debug/

#==========================================================================
#cl.exe /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"Debug/" /Fp"Debug/bbb.pch" /Yu"stdafx.h" /Fo"Debug/" /Fd"Debug/" /FD /GZ   *.cpp
#pch�ļ�ȥ��, �������ͷ�ļ����� pch �ļ�. 
#/Yu ѡ�� /Fo ѡ��. 

#==========================================================================
#ֻ���� ������.  /c ѡ��. 
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
