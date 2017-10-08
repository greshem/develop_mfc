#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\..\LmyUnit\UnitLib\UnitCode\MLmyUnit.hpp"

//#include <winsock2.h> //header
#pragma comment (lib, "ws2_32.lib") //lib
#pragma comment (lib, "ws2_32.lib") //lib
#pragma comment (lib, "..\\UnitLib.lib") //lib

long _InitSocket()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKET	hSocket;;
	int err;  
	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {                        
		return -1 ;
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 2 ) {
		
		WSACleanup( );
		return -1 ; 
	}
	
	//scClient=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	hSocket = socket(AF_INET, SOCK_STREAM, 0);
	return  hSocket;
}

/*##############################################################################
#
#
#连接服务器
##############################################################################*/
int _ConnectSocket(long m_hSocket, char *address)
{
	int ret;
	SOCKADDR_IN server;
	
	memset(&server, '\0', sizeof(SOCKADDR_IN));
	server.sin_family=PF_INET;
	server.sin_port	 =htons(8888);
	server.sin_addr.s_addr = inet_addr(address);
	
	ret = connect(m_hSocket, (sockaddr*) &server, sizeof(SOCKADDR_IN)); 
	if(ret==0)
	{
			printf("连接 连接服务器 %s 成功", address );
	}	
	else
	{
			printf("连接 连接服务器%s 失败", address);
			exit(-1);
	}	
	return ret;
}

int main()
{
	long socket;
	char buffer[4096];
	MString		config = "config.ini";
	MString		ip ;
	//上交所
	char						dftshopentime[50]= {0};				//	开盘时间

	MIniFile	iniFile;
	
	

	if ( iniFile.Open(config) >= 0 )
	{
		ip = iniFile.ReadString( "ip","ip", "127.0.0.1" );
	}
	socket=_InitSocket();
	printf("#### 连接服务器%s\n", ip.c_str());
	_ConnectSocket(socket, ip.c_str());

	int i=0;
	while(1)
	{
		int ret=recv(socket, buffer, sizeof(buffer), 0);
		//printf("%d, recv = %d \n", i, ret);
		i++;
	}
	return 1;
}
