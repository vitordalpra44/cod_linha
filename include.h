#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<errno.h>

#define ISVALIDSOCKET(s) ((s) >=0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <stdio_ext.h>

#define MAXCHAR 200
#define MAXBUFFER MAXCHAR*8

