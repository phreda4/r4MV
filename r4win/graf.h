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

#ifndef GRAF_H
#define GRAF_H

#include <ddraw.h>
#include "mat.h"

//#define SCR_WIDTH 1280
//#define SCR_HEIGHT 1024

#define SCR_WIDTH 1024
#define SCR_HEIGHT 768

//#define SCR_WIDTH 640
//#define SCR_HEIGHT 480

#define SCR_SIZE SCR_WIDTH * SCR_HEIGHT

extern HWND hWnd;
extern WNDCLASSEX wc;

extern int gr_buffer[SCR_SIZE]; // buffer de pantalla

extern DWORD gr_color1,gr_color2;
extern BYTE gr_alphav;

void gr_solid(void);
void gr_alpha(void);		// parametros: alpha

void gr_hlined(int x1,int y1,int x2,const BYTE a1,const BYTE a2);
void gr_vlined(int x1,int y1,int x2,const BYTE a1,const BYTE a2);
void gr_hline(int x1,int y1,int x2);
void gr_vline(int x1,int y1,int y2);

//---- basicas
void gr_setpixel(int x,int y);
void gr_setpixela(int x,int y);
void gr_line(int x1,int y1,int x2,int y2);

void gr_pline(int x1,int y1,int x2,int y2,WORD t);
void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_splinec(int x1,int y1,int x2,int y2,int x3,int y3);

//---- poligono
void gr_psegmento(int x1,int y1,int x2,int y2);
void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_psplinec(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_drawPoli(void);	

void redraw(void);
void gr_fin(void);
void gr_ini(void);
void gr_restore(void);

#endif
