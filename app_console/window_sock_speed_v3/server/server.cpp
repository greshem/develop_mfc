#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\..\LmyUnit\UnitLib\UnitCode\MLmyUnit.hpp"
//#include <winsock2.h> //header
#pragma comment (lib, "ws2_32.lib") //lib
#pragma comment (lib, "..\\UnitLib.lib") //lib

long InitSocket()
{
    long  m_hSocket;
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKADDR_IN local;
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
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);

	local.sin_family = AF_INET;
	local.sin_port = htons(8888);	
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	err = bind(m_hSocket, (struct sockaddr *)&local, sizeof(SOCKADDR_IN));
	if(err<0)
	{
		printf("bind socket bind 失败");
		return -2;
	}	
	else
	{
		printf("bind %d成功", m_hSocket);
	}	

	err = listen(m_hSocket, 3);
	if(err < 0)
	{
		printf("listen socket listen 失败\n");	
		return -3;
	}	
	else
	{
		printf("listen listen成功");
	}	
	return m_hSocket;
}

//void SendFile(long *in);
void* __stdcall SendFile(void *in);
void* __stdcall SendFile2(void *in);
int main()
{
	long sockSrv;
	long client;
	sockSrv= InitSocket();
	SOCKADDR_IN addr;
	int len;
	FILE *fp;
	fp=fopen("888888888", "r");
	if(fp==NULL)
	{
	//	printf("open 88888888 error\n");
	//	exit(-1);
	}	
	int addr_len = sizeof(sockaddr);
	MThread thread;
	while(1)
	{
		client= accept(sockSrv, (sockaddr  *)&addr, &addr_len);
		printf("%d\n", client);

		//	int  StartThread(char * ThreadName,void * (__stdcall * ThreadFun)(void *),void * Param,bool PauseFlag = false);
		thread.StartThread("aa", SendFile, (void*)&client );
	//	SendFile(&client);
	}

	return 1;

}
void* __stdcall SendFile2(void *in)
{
	long *socket=(long*)in;
	while(1)
	{
		printf("%d\n", socket);
	}
}
void* __stdcall SendFile(void *in)
{
	long socket= *(long*)in;
	char buffer[4096];
	timeval tm;
	tm.tv_sec=0;
	tm.tv_usec=20;
	timeval tm2;
	tm2.tv_sec=1;
	tm2.tv_usec=20000;
	int i=0;
	int ret;
	while(1)
	{
		fd_set	writefds;
		FD_ZERO(&writefds);
		FD_SET(socket, &writefds);

		ret=select(socket+1, NULL, &writefds,NULL, &tm);
		if(ret >0 )
		{
		//	int len=fread(buffer, 1, sizeof(buffer), fp);
			memset(buffer, 'a', sizeof(buffer));
			int len=sizeof(buffer);
			if(len<=0)
			{
				break;
			}	
			int sendLen=send(socket, buffer, len, 0);
			//printf("%d , send %d 字节\n", i, sendLen);
			if(sendLen != len)
			{
				printf("读取的直接和发送的字节不符合\n");
			}	
			if(sendLen<0)
			{
				return NULL;
			}	
		
		}
		else
		{
			printf("select 失败%d\n", ret);
		}	
		i++;
		MThread::Sleep(1);
	//	select(socket+1, NULL, NULL,NULL, &tm2);
	}

	return NULL;
}
