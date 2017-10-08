
//========================================================================
//
// File:	Shortcut.cpp
//
// Brief:	Create desktop shortcut for link or url suffix.
//
// Author:	David
//
// Date:	2010-08-23
//
//========================================================================

#include "stdafx.h"
#include "Shortcut.h"

#include "ShellPidl.h"
#include   <intshcut.h>		// IUniformResourceLocator

LPTSTR g_pszHomePage = __T("http://www.baidu.com/index.php?tn=richtech1_2_pg");

LPTSTR g_ppszBrowerExe[] =	
{
	{_T("iexplore.exe")},
	{_T("sogouexplorer.exe")},
	{_T("firefox.exe")},
	{_T("opera.exe")},
	{_T("maxthon.exe")},
	{_T("theworld.exe")},
	{_T("chrome.exe")},
	{_T("qqbrowser.exe")},
	{_T("360se.exe")},
	{_T("ttraveler.exe")},
};

LPTSTR g_ppszBlackNameList[] =	
{
	{_T("baidu")},
	{_T("google")},
	{_T("yahoo")},
	{_T("gougou")},
};

INT g_iCountBrowse = arraysize(g_ppszBrowerExe);
INT g_iCountBlack = arraysize(g_ppszBlackNameList);


LPTSTR g_pszLnkSuffix = _T(".lnk");
LPTSTR g_pszUrlSuffix = _T(".url");

HRESULT InitShortcut(LPCTSTR pszHomePage, 
					 LPCTSTR pszLnkSuffix, 
					 LPCTSTR pszUrlSuffix,
					 LPTSTR ppszBlackNameList[],
					 INT iCountBlack )
{
	HRESULT hResult = S_OK;
	IShellFolder *lpsfDesk = NULL;
	ITEMIDLIST   *lpidlDesk = NULL; 

	::SHGetDesktopFolder(&lpsfDesk);									// get desktop IShellFolder interface, m_psfDesk point this structure
	::SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &lpidlDesk);		// get desktop directory list

	hResult = FindDesktopShortcut(lpsfDesk, lpidlDesk, pszHomePage, pszLnkSuffix, pszUrlSuffix, ppszBlackNameList, iCountBlack);

	if ( FAILED(hResult) )
	{
		OutputDebugString("InitShortcut Fail!\n");
	} 

	return hResult;
}

