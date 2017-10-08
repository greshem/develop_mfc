#include <afxwin.h>
int logger(CString logstr)
{
	CStdioFile file;
	//file.Open("all.log",CFile::modeCreate|CFile::modeWrite);
	//file.Open("all.log", CFile::modeWrite);
	file.Open("all.log", CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	
	//Ð´ÈëÎÄ¼þ
	CString str;
	//str.Format("%s\r\n","hello!I am talkingmute!");
	file.Seek(0,CFile::end);
	file.WriteString( logstr ); 
	file.Close();
	return 1;
}
