; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=EditDiag
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "getFilePath.h"

ClassCount=5
Class1=CGetFilePathApp
Class2=CGetFilePathDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_GETFILEPATH_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=EditDialog
Class5=EditDiag
Resource4=IDD_DIALOG1

[CLS:CGetFilePathApp]
Type=0
HeaderFile=getFilePath.h
ImplementationFile=getFilePath.cpp
Filter=N

[CLS:CGetFilePathDlg]
Type=0
HeaderFile=getFilePathDlg.h
ImplementationFile=getFilePathDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST1

[CLS:CAboutDlg]
Type=0
HeaderFile=getFilePathDlg.h
ImplementationFile=getFilePathDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GETFILEPATH_DIALOG]
Type=1
Class=CGetFilePathDlg
ControlCount=5
Control1=IDOK,button,1476460545
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_LIST1,SysListView32,1350631429
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:EditDialog]
Type=0
HeaderFile=EditDialog.h
ImplementationFile=EditDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=EditDiag
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NAME,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_NUMBER,static,1342308352
Control8=IDC_CATA,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_BUTTON1,button,1342242816

[CLS:EditDiag]
Type=0
HeaderFile=EditDiag.h
ImplementationFile=EditDiag.cpp
BaseClass=CDialog
Filter=D
LastObject=EditDiag
VirtualFilter=dWC

