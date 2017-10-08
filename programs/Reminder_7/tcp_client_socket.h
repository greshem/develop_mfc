//########################################################################
#ifndef __NET_HEADER__
#define __NET_HEADER__
#ifdef WINDOWSCODE
#else
#include <dirent.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stringprep.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <locale.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <assert.h>
#include "log.h"

class tcp_client_socket {
private:
		int m_fd;
public:
	tcp_client_socket():m_fd(-1){};
	int open_client_socket(const char * server_ip, unsigned short port );
	void close_client_socket();
	size_t send( const void * data, size_t data_size);
	size_t recv(void * buf, size_t buf_len);


	int  is_readable(int sec, int usec);
	int  is_writeable(int sec);
	int  get_fd();
};
#endif //__NET_HEADER__
 
