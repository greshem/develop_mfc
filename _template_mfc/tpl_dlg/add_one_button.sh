Index: name.rc.tpl
===================================================================
--- name.rc.tpl	(�汾 26)
+++ name.rc.tpl	(��������)
@@ -92,6 +92,7 @@
     DEFPUSHBUTTON   "ȷ��",IDOK,260,7,50,14
     PUSHBUTTON      "ȡ��",IDCANCEL,260,23,50,14
 	LTEXT           "TODO: ���������öԻ����ơ�",IDC_STATIC,50,90,200,8
+    PUSHBUTTON      "Button1",IDC_BUTTON1,179,131,88,17
 END
 
 /////////////////////////////////////////////////////////////////////////////
nameDlg.cpp.tpl
===================================================================
--- nameDlg.cpp.tpl	(�汾 25)
+++ nameDlg.cpp.tpl	(��������)
@@ -82,6 +82,7 @@
 	ON_WM_SYSCOMMAND()
 	ON_WM_PAINT()
 	ON_WM_QUERYDRAGICON()
+	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
 END_MESSAGE_MAP()
 

+void C[%Name%]Dlg::OnButton1() 
+{
+	// TODO: Add your control notification handler code here
+	MessageBox("linux");	
+}

Index: Resource.h.tpl
===================================================================
--- Resource.h.tpl	(�汾 25)
+++ Resource.h.tpl	(��������)
@@ -7,6 +7,7 @@
 #define IDD_ABOUTBOX					100
 #define IDS_ABOUTBOX					101
 #define IDD_[%Name%]_DIALOG				102
+#define IDC_BUTTON1					1000
 
 // Next default values for new objects
 // 
Index: nameDlg.h.tpl
===================================================================
--- nameDlg.h.tpl	(�汾 25)
+++ nameDlg.h.tpl	(��������)
@@ -39,6 +39,7 @@
 	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
 	afx_msg void OnPaint();
 	afx_msg HCURSOR OnQueryDragIcon();
+	afx_msg void OnButton1();

 	//}}AFX_MSG
 	DECLARE_MESSAGE_MAP()
 };