HRESULT FindDesktopShortcut(IShellFolder *psfParent, 
							LPITEMIDLIST pidlParent, 
							LPCTSTR pszHomePage, 
							LPCTSTR pszLnkSuffix,
							LPCTSTR pszUrlSuffix,
							LPTSTR ppszBlackNameList[],
							INT iCountBlack )
{
	CShellPidl		shellClass;
	IEnumIDList		*peidl;
	LPITEMIDLIST	pidl;
	LPITEMIDLIST	pidlAbs;
	IShellFolder	*psf = NULL;
	HRESULT			hResult = S_OK;

	//-------------------------------------------------------------
	//				Enumerate Desktop File
	//-------------------------------------------------------------
	hResult = psfParent->EnumObjects(NULL, SHCONTF_NONFOLDERS, &peidl);
	if (NOERROR != hResult)
		return hResult;

	while ( NOERROR == hResult )
	{
		TCHAR	szPath[_MAX_PATH] = {0};				// memset(szPath, 0, sizeof(szPath));
		TCHAR	szFullPath[_MAX_PATH] = {0};

		TCHAR	szFullPathLower[_MAX_PATH] = {0};		// lower char
		//errno_t err = 0;								// =_strdup(szPath)
		int err = 0;
		LPTSTR  pszIncLnk = NULL;
		LPTSTR	pszIncUrl = NULL;

		hResult = peidl->Next(1, &pidl, NULL);
		if ( hResult == S_FALSE || pidl == NULL )
			break;

		pidlAbs = shellClass.ConcatPidl(pidlParent,pidl);
		psfParent->BindToObject(pidl, NULL, IID_IShellFolder, (void**)&psf);

		::SHGetPathFromIDList(pidlAbs, szPath);	

		if ( !lstrlen(szPath) )
		{
			continue;
		}

		lstrcpy(szFullPath, szPath);					// raw link file path
		//err = _strlwr_s(szPath, _MAX_PATH);				// =_strdup(szPath).
		_strlwr(szPath);				// =_strdup(szPath)
		lstrcpy(szFullPathLower, szPath);

		pszIncLnk = strstr( szFullPathLower, pszLnkSuffix );
		pszIncUrl = strstr( szFullPathLower, pszUrlSuffix );

		//-----------------------------------------------
		//			Create .lnk Desktop Shortcut
		//-----------------------------------------------
		if ( pszIncLnk != NULL)				
		{
			LPTSTR			pszBrowserName = NULL;
			LPTSTR			pszIncExe = NULL;
			SHORTCUTSTRUCT	ss;
			//errno_t			err = 0;
			int				err = 0;
			TCHAR szExlorerPath[_MAX_PATH] = {0};
			TCHAR szExlorerPathLower[_MAX_PATH] = {0};

			hResult = ParseShortcut(szFullPath, &ss);
			if ( FAILED(hResult) )
				return hResult;

			lstrcpy(szExlorerPath, ss.pszTarget);
			lstrcpy(szExlorerPathLower, ss.pszTarget);
			//err = _strlwr_s(szExlorerPathLower, _MAX_PATH);	// lower path
			_strlwr(szExlorerPathLower);
			int iCount = arraysize(g_ppszBrowerExe);		// 10 ‰Ø¿¿∆˜¿‡–Õ
			for ( int i=0; i<iCount; i++ )
			{
				pszBrowserName = g_ppszBrowerExe[i];

				pszIncExe = strstr(szExlorerPathLower, pszBrowserName);
				if ( pszIncExe != NULL )
				{
					break;
				}
			}

			if ( pszIncExe != NULL )
			{
				//errno_t err = -1;
				int err = -1;
				HRESULT	hResult = 0;

				TCHAR drive[_MAX_DRIVE];
				TCHAR dir[_MAX_DIR];
				TCHAR fname[_MAX_FNAME];
				TCHAR ext[_MAX_EXT];

				TCHAR szDesktopPath[_MAX_PATH] = {0};
				TCHAR szShortcutName[_MAX_PATH] = {0};
				TCHAR szExeFile[_MAX_PATH] = {0};
				TCHAR szWorkDir[_MAX_PATH] = {0};

				//err = _splitpath_s(szFullPath, drive, dir, fname, ext);
				//err = _makepath_s(szDesktopPath, _MAX_PATH, drive, dir, NULL, NULL);
				//err = _makepath_s(szShortcutName, _MAX_PATH, NULL, NULL, fname, NULL);

				//err = _splitpath_s(szExlorerPath, drive, dir, fname, ext);
				//err = _makepath_s(szExeFile, _MAX_PATH, NULL, NULL, fname, ext);
				//err = _makepath_s(szWorkDir, _MAX_PATH, drive, dir, NULL, NULL);
				_splitpath(szFullPath, drive, dir, fname, ext);
				_makepath(szDesktopPath, drive, dir, NULL, NULL);
				_makepath(szShortcutName, NULL, NULL, fname, NULL);

				_splitpath(szExlorerPath, drive, dir, fname, ext);
				_makepath(szExeFile, NULL, NULL, fname, ext);
				_makepath(szWorkDir,drive, dir, NULL, NULL);
				hResult = CreateLnkShortcut(szShortcutName, szExeFile, pszHomePage, szDesktopPath, szWorkDir, pszLnkSuffix, ppszBlackNameList, iCountBlack);

				if ( FAILED(hResult) )
				{
					OutputDebugString("Create shortcut fail.\n");	
				}
			}
		} 

		//-----------------------------------------------
		//			Create .url Desktop Shortcut
		//-----------------------------------------------
		if ( pszIncUrl != NULL )
		{	
			HRESULT	hResult = 0;

			TCHAR drive[_MAX_DRIVE];
			TCHAR dir[_MAX_DIR];
			TCHAR fname[_MAX_FNAME];
			TCHAR ext[_MAX_EXT];

			TCHAR szDesktopPath[_MAX_PATH] = {0};
			TCHAR szShortcutName[_MAX_PATH] = {0};
			//errno_t	err = 0;
			int err = 0;

			_splitpath(szFullPath, drive, dir, fname, ext);
			_makepath(szDesktopPath,drive, dir, NULL, NULL);
			_makepath(szShortcutName,NULL, NULL, fname, NULL);

			hResult = CreateUrlShortcut(szDesktopPath, szShortcutName, 
				pszUrlSuffix, pszHomePage, ppszBlackNameList, iCountBlack);

			if ( FAILED(hResult) )
			{
				OutputDebugString("Create shortcut fail.\n");	
			}
		}
	}
	peidl->Release();

	return hResult;
}

