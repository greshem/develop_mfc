#2011_08_29   ����һ   add by greshem
E:\svn_working_path\develop_mfc\programs\MySQLTool\MySQLTool.bkl 
�޸�ǰ�汾��: 79 
ע��: ���ⲻ�� �����ʱ��  ���� �����һ��log.cpp �ļ� Ȼ������ִ��bakefile ����֮��  nmake �������ǳ�������.
########################################################################
��ʱ: 1��Сʱ, 2�Կ������������, bakefile ��filelist("*.cpp") ͬ�����ڿո��֧�ֲ����ر��.  
	������bakefile ��ͨ��.
#==========================================================================
1. ��Ŀ  bakefile ���� 
<include>"C:\Program Files\MySQL\MySQL Server 5.1\include"</include>
	<sys-lib> libmysql </sys-lib>
	<lib-path>  "c:\\Program Files\\MySQL\\MySQL Server 5.1\\lib\\opt" </lib-path>

��������makefile ��ʱ��  һ��̫������ include ��·���ķָ�
#==========================================================================
���ɵ�makefile ��
MYSQLTOOL_CXXFLAGS = /MD /DWIN32 /I"C:\Program Files\MySQL\MySQL Server \
	5.1\include" /GR /EHsc /D "WIN32" /D "WIN32" /D "_AFXDLL" /D "_DEBUG" /D "_MBCS" /D \

include �������һ���ո�, ���ҷָ���������

#==========================================================================
����nmake ��ʱ�� ��ʼ���� �����ķ���  ����������Ǳ���, mysql.h �ļ��Ҳ���
 cl /c /nologo /TP /FoMySQLTool_MySQLTool.obj /MD /DWIN32 /I"C:\Program Files\MySQL\MySQL Server  5.1\include"


�����������
MySQL Server  5.1 
��ʵ��:
MySQL Server 5.1 

