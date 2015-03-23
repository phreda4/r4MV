// Socket
// --------------------------

int iserror;

#ifdef LINUX

int getSerr (int err) 
{
iserror=strlen(strerror(err)); 
return (int)strerror(err); 
}

int GetHName (char *name) 
{
iserror = gethostname (name) ? errno : 0;
if (iserror==0) return strlen(name);
return 0; 
}

struct sockaddr_in sinhim;

int open_service (int port) 
{
int fd;
memset((char *)&sinhim,0,sizeof(sinhim));
sinhim.sin_family = AF_INET;
sinhim.sin_addr.s_addr = INADDR_ANY;
sinhim.sin_port = htons(port);
if ((fd=socket(AF_INET,SOCK_STREAM,0)) < 0) 
	{ iserror=errno; return -1; }
if (bind(fd,(struct sockaddr *)&sinhim,sizeof(sinhim)) < 0) 
	{ iserror=errno; return -1; }
iserror=0; 
return fd; 
}

int open_server (char* hostname, int port) 
{
int fd; struct hostent *hp;
if ((fd=socket(AF_INET,SOCK_STREAM,0)) < 0) 
	{ iserror=errno; return -1;}
sinhim.sin_family = AF_INET;
sinhim.sin_port = htons(port);
hp = gethostbyname (hostname);
if (hp == NULL) 
	{ iserror=errno; return -1;}
memcpy(&sinhim.sin_addr,hp->h_addr,hp->h_length);
if (connect(fd,(struct sockaddr *)&sinhim,sizeof(sinhim)) < 0) 
	{ iserror=errno; return -1;}
iserror=0;
return fd; 
}

int recv4 (int s, char *buf, int len) 
{
int numbytes = recv(s,buf,len,0);
if (numbytes < 0) { iserror=errno; return -1;}
iserror=0; return numbytes;
}

int setnonblocking (int s, int on_off) 
{
iserror = (on_off ? fcntl(s,F_SETFL,O_NONBLOCK) : fcntl(s,F_SETFL,0));
if (iserror < 0) iserror=errno;
return iserror; 
}

int send4 (int s, char *buf, int len) 
{
int numbytes = send(s,buf,len,0);
if (numbytes < 0) { iserror=errno; return -1;}
iserror=0; return numbytes;
}

int closesocket4 (int s)
{
if (close(s) < 0) { iserror=errno; return -1;}
return iserror=0;
}

int listen4 (int socket, int backlog) 
{
if (listen(socket, backlog) < 0) return errno;
return 0;
}

int accept4 (int listening)
{
int socket,alen=sizeof(sinhim);
if ((socket=accept(listening,(struct sockaddr *)&sinhim,&alen)) < 0) 
	{ iserror=errno; return -1;}
iserror=0; return socket;
}

#else

#include <winsock.h>
#include <windowsx.h>

typedef unsigned short WORD;

// makestr() is a function that converts a c-addr u to a C-string (it uses a buffer)
// iserror is a C-variable that iForth can access. An iForth SYSCALL works like
// this:  SYSCALL ( {param}*n n function# -- Creturnvalue iserror ) 

// call this once when iForth starts
void OpenSockets(void) {
    WORD wVersionRequested = MAKEWORD(2,0);
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData); }

// call this once when iForth exits to the OS
void CloseSockets(void) {WSACleanup();}

static char * SAerr[18] =
     { "A successful SAStartup must occur before using this function.",
       "The Sockets implementation has detected that the network subsystem has failed.",
       "Authoritative Answer Host not found.", 
       "Non-Authoritative Host not found, or SERVERFAIL.",
       "Nonrecoverable errors: FORMERR, REFUSED, NOTIMP.",
       "Valid name, no data record of requested type.",
       "A blocking Sockets operation is in progress.", 
       "The (blocking) call was canceled using SACancelBlockingCall.",
       "The namelen parameter is too small.",
       "Software caused connection abort.",
       "Connection refused.", 
       "Connection reset by peer.",
       "Connection timed out.",
       "Graceful shutdown in progress.",
       "Socket operation on non-socket.",
       "The specified address is already in use.", 
       "The socket has been shutdown, recv() not possible.",
       "Error text not available." };

