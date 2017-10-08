// CDImage_GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDImage_GUI.h"
#include "CDImage_GUIDlg.h"
#include <io.h>
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable:  4996)
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About;

using namespace std;
CString Filename;
string basename(string &in)
{
	string basename=in.substr(in.rfind('\\')+1, in.length());
	return basename;
}


bool FileIsExist(char * FileName)
{
	if ( _access(FileName,0) == -1 ) 
	{    
		return(false);
	}    

	return(true);
}

int HaveSemicolon(char *str)
{
	if(str==NULL)
	{
		return 0;
	}
	char *p;
	for(p=str; *p!='\0';p++)
	{
		if(*p==';')
		{
			return 1;
		}
	}
	return 0;
}
extern int   TransDirectoryCheckSemicolon(char*   DirName )
{
	CFileFind   tempFind;   		
	char   tempFileFind[1024];   	
	sprintf(tempFileFind, "%s\\*.*",DirName);
	//ƥ���ʽΪ*.*,����Ŀ¼�µ������ļ�  

	BOOL   IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
	if(IsFinded)
	{
		//printf("�ҵ���\n");
	}
	else
	{
		printf("%s\n", tempFileFind);
		//printf("û���ҵ�\n");
		return 0;
	}
	//���ҵ�һ���ļ�
	while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();   		//�ݹ������������ļ�  
		if(!tempFind.IsDots())  						//������� ". "Ŀ¼
		{
			char   foundFileName[1024];
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(1024));
			if(HaveSemicolon(foundFileName))
			{
				Filename=foundFileName;
				return 1;
			}
			if(tempFind.IsDirectory())  				//�����Ŀ¼����ݹ�ص���
			{   
				char   tempDir[1024];
				_snprintf(tempDir, sizeof(tempDir), "%s\\%s",DirName,foundFileName);
				printf("DIR: %s\n", tempDir);
				TransDirectoryCheckSemicolon(tempDir);
			}
			else
			{   
				char   tempFileName[1024];
				_snprintf(tempFileName ,sizeof(tempFileName), "%s\\%s",DirName,foundFileName);
				
			}
		}

	}
	//	char   foundFileName[1024];
	//	strcpy(foundFileName,tempFind.GetFileName().GetBuffer(1024));
	//	char   tempFileName[1024];
	//	_snprintf(tempFileName ,sizeof(tempFileName), "%s\\%s",DirName,foundFileName);
	//	out.push_back(string(tempFileName));

	tempFind.Close();

	return   0;
} 


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDImage_GUIDlg dialog

