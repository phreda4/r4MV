/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2006,2007,2008, Pablo Hugo Reda <pabloreda@gmail.com>, 
 * Mar del Plata, Argentina
 * All rights reserved.
*/
// rutinas graficas

#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <string.h>
#include "graf.h"
#include "mat.h"

//---- variables internas
DWORD gr_color1,gr_color2;

//---- variables para dibujo de poligonos
struct gr_segpoli {
	int ymax;// donde corta
	int x,dx;// inicio de x, avance de x
	struct gr_segpoli *next,*nextValid;
};

#define SEGFRAC			8	// precision de los poligonos
#define MASFRAC			0xff	
#define NB_SEGMENT_MAX	1025 // cada segmento es una linea

int gr_limymin,gr_limymax;
gr_segpoli *gr_linact;
gr_segpoli *gr_lines[SCR_HEIGHT+1];
gr_segpoli gr_seg[NB_SEGMENT_MAX];

#define RED_MASK 0xFF0000
#define GRE_MASK 0xFF00
#define BLU_MASK 0xFF

int gr_buffer[SCR_SIZE];		// buffer de pantalla
BYTE gr_alphav;

#define MASK1 (RED_MASK|BLU_MASK)
#define MASK2 (GRE_MASK)

inline DWORD gr_mix(DWORD col,BYTE alpha)
{
register DWORD B=col & MASK1;
register DWORD RB=(((((gr_color1&MASK1)-B)*alpha)>>8)+B)&MASK1;
B=col&MASK2;
return ((((((gr_color1&MASK2)-B)*alpha)>>8)+B)&MASK2)|RB;
}

//--------------- RUTINAS DE DIBUJO
//---- solido
void _gr_pixels(DWORD *gr_pos)		{*gr_pos=gr_color1;}
void _gr_pixela(DWORD *gr_pos,BYTE a){*gr_pos=gr_mix(*gr_pos,a);}

//---- solido con alpha
void _gr_pixelsa(DWORD *gr_pos)		{*gr_pos=gr_mix(*gr_pos,gr_alphav);}
void _gr_pixelaa(DWORD *gr_pos,BYTE a) {*gr_pos=gr_mix(*gr_pos,(BYTE)((DWORD)(a*gr_alphav)>>8));}

//--------------- RUTINAS DE DIBUJO
void (*gr_pixel)(DWORD *gr_pos);
void (*gr_pixela)(DWORD *gr_pos,BYTE a);

void gr_solid(void) {gr_pixel=_gr_pixels;gr_pixela=_gr_pixela;gr_alphav=255;}
void gr_alpha(void) {gr_pixel=_gr_pixelsa;gr_pixela=_gr_pixelaa;}

//------------------------------------
#define GR_SET(X,Y) gr_pos=(DWORD*)gr_buffer+Y*SCR_WIDTH+X;
#define GR_X(X) gr_pos+=X;
#define GR_Y(Y) gr_pos+=SCR_WIDTH*Y;
//------------------------------------

