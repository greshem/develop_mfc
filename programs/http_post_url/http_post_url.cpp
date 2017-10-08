//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <fstream>
#include <string> 
#include <iostream>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <Wininet.h>

using namespace std;

//打开URL，读取网页文件
DWORD   HttpPost( LPCTSTR lpURL )
{
        HINTERNET       hInternet       = NULL ;
        HINTERNET       hHttp           = NULL;
        DWORD           dwError = 0;
		DWORD 			dwBytesRead = 0;
		char buffer[10*1024] ;

        do
        {
                hInternet = InternetOpen( "RS" , INTERNET_OPEN_TYPE_DIRECT ,NULL ,NULL ,0);
                if ( hInternet == NULL )
                {
                        dwError =  GetLastError();
                        break;
                }

                hHttp = InternetOpenUrl( hInternet , lpURL ,NULL ,0 ,INTERNET_FLAG_RELOAD|INTERNET_FLAG_PRAGMA_NOCACHE|INTERNET_FLAG_NO_CACHE_WRITE ,0 );
                if( hHttp == NULL )
                {
                        dwError = GetLastError();
                        break;
                }
				
				BOOL bRead = InternetReadFile(hHttp,buffer,sizeof(buffer),&dwBytesRead);
				if(bRead == FALSE)
				{
					dwError = GetLastError();
                    break;
				}
				cout<<buffer<<endl;

        }while( 0 );

        if ( hInternet != NULL )
        {
                InternetCloseHandle( hInternet );
                hInternet = NULL;
        }
        if ( hHttp != NULL )
        {
                InternetCloseHandle( hHttp );
                hHttp = NULL;
        }

        return dwError;
}

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		cout<<"Please Input URL address "<<endl;
		return -1;
	}
	else if(0 != HttpPost((LPCTSTR)argv[1]))
	{
		cout<<"open url error"<<endl;
		return -1;
	}
	else
	{
		return 0;
	}
}
