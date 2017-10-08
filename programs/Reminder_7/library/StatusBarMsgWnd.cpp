/*******************************************************************************
File:        StatusBarMsgWnd.cpp

Description: This file contains the module for creating a status bar message 
             window like MSN messenger

Created: Oct 13, 2001
Author:  Prateek Kaul
e-mail:  kaulpr@yahoo.com

Compiler with version number : Visual C++ 6.0


Copyright (c) 2001, Centre for Development of Advanced Computing (C-DAC), Pune.
All rights Reserved.

The copyright to the computer program(s) herein is the property of C-DAC, Pune.
The program(s) may be used and/or copied only with the written permission of 
C-DAC, Pune or in accordance with the terms and conditions stipulated
in the agreement/contract under which the program(s) have been supplied.
********************************************************************************/

#include "../stdafx.h"
#include "../remind.h"
#include "StatusBarMsgWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*----------------------------------------------------------------------------
 Message map
----------------------------------------------------------------------------*/

BEGIN_MESSAGE_MAP(CStatusBarMsgWnd, CFrameWnd)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_WM_SETCURSOR()
    ON_WM_DESTROY()
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
    ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()



/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::CStatusBarMsgWnd()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Constructor

 Parameters : 
    1. strMsg     -> Message to be shown in the window
    2. nWndWidth  -> Width of the message window
    3. nWndHeight -> Height if the message window
    4. nMsgTimeOut -> Seconds the window remains stationary
    5. nMsgWndCreationDelay -> Seconds in which the window gets shown
    4. pParent    -> Pointer to the parent window
    5  rectMsgRect -> Rectangle in the window where the message will be

 Return Value : none

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

CStatusBarMsgWnd::CStatusBarMsgWnd(
                      CString strMsg, 
                      unsigned int nWndWidth,
                      unsigned int nWndHeight,
                      unsigned int nMsgTimeOut,         
                      unsigned int nMsgWndCreationDelay, 
                      CRect rectMsgRect,
                      CWnd* pWndParent) : m_strMsg(strMsg), m_rectMsgRect(rectMsgRect)
{
    m_nWndWidth  = nWndWidth;
    m_nWndHeight = nWndHeight;

    m_pWndParent = pWndParent;

    m_nMsgTimeOut          = nMsgTimeOut;
    m_nMsgWndCreationDelay = nMsgWndCreationDelay;

    m_bMouseOverWnd = FALSE;

    m_hCursor = NULL;

	ColorR = 255;
	ColorG = 255;
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::~CStatusBarMsgWnd()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Destructor

 Parameters : none

 Return Value : none

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

CStatusBarMsgWnd::~CStatusBarMsgWnd()
{
}



/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::PopWndForLeftStatusBar()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Pops up a message window on the system tray when the status bar is
            is on the left side

 Parameters : none

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::PopWndForLeftStatusBar()
{
    CRect t_rect(0, 0, 0, 0);
    Create(NULL, NULL, WS_VISIBLE | WS_OVERLAPPEDWINDOW, t_rect, m_pWndParent);
    
    CRect rectDesktopWithoutTaskbar;   // The desktop area 

    // Get the desktop area
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesktopWithoutTaskbar, 0);
    
    // Calculate the actual width of the Window and its position
    m_nWndLeft   = rectDesktopWithoutTaskbar.left;
    m_nWndTop    = rectDesktopWithoutTaskbar.bottom - m_nWndHeight;
    m_nWndRight  = m_nWndLeft + m_nWndWidth;
    m_nWndBottom = m_nWndTop + m_nWndHeight;
    
    m_nWndSize = 0; // The height of window is zero before showing

    SetTimer(IDT_POP_WINDOW_TIMER, m_nMsgWndCreationDelay, NULL);

}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::PopWndForRightStatusBar()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Pops up a message window on the system tray when the status bar is
            is on the right side

 Parameters : none

 Return Value : none

 Exceptions : none

 Revisions : The previous version used ::Sleep API for animation and display
             which blocked the application, i.e the parent window.
             Now we use WM_TIMER messages for animation and display so
             the application remains responsive in between WM_TIMER
             messages
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::PopWndForRightStatusBar()
{
    PopWndForBottomStatusBar();
}




