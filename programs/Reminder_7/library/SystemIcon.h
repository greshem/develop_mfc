#if !defined(AFX_SYSTEMICON_H__96987E1F_3585_42A3_8086_CB8EB1BB240B__INCLUDED_)
#define AFX_SYSTEMICON_H__96987E1F_3585_42A3_8086_CB8EB1BB240B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemIcon.h : header file
//

#ifndef _INCLUDED_SYSTEMICON_H_ 
#define _INCLUDED_SYSTEMICON_H_ 

#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemIcon window 

class CSystemIcon : public CObject
{
	DECLARE_DYNCREATE(CSystemIcon)
		
// Construction/destruction 
public: 
	CSystemIcon(); 
	CSystemIcon(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID); 
	virtual ~CSystemIcon(); 
	
// Attributes
public:
// Operations
	BOOL Enabled() { return m_bEnabled; } 
	BOOL Visible() { return !m_bHidden; } 
	//创建系统图标 
	BOOL Create(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID); 
	//关于提示文本 
	BOOL SetTooltipText(LPCTSTR pszTooltipText); 
	BOOL SetTooltipText(UINT nID); 
	CString GetTooltipText() const; 
	//关于图标 
	BOOL SetIcon(HICON hIcon); 
	BOOL SetIcon(LPCTSTR lpIconName); 
	BOOL SetIcon(UINT nIDResource); 
	BOOL SetStandardIcon(LPCTSTR lpIconName); 
	BOOL SetStandardIcon(UINT nIDResource); 
	HICON GetIcon() const; 
	void HideIcon(); 
	void ShowIcon(); 
	void DeleteIcon(); 
	//关于通知窗口 
	BOOL SetNotificationWnd(CWnd* pNotifyWnd); 
	CWnd* GetNotificationWnd() const; 
	//自定义消息处理函数 
	virtual LRESULT OnIconNotification(WPARAM uID, LPARAM lEvent); 
	
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemIcon)
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	BOOL m_bEnabled; //是否支持图标 
	BOOL m_bHidden; //是否隐藏图标 
	NOTIFYICONDATA m_tnd; //数据结构，请参考在线帮助 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMICON_H__96987E1F_3585_42A3_8086_CB8EB1BB240B__INCLUDED_)
