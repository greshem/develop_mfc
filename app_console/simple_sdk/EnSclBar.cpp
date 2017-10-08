
#include <windows.h>  
#include "EnSclBar.h" 


HINSTANCE hInst;   // current instance

LPCTSTR lpszAppName  = "MyApp";
LPCTSTR lpszTitle    = "My Application"; 


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
      return( FALSE );

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
      return( FALSE );

   ShowWindow( hWnd, nCmdShow ); 
   UpdateWindow( hWnd );         

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
                 RECT rect;
                 GetClientRect( hWnd, &rect );

                 nDspLines = rect.bottom / 20;

                 if ( nDspLines < nNumItems ) 
                 {
                    SCROLLINFO scInfo;

                    EnableScrollBar( hWnd, SB_VERT, ESB_ENABLE_BOTH );

                    scInfo.cbSize = sizeof( scInfo );
                    scInfo.fMask  = SIF_POS | SIF_RANGE;
                    scInfo.nPos   = nCurPos;
                    scInfo.nMin   = 0;
                    scInfo.nMax   = nNumItems-nDspLines;

                    SetScrollInfo( hWnd, SB_VERT, &scInfo, FALSE );
                 }
                 else
                    EnableScrollBar( hWnd, SB_VERT, ESB_DISABLE_BOTH );
              }
              break;

      case WM_PAINT :
              {
                 PAINTSTRUCT ps;
                 int         i,j;
                 int         nNumPaint;

                 nNumPaint = min( nCurPos+nDspLines, nNumItems );

                 BeginPaint( hWnd, &ps );

                 for ( j=0,i=nCurPos; i<nNumPaint; i++,j++ )
                 {
                    itoa( i, szBuf, 10 );
                    TextOut( ps.hdc, 10, j*20, "Line of Text:", 13 );
                    TextOut( ps.hdc, 90, j*20, szBuf, strlen( szBuf ) );
                 }
                  
                 EndPaint( hWnd, &ps );
              }
              break;

      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
                 case IDM_TEST :
                        if ( nDspLines == nNumItems ) 
                           EnableScrollBar( hWnd, SB_VERT, ESB_ENABLE_BOTH );

                        nNumItems++;
                        if ( nDspLines < nNumItems )
                        {
                           SCROLLINFO scInfo;

                           scInfo.cbSize = sizeof( scInfo );
                           scInfo.fMask  = SIF_RANGE;
                           scInfo.nMin   = 0;
                           scInfo.nMax   = nNumItems-nDspLines;

                           SetScrollInfo( hWnd, SB_VERT, &scInfo, TRUE );
                        }

                        InvalidateRect( hWnd, NULL, FALSE );
                        break;

                 case IDM_ABOUT :
                        DialogBox( hInst, "AboutBox", hWnd, (DLGPROC)About );
                        break;

                 case IDM_EXIT :
                        DestroyWindow( hWnd );
                        break;
              }
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
