
import os
import sys

def create_bkl():
	build_data='''<?xml version="1.0" ?>
<!-- $Id: bakefile_quickstart.txt,v 1.5 2006/02/11 18:41:11 KO Exp $ -->

<makefile>
    
    <include file="presets/wx.bkl"/>
        <exe id="MyApp">
			'''
	wx_data='''<app-type>gui</app-type>
	<define>wxUSE_OLE</define>
	<define>WXUSINGDLL</define>
	<cxxflags>/D_UNICODE</cxxflags>
	<cxxflags>/D__WXMSW__</cxxflags>
	<cxxflags>/DWINDOWSCODE</cxxflags>
	<cxxflags>/D__WXDEBUG__</cxxflags>
	<cxxflags>/MTd</cxxflags>
	<include>D:\usr\include</include>
	<include>D:\usr\include\msvc</include>
	<lib-path>D:\usr\lib</lib-path>
    <sys-lib>wxmsw28ud_core</sys-lib>
	<sys-lib>wxbase28ud_net</sys-lib>
    <sys-lib>wxbase28ud</sys-lib>
	<sys-lib>wxtiffd</sys-lib>
	<sys-lib>wxjpegd</sys-lib>
	<sys-lib>wxpngd</sys-lib>
	<sys-lib>wxzlibd</sys-lib>
	<sys-lib>wxregexud</sys-lib>
	<sys-lib>wxexpatd</sys-lib>
	'''
	mfc_data='''<cxxflags>/D_AFXDLL</cxxflags> 
	<cxxflags>/D_MBCS</cxxflags>
	<cxxflags>/MDd</cxxflags>
	<ldflags>/INCREMENTAL:NO</ldflags>
	<ldflags>/NOLOGO</ldflags>
	<ldflags>/DEBUG</ldflags>
	<ldflags>/SUBSYSTEM:WINDOWS</ldflags>
	<ldflags>/MACHINE:X86</ldflags>
	'''
	data='''<cxxflags>/DWIN32</cxxflags>
			<cxxflags>/D_DEBUG</cxxflags>			
			<cxxflags>/D_WINDOWS</cxxflags>
			<cxxflags>/DNOPCH</cxxflags>   
			<sys-lib>winmm</sys-lib>
			<sys-lib>comctl32</sys-lib>
			<sys-lib>rpcrt4</sys-lib>
			<sys-lib>wsock32</sys-lib>
			<sys-lib>odbc32</sys-lib>
			<sys-lib>kernel32</sys-lib>
            <sys-lib>user32</sys-lib>
			<sys-lib>gdi32</sys-lib>
			<sys-lib>winspool</sys-lib>
			<sys-lib>comdlg32</sys-lib>
			<sys-lib>advapi32</sys-lib>
			<sys-lib>shell32</sys-lib>
			<sys-lib>ole32</sys-lib>
			<sys-lib>oleaut32</sys-lib>
			<sys-lib>uuid</sys-lib>
			<sys-lib>odbccp32</sys-lib>
			<sources>$(fileList('*.cpp'))</sources> 
        </exe>


</makefile>'''
	f=open("build.bkl","wt")
	dir=os.getcwd()
	dir_array=os.listdir(dir)
	res=''
	for path in dir_array:
		if path.endswith(".rc"):
			res='''<win32-res>'''+path+'''</win32-res>
			'''		
			break
	find=0
	for path in dir_array:
		if path.endswith(".h"):
			if path=="StdAfx.h":
				find=1
				break
	if 1==find:
		build_data=build_data+res+mfc_data+data
	else:
		build_data=build_data+res+wx_data+data
	f.write(build_data)
	f.close()


create_bkl()
	
if 0!=os.system("bakefile -f msvc build.bkl"):
	print "bakefile -f msvc build.bkl failed, please check"
	sys.exit(1)
if 0!=os.system("nmake /f makefile.vc"):
	print "nmake /f makefile.vc failed, please check"
	sys.exit(2)