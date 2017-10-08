// Pop3.h: interface for the CPop3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POP3_H__1649A51D_2F28_462E_948C_EA0A8CEF550F__INCLUDED_)
#define AFX_POP3_H__1649A51D_2F28_462E_948C_EA0A8CEF550F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <afxsock.h>

#define CONNECTION_CHECK 0
#define USER_CHECK		1
#define PASSWORD_CHECK	2
#define QUIT_CHECK		3
#define DELETE_CHECK	4
#define RSET_CHECK		5 
#define STAT_CHECK		6 
#define NOOP_CHECK		7
#define LIST_CHECK		8
#define RETR_CHECK		9

class CPop3  
{
public:
	BOOL Connect(CString host, CString user, CString password);
	BOOL Delete(int &MsgNumber);
	BOOL Disconnect();
	BOOL Noop();
	int GetMessageSize(int MsgNumber);
	BOOL Reset();
	BOOL Retrieve(int MsgNumber);
	BOOL Statistics();
	CString GetMsgContents();
	int GetNumberOfMails();
	int GetTotalMailSize();
	BOOL Connect();
	void SetHost(CString host);
	CString GetHost();
	void SetUser(CString user);
	CString GetUser();
	void SetPassword(CString password);
	CString GetPassword();
	CString GetErrorMessage();
	CWordArray m_sizeofMsg;
	BOOL List();
	CPop3();
	virtual ~CPop3();

private:
	BOOL CheckResponse(int ResponseType);
	CString m_strErrorMessage;
	CString m_strPassword;
	CString m_strUser;
	CString m_strHost;
	CString m_strMsgContents;
	int m_nTotalSize;
	int m_nNumberMail;
	CSocket m_pop3Server;
};

#endif // !defined(AFX_POP3_H__1649A51D_2F28_462E_948C_EA0A8CEF550F__INCLUDED_)
