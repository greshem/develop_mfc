// MyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "MyDlg.h"


// CMyDlg �Ի���

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)
CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
END_MESSAGE_MAP()


// CMyDlg ��Ϣ�������
