
#include <windows.h>  
#include <stdlib.h>
#include <stdio.h>
#include "HideMySelf.h" 
#include "log.h"


HINSTANCE hInst;   // current instance

LPCTSTR lpszAppName  = "HideMySelf";
LPCTSTR lpszTitle    = "HideMySelf_Application"; 
bool WINAPI LoopThread(LPVOID lParam);

bool WINAPI HideInWin2000();

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine, int nCmdShow)
{
   MSG      msg;
   HWND     hWnd; 
   WNDCLASSEX wc;

   // Register the main application window class.
   //............................................
   wc.style         = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc   = (WNDPROC)WndProc;       
   wc.cbClsExtra    = 0;                      
   wc.cbWndExtra    = 0;                      
   wc.hInstance     = hInstance;              
   wc.hIcon         = LoadIcon( hInstance, lpszAppName ); 
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
   wc.lpszMenuName  = lpszAppName;              
   wc.lpszClassName = lpszAppName;              
   wc.cbSize        = sizeof( WNDCLASSEX );
   wc.hIconSm       = (HICON)LoadImage( hInstance, lpszAppName,
                                 IMAGE_ICON, 16, 16,
                                 LR_DEFAULTCOLOR );

   	if ( !RegisterClassEx( &wc ) )
	{
		log::Instance()->logger("注册失败\n");
		return( FALSE );
	}

   hInst = hInstance; 

   // Create the main application window.
   //....................................
   hWnd = CreateWindow( lpszAppName, 
                        lpszTitle,    
                        WS_OVERLAPPEDWINDOW | WS_VSCROLL, 
                        CW_USEDEFAULT, 0, 
                        CW_USEDEFAULT, 0,  
                        NULL,              
                        NULL,              
                        hInstance,         
                        NULL               
                      );

   	if ( !hWnd ) 
	{
		log::Instance()->logger("创建窗口失败\n");
		return( FALSE );
	}

	//========================================================================
   	WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	wp.flags = WPF_RESTORETOMAXIMIZED;
	wp.showCmd = SW_HIDE;
	SetWindowPlacement(hWnd, &wp);
	//========================================================================
	HideInWin2000();
    
	//========================================================================

	log::Instance()->logger("启动线程\n");
	DWORD dw;
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)LoopThread,0,0,&dw);
	

   //ShowWindow( hWnd, nCmdShow ); 
   //UpdateWindow( hWnd );         

   while( GetMessage( &msg, NULL, 0, 0) )   
   {
      TranslateMessage( &msg ); 
      DispatchMessage( &msg );  
   }

   return( msg.wParam ); 
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
static int  nDspLines;
static int  nNumItems = 0;
static int  nCurPos   = 0;
static char szBuf[10];

   switch( uMsg )
   {
      case WM_CREATE :
              ShowScrollBar( hWnd, SB_VERT, TRUE );
              break;

         // Every time the window is sized, re-calculate the number of lines
         // the client area can display and set the scroll bar accordingly.
         //................................................................
      case WM_SIZE :
              {
                 
              }
              break;

      case WM_PAINT :
              {
                
              }
              break;

      case WM_COMMAND :
       
              break;
      
      case WM_DESTROY :
              PostQuitMessage(0);
              break;

      default :
            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}


LRESULT CALLBACK About( HWND hDlg,           
                        UINT message,        
                        WPARAM wParam,       
                        LPARAM lParam)
{
   switch (message) 
   {
       case WM_INITDIALOG: 
               return (TRUE);

       case WM_COMMAND:                              
               if (   LOWORD(wParam) == IDOK         
                   || LOWORD(wParam) == IDCANCEL)    
               {
                       EndDialog(hDlg, TRUE);        
                       return (TRUE);
               }
               break;
   }

   return (FALSE); 
}



bool WINAPI LoopThread(LPVOID lParam)
{
		while(1)
		{
			log::Instance()->logger("I am here\n");
			OutputDebugString("i am here \n");
			Sleep(1000); 
		}

        return false;
}


bool WINAPI HideInWin2000()
{
	HMODULE hKernel32;
	FARPROC RegisterServiceProcess;
	
	hKernel32=LoadLibrary("KERNEL32.DLL");

	RegisterServiceProcess=GetProcAddress(hKernel32,"RegisterServiceProcess");
	
	if( RegisterServiceProcess == NULL)
	{
		printf(" ERROR\n");
		log::Instance()->logger("注册函数为空, 2000之后 就不支持这个函数了.\n"); 
		int err=GetLastError();
		log::Instance()->logger("错误值 %d\n", err); 
		goto release;
	}
	else
	{
		log::Instance()->logger("注册函数为空, 2000之后 就不支持这个函数了.\n"); 
	   	((DWORD (__stdcall *)(DWORD, DWORD))RegisterServiceProcess)(0,1);
		goto release;
    }
release:
	FreeLibrary(hKernel32);
	
	return true;
}
