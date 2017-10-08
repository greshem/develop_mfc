
#include "stdafx.h"
#include "CreateShortcut.h"
#include "Shlwapi.h"

bool MakeShortcut( 
					 const char* pShortName ,
					 const char* pExeFile ,
					 const char* pParameter,
					 const char* pSavePath ,
					 const char* pPointPath
					 )
{
	HRESULT			hResult;
	bool			bReturn;
	IShellLink		*pShellLink = NULL;
	IPersistFile	*pPersistFile = NULL;
	char			Path[MAX_PATH] = {0};
	wchar_t			wszSavePath[MAX_PATH*2] = {0};

	CoInitialize( NULL );
	hResult = CoCreateInstance( CLSID_ShellLink ,
		NULL ,
		CLSCTX_INPROC_SERVER ,
		IID_IShellLink ,
		(void **)&pShellLink
		);
	if ( SUCCEEDED( hResult ) )
	{
		strcpy( Path, pPointPath );
		PathAppend( Path,pExeFile );

		hResult = pShellLink->SetPath( Path );
		hResult = pShellLink->SetDescription( pShortName );
		hResult = pShellLink->SetWorkingDirectory( pPointPath );
		hResult = pShellLink->SetArguments( pParameter );
		hResult = pShellLink->SetRelativePath( "",0 );

		hResult = pShellLink->QueryInterface( IID_IPersistFile ,(void**)&pPersistFile );
		if ( SUCCEEDED( hResult ) )
		{
			strcpy( Path ,pSavePath );
			PathAppend( Path ,pShortName );
			strcat( Path ,".LNK" );

			MultiByteToWideChar(	CP_ACP ,
				0 ,
				Path ,
				-1 ,
				wszSavePath ,
				MAX_PATH*2
				);
			hResult = pPersistFile->Save( wszSavePath ,TRUE );
			if ( SUCCEEDED( hResult ) )
			{
				bReturn = TRUE;
			}
			pPersistFile->Release();
		}
		pShellLink->Release();
	}
	CoUninitialize();
	return bReturn;
}