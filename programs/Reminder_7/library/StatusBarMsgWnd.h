/*******************************************************************************
File:        StatusBarMsgWnd.h

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


#ifndef _STATUSBARMSGWND_H
#define _STATUSBARMSGWND_H
#include "afxwin.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*---------------------------------------------------------------------------
 class CStatusBarMsgWnd

 Created: Oct 13, 2001
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : For creating a status bar message window like MSN messenger

 Revisions :none.
----------------------------------------------------------------------------*/

const int IDT_POP_WINDOW_TIMER       = 100;
const int IDT_COLLAPSE_WINDOW_TIMER  = 101;
const int IDT_SHOW_WINDOW_TIMER      = 102;

const int STP_BOTTOM = 200;
const int STP_TOP    = 201;
const int STP_RIGHT  = 202;
const int STP_LEFT   = 203;


class CStatusBarMsgWnd : public CFrameWnd
{
    DECLARE_MESSAGE_MAP()
public:

    //	CStatusBarMsgWnd(); // No default constructor, sorry!!, use CreateObject then only
                            // use this class

    // Create the message box using this function, as we want to force heap creation
    // Don't use delete to destroy the window, OnTimer() does it automatically.
    static CStatusBarMsgWnd* CreateObject(CString strMsg,
                                    unsigned int nWndWidth,
                                    unsigned int nWndHeight, 
                                    unsigned int nMsgTimeOut,         
                                    unsigned int nMsgWndCreationDelay, 
                                    CRect rectMsgRect,
                                    CWnd* pWndParent = NULL);

    void PopMsg();  // Interface for actually poping up the message window
    
protected:
	void OnSize(unsigned int nType, int cx, int cy);
    int OnCreate(LPCREATESTRUCT lpCreateStruct);
    void OnMouseMove(UINT nFlags, CPoint point);
    void OnTimer(UINT nIDEvent);
    LRESULT OnMouseHover(WPARAM w, LPARAM l);
    LRESULT OnMouseLeave(WPARAM w, LPARAM l);
    BOOL OnSetCursor(CWnd* pWnd , UINT nHitTest , UINT message);
    void OnDestroy();
    void OnPaint(void);
    void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL OnEraseBkgnd(CDC* pDC);
 
private:

    /* Constructor and destructor private, we want to force heap creation,
       so use CreateObject */

    CStatusBarMsgWnd(
        CString strMsg,
        unsigned int nWndWidth,
        unsigned int nWndHeight, 
        unsigned int MsgTimeOut,         
        unsigned int MsgWndCreationDelay, 
        CRect rectMsgRect,
        CWnd* pWndParent = NULL
     );
    
    ~CStatusBarMsgWnd();  // self destruction in OnTimer, no one should call this function



	BOOL CheckIfStatusBarBottom(); // Is Status bar at bottom ?
	BOOL CheckIfStatusBarTop();    // Is Status bar on top ?
	BOOL CheckIfStatusBarRight();  // Is Status bar at right side?
	BOOL CheckIfStatusBarLeft();   // Is Status bar at left side?
	
	void PopWndForBottomStatusBar(); // Pop window when status bar is at bottom
	void PopWndForTopStatusBar();    // Pop window when status bar on top
	void PopWndForRightStatusBar();  // Pop window when status bar is at right side
	void PopWndForLeftStatusBar();   // Pop window when status bar is at left side
	
    unsigned int m_nWndWidth;            // Message window width
	unsigned int m_nWndHeight;           // Mesaage window height
    unsigned int m_nMsgTimeOut;          // Seconds the window remains stationary
    unsigned int m_nMsgWndCreationDelay; // Seconds in which the window gets shown

    unsigned int m_nWndLeft;   // Message window left corner screen coordinates   
    unsigned int m_nWndTop;    // Message window top corner screen coordinates
    unsigned int m_nWndRight;  // Message window right corner screen coordinates
    unsigned int m_nWndBottom; // Message window bottom corner screen coordinates
    unsigned int m_nWndSize;    // Temp variable for storing window size for animation

    unsigned int m_nStatusBarPos; // const about where the status bar.
                                  	
    CString m_strMsg;    // Message to be shown

    CWnd* m_pWndParent;  // Parent of this message window

    CRect m_rectMsgRect; // Rect in which the message will be formatted

    CFont m_fontMessageUnderline;  // Font of the message with underline
    CFont m_fontMessageNoUnderline; // Font of the message without underline
    
    BOOL m_bMouseOverWnd; // Is Mouse over window ?

    HCURSOR m_hCursor; // Cursor when mouse is on window, Hand cursor

	int ColorR;
	int ColorG;
};

#endif // _STATUSBARMSGWND_H
