// Pop3.cpp: implementation of the CPop3 class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "../remind.h"
#include "Pop3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPop3::CPop3()
{
	if(!m_pop3Server.Create())
	{
		MessageBox(NULL,"can not create socket","error",MB_OK);
	}
}

CPop3::~CPop3()
{
	m_pop3Server.Close();
}

BOOL CPop3::List()
{
	char buf[512];

	wsprintf(buf,"LIST \r\n");
	m_pop3Server.Send(buf,strlen(buf));
	if(CheckResponse(LIST_CHECK)==FALSE)
		return FALSE;
	else
		return TRUE;
}

CString CPop3::GetErrorMessage()
{
	return m_strErrorMessage;
}

CString CPop3::GetPassword()
{
	return m_strPassword;
}

void CPop3::SetPassword(CString password)
{
	m_strPassword = password;
}

CString CPop3::GetUser()
{
	return m_strUser;
}

void CPop3::SetUser(CString user)
{
	m_strUser = user;
}

CString CPop3::GetHost()
{
	return m_strHost;
}

void CPop3::SetHost(CString host)
{
	m_strHost = host;
}

BOOL CPop3::Connect()
{
	char buf[512];

	if(!m_pop3Server.Connect(m_strHost,110))
	{
		m_strErrorMessage = _T("Server cannot be connected.");
		return FALSE;
	}
	else
	{
		if(CheckResponse(CONNECTION_CHECK)==FALSE)
			return FALSE;

		wsprintf(buf,"USER %s \r\n",(LPCSTR)m_strUser);
		m_pop3Server.Send(buf,strlen(buf));
		if(CheckResponse(USER_CHECK)==FALSE)
			return FALSE;

		wsprintf(buf,"PASS %s \r\n",(LPCSTR)m_strPassword);
		m_pop3Server.Send(buf,strlen(buf));
		if(CheckResponse(PASSWORD_CHECK)==FALSE)
			return FALSE;

		return TRUE;
	}
}

int CPop3::GetTotalMailSize()
{
	return m_nTotalSize;
}

int CPop3::GetNumberOfMails()
{
	return m_nNumberMail;
}

CString CPop3::GetMsgContents()
{
	return m_strMsgContents;
}

BOOL CPop3::Statistics()
{
	char buf[512];

	wsprintf(buf,"STAT \r\n");
	m_pop3Server.Send(buf,strlen(buf));
	if(CheckResponse(STAT_CHECK)==FALSE)
		return FALSE;
	else
		return TRUE;
}

BOOL CPop3::Retrieve(int MsgNumber)
{
	char buf[512];

	wsprintf(buf,"PETR %d \r\n",MsgNumber);
	m_pop3Server.Send(buf,strlen(buf));
	if(CheckResponse(RETR_CHECK)==FALSE)
		return FALSE;
	else
		return TRUE;
}

BOOL CPop3::Reset()
{
	char buf[512];

	wsprintf(buf,"RSET \r\n");
	m_pop3Server.Send(buf,strlen(buf));
	if(CheckResponse(RSET_CHECK)==FALSE)
		return FALSE;
	else
		return TRUE;
}

int CPop3::GetMessageSize(int MsgNumber)
{
	if(m_sizeofMsg.GetSize() < MsgNumber+1)
		return 0;
	else
		return m_sizeofMsg[MsgNumber+1];
}

BOOL CPop3::Noop()
{
	char buf[512];

	wsprintf(buf,"NOOP \r\n");
	m_pop3Server.Send(buf,strlen(buf));
	if(CheckResponse(NOOP_CHECK)==FALSE)
		return FALSE;
	else
		return TRUE;
}

BOOL CPop3::Disconnect()
{
	char buf[512];

	wsprintf(buf,"QUIT \r\n");
	m_pop3Server.Send(buf,strlen(buf));
	if(CheckResponse(QUIT_CHECK)==FALSE)
		return FALSE;
	else
		return TRUE;
}

BOOL CPop3::Delete(int &MsgNumber)
{
	char buf[512];

	wsprintf(buf,"DELETE %d \r\n",MsgNumber);
	m_pop3Server.Send(buf,strlen(buf));
	if(CheckResponse(DELETE_CHECK)==FALSE)
		return FALSE;
	else
		return TRUE;
}

BOOL CPop3::Connect(CString host, CString user, CString password)
{
	char buf[512];

	if(!m_pop3Server.Connect(host,110))
	{
		m_strErrorMessage = _T("Server cannot be connected.");
		return FALSE;
	}
	else
	{
		if(CheckResponse(CONNECTION_CHECK)==FALSE)
			return FALSE;

		wsprintf(buf,"USER %s \r\n",(LPCSTR)user);
		m_pop3Server.Send(buf,strlen(buf));
		if(CheckResponse(USER_CHECK)==FALSE)
			return FALSE;

		wsprintf(buf,"PASS %s \r\n",(LPCSTR)password);
		m_pop3Server.Send(buf,strlen(buf));
		if(CheckResponse(PASSWORD_CHECK)==FALSE)
			return FALSE;

		return TRUE;
	}
}

BOOL CPop3::CheckResponse(int ResponseType)
{
	char buf[1000];

	for(int i=0;i<512;i++)
		buf[i] = '\0';

	m_pop3Server.Receive(buf,sizeof(buf));

	switch(ResponseType)
	{
	case CONNECTION_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Bad connection.");
			return FALSE;
		}
		break;
	case USER_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Bad user name.");
			return FALSE;
		}
		break;
	case PASSWORD_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Bad password.");
			return FALSE;
		}
		break;
	case QUIT_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Error occured during QUIT.");
			return FALSE;
		}
		break;
	case DELETE_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Error occured during DELETE.");
			return FALSE;
		}
		break;
	case RSET_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Error occured during RSET.");
			return FALSE;
		}
		break;
	case STAT_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Error occured during STAT.");
			return FALSE;
		}
		else
		{
			BOOL bEmailNumber = TRUE;
			for(char *p=buf;*p!='\0';p++)
			{
				if(*p=='\t' || *p==' ')
				{
					if(bEmailNumber==TRUE)
					{
						m_nNumberMail = atoi(p);
						bEmailNumber = FALSE;
					}
					else
					{
						m_nTotalSize = atoi(p);
						return TRUE;
					}
				}
			}
		}
		break;
	case NOOP_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Error occured during NOOP.");
			return FALSE;
		}
		break;
	case LIST_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Error occured during LIST.");
			return FALSE;
		}
		else
		{
			m_pop3Server.Receive(buf,sizeof(buf));
			for(char *p=buf;*p!='.';p++)
			{
				if(*p=='\t' || *p==' ')
					m_sizeofMsg.Add(atoi(p));
			}
		}
		break;
	case RETR_CHECK:
		if(strnicmp(buf,"-ERR",4)==0)
		{
			m_strErrorMessage = _T("Error occured during RETR.");
			return FALSE;
		}
		else
		{
			char temp[9000];
			m_pop3Server.Receive(temp,sizeof(temp));
			m_strMsgContents = temp;
		}
		break;
	}
	return TRUE;
}