/*-----------------------------------------------------------------------------
Function : CStatusBarMsgWnd::PopWndForTopStatusBar()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Pops up a message window on the system tray when the status bar is
            is on the top. 

 Parameters : none

 Return Value : void

 Exceptions : none

 Revisions : The previous version used ::Sleep API for animation and display
             which blocked the application, i.e the parent window.
             Now we use WM_TIMER messages for animation and display so
             the application remains responsive in between WM_TIMER
             messages
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::PopWndForTopStatusBar()
{
    CRect t_rect(0, 0, 0, 0);
    Create(NULL, NULL, WS_VISIBLE | WS_OVERLAPPEDWINDOW, t_rect, m_pWndParent);
    
    CRect rectDesktopWithoutTaskbar;   // The desktop area 

    // Get the desktop area
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesktopWithoutTaskbar, 0);
    
    // Calculate the actual width of the Window and its position in screen co-ordinates
    m_nWndLeft   = rectDesktopWithoutTaskbar.right - m_nWndWidth;
    m_nWndTop    = rectDesktopWithoutTaskbar.top;
    m_nWndRight  = m_nWndLeft + m_nWndWidth;
    m_nWndBottom = m_nWndTop + m_nWndHeight;

    m_nWndSize = 0; // The height of window is zero before showing

    SetTimer(IDT_POP_WINDOW_TIMER, m_nMsgWndCreationDelay, NULL);
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::PopWndForBottomStatusBar()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Pops up a message window on the system tray when the status bar is
            is at the bottom

 Parameters : none

 Return Value : void

 Exceptions : none

 Revisions : The previous version used ::Sleep API for animation and display
             which blocked the application, i.e the parent window.
             Now we use WM_TIMER messages for animation and display so
             the application remains responsive in between WM_TIMER
             messages
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::PopWndForBottomStatusBar()
{
    CRect t_rect(0, 0, 0, 0);
    
    Create(NULL, NULL, WS_VISIBLE | WS_OVERLAPPEDWINDOW, t_rect, m_pWndParent); 
    
    CRect rectDesktopWithoutTaskbar;   // The desktop area 

    // Get the desktop area
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesktopWithoutTaskbar, 0);
    
    // Calculate the actual width of the Window and its position in screen co-ordinates
    m_nWndLeft   = rectDesktopWithoutTaskbar.right - m_nWndWidth;
    m_nWndTop    = rectDesktopWithoutTaskbar.bottom - m_nWndHeight;
    m_nWndRight  = m_nWndLeft + m_nWndWidth;
    m_nWndBottom = m_nWndTop + m_nWndHeight;
    
    m_nWndSize = 0; // The height of window is zero before showing

    SetTimer(IDT_POP_WINDOW_TIMER, m_nMsgWndCreationDelay, NULL);
}



/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::PopMsg()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Pops a message window above the system tray

 Parameters : none

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::PopMsg()
{
    if (CheckIfStatusBarBottom())  // Most frequent case is status bar at bottom
    {
        PopWndForBottomStatusBar();
    }
    else
    {
        if (CheckIfStatusBarTop())
        {
            PopWndForTopStatusBar();
        }
        else
        {
            if (CheckIfStatusBarLeft())
            {
                PopWndForLeftStatusBar();
            }
            else
            {
                m_nStatusBarPos = STP_RIGHT; // Force it, as no need for calling "CheckIfStatusBarRight()
                PopWndForRightStatusBar();
            }
        }
    }
}



/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::CheckIfStatusBarLeft()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Checks if the status bar is on the left side

 Parameters : none

 Return Value : BOOL (TRUE or FALSE)

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

BOOL CStatusBarMsgWnd::CheckIfStatusBarLeft()
{
    unsigned int nAvailableScreenTop;
    unsigned int nAvailableScreenLeft;
    
    CRect rectDesktopWithoutTaskbar;   // The desktop area without status bar
    
    // Get the desktop area minus the status
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesktopWithoutTaskbar, 0);
    nAvailableScreenLeft  = rectDesktopWithoutTaskbar.left;
    nAvailableScreenTop = rectDesktopWithoutTaskbar.top;

    if ((nAvailableScreenLeft > 0) && (nAvailableScreenTop == 0))
    {
        m_nStatusBarPos = STP_LEFT;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::CheckIfStatusBarRight()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Checks if the status bar is on the right side

 Parameters : none

 Return Value : BOOL (TRUE or FALSE)

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

BOOL CStatusBarMsgWnd::CheckIfStatusBarRight()
{
    unsigned int nAvailableScreenWidth;
    unsigned int nAvailableScreenHeight;
    unsigned int nActualScreenWidth;
    unsigned int nActualScreenHeight;

    // Calculate the actual screen height and width
    nActualScreenWidth  = ::GetSystemMetrics(SM_CXFULLSCREEN);
    nActualScreenHeight = ::GetSystemMetrics(SM_CYFULLSCREEN);

  
    CRect rectDesktopWithoutTaskbar;   // The desktop area without status bar
    
    // Get the desktop area minus the status
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesktopWithoutTaskbar, 0);
    nAvailableScreenWidth  = rectDesktopWithoutTaskbar.Width();
    nAvailableScreenHeight = rectDesktopWithoutTaskbar.Height();

    if ((nAvailableScreenWidth != nActualScreenWidth) &&
        (nAvailableScreenHeight == nActualScreenHeight))
    {
        m_nStatusBarPos = STP_RIGHT;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}



/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::CheckIfStatusBarTop()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Checks if the status bar is on the top

 Parameters : none

 Return Value : BOOL (TRUE or FALSE)

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

BOOL CStatusBarMsgWnd::CheckIfStatusBarTop()
{
    unsigned int nAvailableScreenTop;
    unsigned int nAvailableScreenLeft;
    
    CRect rectDesktopWithoutTaskbar;   // The desktop area without status bar
    
    // Get the desktop area minus the status
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesktopWithoutTaskbar, 0);
    nAvailableScreenLeft  = rectDesktopWithoutTaskbar.left;
    nAvailableScreenTop = rectDesktopWithoutTaskbar.top;

    if ((nAvailableScreenLeft == 0) && (nAvailableScreenTop > 0))
    {
        m_nStatusBarPos = STP_TOP;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::CheckIfStatusBarBottom()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Checks if the status bar is at the bottom

 Parameters : none

 Return Value : BOOL (TRUE or FALSE)

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

BOOL CStatusBarMsgWnd::CheckIfStatusBarBottom()
{
    unsigned int nAvailableScreenWidth;
    unsigned int nAvailableScreenBottom;
    unsigned int nActualScreenWidth;
    unsigned int nActualScreenBottom;

    // Calculate the actual screen height and width
    nActualScreenWidth  = ::GetSystemMetrics(SM_CXSCREEN);
    nActualScreenBottom = ::GetSystemMetrics(SM_CYSCREEN);

  
    CRect rectDesktopWithoutTaskbar;   // The desktop area without status bar
    
    // Get the desktop area minus the status
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesktopWithoutTaskbar, 0);
    nAvailableScreenWidth  = rectDesktopWithoutTaskbar.Width();
    nAvailableScreenBottom = rectDesktopWithoutTaskbar.bottom;

    if ((nAvailableScreenWidth == nActualScreenWidth) &&
        (nAvailableScreenBottom < nActualScreenBottom))
    {
        m_nStatusBarPos = STP_BOTTOM;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}



/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnSize()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when the window is resize message is received

 Parameters : Look in MFC documentation

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::OnSize(unsigned int nType, int cx, int cy)
{
    CFrameWnd::OnSize(nType, cx, cy);

    //SendMessage(WM_MOUSEMOVE, 0);
    CFont* pFont = NULL;
    CClientDC dc(this);

    if (m_bMouseOverWnd)
    {
        pFont = dc.SelectObject(&m_fontMessageUnderline);
    }
    else
    {
        pFont = dc.SelectObject(&m_fontMessageNoUnderline);
    }

	//dc.SetBkColor(RGB(186,213,242));
	dc.SetBkMode(TRANSPARENT);
    // Show with the message with the new font
    dc.DrawText(m_strMsg, &m_rectMsgRect, DT_WORDBREAK | DT_CENTER);
    dc.SelectObject(pFont);

    //dc.DrawText(m_strMsg, &m_rectMsgRect, DT_WORDBREAK | DT_CENTER);
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnCreate()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when the window is created but not shown.

 Parameters : Look in MFC documentation

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

int CStatusBarMsgWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(WS_CAPTION, 0, SWP_FRAMECHANGED); // removes title bar
    
    // Start creating two fonts, one underlined , other non underlined
    //
    // LOGFONT structure for font properties
    LOGFONT lf;
    ::ZeroMemory (&lf, sizeof (lf));
    lf.lfHeight = 100;
    lf.lfWeight = FW_MEDIUM;
    lf.lfUnderline = TRUE;
	//lf.lfItalic = TRUE;

    ::strcpy (lf.lfFaceName, _T("宋体"));

    // Prepare for an underlined font
    m_fontMessageUnderline.CreatePointFontIndirect(&lf);

    // Prepare  an non undelined font
    lf.lfUnderline = FALSE;
	//lf.lfItalic = FALSE;
    m_fontMessageNoUnderline.CreatePointFontIndirect(&lf);

    // Initialize the cursor.
    //m_hCursor = ::LoadCursor(NULL, IDC_ARROW); // Use IDC_HAND if it compiles
	//m_hCursor = ::LoadCursorFromFile("res\\hand.cur");
	m_hCursor = AfxGetApp()->LoadCursor(IDC_HAND);
    	
    return 0;
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnMouseMove(UNIT nFlags, CPoint point)

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when the mouse is moved.

 Parameters : Look in MFC documentation

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    // Register the tracking of Mouse entering and leaveing the window
    // for WM_MOUSEHOVER and WM_MOUSELEAVE
    TRACKMOUSEEVENT t_MouseEvent;
    t_MouseEvent.cbSize      = sizeof(TRACKMOUSEEVENT);
    t_MouseEvent.dwFlags     = TME_LEAVE | TME_HOVER;
    t_MouseEvent.hwndTrack   = m_hWnd;
    t_MouseEvent.dwHoverTime = 1;

    ::_TrackMouseEvent(&t_MouseEvent);
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnTimer(UNIT nFlags, CPoint point)

 Created: Oct 17, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when a TIMER message is generated

 Parameters : Look in MFC documentation

 Return Value : void

 Exceptions : none

 Revisions : The previous version used ::Sleep API for animation and display
             which blocked the application, i.e the parent window.
             Now we use WM_TIMER messages for animation and display so
             the application remains responsive in between WM_TIMER
             messages
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::OnTimer(UINT nIDEvent)
{
    switch (nIDEvent)
    {
        case IDT_POP_WINDOW_TIMER:    // When the window comes up
        {
            switch (m_nStatusBarPos)
            {
                case STP_BOTTOM:
                case STP_RIGHT:
                {
                    ++m_nWndSize;
                    if (m_nWndSize > m_nWndHeight)
                    {
                        KillTimer(IDT_POP_WINDOW_TIMER);
                        SetTimer(IDT_SHOW_WINDOW_TIMER, m_nMsgTimeOut, NULL);
                    }
                    else
                    {
                        // Keep sizing the window, show it
                        SetWindowPos(
                            &wndTopMost,
                            m_nWndLeft,
                            m_nWndBottom - m_nWndSize -5, 
                            m_nWndWidth - 10,
                            m_nWndSize,
                            SWP_SHOWWINDOW
                        );
                    }
                }
                break;

                case STP_TOP:
                {
                    ++m_nWndSize;
                    if (m_nWndSize > m_nWndHeight)
                    {
                        KillTimer(IDT_POP_WINDOW_TIMER);
                        SetTimer(IDT_SHOW_WINDOW_TIMER, m_nMsgTimeOut, NULL);
                    }
                    else
                    {
                        // Keep sizing the window, collapse it
                        SetWindowPos(
                            &wndTopMost,
                            m_nWndLeft,
                            m_nWndTop, 
                            m_nWndWidth - 10,
                            m_nWndSize,
                            SWP_SHOWWINDOW
                        );
                    }
                }
                break;

                case STP_LEFT:
                {
                    ++m_nWndSize;
                    if (m_nWndSize > m_nWndHeight)
                    {
                        KillTimer(IDT_POP_WINDOW_TIMER);
                        SetTimer(IDT_SHOW_WINDOW_TIMER, m_nMsgTimeOut, NULL);
                    }
                    else
                    {
                        // Keep sizing the window, collpase it
                        SetWindowPos(
                            &wndTopMost,
                            m_nWndLeft + 10,
                            m_nWndBottom - m_nWndSize - 5, 
                            m_nWndWidth,
                            m_nWndSize,
                            SWP_SHOWWINDOW
                        );
                    }
                }
                break;
            }
        }
        break;

        case IDT_SHOW_WINDOW_TIMER:
        {
            KillTimer(IDT_SHOW_WINDOW_TIMER);
            SetTimer(IDT_COLLAPSE_WINDOW_TIMER, m_nMsgWndCreationDelay, NULL);
        }
        break;

        case IDT_COLLAPSE_WINDOW_TIMER:
        {
            switch (m_nStatusBarPos)
            {
                case STP_BOTTOM:
                case STP_RIGHT:
                {
                    --m_nWndSize;
                    if (m_nWndSize <= 0) 
                    {
                        KillTimer(IDT_COLLAPSE_WINDOW_TIMER);
                        m_nWndSize = 0;

                        delete this;
                    }
                    else
                    {
                        // Keep showing the window, collapse it
                        SetWindowPos(
                            &wndTopMost,
                            m_nWndLeft,
                            m_nWndBottom - m_nWndSize - 5, 
                            m_nWndWidth - 10,
                            m_nWndSize,
                            SWP_SHOWWINDOW
                        );      
                    }
                }
                break;

                case STP_TOP:
                {
                    --m_nWndSize;
                    if (m_nWndSize <= 0)
                    {
                        KillTimer(IDT_COLLAPSE_WINDOW_TIMER);
                        m_nWndSize = 0;

                        delete this;
                    }
                    else
                    {
                        SetWindowPos(
                            &wndTopMost,
                            m_nWndLeft,
                            m_nWndTop, 
                            m_nWndWidth - 10,
                            m_nWndSize,
                            SWP_SHOWWINDOW
                        );
                    }
                }
                break;

                case STP_LEFT:
                {
                    --m_nWndSize;
                    if (m_nWndSize <= 0)
                    {
                        KillTimer(IDT_COLLAPSE_WINDOW_TIMER);
                        m_nWndSize = 0;

                        delete this;
                    }
                    else
                    {
                        SetWindowPos(
                            &wndTopMost,
                            m_nWndLeft + 10,
                            m_nWndBottom - m_nWndSize - 5, 
                            m_nWndWidth,
                            m_nWndSize,
                            SWP_SHOWWINDOW
                        );
                    }
                }
                break;
            }
        }
        break;
    }

}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnMouseHover(WPARAM, LPARAM)

 Created: Oct 17, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when mouse is above a window

 Parameters : Look in MFC documentation

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

LRESULT CStatusBarMsgWnd::OnMouseHover(WPARAM w, LPARAM l)
{
    if (m_bMouseOverWnd == FALSE) // Mouse was not on window
    {
		//Invalidate();

        CClientDC dc(this);
        CFont* pFont = dc.SelectObject(&m_fontMessageUnderline);
		dc.SetTextColor(RGB(0,0,255));
		//dc.SetBkColor(RGB(186,213,242));
		dc.SetBkMode(TRANSPARENT);
        // Show with the message with the new font
        dc.DrawText(m_strMsg, &m_rectMsgRect, DT_WORDBREAK | DT_CENTER);
        
        dc.SelectObject(pFont); // restore the DC to its original state

        m_bMouseOverWnd = TRUE; // Mouse is now over window
    }
    return 0;
}



/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnMouseLeaves(WPARAM, LPARAM)

 Created: Oct 17, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when mouse is leaves a window

 Parameters : Look in MFC documentation

 Return Value : LRESULT

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

LRESULT CStatusBarMsgWnd::OnMouseLeave(WPARAM w, LPARAM l)
{
    if (m_bMouseOverWnd) // Mouse was over window, now it is leaving
    {
		Invalidate();

        CClientDC dc(this);
        CFont* pFont = dc.SelectObject(&m_fontMessageNoUnderline);
		dc.SetBkMode(TRANSPARENT);
        // Show with the message with the new font
        dc.DrawText(m_strMsg, &m_rectMsgRect, DT_WORDBREAK | DT_CENTER);

        dc.SelectObject(pFont); // Restore DC back to its original state

        m_bMouseOverWnd = FALSE; // Mouse is not over window
    }
    return 0;
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnSetCursor(WPARAM, LPARAM)

 Created: Oct 17, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when mouse is moved on a window

 Parameters : Look in MFC documentation

 Return Value : BOOL

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

BOOL CStatusBarMsgWnd::OnSetCursor(CWnd* pWnd , UINT nHitTest , UINT message)
{
    if (nHitTest == HTCLIENT)
    {
        ::SetCursor(m_hCursor);  // Set cursor to HAND type when mouse is over window

        return TRUE;
    }
    
    return CFrameWnd::OnSetCursor (pWnd, nHitTest, message);
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnDestroy()

 Created: Oct 17, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when window is about to be destroyed and it becomes 
            already invisible

 Parameters : Look in MFC documentation

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::OnDestroy(void)
{
    ::CloseHandle(m_hCursor); // Free the cursor as it is a shared resource..

    CFrameWnd::OnDestroy();
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnPaint()

 Created: Oct 17, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when a window recives a WM_PAINT message

 Parameters : Look in MFC documentation

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::OnPaint()
{
    CFont* pFont = NULL;
    CPaintDC dc(this);

    if (m_bMouseOverWnd)
    {
        pFont = dc.SelectObject(&m_fontMessageUnderline);
    }
    else
    {
        pFont = dc.SelectObject(&m_fontMessageNoUnderline);
    }
	//dc.SetBkColor(RGB(186,213,242));
	dc.SetBkMode(TRANSPARENT);

    // Show with the message with the new font
    dc.DrawText(m_strMsg, &m_rectMsgRect, DT_WORDBREAK | DT_CENTER);
    dc.SelectObject(pFont); // restore the DC to its original state
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::OnLButtonDown(UINT, CPoint)

 Created: Oct 17, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by MFC when a window recives a WM_LBUTTONDOWN message

 Parameters : Look in MFC documentation

 Return Value : void

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

void CStatusBarMsgWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	//打开默认邮件接收器
	char regvalue[128];
	memset(regvalue, 0, sizeof(regvalue));
	GetRegValue("mailto\\shell\\open\\command\0", "", regvalue, HKEY_CLASSES_ROOT);

	CString sresult = regvalue;
	int p1,p2;
	p1 = sresult.Find('"',0);
	p2 = sresult.Find('"',p1+1);
	sresult = sresult.Mid(p1+1,p2-p1-1);
	ShellExecute(m_hWnd,NULL,(LPCTSTR)sresult,NULL,NULL,SW_SHOWNORMAL);
}




/*-----------------------------------------------------------------------------
 Function : CStatusBarMsgWnd::CreateObject()

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Creates an CStatusBarMsgWnd, constructor is not public because we
            want to force heap creation for better response for the
            parent window. So we use SetTimer in PopWnd() and return. 
            So no blocking with Sleep() API.

 Parameters : 
    1. strMsg     -> Message to be shown in the window
    2. nWndWidth  -> Width of the message window
    3. nWndHeight -> Height if the message window
    4. nMsgTimeOut -> Seconds the window remains stationary
    5. nMsgWndCreationDelay -> Seconds in which the window gets shown
    4. pParent    -> Pointer to the parent window
    5  rectMsgRect -> Rectangle in the window where the message will be

 Return Value : none

 Exceptions : none

 Revisions : none
----------------------------------------------------------------------------*/

