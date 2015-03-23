// Socket
#ifndef SOCKET_H
#define SOCKET_H

#include <winsock.h>
#include <windowsx.h>

extern int iserror;
extern SOCKADDR_IN sinhim;

// With NT it is not possible to use a socket like a file handle (!)
// recv, send and closesocket are required ..
// This sets up a service listening to the given port.
int open_service (int port);
// This connects to a service (ftp, www, telnet..). The service lives at the internet URL
// given by the string and listens to the given port. You have to know the magic port#.
int open_server (char* hostname, int size, int port);
int recv4 (SOCKET s, char *buf, int len);
int setnonblocking (SOCKET s, int on_off);// So you don't hang on the socket (like KEY?)
int send4 (SOCKET s, char *buf, int len);// Like write()
int closesocket4 (SOCKET s);    // like close()
int listen4(int socket, int backlog);    // To enable your own server
int accept4 (int listening);         // Again to enable your own server to serve.

#endif
