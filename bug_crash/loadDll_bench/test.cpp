#include <string>
#include <afxwin.h>
#include <windows.h> 
#include <iostream>

//using namespace std;
typedef DWORD(CALLBACK * USERID)();//GetUserID

int logger(CString logstr)
{
	CStdioFile file;
	file.Open("all.log", CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	
	//д���ļ�
	CString str;
	file.Seek(0,CFile::end);
	file.WriteString( logstr ); 
	file.Close();
	return 1;
}

int main()
{
    USERID get_user_id;
	HINSTANCE hInst;//ʵ�����
	CString dll_name;
	for(int i= 1; i<5000; i++)
	{
		dll_name.Format("%d.dll",i);
		hInst=LoadLibrary(dll_name);
		if(!hInst)
		{
			//logger("���ؿ�dklib.dllʧ��\n");
//			cout<<"���ؿ�"<<dll_name<<"ʧ��"<<endl;
			printf("���ؿ�%sʧ��\n",dll_name.GetBuffer(0));

			int err = GetLastError();
			printf("Error= %d",err);
			Sleep(1000000);
			//return -1;
		}
		else
		{
			printf("���ؿ�%s�ɹ�\n",dll_name.GetBuffer(0));
		}
	}

			Sleep(1000000);
/*
	//��ȡ������ַ 
	get_user_id =(USERID)GetProcAddress(hInst,"DK_GetUserId");
	if(get_user_id == NULL)
	{
		logger("��ȡget_user_id��ַʧ��\n");
	}
	int ret = get_user_id();
	CString logstr;
	logstr.Format("��ȡ�û�id��: %d\n", ret);
	logger(logstr);
    printf("user_id = %d\n",ret);  
*/
    return  0;
}