void gr_hlined(int x1,int y1,int x2,const BYTE a1,const BYTE a2)
{
int alpha=a1<<8;
int da=((a2-a1)<<8)/(x2-x1);
if (x1<0) { alpha+=da*(-x1);x1=0; }
if (x2>=SCR_WIDTH) { x2=SCR_WIDTH-1;if (x1>=SCR_WIDTH) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+x2-x1+1;
do {
	gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da;
} while (gr_pos<pf);
}

void gr_vlined(int x1,int y1,int y2,const BYTE a1,const BYTE a2)
{
int alpha=(a1<<8);
int da=((a2-a1)<<8)/(y2-y1);
if (y1<0) { alpha+=da*(-y1);y1=0; }
if (y2>=SCR_HEIGHT) { y2=SCR_HEIGHT-1;if (y1>=SCR_HEIGHT) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+((y2-y1+1)*SCR_WIDTH);
do {
	gr_pixela(gr_pos,alpha>>8);gr_pos+=SCR_WIDTH;alpha+=da;
} while (gr_pos<pf);
}

//---- clip
void gr_hline(int x1,int y1,int x2)
{
if (x1<0) x1=0;
if (x2>=SCR_WIDTH) { x2=SCR_WIDTH-1;if (x1>=SCR_WIDTH) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+x2-x1+1;
do { gr_pixel(gr_pos);gr_pos++; } while (gr_pos<pf);
}

void gr_vline(int x1,int y1,int y2)
{
if (y1<0) y1=0;
if (y2>=SCR_HEIGHT) { y2=SCR_HEIGHT-1;if (y1>=SCR_HEIGHT) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+((y2-y1+1)*SCR_WIDTH);
do { gr_pixel(gr_pos);gr_pos+=SCR_WIDTH; } while (gr_pos<pf);
}

bool gr_clipline(int *X1,int *Y1,int *X2,int *Y2)
{
int C1,C2,V;
if (*X1<0) C1=1; else C1=0;
if (*X1>=SCR_WIDTH) C1|=0x2;
if (*Y1<0) C1|=0x4;
if (*Y1>=SCR_HEIGHT-1) C1|=0x8;
if (*X2<0) C2=1; else C2=0;
if (*X2>=SCR_WIDTH) C2|=0x2;
if (*Y2<0) C2|=0x4;
if (*Y2>=SCR_HEIGHT-1) C2|=0x8;
if ((C1&C2)==0 && (C1|C2)!=0) {
	if ((C1&12)!=0) {
		if (C1<8) V=0; else V=SCR_HEIGHT-2;
		*X1+=(V-*Y1)*(*X2-*X1)/(*Y2-*Y1);*Y1=V;
		if (*X1<0) C1=1; else C1=0;
		if (*X1>=SCR_WIDTH) C1|=0x2;
		}
    if ((C2&12)!=0) {
		if (C2<8) V=0; else V=SCR_HEIGHT-2;
		*X2+=(V-*Y2)*(*X2-*X1)/(*Y2-*Y1);*Y2=V;
		if (*X2<0) C2=1; else C2=0;
		if (*X2>=SCR_WIDTH) C2|=0x2;
		}
    if ((C1&C2)==0 && (C1|C2)!=0) {
		if (C1!=0) {
			if (C1==1) V=0; else V=SCR_WIDTH-1;
			*Y1+=(V-*X1)*(*Y2-*Y1)/(*X2-*X1);*X1=V;C1=0;
			}
		if (C2!=0) {
			if (C2==1) V=0; else V=SCR_WIDTH-1;
			*Y2+=(V-*X2)*(*Y2-*Y1)/(*X2-*X1);*X2=V;C2=0;
			}
		}
	}
return (C1|C2)==0;
}

//---- con clip
inline void gr_setpixel(int x,int y)
{
if ((unsigned)x>=(unsigned)SCR_WIDTH || (unsigned)y>=(unsigned)SCR_HEIGHT) return;
register DWORD *gr_pos;
GR_SET(x,y);gr_pixel(gr_pos);
}

inline void gr_setpixela(int x,int y,BYTE a)
{
if ((unsigned)x>=(unsigned)SCR_WIDTH || (unsigned)y>=(unsigned)SCR_HEIGHT) return;
register DWORD *gr_pos;
GR_SET(x,y);gr_pixela(gr_pos,a);
}

inline void swap(int &a,int &b)//int t=a;a=b;b=t;
{ a^=b;b^=a;a^=b; }

void gr_line(int x1,int y1,int x2,int y2)
{
if (!gr_clipline(&x1,&y1,&x2,&y2)) return;
int dx,dy,sx,d;
if (x1==x2) { if (y1>y2) swap(y1,y2);
            gr_vline(x1,y1,y2); return; }
if (y1==y2) { if (x1>x2) swap(x1,x2);
            gr_hline(x1,y1,x2);	return;	};
if (y1>y2) { swap(x1,x2);swap(y1,y2); }            
dx=x2-x1;dy=y2-y1;
if (dx>0) sx=1; else { sx=-1;dx=-dx; }
//if (dy>0) sy=1; else { sy=-1;dy=-dy; }
WORD ea,ec=0;BYTE ci;
register DWORD *gr_pos;
GR_SET(x1,y1);gr_pixel(gr_pos);
if (dy>dx) 	{
	ea=(dx<<16)/dy;
    while (dy>0) {
        dy--;d=ec;ec+=ea;if (ec<=d) x1+=sx;
        y1++;ci=ec>>8;
		GR_SET(x1,y1);gr_pixela(gr_pos,255-ci);GR_X(sx);gr_pixela(gr_pos,ci);
		}
} else {// DY <= DX
    ea=(dy<<16)/dx;
    while (dx>0) {
        dx--;d=ec;ec+=ea;if (ec<=d) y1++;
        x1+=sx;ci=ec>>8;
		GR_SET(x1,y1);gr_pixela(gr_pos,255-ci);
//        if (y1<SCR_HEIGHT-1) { // 640x480 necesita
        GR_Y(1);gr_pixela(gr_pos,ci); 
//                        }
		}
	}
}

void gr_pline(int x1,int y1,int x2,int y2,WORD t)
{
if (!gr_clipline(&x1,&y1,&x2,&y2)) return;
int dx,dy,xinc,yinc,s,dx2,dy2,dxy,x,y;
if (x1<x2) xinc=1; else xinc=-1;
dx=abs(x1-x2);
if (y1<y2) yinc=1; else yinc=-1;
dy=abs(y1-y2);
dx2=dx+dx;dy2=dy+dy;
x=x1;y=y1;
WORD mask=0x2;
register DWORD *gr_pos;
if ((t&1)!=0) { GR_SET(x,y);gr_pixel(gr_pos); }
if (dx>dy) {
	s = dy2 - dx;
	dxy = dy2 - dx2;
	for (int i=1;i<dx+1;i++) {
		if (s>=0) { y+=yinc;s+=dxy; }	else s+=dy2;
		x+=xinc;
		if ((t&mask)!=0) { GR_SET(x,y);gr_pixel(gr_pos); }
		if (mask==0x8000) mask=0x1; else mask<<=1;
		}
} else {
	s = dx2 - dy;
	dxy = dx2 - dy2;
	for (int i=1;i<dy+1;i++) {
		if (s>=0) { x+=xinc;s+=dxy; }	else s+=dx2;
		y+=yinc;
		if ((t&mask)!=0) { GR_SET(x,y);gr_pixel(gr_pos); }
		if (mask==0x8000) mask=0x1; else mask<<=1;
		}
	}
}

void gr_splineiter(int x1,int y1,int x2,int y2,int x3,int y3)
{//dist(x1,y1,x3,y3)<(4<<4)){//if (angle(x1,y1,x2,y2,x3,y3)<100) {
if (recta(x1,y1,x2,y2,x3,y3)<1000) { gr_line(x1>>4,y1>>4,x3>>4,y3>>4); return; }
int x11=(x1+x2)>>1,y11=(y1+y2)>>1;
int x21=(x2+x3)>>1,y21=(y2+y3)>>1;
int x22=(x11+x21)>>1,y22=(y11+y21)>>1;
gr_splineiter(x1,y1,x11,y11,x22,y22);
gr_splineiter(x22,y22,x21,y21,x3,y3);
}

void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3)
{
gr_splineiter(x1<<4,y1<<4,x2<<4,y2<<4,x3<<4,y3<<4);
}

void gr_splinec(int x1,int y1,int x2,int y2,int x3,int y3)
{
int mx,my;
mx=(x1+x3)>>1;my=(y1+y3)>>1;x2=mx+((x2-mx)<<1);y2=my+((y2-my)<<1);
gr_splineiter(x1<<4,y1<<4,x2<<4,y2<<4,x3<<4,y3<<4);
}

// poligono
void gr_iteracionSP(long x1,long y1,long x2,long y2,long x3,long y3)
{//dist(x1,y1,x3,y3)<(4<<4)){//angle(x1,y1,x2,y2,x3,y3)<100) {
if (recta(x1,y1,x2,y2,x3,y3)<1000){ gr_psegmento(x1>>4,y1>>4,x3>>4,y3>>4);return; }
long x11=(x1+x2)>>1,y11=(y1+y2)>>1;
long x21=(x2+x3)>>1,y21=(y2+y3)>>1;
long x22=(x11+x21)>>1,y22=(y11+y21)>>1;
gr_iteracionSP(x1,y1,x11,y11,x22,y22);
gr_iteracionSP(x22,y22,x21,y21,x3,y3);
}

void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3)
{
gr_iteracionSP(x1<<4,y1<<4,x2<<4,y2<<4,x3<<4,y3<<4);
}

void gr_psplinec(int x1,int y1,int x2,int y2,int x3,int y3)
{
int mx=(x1+x3)>>1;int my=(y1+y3)>>1;
x2=mx+((x2-mx)<<1);y2=my+((y2-my)<<1);
gr_iteracionSP(x1<<4,y1<<4,x2<<4,y2<<4,x3<<4,y3<<4);
}

void gr_psegmento(int x1,int y1,int x2,int y2)
{
gr_segpoli *s;
int dx,x,ymin,ymax;
if (y1==y2) return;
if (y1<y2) { ymin=y1;ymax=y2;} else { ymin=y2;ymax=y1;swap(x1,x2); }
if (ymax<=0 || ymin>=SCR_HEIGHT ) return;
x=(x1<<SEGFRAC);
dx=((x2-x1)<<SEGFRAC)/(ymax-ymin);
if (ymin<0) { x+=dx*(-ymin);ymin=0; }
if (ymax>SCR_HEIGHT) ymax=SCR_HEIGHT;//-1 (**1)
if ((gr_linact-gr_seg)>=NB_SEGMENT_MAX) return;
s=gr_linact++;
s->next=s->nextValid=0;s->ymax=ymax;s->x=x;s->dx=dx;
if (ymin<gr_limymin) gr_limymin=ymin;
if (ymax>gr_limymax) gr_limymax=ymax;
if (gr_lines[ymin]==NULL) gr_lines[ymin]=s;
else {
    gr_segpoli *act,*prev;prev=0;
    for(act=gr_lines[ymin];act;prev=act,act=act->next) {
        if ((act->x+act->dx)>(s->x+s->dx)) {
            if (prev) { prev->next=s;s->next=act; } 
			else { s->next=gr_lines[ymin];gr_lines[ymin]=s; }
            break;
            }
        }
	if (act==0) { prev->next=s;s->next=act; }
    }
}

gr_segpoli *avanzaS(gr_segpoli *curSegs,int y)
{
gr_segpoli *s,*prev,*ant;
s=curSegs;prev=ant=0;
while(s) {
    if (y>=s->ymax) {// == para evitar superpuestos (**1)
        if (prev) prev->nextValid=s->nextValid;
		else curSegs=s->nextValid;
        s=s->nextValid;
    } else {
		s->x+=s->dx;
		if (prev!=0 && s->x<prev->x) { // se invirtio el orden
			if (ant==0) curSegs=s; else ant->nextValid=s;
			prev->nextValid=s->nextValid;
			s->nextValid=prev;ant=s;s=prev->nextValid;
		} else  { ant=prev;prev=s;s=s->nextValid; }// sigue igual
        }
    }
return curSegs;
}

gr_segpoli *nuevoS(gr_segpoli *curSegs,gr_segpoli *newSegs)
{
gr_segpoli *s,*se,*prev;
s=curSegs;prev=0;
for (se=newSegs;se;se=se->next) {
	if (curSegs==0) { curSegs=se;se->nextValid=0; } 
	else {
        for(;s;prev=s,s=s->nextValid) {
            if (s->x>se->x)	{
                if (prev) { se->nextValid=s;prev->nextValid=se; } 
				else { se->nextValid=curSegs;curSegs=se; }
                break;
                }
            }
		if (s==0) { prev->nextValid=se;se->nextValid=0; }// agregar al final
        }
    s=se;
    }
return curSegs;
}

// Poligonos con antialiasing
inline void Flinea(int y,int x1,int x2,int x3,int x4)
{
int ex1=x1>>SEGFRAC,ex2=x2>>SEGFRAC;
int ex3=x3>>SEGFRAC,ex4=x4>>SEGFRAC;
register DWORD *gr_pos;
if (ex2>=0) {
	if (ex1<ex2) gr_hlined(ex1,y,ex2,0,255);
	else { GR_SET(ex1,y);gr_pixela(gr_pos,255-(BYTE)((x1+x2)>>1));
		if (ex2==ex4) return;}
	}
ex2++;
if (ex2<ex3) gr_hline(ex2,y,ex3-1);
if (ex3<SCR_WIDTH) {
	if (ex3<ex4) gr_hlined(ex3,y,ex4,255,0);
	else { GR_SET(ex3,y);gr_pixela(gr_pos,(BYTE)((x3+x4)>>1)); }
	}
}

//**************************************************
//***** DIBUJO DE POLIGONO
//**************************************************
void gr_drawPoli(void)
{
int x1,x3,y;
int x2,x4;
int auxl=SCR_WIDTH<<SEGFRAC;
gr_segpoli *curSegs,*s;
if (gr_limymax==-1) return;
curSegs=NULL;
gr_segpoli **linesp=&gr_lines[gr_limymin];
for(y=gr_limymin;y<gr_limymax;y++) {
    curSegs=avanzaS(curSegs,y);
    curSegs=nuevoS(curSegs,*linesp);
	s=curSegs;// salto anteriores a la pantalla
	while (s && s->nextValid && s->nextValid->x<0)
		s=s->nextValid->nextValid;
	while (s && s->nextValid && s->x<auxl) {// hasta que este afuera
		x1=s->x;x2=s->x+s->dx;if (s->dx<0) swap(x1,x2);
		s=s->nextValid;
		x3=s->x;x4=s->x+s->dx;if (s->dx<0) swap(x3,x4);
		Flinea(y,x1,x2,x3,x4);
/*/// sin antialiasing (mas rapido)
		x1=(s->x>>SEGFRAC);s=s->nextValid;
		x3=(s->x>>SEGFRAC);
		if (x1<0) x1=0;
		if (x3>=SCR_WIDTH) x3=SCR_WIDTH-1;
		gr_set(x1,y);gr_hline(x3-x1);
*/
		s=s->nextValid;
		}
	*linesp=NULL;linesp++;
    }
gr_limymax=-1;gr_limymin=SCR_HEIGHT+1;gr_linact=gr_seg;
}

int width=SCR_WIDTH;
int height=SCR_HEIGHT;
WNDCLASSEX wc;
HWND hWnd;
LPDIRECTDRAW7        g_lpdd7;        // DirectDraw object
LPDIRECTDRAWSURFACE7 g_lpddsPrimary; // DirectDraw primary surface
LPDIRECTDRAWSURFACE7 g_lpddsBack;    // DirectDraw back buffer surface
DDSURFACEDESC2 ddsd;

//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
void gr_ini(void)
{
DDSCAPS2            ddscaps;     
DirectDrawCreateEx( NULL, (LPVOID*)&g_lpdd7, IID_IDirectDraw7, NULL);
g_lpdd7->SetCooperativeLevel( hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
g_lpdd7->SetDisplayMode(SCR_WIDTH,SCR_HEIGHT,32, 0, 0 );
ZeroMemory( &ddsd, sizeof(ddsd) );
ddsd.dwSize = sizeof(DDSURFACEDESC2);
ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX ;//|DDSCAPS_VIDEOMEMORY;
ddsd.dwBackBufferCount = 1;
ddsd.dwWidth  =SCR_WIDTH;
ddsd.dwHeight =SCR_HEIGHT;
g_lpdd7->CreateSurface( &ddsd, &g_lpddsPrimary, NULL );
ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
ddscaps.dwCaps2 = ddscaps.dwCaps3 = ddscaps.dwCaps4 = 0;
g_lpddsPrimary->GetAttachedSurface( &ddscaps, &g_lpddsBack );

SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, 0, 0, 0);

ZeroMemory( &ddsd, sizeof(ddsd) );
ddsd.dwSize = sizeof(ddsd);
     
//....................
//---- poligonos
gr_linact=gr_seg;
gr_segpoli **p=gr_lines;
for (int i=0;i<=SCR_HEIGHT;i++,p++) *p=0;
gr_limymin=SCR_HEIGHT+1;gr_limymax=-1;
//---- colores
gr_color1=0xffffff;
gr_color2=0;
gr_solid();
//----
}

//--------------------------------------------------
void redraw(void)
{
char *src,*dst;
int y,dst_pitch;

g_lpddsBack->Lock(NULL, &ddsd,0,0);//DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
dst_pitch = (int)ddsd.lPitch; 
dst = (char*) ddsd.lpSurface;
src = (char*) gr_buffer;
for (y=0; y<SCR_HEIGHT; y++)
    {
    memcpy(dst,src,SCR_WIDTH*4);
    src += SCR_WIDTH*4;
    dst += dst_pitch;
    }
g_lpddsBack->Unlock(NULL);
g_lpddsPrimary->Flip(g_lpddsBack, DDFLIP_WAIT );
}

void gr_restore(void)
{
g_lpddsPrimary->Restore();
}

void gr_fin()
{
if (g_lpddsPrimary) { delete(g_lpddsPrimary);g_lpddsPrimary=NULL; }     
if (g_lpdd7) { delete(g_lpdd7);g_lpdd7=NULL; }     
SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, 1, 0, 0);
}