CCDImage_GUIDlg::CCDImage_GUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDImage_GUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCDImage_GUIDlg)
	m_strVolumn = _T("");
	m_bAllOneTime = FALSE;
	m_strMtime = _T("");
	m_bLongName = true;
	m_bCheckWithFileContent = FALSE;
	m_bUpcase = true;
	m_strIsoDir = _T("");
	m_strBootSectFile = _T("");
	m_bDVD = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCDImage_GUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDImage_GUIDlg)
	DDX_Text(pDX, IDC_VOLUMN, m_strVolumn);
	DDX_Check(pDX, IDC_CHECK_MTIME, m_bAllOneTime);
	DDX_Text(pDX, IDC_EDIT_MTIME, m_strMtime);
	DDX_Check(pDX, IDC_CHECK_LONGNAME, m_bLongName);
	DDX_Check(pDX, IDC_CHECK_WITH_ALL_CONTENT, m_bCheckWithFileContent);
	DDX_Check(pDX, IDC_CHECK_UPCASE, m_bUpcase);
	DDX_Text(pDX, IDC_SRC_DIR, m_strIsoDir);
	DDX_Text(pDX, IDC_BOOT_RECORD, m_strBootSectFile);
	DDX_Check(pDX, IDC_CHECK_DVD, m_bDVD);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCDImage_GUIDlg, CDialog)
	//{{AFX_MSG_MAP(CCDImage_GUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GEN, OnGen)
	ON_BN_CLICKED(IDC_CHECK_MTIME, OnCheckMtime)
	ON_BN_CLICKED(IDC_CHECK_LONGNAME, OnCheckLongname)
	ON_BN_CLICKED(IDC_CHECK_WITH_ALL_CONTENT, OnCheckWithAllContent)
	ON_BN_CLICKED(IDC_CHECK_UPCASE, OnCheckUpcase)
	ON_BN_CLICKED(IDC_BUT_DIRETORY, OnButDiretory)
	ON_BN_CLICKED(IDC_BUT_BOOT_RECORD, OnButBootRecord)
	ON_EN_CHANGE(IDC_VOLUMN, OnChangeVolumn)
	ON_BN_CLICKED(IDC_CHECK_DVD, OnCheckDvd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDImage_GUIDlg message handlers

BOOL CCDImage_GUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	if(_access("CDImage.exe", 0 )== -1 )
	{
		ExtractExe();
	}
	else
	{

	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCDImage_GUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCDImage_GUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCDImage_GUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCDImage_GUIDlg::OnGen() 
{
	// TODO: Add your control notification handler code here
	//20101026 add by greshem 
	// -l  volume label, no spaces (e.g. -lMYLABEL) û�пո�
	// �÷� CDImage.exe -n -d -oc /root /root.iso
	//  CDImage.exe -lroot -n -d -oc -m /root /root.iso  -m ��������DVD
	//////////////////////////////////////////////////////////////////////////
	// ��������
	//-b  "El Torito" boot sector file, no spaces
    //   (e.g. -bc:\location\cdboot.bin)
	//////////////////////////////////////////////////////////////////////////
	//-t   ͳһʱ��
	//  -t  time stamp for all files and directories, no spaces, any delimiter
    //    (e.g. -t12/31/91,15:01:00)
	//////////////////////////////////////////////////////////////////////////
	//   ���ļ���
	//   -n  allow long filenames (longer than DOS 8.3 names)
	//////////////////////////////////////////////////////////////////////////
	//   ����ֽ��ж��ظ��ļ��� ȡ��MD5	
	//    -oc slower duplicate file detection using binary comparisons rather
    //    than MD5 hash values
	//////////////////////////////////////////////////////////////////////////
	//     -d  don't force lowercase filenames to uppercase
	//	 �ļ�����ת���ɴ�Сд�� 
	//	 ƴ��������,  cdimage.exe �� ������
	CString cmd("CDImage.exe  ");
	if(m_strVolumn.GetLength()>=1)
	{
		cmd+="-l";
		cmd+=m_strVolumn;
		cmd+="   ";
	}

	if(m_strBootSectFile.GetLength()>=1)
	{
		cmd+="-b";
		cmd+=m_strBootSectFile;
		cmd+="   ";
	}

	if(m_bLongName)
	{
		cmd+="  -n ";
	}
	if(m_bCheckWithFileContent)
	{
		cmd+="-oc  ";
	}
	if(m_bUpcase)
	{
		cmd+=" -d ";
	}
	if(m_bAllOneTime)
	{
		cmd+="-t12/31/91,15:01:00  ";
	}

	if(m_bDVD)
	{
		cmd+="  -m  ";
	}
	if(m_strIsoDir.GetLength()==0)
	{
		MessageBox("��������Ŀ¼�Ǳ����");
		return ;
	}
	if(m_strIsoDir.GetLength()<=3)
	{
		MessageBox("������Ѵ�������ISO����,����ѡ������Ŀ¼");
		return ;
	}
	cmd+=m_strIsoDir;
	cmd+="   ";

	cmd+=m_strIsoDir;
	cmd+=".iso ";
	//========================================================================
	//ssageBox(cmd);

	//========================================================================
	//������� ճ������ȥ.
	HGLOBAL data=GlobalAlloc(GPTR, cmd.GetLength());
	LPBYTE lpSmpData=(LPBYTE) GlobalLock(data);
	memcpy(lpSmpData, cmd, cmd.GetLength());


	OpenClipboard();
	EmptyClipboard();
	SetClipboardData(CF_TEXT, data);
	CloseClipboard();


	//���ļ�������û�пո�.
	if(TransDirectoryCheckSemicolon(m_strIsoDir.GetBuffer(0)))
	{
		CString log;
		log+=Filename;
		log+="�ļ�����;�ţ� ȥ���ֺ�֮���ٽ�������";
		MessageBox(log);
		return ;
	}

	GetDlgItem(IDC_GEN)->EnableWindow(FALSE);
	//WinExec ˵�����������У� ����ʵ�ʵ�Ч���������� ���������У� ֮����.
	WinExec(cmd, TRUE);
	GetDlgItem(IDC_GEN)->EnableWindow(TRUE);

	CString outIso=m_strIsoDir;
	outIso+=".iso";
	if(_access(outIso, 0) != -1)
	{
	//	MessageBox(outIso+=" �Ѿ�����");
	}
	else
	{
	//	MessageBox(outIso+=" û������");
	}
}

void CCDImage_GUIDlg::OnCheckMtime() 
{
	// TODO: Add your control notification handler code here
	
	//	GetTimeZoneInformation(LPTIME_ZONE_INFORMATION   lpTimeZoneInformation   ) 
	CTime cur;

	//cur.GetCurrentTime
	cur= CTime::GetCurrentTime();
	//m_strMtime = cur.Format("%D/%M/%Y:%T");

	CString	tmp;
	tmp.Format("%d/%d/%d,%d:%d:%d", cur.GetYear(), cur.GetMonth(), cur.GetDay(), cur.GetHour(), cur.GetMinute(), cur.GetSecond());
	//MessageBox(tmp);
	//tmp=cur.FormatGmt(_T("%m/%d/%Y:%X: --- %H:%M:%S"));
	//%H.%M.%S"));

	if(m_bAllOneTime==FALSE)
	{
		m_bAllOneTime=TRUE;
	}
	else
	{
		m_bAllOneTime=FALSE;
	}
	GetDlgItem(IDC_EDIT_MTIME)->SetWindowText(tmp);
	if(m_bAllOneTime==FALSE)
	{
		GetDlgItem(IDC_EDIT_MTIME)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MTIME)->EnableWindow(TRUE);
	}
	
}

void CCDImage_GUIDlg::OnCheckLongname() 
{
	// TODO: Add your control notification handler code here
	if(m_bLongName==TRUE)
	{
		m_bLongName=FALSE;
	}
	else
	{
		m_bLongName=TRUE;
	}
}

void CCDImage_GUIDlg::OnCheckWithAllContent() 
{
	// TODO: Add your control notification handler code here
	if(m_bCheckWithFileContent==TRUE)
	{
		m_bCheckWithFileContent=FALSE;
	}
	else
	{
		m_bCheckWithFileContent=TRUE;
	}
}

void CCDImage_GUIDlg::OnCheckUpcase() 
{
	// TODO: Add your control notification handler code here
	if(m_bUpcase==TRUE)
	{
		m_bUpcase=FALSE;
	}
	else
	{
		m_bUpcase=TRUE;
	}
}

void CCDImage_GUIDlg::OnButDiretory() 
{
	// TODO: Add your control notification handler code here
	
	char   strFilePath[225]; //CSIDL_DESKTOPDIRECTORY   
	LPITEMIDLIST   pidlBeginAt,   pidlDestination;   
	SHGetSpecialFolderLocation(HWND_DESKTOP,   CSIDL_DRIVES,   &pidlBeginAt);//   ȡ�ÿ�ʼ�˵��������PIDL   
	BROWSEINFO   BrInfo;   
	ZeroMemory(&BrInfo,   sizeof(BrInfo));   
	BrInfo.hwndOwner =   HWND_DESKTOP;//�ɲ���   
	BrInfo.pidlRoot =   pidlBeginAt;   
	BrInfo.lpszTitle =   "��ѡ��һ���ļ��У�";   
	pidlDestination =   SHBrowseForFolder(&BrInfo);//����ļ���   
	if(NULL   ==   pidlDestination)//�û�ѡ����ȡ����ť   
		return;   
	SHGetPathFromIDList(pidlDestination,   strFilePath);//   ��PIDLת��Ϊ·����   
	//�滻��(IDC_EDIT_MAIN_DATA_PATH)
	GetDlgItem(IDC_SRC_DIR)->SetWindowText(strFilePath);

	GetDlgItem(IDC_VOLUMN)->SetWindowText(basename(string(strFilePath)).c_str());
	
	CString path1("..\\pe_livece_my_iso_res\\tools\\iso_boot_sect.bif");
	CString path2("..\\..\\pe_livece_my_iso_res\\tools\\iso_boot_sect.bif");
	if(FileIsExist(path1.GetBuffer(0)))
	{
		GetDlgItem(IDC_BOOT_RECORD)->SetWindowText(path1);
	}

	if(FileIsExist(path2.GetBuffer(0)))
	{
		GetDlgItem(IDC_BOOT_RECORD)->SetWindowText(path2);
	}
	//GetDlgItem(IDC_BOOT_RECORD)->SetWindowText(path2);
	UpdateData();

}

void CCDImage_GUIDlg::OnButBootRecord() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(true);
	if(dlg.DoModal()==IDOK)
	{
		CString tmp=dlg.GetPathName();
		GetDlgItem(IDC_BOOT_RECORD)->SetWindowText(tmp);
	}
	UpdateData();
}