HRESULT ParseShortcut(LPCTSTR szLnkFile, PSHORTCUTSTRUCT lpss)
{
	HRESULT			hResult = S_OK;
	WCHAR			wszLnkFile[_MAX_PATH] = {0};
	IShellLink		*pShellLink = NULL;
	IPersistFile	*pPF = NULL;
	HRESULT			hr = S_OK;
	CHAR			szGetParam[MAX_PATH] = {0};

	CoInitialize( NULL );

	// Create the appropriate COM server
	hr = CoCreateInstance(CLSID_ShellLink, NULL,
		CLSCTX_INPROC_SERVER, IID_IShellLink,
		reinterpret_cast<LPVOID*>(&pShellLink));
	if(FAILED(hr))
		return hr;

	// Get the IPersistFile interface to load the LNK file
	hr = pShellLink->QueryInterface(IID_IPersistFile, reinterpret_cast<LPVOID*>(&pPF));
	if(FAILED(hr))
	{
		pShellLink->Release();
		return hr;
	}

	// Load the shortcut (Unicode name)
	MultiByteToWideChar(CP_ACP, 0, szLnkFile, -1, wszLnkFile, _MAX_PATH);
	hr = pPF->Load(wszLnkFile, STGM_READ);

	if(FAILED(hr))
	{
		pPF->Release();
		pShellLink->Release();
		return hr;
	}

	// Resolve the link
	hr = pShellLink->Resolve(NULL, SLR_NO_UI);	// SLR_ANY_MATCH
	if(FAILED(hr))
	{
		pPF->Release();
		pShellLink->Release();
		return hr;
	}

	// Extract the information to fill lpss
	if( lpss != NULL )
	{
		TCHAR szPath[_MAX_PATH] = {0};
		TCHAR szDesc[_MAX_PATH] = {0};
		TCHAR szIcon[_MAX_PATH] = {0};
		WORD w = 0;
		// WORD wIcon = 0;
		int wIcon = 0;
		WIN32_FIND_DATA wfd;

		pShellLink->GetPath(szPath, _MAX_PATH, &wfd, SLGP_RAWPATH );	// SLGP_SHORTPATH
		pShellLink->GetDescription(szDesc, _MAX_PATH);
		pShellLink->GetHotkey(&w);
		pShellLink->GetIconLocation(szIcon, _MAX_PATH, (&wIcon));	// reinterpret_cast<int*>(&wIcon)

		hResult = pShellLink->GetArguments( szGetParam, MAX_PATH );

		lpss->pszTarget = szPath;
		lpss->pszDesc = szDesc;
		lpss->pszIconPath = szIcon;
		lpss->wHotKey = w;
		lpss->wIconIndex = wIcon;
	}

	pPF->Release();
	pShellLink->Release();

	CoUninitialize();
	return hr;
}

HRESULT CreateLnkShortcut(LPCTSTR pShortName,
						  LPCTSTR pExeFile,
						  LPCTSTR pParameter,
						  LPCTSTR pSavePath,
						  LPCTSTR pPointPath,
						  LPCTSTR pSuffix,					// .lnk
						  LPTSTR ppszBlackNameList[],
						  INT iCountBlack )			
{
	HRESULT			hResult = S_OK;
	IShellLink		*pShellLink = NULL;
	IPersistFile	*pPersistFile = NULL;
	TCHAR			Path[_MAX_PATH] = {0};
	WCHAR			wszSavePath[_MAX_PATH*2] = {0};
	CHAR			szGetParam[MAX_PATH] = {0};

	CoInitialize( NULL );
	hResult = CoCreateInstance( 
		CLSID_ShellLink,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IShellLink,
		(void **)&pShellLink );

	if ( SUCCEEDED( hResult ) )
	{
		hResult = pShellLink->QueryInterface( IID_IPersistFile ,(void**)&pPersistFile );
		if ( SUCCEEDED( hResult ) )
		{
			lstrcpy( Path, pSavePath );
			if ( Path[lstrlen(Path)-1] != _T('\\') )
			{
				lstrcat(Path, _T("\\"));
			}
			lstrcat(Path, pShortName);
			Path[lstrlen(Path)] = _T('\0'); 
			lstrcat( Path, pSuffix );

			MultiByteToWideChar( CP_ACP, 0, (LPCTSTR)Path, -1, wszSavePath, _MAX_PATH*2 );
			hResult = pPersistFile->Load(wszSavePath, STGM_READ);


			hResult = pShellLink->GetArguments( szGetParam, MAX_PATH );

			if ( lstrlen(szGetParam) )
			{
				//errno_t err = _strlwr_s( szGetParam, MAX_PATH );
				_strlwr( szGetParam );
				LPTSTR	pszBlackName = NULL;
				LPTSTR	pszIncBlack = NULL;		
				//int		iCount = arraysize(g_ppszBlackNameList);

				for ( int i=0; i<iCountBlack; i++ )		// include black name list
				{
					pszBlackName = ppszBlackNameList[i];
					pszIncBlack = strstr(szGetParam, pszBlackName);
					if ( pszIncBlack != NULL )
					{
						lstrcpy( Path, pPointPath );
						if ( Path[strlen(Path)-1] != _T('\\') )
						{
							lstrcat(Path, _T("\\"));
						}
						lstrcat(Path, pExeFile);

						hResult = pShellLink->SetPath( Path );
						hResult = pShellLink->SetDescription( pShortName );
						hResult = pShellLink->SetWorkingDirectory( pPointPath );
						hResult = pShellLink->SetArguments( pParameter );
						hResult = pShellLink->SetRelativePath( "", 0 );

						hResult = pPersistFile->Save( wszSavePath, TRUE );
						break;
					}
				}
			}
			else	// parameter blank
			{
				lstrcpy( Path, pPointPath );
				if ( Path[strlen(Path)-1] != _T('\\') )
				{
					lstrcat(Path, _T("\\"));
				}
				lstrcat(Path, pExeFile);

				hResult = pShellLink->SetPath( Path );
				hResult = pShellLink->SetDescription( pShortName );
				hResult = pShellLink->SetWorkingDirectory( pPointPath );
				hResult = pShellLink->SetArguments( pParameter );
				hResult = pShellLink->SetRelativePath( "", 0 );

				hResult = pPersistFile->Save( wszSavePath, TRUE );	
			}

			pPersistFile->Release();
		}
		pShellLink->Release();
	}
	CoUninitialize();

	return hResult;
}

