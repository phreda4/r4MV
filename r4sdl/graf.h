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

#include <SDL/SDL.h>

#define DWORD unsigned int
#define WORD unsigned short
#define BYTE unsigned char

extern SDL_Surface *gr_screen;
extern DWORD *gr_buffer;		// buffer de pantalla
extern int gr_ancho,gr_alto;
extern int gr_sizescreen;	// tamanio de pantalla

extern DWORD gr_color1,gr_color2;
extern BYTE gr_alphav;

int gr_init(void);
void gr_fin(void);
void gr_redraw(void); 

void gr_clrscr(void);

// ALPHA
void gr_solid(void);
void gr_alpha(void);

// FILL POLY
void fillSol(void);
void fillLin(void);
void fillRad(void);

void fillcent(int mx,int my);
void fillmat(int a,int b);
void fillcol(DWORD c1,DWORD c2);

void gr_hlined(int x1,int y1,int x2,const BYTE a1,const BYTE a2);
void gr_vlined(int x1,int y1,int x2,const BYTE a1,const BYTE a2);
void gr_hline(int x1,int y1,int x2);
void gr_vline(int x1,int y1,int y2);

//---- basicas
void gr_setpixel(int x,int y);
void gr_setpixela(int x,int y);
void gr_line(int x1,int y1,int x2,int y2);
void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3);

//---- poligono
void gr_psegmento(int x1,int y1,int x2,int y2);
void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_drawPoli(void);	


#endif
