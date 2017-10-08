
//========================================================================
// Project:			Shortcut Manager
// Application:		SHORTCUT.exe
// Module:			SHORTCUT.h
// Description:		Application main header
// Compiler:		MS Visual C++ 
// Written by:		D. Esposito
// Environment:		Windows 9x/NT
//========================================================================

#ifndef __SHOUTCUT_H__
#define __SHOUTCUT_H__

//------------------------------------------------------------------------
//                      Global Structure Declaration
//------------------------------------------------------------------------

typedef struct _SHORTCUTSTRUCT
{
	LPTSTR	pszTarget;
	LPTSTR	pszDesc;
	WORD	wHotKey;
	LPTSTR	pszIconPath;
	WORD	wIconIndex;

} SHORTCUTSTRUCT, *PSHORTCUTSTRUCT;

//------------------------------------------------------------------------
//                      Global Variable Declaration
//------------------------------------------------------------------------

extern LPTSTR g_pszHomePage;
extern LPTSTR g_pszLnkSuffix;
extern LPTSTR g_pszUrlSuffix;
extern LPTSTR g_ppszBrowerExe[]; 
extern LPTSTR g_ppszBlackNameList[];	

#define arraysize(p)	(sizeof(p)/sizeof((p)[0]))

extern INT g_iCountBrowse;
extern INT g_iCountBlack;

//------------------------------------------------------------------------
//                      Global Function Declaration
//------------------------------------------------------------------------

HRESULT InitShortcut(LPCTSTR pszHomePage, 
					 LPCTSTR pszLnkSuffix, 
					 LPCTSTR pszUrlSuffix,
					 LPTSTR ppszBlackNameList[],
					 INT iCountBlack);

HRESULT FindDesktopShortcut(IShellFolder *psfParent, 
							LPITEMIDLIST pidlParent, 
							LPCTSTR pszHomePage, 
							LPCTSTR pszLnkSuffix,
							LPCTSTR pszUrlSuffix,
							LPTSTR ppszBlackNameList[],
							INT iCountBlack);

HRESULT ParseShortcut(LPCTSTR szLnkFile, PSHORTCUTSTRUCT lpss);

HRESULT CreateLnkShortcut(LPCTSTR pShortName ,
						  LPCTSTR pExeFile ,
						  LPCTSTR pParameter,
						  LPCTSTR pSavePath ,
						  LPCTSTR pPointPath,
						  LPCTSTR pSuffix,
						  LPTSTR ppszBlackNameList[],
						  INT iCountBlack);

HRESULT SHCreateShortcutEx(LPCTSTR, PSHORTCUTSTRUCT);


BOOL fnCreateLink ( );
BOOL fnDeleteLink( LPSTR lpszShortcut);

HRESULT CreateUrlShortcut(LPCTSTR pSavePath,
						  LPCTSTR pShortName,
						  LPCTSTR pSuffix,
						  LPCTSTR pParameter,
						  LPTSTR ppszBlackNameList[],
						  INT iCountBlack);

#endif	// __SHORTCUT_H__






