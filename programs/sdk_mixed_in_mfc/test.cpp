#include   <afxwin.h>
#include   <afxtempl.h>
//void   main()


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
	
{
AfxWinInit(::GetModuleHandle(NULL),   NULL,   ::GetCommandLine(),   0);
CMap <int,   int,   CString,   CString>   m_cMap;

m_cMap.SetAt(9923033,     "张三 ");
m_cMap.SetAt(9826033,     "张A ");
m_cMap.SetAt(9923063,     "张B ");
m_cMap.SetAt(9923093,     "张C ");

CString   strName;
m_cMap.Lookup(9923063,   strName);
AfxMessageBox(strName);
return 0;
}
