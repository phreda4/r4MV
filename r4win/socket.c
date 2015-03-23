// Socket
// --------------------------
#include <winsock.h>
#include <windowsx.h>
#include "socket.h"

int iserror=0;
SOCKADDR_IN sinhim; // The address structure for a TCP socket

int open_service (int port) 
{
int fd;     
memset((char *)&sinhim,0,sizeof(sinhim));
sinhim.sin_family = AF_INET;
sinhim.sin_addr.s_addr = INADDR_ANY;
sinhim.sin_port = htons(port);
if ((fd=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET) {iserror=WSAGetLastError(); return (int)-1;} 
if (bind(fd,(LPSOCKADDR)&sinhim,sizeof(sinhim)) == SOCKET_ERROR) {iserror=WSAGetLastError(); return (int)-1;}
iserror=0; return fd; 
}

// This connects to a service (ftp, www, telnet..). The service lives at the internet URL
// given by the string and listens to the given port. You have to know the magic port#.
int open_server (char* hostname, int size, int port) 
{
int fd; struct hostent *hp;
if ((fd=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET) {iserror=WSAGetLastError(); return (int)-1;}
sinhim.sin_family = AF_INET;
sinhim.sin_port = htons(port);
hp = gethostbyname (hostname);
if (hp == NULL) {iserror=WSAGetLastError(); return (int)-1;}
memcpy(&sinhim.sin_addr,hp->h_addr,hp->h_length);
if (connect(fd,(LPSOCKADDR)&sinhim,sizeof(sinhim))==SOCKET_ERROR) {iserror=WSAGetLastError(); return (int)-1;} 
iserror=0; return fd; 
}

// Like read()
int recv4(SOCKET s, char *buf, int len) 
{
int numbytes=recv(s,buf,len,0);
if (numbytes==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
iserror=0; return numbytes;
} 

// So you don't hang on the socket (like KEY?)
int setnonblocking(SOCKET s, int on_off) 
{
iserror = ioctlsocket (s,FIONBIO,(u_long *)&on_off);
if (iserror==SOCKET_ERROR) iserror=WSAGetLastError(); 
return iserror; 
}

// Like write()
int send4(SOCKET s, char *buf, int len) 
{
iserror=send (s,buf,len,0);
if (iserror==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
return iserror=0;
}

// like close()
int closesocket4(SOCKET s) 
{
if (closesocket(s)==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
return iserror=0;
}
// To enable your own server
int listen4(int socket, int backlog) 
{
if (listen(socket,backlog) < 0) return errno;
return 0;
} // backlog == queue limit incoming connections

// Again to enable your own server to serve.
int accept4(int listening) 
{
int socket,alen=sizeof(sinhim);
if ((socket=accept(listening,(struct sockaddr *)&sinhim,&alen)) < 0)
   {iserror=errno; return (int)-1;} 
iserror=0; return socket;
}