//------------------------------------------------------------------------
//
// Brief:	Create internet shortcut
//
// Other:	Need include intshcut.h header file
//
//------------------------------------------------------------------------

HRESULT 
CreateUrlShortcut(
				  LPCTSTR pDesktopPath,
				  LPCTSTR pShortName,
				  LPCTSTR pSuffix,			// .url
				  LPCTSTR pParameter,
				  LPTSTR ppszBlackNameList[],
				  INT iCountBlack
				  )
{
	HRESULT hResult = S_OK; 
	IUniformResourceLocator *pURL = NULL; 
	IPersistFile *ppf = NULL;
	CHAR szGetParam[MAX_PATH] = {0}; 

	TCHAR szFullPath[MAX_PATH] = {0};
	hResult = ::CoInitialize(NULL);

	// Create an IUniformresourceLocator object
	hResult = CoCreateInstance(CLSID_InternetShortcut, NULL, 
		CLSCTX_INPROC_SERVER, IID_IUniformResourceLocator, (void**)&pURL); 

	if ( SUCCEEDED(hResult) )
	{
		hResult = pURL->QueryInterface(IID_IPersistFile, (void**)&ppf);	// get IPersistFile interface
		if ( SUCCEEDED(hResult) )
		{
			WCHAR wszFullPath[MAX_PATH] = {0};
			LPTSTR pszGetURL = NULL;

			lstrcpy(szFullPath, pDesktopPath);
			if ( szFullPath[lstrlen(szFullPath)-1] != _T('\\') )
			{
				lstrcat(szFullPath, _T("\\"));
			}
			lstrcat(szFullPath, pShortName);
			szFullPath[lstrlen(szFullPath)] = _T('\0'); 
			lstrcat(szFullPath, pSuffix);

			MultiByteToWideChar(CP_ACP, 0, (LPCSTR)szFullPath, -1, wszFullPath, MAX_PATH*2);

			hResult = ppf->Load(wszFullPath, STGM_READ);
			hResult = pURL->GetURL(&pszGetURL);
			lstrcpy( szGetParam, pszGetURL );

			if ( lstrlen(szGetParam) )
			{
				//errno_t err = _strlwr_s( szGetParam, MAX_PATH );
				_strlwr( szGetParam );
				LPTSTR	pszBlackName = NULL;
				LPTSTR	pszIncBlack = NULL;		
				//int		iCount = arraysize(g_ppszBlackNameList);

				for ( int i=0; i<iCountBlack; i++ )		// include black name list
				{
					pszBlackName = ppszBlackNameList[i];
					pszIncBlack = strstr(szGetParam, pszBlackName);
					if ( pszIncBlack != NULL )
					{
						hResult = pURL->SetURL(pParameter, 0);

						// Save the shortcut via the IPersistFile::Save member function.
						hResult = ppf->Save(wszFullPath, TRUE);

						break;
					}
				}
			}
			else	// parameter blank
			{
				hResult = pURL->SetURL(pParameter, 0);

				// Save the shortcut via the IPersistFile::Save member function.
				hResult = ppf->Save(wszFullPath, TRUE);

			}

			// Release the pointer to IPersistFile.
			ppf->Release();
		}

		// Release the pointer to IUniformResourceLocator.
		pURL->Release();
	}

	::CoUninitialize();

	return hResult;
}