CStatusBarMsgWnd* CStatusBarMsgWnd::CreateObject(CString strMsg,
                                       unsigned int nWndWidth,
                                       unsigned int nWndHeight, 
                                       unsigned int nMsgTimeOut,         
                                       unsigned int nMsgWndCreationDelay, 
                                       CRect rectMsgRect,
                                       CWnd* pWndParent)
{
    CStatusBarMsgWnd* t_StatusBarMsgWnd = new CStatusBarMsgWnd(
                                                  strMsg,
                                                  nWndWidth,
                                                  nWndHeight, 
                                                  nMsgTimeOut,         
                                                  nMsgWndCreationDelay, 
                                                  rectMsgRect,
                                                  pWndParent
                                              );

    return (t_StatusBarMsgWnd);
}

BOOL CStatusBarMsgWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	// Create a pruple brush.
	/*CBrush brush (RGB (186,213,242) );
	// Select the brush into the device context .
	CBrush* pOldBrush = pDC->SelectObject (&brush);
	// Get the area that needs to be erased .
	CRect rcClip;
	pDC->GetClipBox (&rcClip);
	//Paint the area.
	pDC->PatBlt (rcClip.left , rcClip.top , rcClip.Width ( ) , rcClip.Height( ) , PATCOPY );
	//Unselect brush out of device context .;
	pDC->SelectObject (pOldBrush );
	// Return nonzero to half fruther processing .
	return TRUE;*/
	
	//用渐变色填充窗口
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	int nWidth = m_rcClient.Width(); 
	int nHeight = m_rcClient.Height();
	CRect rectangle;
	for(int i = 0;i < nWidth;i++ )
	{
		rectangle.SetRect(i, 0, i+1, nHeight);
		pDC->FillSolidRect(&rectangle, RGB(ColorR, ColorG, 255-MulDiv(i, 255, nWidth)));
	}
	return TRUE;
	
	//return CFrameWnd::OnEraseBkgnd(pDC);
}
