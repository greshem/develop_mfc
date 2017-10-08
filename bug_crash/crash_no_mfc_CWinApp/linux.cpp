#include <afxwin.h>
//定义一个CWinApp的派生类
// class CMinApp:public CWinApp
// {
// public:
//  virtual BOOL InitInstance();
// };
// 
// //重载CWinApp成员函数InitInstance()
// BOOL CMinApp::InitInstance()                     //应用程序初始化
// {
// 	CFrameWnd* pFrame=new CFrameWnd;     //动态生成主窗口类对象
// 	pFrame->Create(0,_T("A Minimal MFC Program")); //创建主窗口
// 	pFrame->ShowWindow(SW_SHOWMAXIMIZED); //显示主窗口
// 	pFrame->UpdateWindow();                                         //刷新主窗口
// 	AfxGetApp()->m_pMainWnd=pFrame;                   //指定应用程序主窗口
// 	return TRUE;
// };
// 
// CMinApp HelloApp;   
