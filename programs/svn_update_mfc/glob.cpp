#include <afxwin.h>
#include <direct.h>
#include <time.h>

//����һ��CWinApp��������
int logger(CString logstr)
{
	CStdioFile file;
	//file.Open("all.log",CFile::modeCreate|CFile::modeWrite);
	//file.Open("all.log", CFile::modeWrite);
	file.Open("all.log", CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	
	//д���ļ�
	CString str;
	//str.Format("%s\r\n","hello!I am talkingmute!");
	file.Seek(0,CFile::end);
	file.WriteString( logstr ); 
	file.Close();
	return 1;
}


class CMinApp:public CWinApp
{
	public:
 		virtual BOOL InitInstance();
};

BOOL exec_svn_update(LPTSTR dir_path)
{
    CString log;
	if( _chdir(dir_path) )
	{
        log.Format("��Ŀ: %s ����", dir_path); 
		WinExec("svn update",SW_HIDE);
	}
	else
	{
		log.Format("%s chdir ʧ��, Ŀ¼���ܲ�����\n", dir_path);
		logger(log);
	}

	return TRUE;
}

BOOL check_onlyOne_instance()
{
	BOOL bFound = FALSE;
	HANDLE hMutexOneInstantance=CreateMutex(NULL,TRUE,_T("PreventSecondInstance"));
 	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
 		 bFound=TRUE;
	}
 	if(hMutexOneInstantance)
	{
 		ReleaseMutex(hMutexOneInstantance);
	}
	if (bFound==TRUE)
 	{ 
		::AfxMessageBox(" �ó����Ѿ�����");
 		return FALSE;
 	}
	return TRUE;
}
//����CWinApp��Ա����InitInstance()
BOOL CMinApp::InitInstance()                     //Ӧ�ó����ʼ��
{
    int count=0;
	char time_buf[1024] = {0};
	char dir_exe[1024] = {0};
	time_t t = 0;

	if(FALSE == check_onlyOne_instance())
	{
		return FALSE;
	}
	if(0 == GetCurrentDirectory(sizeof(dir_exe),dir_exe))
	{
		return FALSE;
	}

	while(1)
	{
		CString logstr;	
		t=time(NULL);
		strftime(time_buf, sizeof(time_buf), "%Y_%m_%d_%H:%M:%S", localtime(&t));

		logstr.Format("%s svn ��ʼ��%d�θ���\n", time_buf,count); 
		logger(logstr); 
			
		exec_svn_update("c:\\bin");
		//exec_svn_update("E:\\svn_working_path\\doc_collaboration");
		exec_svn_update("E:\\svn_working_path\\rich_addvalue2");
		
		
		exec_svn_update("e:\\svn_working_path\\90_develop_wxwidgets");
		exec_svn_update("e:\\svn_working_path\\bin");
		exec_svn_update("e:\\svn_working_path\\develop_cpp");
		exec_svn_update("e:\\svn_working_path\\develop_ddk");
		exec_svn_update("e:\\svn_working_path\\develop_mfc");
		exec_svn_update("e:\\svn_working_path\\develop_perl");
		exec_svn_update("e:\\svn_working_path\\develop_perl_windows");
		exec_svn_update("e:\\svn_working_path\\develop_python");
		exec_svn_update("e:\\svn_working_path\\develop_thread");
		exec_svn_update("e:\\svn_working_path\\develop_wxwidgets");
		exec_svn_update("e:\\svn_working_path\\doc_collaboration");
		exec_svn_update("e:\\svn_working_path\\fulldisk");
		exec_svn_update("e:\\svn_working_path\\iso_index_and_search");
		exec_svn_update("e:\\svn_working_path\\lmyunit");
		exec_svn_update("e:\\svn_working_path\\netware_emulator");
		exec_svn_update("e:\\svn_working_path\\octopus_agile");
		exec_svn_update("e:\\svn_working_path\\PartImage");
		exec_svn_update("e:\\svn_working_path\\project_collaboration");
		exec_svn_update("e:\\svn_working_path\\remote_manager_system");
		exec_svn_update("e:\\svn_working_path\\rich_addvalue2");
		exec_svn_update("e:\\svn_working_path\\rich_addvalue3");
		exec_svn_update("e:\\svn_working_path\\rich_addvalue4");
		exec_svn_update("e:\\svn_working_path\\rich_netclone2");
		exec_svn_update("e:\\svn_working_path\\richtech-scripts_rpm");
		exec_svn_update("e:\\svn_working_path\\system_initialization_win");
		exec_svn_update("e:\\svn_working_path\\vim_common");
		
		_chdir(dir_exe);//���ؿ�ִ���ļ�Ŀ¼
		memset(time_buf,'0',sizeof(time_buf));
		Sleep(1000*300);
		count++;
	}
	return TRUE;
}

CMinApp HelloApp;   