// Ask OS what an error code means.
int getSerr (int err) {       /* 220 */
    switch (err) {
     case WSANOTINITIALISED: err=0;  break;
     case WSAENETDOWN:      err=1;  break;
     case WSAHOST_NOT_FOUND: err=2;  break; 
     case WSATRY_AGAIN:      err=3;  break;
     case WSANO_RECOVERY:    err=4;  break;
     case WSANO_DATA:       err=5;  break;
     case WSAEINPROGRESS:    err=6;  break;
     case WSAEINTR:       err=7;  break; 
     case WSAEFAULT:      err=8;  break;
     case WSAECONNABORTED:   err=9;  break;
     case WSAECONNREFUSED:   err=10; break;
     case WSAECONNRESET:     err=11; break;
     case WSAETIMEDOUT:      err=12; break; 
     case WSAEDISCON:      err=13; break;
     case WSAENOTSOCK:       err=14; break;
     case WSAEADDRINUSE:     err=15; break;
     case WSAESHUTDOWN:      err=16; break;
     default:        err=17; }
    iserror=strlen(SAerr[err]);
    return (int)SAerr[err]; }

// Get the local computer's name in a buffer
int GetHName (char *name, int size) {     /* 221 */
    iserror = gethostname (name,size) ? WSAGetLastError() : 0;
    if (iserror==0) return strlen(name);
    return 0; }

struct sockaddr_in sinhim = { AF_INET };

// With NT it is not possible to use a socket like a file handle (!)
// recv, send and closesocket are required ..
// This sets up a service listening to the given port.
int open_service (int port) {int fd;      /* 222 */ 
    memset((char *)&sinhim,0,sizeof(sinhim));
    sinhim.sin_family = AF_INET;
    sinhim.sin_addr.s_addr = INADDR_ANY;
    sinhim.sin_port = htons(port);
    if ((fd=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET) {iserror=WSAGetLastError(); return (int)-1;} 
    if (bind(fd,&sinhim,sizeof(sinhim)) == SOCKET_ERROR) {iserror=WSAGetLastError(); return (int)-1;}
    iserror=0; return fd; }

// This connects to a service (ftp, www, telnet..). The service lives at the internet URL
// given by the string and listens to the given port. You have to know the magic port#.
int open_server (char* hostname, int size, int port) {   /* 223 */ 
    int fd; struct hostent *hp;
    if ((fd=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET) {iserror=WSAGetLastError(); return (int)-1;}
    sinhim.sin_family = AF_INET;
    sinhim.sin_port = htons(port);
    hp = gethostbyname (hostname);
    if (hp == NULL) {iserror=WSAGetLastError(); return (int)-1;}
    memcpy(&sinhim.sin_addr,hp->h_addr,hp->h_length);
    if (connect(fd,&sinhim,sizeof(sinhim))==SOCKET_ERROR) {iserror=WSAGetLastError(); return (int)-1;} 
    iserror=0; return fd; }

// Like read()
int recv4 (SOCKET s, char *buf, int len) {    /* 224 */
    int numbytes=recv(s,buf,len,0);
    if (numbytes==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
    iserror=0; return numbytes;} 

// So you don't hang on the socket (like KEY?)
int setnonblocking (SOCKET s, int on_off) {    /* 225 */
    iserror = ioctlsocket (s,FIONBIO,(u_long *)&on_off);
    if (iserror==SOCKET_ERROR) iserror=WSAGetLastError(); 
    return iserror; }

// Like write()
int send4 (SOCKET s, char *buf, int len) {    /* 226 */
    iserror=send (s,buf,len,0);
    if (iserror==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
    return iserror=0;}

// like close()
int closesocket4 (SOCKET s) {       /* 227 */
    if (closesocket(s)==SOCKET_ERROR) {iserror=WSAGetLastError(); return 0;}
    return iserror=0;}

// To enable your own server
int listen4 (int socket, int backlog) {     /* 228 */
    if (listen(socket,backlog) < 0) return errno;
    return 0;} // backlog == queue limit incoming connections

// Again to enable your own server to serve.
int accept4 (int listening) {int socket,alen=sizeof(sinhim);  /* 229 */
    if ((socket=accept(listening,(struct sockaddr *)&sinhim,&alen)) < 0)
       {iserror=errno; return (int)-1;} 
    iserror=0; return socket;}

#endif