void CCDImage_GUIDlg::OnChangeVolumn() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CCDImage_GUIDlg::OnCheckDvd() 
{
	// TODO: Add your control notification handler code here
	if(m_bDVD==TRUE)
	{
		m_bDVD=FALSE;
	}
	else
	{
		m_bDVD=TRUE;
	}
}

int  CCDImage_GUIDlg::ExtractExe()
{
	HRSRC hResInfo;
	HGLOBAL hResData;
	DWORD dwSize,dwWritten;
	LPBYTE p;
	HANDLE hFile;
	
	
    // �����������Դ
	hResInfo = FindResource(NULL,MAKEINTRESOURCE(EXE_CDIMAGE),"EXE");
	if(hResInfo == NULL) return -1;
    // �����Դ�ߴ�
	dwSize = SizeofResource(NULL,hResInfo);
    // װ����Դ
	hResData = LoadResource(NULL,hResInfo);
	if(hResData == NULL) return -2;
	// Ϊ���ݷ���ռ�
	p = (LPBYTE)GlobalAlloc(GPTR, dwSize); 
	if (p == NULL)     return -3 ;
	// ������Դ����
	
	CopyMemory((LPVOID)p, (LPCVOID)LockResource(hResData), dwSize);
	
	//	CString tmp(p);
	//	MessageBox(tmp);
	
	
	hFile = CreateFile("CDImage.exe",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	if(hFile == NULL) return -4 ;
	
	WriteFile(hFile,(LPVOID)p,dwSize,&dwWritten,NULL);
	CloseHandle(hFile);

	if(CopyFile("./CDImage.exe", "c:\\windows\\CDImage.exe", TRUE))
	{
		DeleteFile("./CDImage.exe");
	}

	return 0;
}
