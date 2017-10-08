// getFilePathDlg.cpp : implementation file
//

#include "stdafx.h"
#include "getFilePath.h"
#include "getFilePathDlg.h"
#include "EditDiag.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <stdlib.h>
//#include <hash>
//#include <string>
//#include <map>
//using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CGetFilePathDlg dialog

CGetFilePathDlg::CGetFilePathDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetFilePathDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetFilePathDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetFilePathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetFilePathDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetFilePathDlg, CDialog)
	//{{AFX_MSG_MAP(CGetFilePathDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetFilePathDlg message handlers

BOOL CGetFilePathDlg::OnInitDialog()
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
	//CStatic
	//20100520, 对于list的选择，重要， LVS_EX_GRIDLINES, 
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CListCtrl  * pListCtrl = ( CListCtrl *)GetDlgItem(IDC_LIST1);
//	pListCtrl->DeleteAllItems();
	pListCtrl->SetTextBkColor(RGB(170, 240, 150)); 
	pListCtrl->InsertColumn(0, "名称",LVCFMT_LEFT,60);
	pListCtrl->InsertColumn(1, "路径",LVCFMT_LEFT,200*2);
	pListCtrl->InsertColumn(2, "简介",LVCFMT_LEFT,60);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetFilePathDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetFilePathDlg::OnPaint() 
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
HCURSOR CGetFilePathDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetFilePathDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_strPath="list";
	CFileDialog cfd(true,_T(".txt"),NULL,OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Executable   Files   (*.txt)|*.txt|All   Files   (*.*)|*.*||"),this);    
	if(m_strPath=="")
	{
		if(cfd.DoModal()==IDOK)    
		{  
			m_strPath = cfd.GetPathName();       
			MessageBox(m_strPath);
			UpdateData(false);    
		}
	}	

		CListCtrl  * pListCtrl = ( CListCtrl *)GetDlgItem(IDC_LIST1);
		pListCtrl->DeleteAllItems();
		pListCtrl->SetTextBkColor(RGB(170, 240, 150)); 
	//	pListCtrl->GetSafeHwnd();
//		pListCtrl->InsertColumn(0, "名称",LVCFMT_LEFT,60);
//		pListCtrl->InsertColumn(1, "路径",LVCFMT_LEFT,200);
//		pListCtrl->InsertColumn(2, "简介",LVCFMT_LEFT,60);
		
		//int nItem = pListCtrl->GetItemCount();
/*		pListCtrl->InsertItem(0, "成都");
		pListCtrl->SetItemText(0, 1, "450百万");
		pListCtrl->SetItemText(0, 2, "40立方米");
		
		pListCtrl->InsertItem(1, "石家庄");
		pListCtrl->SetItemText(1, 1, "350百万");
		pListCtrl->SetItemText(1, 2, "460立方米"); 
		
		pListCtrl->InsertItem(2, "西安");
		pListCtrl->SetItemText(2, 1, "400百万");
		pListCtrl->SetTextColor(RGB(255, 0, 0));
		pListCtrl->SetItemText(2, 2, "450立方米");
	
		pListCtrl->InsertItem(2, "成都444");
		pListCtrl->SetItemText(2, 1, "450百万");
		pListCtrl->SetItemText(2, 2, "40立方米");*/
		
/*		for(int i=0;i<=100;i++)
		{
			CString name="钱忠杰";
			name.Format("%s%d", "钱忠杰", i);
			CString number;
			number.Format("%d", i);
			int tmp=pListCtrl->InsertItem(i, name);
			pListCtrl->SetItemText(tmp, 1, number);
			pListCtrl->SetItemText(tmp, 2,  number );
			pListCtrl->SetItemText(tmp, 3,  number );
		}	*/

		//CFile file;
		FILE *fp;
		char temp[1024];
		fp=fopen(m_strPath,"r" );
		//while(file.)
		int i=0;
		//	CListCtrl  * pListCtrl = ( CListCtrl *)GetDlgItem(IDC_LIST1);
		CEdit *ptrEdit=(CEdit *) GetDlgItem(IDC_EDIT1);
		CString pattern;
						CMapStringToString mapCata(100);
		ptrEdit->GetWindowText(pattern);
				int cataCount=0;	
		while(fgets(temp, sizeof(temp), fp)> 0)
		{
			//pattern 
			if(!pattern.IsEmpty())
			{
				if(!strstr(temp,  pattern) )
				{
					continue;	
				}
				//最多只列出1000个
				if(i > 1000)
				{
					continue;
				}
				CString name="钱忠杰";
				name.Format("%s%d", "钱忠杰", i);
				int tmp=pListCtrl->InsertItem(i, name);
				
				pListCtrl->SetItemText(tmp, 1, temp);
				
				CString number;
				number.Format("%d", i);
				pListCtrl->SetItemText(tmp, 2,  number );
				
				i++;
			}	
			else
			{
				//获取第二列, 分类信息
				
				char cata[1024];
			//	map<string, int> mapCata;

				memset(cata, '\0', sizeof(cata));
				char *tmp=strstr(temp,"/");
				if(tmp==NULL)
				{
					continue;
				}	
				char *end=NULL;
					tmp=strstr(tmp+1,"/");
					if(tmp==NULL)
					{
						continue;
					}	
					end=strstr(tmp+1, "/");
				if(tmp==NULL || end==NULL|| tmp==end)
				{
					continue;
				}
				int countN=_snprintf(cata, end-tmp-1,"%s",	 tmp+1); 
				CString  value;

				if(mapCata.Lookup(CString(cata), value ))
				{
					//找到了
					CString strErr;
					strErr.Format("%s 已经保存过了", strErr);
					cataCount++;
				//	MessageBox(strErr);
					
				}
				else
				{
					//没有找到
					mapCata[CString
						(cata)]= "ok";
					
					CString name="钱忠杰";
					name.Format("%s%d", "钱忠杰", i);
					int tmp=pListCtrl->InsertItem(i, name);
					
					pListCtrl->SetItemText(tmp, 1, cata);
					
					CString number;
					number.Format("%d", i);
					pListCtrl->SetItemText(tmp, 2,  number );

				}	


			}

		}


}

void CGetFilePathDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	m_nIndex = m_list.GetNextSelectedItem(pos);  // 得到项目索引
	*pResult = 0;
}

void CGetFilePathDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	m_nIndex = m_list.GetNextSelectedItem(pos);  // 得到项目索引
	//MessageBox("双击");	
	EditDiag ed;
	ed.m_strName=m_list.GetItemText(m_nIndex,0);
	ed.m_strCata=m_list.GetItemText(m_nIndex,1);
	ed.m_strNumber=m_list.GetItemText(m_nIndex,2);
	
	if(ed.DoModal()==IDOK)
	{			
		m_list.SetItemText(m_nIndex,0,ed.m_strName);
		m_list.SetItemText(m_nIndex,1,ed.m_strCata);
		m_list.SetItemText(m_nIndex,2,ed.m_strNumber);
	}

	*pResult = 0;
}
