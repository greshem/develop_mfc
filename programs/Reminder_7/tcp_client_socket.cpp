#ifdef WINDOWSCODE
//#include <windows.h>
#include <winsock.h>
#else
#include <sys/wait.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#endif
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
//#include "../../include/protocol.h"
#include "tcp_client_socket.h"

#ifndef INFTIM
#define INFTIM (-1)
#endif

//========================================================================
//创建socket 并连接.
int  tcp_client_socket::open_client_socket(const char * server_ip, unsigned short port)
{
	//int s;
	#ifdef WINDOWSCODE
	SOCKADDR_IN server_addr;
	#else
	struct sockaddr_in server_addr;
	#endif
	int one;

	#ifdef WINDOWSCODE
	WSADATA WD;
	if(::WSAStartup(MAKEWORD(2, 0), &WD) != 0)
		return -1;
	#endif

	m_fd = (int)socket(AF_INET, SOCK_STREAM, 0);
	if ( m_fd  < 0)
	{
		perror("client: tcp socket");
		log::Instance()->logger("创建socket() 错误\n");
		return -1;
	}
	log::Instance()->logger("创建socket() 成功 \n");
	one = 1;
	if (setsockopt( m_fd , SOL_SOCKET, SO_REUSEADDR, (char*)&one, sizeof(int)) < 0)
	{
		perror("client: setsockopt");
		log::Instance()->logger("setsockopt 错误\n");
		#ifdef WINDOWSCODE
		::closesocket(m_fd);
		#else
		close(m_fd);
		#endif
		return -1;
	}

	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port   = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(server_ip);
	if (connect( m_fd , (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("client: connect");
		log::Instance()->logger("socket connect()  连接错误\n");
		#ifdef WINDOWSCODE
		::closesocket(m_fd);
		::WSACleanup();
		#else
		close(m_fd);
		#endif
		m_fd=-1;
		return -1;
	}
	return m_fd ;
}


//========================================================================
void  tcp_client_socket::close_client_socket()
{
	if (m_fd < 0)
		return;

	#ifdef WINDOWSCODE
	::closesocket(m_fd);
	m_fd = INVALID_SOCKET;
	#else
	shutdown(m_fd , SHUT_RDWR);
	close(m_fd);
	m_fd = -1;
	#endif
	
}

//========================================================================
size_t  tcp_client_socket::send( const void * data, size_t data_size)
{
	int rc;
	if(m_fd< 0)
	{
		log::Instance()->logger(" tcp_client_socket::send_request()  m_fd 错误 < 0  \n");
		return -1;
	}		
	if ( !data || data_size <= 0)
	{
		log::Instance()->logger(" tcp_client_socket:: send_request data data_size 错误.  \n");
		return -1;
	}

	rc = ::send(m_fd , (const char *)data, data_size, 0);
	if (rc < 0)
	{
		log::Instance()->logger("socket send 错误 \n");
		return -1;
	}
	else
	{
		return rc;
	}	
}

//========================================================================
size_t tcp_client_socket::recv( void * buf, size_t buf_len)
{
	int rc;
	if(m_fd< 0)
	{
		log::Instance()->logger(" recv_response:: m_fd 错误 < 0  \n");
		return -1;
	}		

	if (  !buf || buf_len <= 0)
	{
		//fprintf(stderr, "client recv_response invalid argument\n");
		log::Instance()->logger(" tcp_client_socket::  recv_response buf buf_len 错误  \n");
		return -1;
	}

	rc = ::recv(m_fd , (char *)buf, buf_len, 0);
	if (rc < 0)
	{
		perror("client recv");
		log::Instance()->logger(" tcp_client_socket recv 错误. \n");
		m_fd=-1;
		return -1;
	}
	else
	{
		return rc;
	}
}

//========================================================================
//是否可读.
int  tcp_client_socket::is_readable(int sec=0, int usec=40000)
{
        struct timeval to;
        fd_set qready;
        int err;
		//struct pollfd fds[1];

        if (m_fd < 0 )
		{
			log::Instance()->logger("is_readable  m_fd < 0 \n");
			return 0;
		}
		if(sec < 0)
		{
			log::Instance()->logger("is_readable  参数 错误 sec = %d < 0 \n", sec );
			return 0;
		}

        FD_ZERO(&qready);
        FD_SET(m_fd, &qready);
        to.tv_sec = sec;
        to.tv_usec = usec;
        if ((err = select(m_fd + 1, &qready, NULL, NULL, &to)) < 0)
        {
				log::Instance()->logger("select 失败\n");
                if (errno == EINTR)
                        return 0;
                perror("select");
                return 0;
        }
        if (err == 0)
		{	
			log::Instance()->logger("select 返回为0, 超时.\n");
			// fds[0].fd = m_fd;
			// fds[0].events = POLLIN;
			// poll(fds, 1, INFTIM);
			return err;				
            //return 0;
		}

        /* If there's someone waiting to get it, let them through */
		int ret= FD_ISSET(m_fd, &qready) ? 1 : 0;
        return ret;
}

//========================================================================
//是否可写.
int  tcp_client_socket::is_writeable(int sec=1)
{
        struct timeval to;
        fd_set qready;
        int err;

		 if (m_fd < 0 )
		{
			log::Instance()->logger("is_writeable  m_fd < 0 \n");
			return 0;
		}
		if(sec < 0)
		{
			log::Instance()->logger("is_wirteable   sec 参数错误. sec < 0 \n");
			return 0;
		}

        
        FD_ZERO(&qready);
        FD_SET(m_fd, &qready);
        to.tv_sec = sec;
        to.tv_usec = 0;
        if ((err = select(m_fd + 1,NULL,  &qready, NULL, &to)) < 0)
        {
                if (errno == EINTR)
                        return 0;
                perror("select");
                return -1;
        }
        if (err == 0)
                return 0;

        /* If there's someone waiting to get it, let them through */
		int ret= FD_ISSET(m_fd, &qready) ? 1 : 0;
        return ret;
}


int  tcp_client_socket::get_fd()
{
	return m_fd;
}

