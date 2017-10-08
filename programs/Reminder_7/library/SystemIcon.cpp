// SystemIcon.cpp : implementation file
//

#include "../stdafx.h"
#include "SystemIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemIcon

IMPLEMENT_DYNCREATE(CSystemIcon, CObject)

CSystemIcon::CSystemIcon() 
{ 
	memset(&m_tnd, 0, sizeof(m_tnd)); 
	m_bEnabled = FALSE; 
	m_bHidden = FALSE; 
} 

CSystemIcon::~CSystemIcon() 
{ 
	DeleteIcon(); 
} 


/////////////////////////////////////////////////////////////////////////////
// CSystemIcon message handlers

CSystemIcon::CSystemIcon(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szToolTip, 
		HICON icon, UINT uID) 
{ 
	Create(pWnd, uCallbackMessage, szToolTip, icon, uID); 
	m_bHidden = FALSE; 
} 

BOOL CSystemIcon::Create(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szToolTip, 
		HICON icon, UINT uID) 
{ 
	//�ļ�ֻ��ʹ����WINDOW 95���ϵİ汾�� 
	VERIFY(m_bEnabled = ( GetVersion() & 0xff ) >= 4); 
	if (!m_bEnabled) return FALSE; 
	
	//ȷ��֪ͨ������Ч 
	VERIFY(m_bEnabled = (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))); 
	if (!m_bEnabled) return FALSE; 
	
	//ȷ���Զ�����Ϣ����WM_USER 
	ASSERT(uCallbackMessage >= WM_USER); 
	
	//ȷ����ʾ�ı�����С��64 
	ASSERT(_tcslen(szToolTip) <= 64); 
	
	//����NOTIFYICONDATA�ṹ�������� 
	m_tnd.cbSize = sizeof(NOTIFYICONDATA); 
	m_tnd.hWnd = pWnd->GetSafeHwnd(); 
	m_tnd.uID = uID; 
	m_tnd.hIcon = icon; 
	m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
	m_tnd.uCallbackMessage = uCallbackMessage; 
	strncpy (m_tnd.szTip, szToolTip,sizeof(m_tnd.szTip)); 

	//����ͼ�� 
	VERIFY(m_bEnabled = Shell_NotifyIcon(NIM_ADD, &m_tnd)); 
	return m_bEnabled; 
} 

///////////////////////////////////////////////////////////////////////////// 

void CSystemIcon::DeleteIcon() 
{ 
	if (!m_bEnabled) return; 
	m_tnd.uFlags = 0; 
	Shell_NotifyIcon(NIM_DELETE, &m_tnd); 
	m_bEnabled = FALSE; 
} 

void CSystemIcon::HideIcon() 
{ 
	if (m_bEnabled && !m_bHidden)
	{ 
		m_tnd.uFlags = NIF_ICON; 
		Shell_NotifyIcon (NIM_DELETE, &m_tnd); 
		m_bHidden = TRUE; 
	} 
} 

void CSystemIcon::ShowIcon() 
{ 
	if (m_bEnabled && m_bHidden)
	{ 
		m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
		Shell_NotifyIcon(NIM_ADD, &m_tnd); 
		m_bHidden = FALSE; 
	} 
} 

BOOL CSystemIcon::SetIcon(HICON hIcon) 
{ 
	if (!m_bEnabled) return FALSE; 
	m_tnd.uFlags = NIF_ICON; 
	m_tnd.hIcon = hIcon; 
	return Shell_NotifyIcon(NIM_MODIFY, &m_tnd); 
} 

BOOL CSystemIcon::SetIcon(LPCTSTR lpszIconName) 
{ 
	HICON hIcon = AfxGetApp()->LoadIcon(lpszIconName); 
	return SetIcon(hIcon); 
} 

BOOL CSystemIcon::SetIcon(UINT nIDResource) 
{ 
	HICON hIcon = AfxGetApp()->LoadIcon(nIDResource); 
	return SetIcon(hIcon); 
} 

BOOL CSystemIcon::SetStandardIcon(LPCTSTR lpIconName) 
{ 
	HICON hIcon = LoadIcon(NULL, lpIconName); 
	return SetIcon(hIcon); 
} 

BOOL CSystemIcon::SetStandardIcon(UINT nIDResource) 
{ 
	HICON hIcon = LoadIcon(NULL, MAKEINTRESOURCE(nIDResource)); 
	return SetIcon(hIcon); 
} 

HICON CSystemIcon::GetIcon() const 
{ 
	HICON hIcon = NULL; 
	if (m_bEnabled) 
		hIcon = m_tnd.hIcon; 
	
	return hIcon; 
} 

BOOL CSystemIcon::SetTooltipText(LPCTSTR pszTip) 
{ 
	if (!m_bEnabled) return FALSE; 
	
	m_tnd.uFlags = NIF_TIP; 
	_tcscpy(m_tnd.szTip, pszTip); 
	
	return Shell_NotifyIcon(NIM_MODIFY, &m_tnd); 
} 

BOOL CSystemIcon::SetTooltipText(UINT nID) 
{ 
	CString strText; 
	VERIFY(strText.LoadString(nID)); 
	return SetTooltipText(strText); 
} 

CString CSystemIcon::GetTooltipText() const 
{ 
	CString strText; 
	if (m_bEnabled) 
		strText = m_tnd.szTip; 
	
	return strText; 
} 

BOOL CSystemIcon::SetNotificationWnd(CWnd* pWnd) 
{ 
	if (!m_bEnabled) return FALSE; 
	ASSERT(pWnd && ::IsWindow(pWnd->GetSafeHwnd())); 
	m_tnd.hWnd = pWnd->GetSafeHwnd(); 
	m_tnd.uFlags = 0; 
	
	return Shell_NotifyIcon(NIM_MODIFY, &m_tnd); 
} 

CWnd* CSystemIcon::GetNotificationWnd() const 
{ 
	return CWnd::FromHandle(m_tnd.hWnd); 
} 

LRESULT CSystemIcon::OnIconNotification(UINT wParam, LONG lParam) 
{ 
	if (wParam != m_tnd.uID) 
		return 0L; 
	
	CMenu menu, *pSubMenu; 
	
	//�����Ҽ������˵� 
	if (LOWORD(lParam) == WM_RBUTTONUP) 
	{ 
		if (!menu.LoadMenu(m_tnd.uID)) return 0; 
		if (!(pSubMenu = menu.GetSubMenu(0))) return 0; 
		
		//�趨��һ��Ϊȱʡ 
		::SetMenuDefaultItem(pSubMenu->m_hMenu, 0, TRUE); 
		
		//���嵯���˵� 
		CPoint pos; 
		GetCursorPos(&pos); 
		::SetForegroundWindow(m_tnd.hWnd); 
		::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, m_tnd.hWnd, NULL); 
		::PostMessage(m_tnd.hWnd, WM_NULL, 0, 0); 
		menu.DestroyMenu(); 
	} 
	else if (LOWORD(lParam) == WM_LBUTTONDBLCLK) 
	{ 
		if (!menu.LoadMenu(m_tnd.uID)) return 0; 
		if (!(pSubMenu = menu.GetSubMenu(0))) return 0; 
		
		//˫�������ȱʡ�˵� 
		::SetForegroundWindow(m_tnd.hWnd); 
		::SendMessage(m_tnd.hWnd, WM_COMMAND, pSubMenu->GetMenuItemID(0), 0); 
		menu.DestroyMenu(); 
	} 
	return 1; 
} 
