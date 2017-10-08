#2011_08_29   星期一   add by greshem
E:\svn_working_path\develop_mfc\programs\MySQLTool\MySQLTool.bkl 
修改前版本号: 79 
注意: 问题不在 编译的时候  在于 想添加一个log.cpp 文件 然后重新执行bakefile 命令之后  nmake 编译老是出现问题.
########################################################################
费时: 1个小时, 2吃卡在这个问题上, bakefile 的filelist("*.cpp") 同样对于空格的支持不是特别好.  
	估计是bakefile 的通病.
#==========================================================================
1. 项目  bakefile 里面 
<include>"C:\Program Files\MySQL\MySQL Server 5.1\include"</include>
	<sys-lib> libmysql </sys-lib>
	<lib-path>  "c:\\Program Files\\MySQL\\MySQL Server 5.1\\lib\\opt" </lib-path>

导致生成makefile 的时候  一行太长导致 include 的路径的分割
#==========================================================================
生成的makefile 是
MYSQLTOOL_CXXFLAGS = /MD /DWIN32 /I"C:\Program Files\MySQL\MySQL Server \
	5.1\include" /GR /EHsc /D "WIN32" /D "WIN32" /D "_AFXDLL" /D "_DEBUG" /D "_MBCS" /D \

include 里面多了一个空格, 而且分割在上下行

#==========================================================================
到了nmake 的时候 开始不能 正常的发现  编译程序老是报错, mysql.h 文件找不到
 cl /c /nologo /TP /FoMySQLTool_MySQLTool.obj /MD /DWIN32 /I"C:\Program Files\MySQL\MySQL Server  5.1\include"


最后区别在于
MySQL Server  5.1 
其实是:
MySQL Server 5.1 

