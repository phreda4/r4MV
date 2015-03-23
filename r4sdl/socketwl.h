/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2006, Pablo Hugo Reda <pabloreda@gmail.com>, Mar del Plata, Argentina
 * All rights reserved.
*/

#ifndef SOCKETWL_H
#define SOCKETWL_H

#ifdef linux
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#else
#include <winsock.h>
#include <windowsx.h>
#endif

int GetHName (char *name);
int open_service (int port);
int open_server (char* hostname, int port);

#ifdef linux
int recv (int s, char *buf, int len);
int setnonblocking (int s, int on_off); 
int send (int s, char *buf, int len);
int closesocket (int s);
#else
int recv (SOCKET s, char *buf, int len);
int setnonblocking (SOCKET s, int on_off);
int send (SOCKET s, char *buf, int len);
int closesocket (SOCKET s);
#endif

int listen (int socket, int backlog);
int accept (int listening);

#endif

