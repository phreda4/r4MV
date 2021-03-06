
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
// rutinas graficas
#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include "graf.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;    

//---- buffer de video
DWORD *gr_buffer;
DWORD *XFB;

//---- variables internas
int gr_ancho,gr_alto;
DWORD gr_color1,gr_color2,col1,col2;
int gr_ypitch;
int MA,MB,MTX,MTY; // matrix de transformacion
int *mTex; // textura
int gr_alphav;
static int gr_sizescreen;	// tamanio de pantalla

//---- variables para dibujo de poligonos
typedef struct { int y,x,yfin,deltax; } Segm;

int cntSegm=0;
Segm segmentos[2048];
int yMax,yMin;          // maximo y actual

Segm seg0={-1,0x80000001,-1,0};
Segm *activelist[1024];
Segm **activelast;

int ImplicitHeapY[2048];
int cntIHY;

void initIHY(void)
{
cntIHY=0;
activelist[0]=&seg0;
activelast=&activelist[1];
cntSegm=0;yMax=-1;
}

void addIHY(int v)
{
int i,j;
cntIHY++;
for (i=cntIHY-1;i>0;) {
	j=(i-1)/2;
	if (ImplicitHeapY[j]<v) { ImplicitHeapY[i]=v;return; }
	ImplicitHeapY[i]=ImplicitHeapY[j];
	i=j; }
ImplicitHeapY[0]=v;
}

void moveDnY(int v,int n) 
{
int i;
while (n<cntIHY/2) { 
    i=(n*2)+1;
    if (i+1<cntIHY && ImplicitHeapY[i]>ImplicitHeapY[i+1]) 
       { i++; }
    if (ImplicitHeapY[i]>=v) 
       { ImplicitHeapY[n]=v;return; }
    ImplicitHeapY[n]=ImplicitHeapY[i];
    n=i;
    }
ImplicitHeapY[n]=v;    
}

int remIHY(void)
{
if (cntIHY==0) return -1;
int val=ImplicitHeapY[0];
moveDnY(ImplicitHeapY[cntIHY-1],0);
cntIHY--;
return val;
}

int heapIHY(void)
{
if (cntIHY==0) return -1;
return ImplicitHeapY[0];
}
//-----------------------------------------

int runlenscan[2048];
int *rl;

#define GETPOS(a) (((a)>>20)&0xfff)
#define GETLEN(a) (((a)>>9)&0x7ff)
#define GETVAL(a) ((a)&0x1ff)
#define GETPOSF(a) ((((a)>>20)&0xfff)+(((a)>>9)&0x7ff))

#define SETPOS(a) ((a)<<20)
#define SETLEN(a) ((a)<<9)
#define SETVAL(a) (a)

//////////////////////////////////////////////////////////////
#define FBASE 8
#define RED_MASK 0xFF0000
#define GRE_MASK 0xFF00
#define BLU_MASK 0xFF


#ifdef NOMUL
int (*setxyf)(int a,int b);

int setxy(int a,int b) { return (int)gr_buffer+((b*gr_ancho+a)<<2); }
int setxy640(int a,int b) { return (int)gr_buffer+(((b<<7)+(b<<9)+a)<<2); } // 128 + 512
int setxy800(int a,int b) { return (int)gr_buffer+(((b<<5)+(b<<8)+(b<<9)+a)<<2); }
int setxy1024(int a,int b) { return (int)gr_buffer+(((b<<10)+a)<<2); }
int setxy1280(int a,int b) { return (int)gr_buffer+(((b<<10)+(b<<8)+a)<<2); }
int setxy1366(int a,int b) { return (int)gr_buffer+(((b*1366)+a)<<2); }
#endif

void gr_fin(void) 
{
VirtualFree(XFB, 0, MEM_RELEASE);
VirtualFree(gr_buffer, 0, MEM_RELEASE);
}

inline void swap(int &a,int &b) { a^=b;b^=a;a^=b; }
inline int abs(int a ) { return (a+(a>>31))^(a>>31); }

//////////////////////////////////////////////////////////////
//---- inicio
int gr_init(int XRES,int YRES)
{
gr_sizescreen=XRES*YRES;// tamanio en DWORD

gr_buffer=(DWORD*)VirtualAlloc(0,gr_sizescreen<<2, MEM_COMMIT, PAGE_READWRITE);
XFB=(DWORD*)VirtualAlloc(0,gr_sizescreen<<2, MEM_COMMIT, PAGE_READWRITE);

gr_ypitch=gr_ancho=XRES;
gr_alto=YRES;
#ifdef NOMUL
switch(XRES) {
    case 640:   setxyf=setxy640;break;
    case 800:   setxyf=setxy800;break;
    case 1024:  setxyf=setxy1024;break;
    case 1280:  setxyf=setxy1280;break;
    case 1366:  setxyf=setxy1366;break;
    default:    setxyf=setxy;
    }
#endif
//---- poligonos2
fillSol();
initIHY();

//---- colores
gr_color2=0;gr_color1=0xffffff;
col1=0;col2=0xffffff;
gr_solid();

SDL_Init(SDL_INIT_VIDEO);
window = SDL_CreateWindow(":r4",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, XRES, YRES, 0);
renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,XRES, YRES);    

return 0;
}

void gr_redraw(void)
{
SDL_UpdateTexture(texture, NULL,gr_buffer,gr_ancho<<2);
SDL_RenderCopy(renderer, texture, NULL, NULL);
SDL_RenderPresent(renderer);
}

void gr_clrscr(void) 
{
register DWORD *PGR=gr_buffer;
register int c=gr_sizescreen;
while (c>0) { 
      *PGR++=gr_color2;*PGR++=gr_color2;*PGR++=gr_color2;*PGR++=gr_color2;
      *PGR++=gr_color2;*PGR++=gr_color2;*PGR++=gr_color2;*PGR++=gr_color2; 
      c-=8; }
}

void gr_toxfb(void)
{
register DWORD *bgr=gr_buffer,*xgr=XFB;
register int c=gr_sizescreen;
while (c>0) { 
      *xgr++=*bgr++;*xgr++=*bgr++;*xgr++=*bgr++;*xgr++=*bgr++;
      *xgr++=*bgr++;*xgr++=*bgr++;*xgr++=*bgr++;*xgr++=*bgr++; 
      c-=8; }
}

void gr_xfbto(void)
{
register DWORD *bgr=gr_buffer,*xgr=XFB;
register int c=gr_sizescreen;
while (c>0) { 
      *bgr++=*xgr++;*bgr++=*xgr++;*bgr++=*xgr++;*bgr++=*xgr++;
      *bgr++=*xgr++;*bgr++=*xgr++;*bgr++=*xgr++;*bgr++=*xgr++; 
      c-=8; }
}


#define MASK1 (RED_MASK|BLU_MASK)
#define MASK2 (GRE_MASK)

inline DWORD gr_mix(DWORD col,BYTE alpha)
{
register DWORD B=(col & MASK1);
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
void gr_alpha(int a) 
{
if (a>254) { gr_solid();return; }     
gr_pixel=_gr_pixelsa;gr_pixela=_gr_pixelaa;gr_alphav=a;
}

//--------------- DIBUJO DE POLIGONO
void runlenSolido(DWORD *linea);
void runlenLineal(DWORD *linea);
void runlenRadial(DWORD *linea);
void runlenTextura(DWORD *linea);

void (*runlen)(DWORD *linea);

void fillSol(void) { runlen=runlenSolido; }
void fillLin(void) { runlen=runlenLineal; }
void fillRad(void) { runlen=runlenRadial; }
void fillTex(void) { runlen=runlenTextura; }

//------------------------------------
#ifdef NOMUL
#define GR_SET(X,Y) gr_pos=(DWORD*)setxyf(X,Y);
#else
#define GR_SET(X,Y) gr_pos=(DWORD*)gr_buffer+Y*gr_ypitch+X;
#endif

#define GR_X(X) gr_pos+=X;
#define GR_Y(Y) gr_pos+=gr_ypitch*Y;

//------------------------------------
void gr_hline(int x1,int y1,int x2)
{
if (x1<0) x1=0;
if (x2>=gr_ancho) { x2=gr_ancho-1;if (x1>=gr_ancho) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+x2-x1+1;
do { gr_pixel(gr_pos);gr_pos++; } while (gr_pos<pf);
}

void gr_vline(int x1,int y1,int y2)
{
if (y1<0) y1=0;
if (y2>=gr_alto) { y2=gr_alto-1;if (y1>=gr_alto) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+((y2-y1+1)*gr_ancho);
do { gr_pixel(gr_pos);gr_pos+=gr_ypitch; } while (gr_pos<pf);
}

bool gr_clipline(int *X1,int *Y1,int *X2,int *Y2)
{
int C1,C2,V;
if (*X1<0) C1=1; else C1=0;
if (*X1>=gr_ancho) C1|=0x2;
if (*Y1<0) C1|=0x4;
if (*Y1>=gr_alto-1) C1|=0x8;
if (*X2<0) C2=1; else C2=0;
if (*X2>=gr_ancho) C2|=0x2;
if (*Y2<0) C2|=0x4;
if (*Y2>=gr_alto-1) C2|=0x8;
if ((C1&C2)==0 && (C1|C2)!=0) {
	if ((C1&12)!=0) {
		if (C1<8) V=0; else V=gr_alto-2;
		*X1+=(V-*Y1)*(*X2-*X1)/(*Y2-*Y1);*Y1=V;
		if (*X1<0) C1=1; else C1=0;
		if (*X1>=gr_ancho) C1|=0x2;
		}
    if ((C2&12)!=0) {
		if (C2<8) V=0; else V=gr_alto-2;
		*X2+=(V-*Y2)*(*X2-*X1)/(*Y2-*Y1);*Y2=V;
		if (*X2<0) C2=1; else C2=0;
		if (*X2>=gr_ancho) C2|=0x2;
		}
    if ((C1&C2)==0 && (C1|C2)!=0) {
		if (C1!=0) {
			if (C1==1) V=0; else V=gr_ancho-1;
			*Y1+=(V-*X1)*(*Y2-*Y1)/(*X2-*X1);*X1=V;C1=0;
			}
		if (C2!=0) {
			if (C2==1) V=0; else V=gr_ancho-1;
			*Y2+=(V-*X2)*(*Y2-*Y1)/(*X2-*X1);*X2=V;C2=0;
			}
		}
	}
return (C1|C2)==0;
}

//---- con clip
inline void gr_setpixel(int x,int y)
{
if ((unsigned)x>=(unsigned)gr_ancho || (unsigned)y>=(unsigned)gr_alto) return;
register DWORD *gr_pos;
GR_SET(x,y);gr_pixel(gr_pos);
}

inline void gr_setpixela(int x,int y,BYTE a)
{
if ((unsigned)x>=(unsigned)gr_ancho || (unsigned)y>=(unsigned)gr_alto) return;
register DWORD *gr_pos;
GR_SET(x,y);gr_pixela(gr_pos,a);
}

void gr_line(int x1,int y1,int x2,int y2)
{
if (!gr_clipline(&x1,&y1,&x2,&y2)) return;
int dx,dy,sx,d;
if (x1==x2) { if (y1>y2) swap(y1,y2); gr_vline(x1,y1,y2);return; }
if (y1==y2) { if (x1>x2) swap(x1,x2); gr_hline(x1,y1,x2);return; }
if (y1>y2) { swap(x1,x2);swap(y1,y2); }            
dx=x2-x1;dy=y2-y1;
if (dx>0) sx=1; else { sx=-1;dx=-dx; }
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
        GR_Y(1);gr_pixela(gr_pos,ci);
		}
	}
}

void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3)
{
int x11=(x1+x2)>>1,y11=(y1+y2)>>1;
int x21=(x2+x3)>>1,y21=(y2+y3)>>1;
int x22=(x11+x21)>>1,y22=(y11+y21)>>1;
if (abs(x22-x2)+abs(y22-y2)<4)
    { gr_line(x1,y1,x22,y22);gr_line(x22,y22,x3,y3); return; }
gr_spline(x1,y1,x11,y11,x22,y22);
gr_spline(x22,y22,x21,y21,x3,y3);
}

void gr_spline3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
if (abs(x1+x3-x2-x2)+abs(y1+y3-y2-y2)+abs(x2+x4-x3-x3)+abs(y2+y4-y3-y3)<=4)
    { gr_line(x1,y1,x4,y4);return; }
int gx=(x2+x3)/2,gy=(y2+y3)/2;
int b2x=(x3+x4)/2,b2y=(y3+y4)/2;
int a1x=(x1+x2)/2,a1y=(y1+y2)/2;
int b1x=(gx+b2x)/2,b1y=(gy+b2y)/2;
int a2x=(gx+a1x)/2,a2y=(gy+a1y)/2;
int mx=(b1x+a2x)/2,my=(b1y+a2y)/2;
gr_spline3(x1,y1,a1x,a1y,a2x,a2y,mx,my); 
gr_spline3(mx,my,b1x,b1y,b2x,b2y,x4,y4);   
}

// poligono
void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3)
{
//if(abs(x1+x3-x2-x2)+abs(y1+y3-y2-y2)<TOLERANCE)
//    { gr_psegmento(x1,y1,x3,y3); return; }           
int x11=(x1+x2)>>1,y11=(y1+y2)>>1;
int x21=(x2+x3)>>1,y21=(y2+y3)>>1;
int x22=(x11+x21)>>1,y22=(y11+y21)>>1;
if (abs(x22-x2)+abs(y22-y2)<TOLERANCE)
    { gr_psegmento(x1,y1,x22,y22);gr_psegmento(x22,y22,x3,y3); return; }
gr_pspline(x1,y1,x11,y11,x22,y22);
gr_pspline(x22,y22,x21,y21,x3,y3);
}

void gr_pspline3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
if (abs(x1+x3-x2-x2)+abs(y1+y3-y2-y2)+abs(x2+x4-x3-x3)+abs(y2+y4-y3-y3)<TOLERANCE)
    { gr_psegmento(x1,y1,x4,y4);return; }
int gx=(x2+x3)/2,gy=(y2+y3)/2;
int b2x=(x3+x4)/2,b2y=(y3+y4)/2;
int a1x=(x1+x2)/2,a1y=(y1+y2)/2;
int b1x=(gx+b2x)/2,b1y=(gy+b2y)/2;
int a2x=(gx+a1x)/2,a2y=(gy+a1y)/2;
int mx=(b1x+a2x)/2,my=(b1y+a2y)/2;
gr_pspline3(x1,y1,a1x,a1y,a2x,a2y,mx,my); 
gr_pspline3(mx,my,b1x,b1y,b2x,b2y,x4,y4);
}

//**************************************************
//***** DIBUJO DE POLIGONO
//**************************************************
void gr_psegmento(int x1,int y1,int x2,int y2)
{
int t;
if (y1==y2) return;
if (y1>y2) { swap(x1,x2);swap(y1,y2); }
if (y1>=(gr_alto<<BPP) || y2<=0) return;
x1=x1<<FBASE;
x2=x2<<FBASE;
t=(x2-x1)/(y2-y1);
if (y1<0) { x1+=t*(-y1);y1=0; }
if (y2>yMax) yMax=y2;
Segm *ii=&segmentos[cntSegm];
addIHY((y1<<16|cntSegm));
ii->x=x1+t/2;
ii->y=y1;
ii->yfin=y2;
ii->deltax=t;
cntSegm++;
}

//-------------------------------------------------
inline void mixcolor(DWORD col1,DWORD col2,int niv)
{
if (niv<1) { gr_color1=col2;return; }
gr_color1=col1;
if (niv>254) return;
gr_color1=gr_mix(col2,niv);
}

//---------------------------------------------------
inline int dist(int dx,int dy)
{
//return abs(dx)+abs(dy);
register int min,max;
dx=abs(dx);dy=abs(dy);
if (dx<dy) { min=dx;max=dy; } else { min=dy;max=dx; }
return ((max<<8)+(max<<3)-(max<<4)-(max<<1)+(min<<7)-(min<<5)+(min<<3)-(min<<1));
}

//---------------------------------------------------
inline void texturet(int dx,int dy)
{
gr_color1=((int*)mTex)[(dx>>8)&0xff|(dy&0xff00)];
}

//----------------------------------------------
// buffer de covertura para optimizar el pintado
void runlenSolido(DWORD *linea)
{
register DWORD *gr_pos=linea;
int i,v,*s=runlenscan;
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==QFULL) // solido
         { while(i-->0) { gr_pixel(gr_pos);gr_pos++; } }
      else if (v!=0) // transparente
         { v=QALPHA(v);while(i-->0) { gr_pixela(gr_pos,v);gr_pos++; } }
      else { gr_pos+=i; } // saltea
      }
}

void runlenLineal(DWORD *linea)
{
register DWORD *gr_pos=linea;
int i,v,*s=runlenscan;
int r=MA*(-MTX)-MB*((yMin>>BPP)-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==QFULL) // solido
         { while(i-->0) { mixcolor(col1,col2,r>>8);gr_pixel(gr_pos);r+=MA;gr_pos++; } }
      else if (v!=0)// transparente
         { v=QALPHA(v);while(i-->0) { mixcolor(col1,col2,r>>8);gr_pixela(gr_pos,v);r+=MA;gr_pos++; } }
      else  { gr_pos+=i;r+=i*MA; } // saltea
      }
}

void runlenRadial(DWORD *linea)
{
register DWORD *gr_pos=linea;
int i,v,*s=runlenscan;
int rx = MA*(-MTX)-MB*((yMin>>BPP)-MTY);
int ry = MB*(-MTX)+MA*((yMin>>BPP)-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==QFULL) // solido
         { while(i-->0) { mixcolor(col1,col2,dist(rx,ry)>>16);gr_pixel(gr_pos);rx+=MA;ry+=MB;gr_pos++; } }
      else if (v!=0)// transparente
         { v=QALPHA(v);while(i-->0) { mixcolor(col1,col2,dist(rx,ry)>>16);gr_pixela(gr_pos,v);rx+=MA;ry+=MB;gr_pos++; } }
      else  { gr_pos+=i;rx+=i*MA;ry+=i*MB; } // saltea
      }
}

void runlenTextura(DWORD *linea)
{
register DWORD *gr_pos=linea;
int i,v,*s=runlenscan;
int rx = MA*(-MTX)-MB*((yMin>>BPP)-MTY);
int ry = MB*(-MTX)+MA*((yMin>>BPP)-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==QFULL) // solido
         { while(i-->0) { texturet(rx,ry);gr_pixel(gr_pos);rx+=MA;ry+=MB;gr_pos++; } }
      else if (v!=0) // transparente
         { v=QALPHA(v);while(i-->0) { texturet(rx,ry);gr_pixela(gr_pos,v);rx+=MA;ry+=MB;gr_pos++; } }
      else { gr_pos+=i;rx+=i*MA;ry+=i*MB; } // saltea
      }
}


void inserta(int *a) // inserta una copia de a
{
int i,j=*a++;
while ((i=*a)!=0) { *a++=j;j=i; }
*a++=j;*a=0;
}

void inserta2(int *a) // inserta dos copias de a
{
int i,j=*a++,k=j;
while ((i=*a)!=0) { *a++=j;j=k;k=i; }
*a++=j;*a++=k;*a=0;
}

//--------- RUNLEN COVER
void add1pxr(int pos,int val)
{
//if (val==0) return;
int v=*rl;
if (GETLEN(v)==1) {
   *rl=v+val;
   rl++;
} else if (GETPOS(v)==pos) {
   inserta(rl);
   *rl=((v&0xfff001ff)+val)|0x200;//SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;//pos=v
   rl++;*rl=v+0x100000-0x200;
} else if (GETPOSF(v)-1==pos) {
//} else if (GETPOS(*(rl+1))-1==pos) {
   inserta(rl);
   *rl=v-0x200;
   rl++;*rl=SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;
   rl++;
} else {
   inserta2(rl);
   *rl=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
   rl++;*rl=SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;
   rl++;*rl=SETPOS(pos+1)|SETLEN(GETPOSF(v)-(pos+1))|GETVAL(v);
   }
}

void addrlr(int pos,int len)
{
again:
if (len==1) { add1pxr(pos,VALUES);return; }
int v=*rl;
if (GETLEN(v)>len ) {            // ocupa menos            ***   OK
   inserta(rl);
   *rl=SETPOS(pos)|SETLEN(len)|GETVAL(v)+VALUES;
   rl++;*rl=SETPOS(pos+len)|SETLEN(GETLEN(v)-len)|GETVAL(v);
} else if (GETLEN(v)<len ) {     // ocupa mas              ******* OK
   *rl=v+VALUES;
   rl++;pos+=GETLEN(v);len-=GETLEN(v);
   goto again;
//     addrlr(GETLEN(v)+pos,len-GETLEN(v));
} else {                         // ocupa igual            ***** OK
   *rl=v+VALUES;
   rl++;
   }
}

void coverpixels(int xa,int xb)
{
int x0=xa>>BPP,x1=xb>>BPP;
if (x0>=gr_ancho||x1<0) return;
while (*rl!=0 && GETPOS(*rl)<=x0) rl++; // puede ser binaria??
//while (GETPOS(*rl)<=x0) rl++; // puede ser binaria??
rl--;
if (x0==x1) {
   x1=(xb&MASK)-(xa&MASK);
   if (x1!=0) add1pxr(x0,x1);
   return; }
if (x0>=0) { 
   add1pxr(x0,VALUES-(xa&MASK)); // nunca 0 => siempre linea al principio
   x0++;if(x0>=gr_ancho) return; }
else { x0=0;rl=runlenscan; }
int largo;
if (x1>=gr_ancho) {
   largo=gr_ancho-x0; 
   if (largo>0) addrlr(x0,largo);
} else { 
   largo=x1-x0;
   if (largo>0) addrlr(x0,largo);
   xb&=MASK;
   if (xb!=0) add1pxr(x1,xb);
   }
}


//-----------------------------------------------------------------------
void sortactive(Segm **j) // ordena ultimo elemento
{
Segm *v=*j;
int vx=v->x;
if ((*(j-1))->x<=vx) return;
*j=*(j-1);j--;
while ((*(j-1))->x>vx) { *j=*(j-1);j--; }
*j=v;
}

void addactive(Segm *s)
{
*activelast=s;
sortactive(activelast);
activelast++;
}

void remactive(void)
{
Segm **j=&activelist[1];     
while (j<activelast)  {
    if (yMin==(*j)->yfin) goto slice;
    j++; }     
return;
slice:
Segm **h=j+1;
while (h<activelast)  {
    if (yMin<(*h)->yfin) 
       { *j=*h;j++; }
    h++; }     
activelast=j;
}     

void gr_drawPoli(void)
{
if (cntSegm<2)  { initIHY();return; }
Segm **jj;
yMin=segmentos[(heapIHY()&0xffff)].y;
int i; 
if (yMax>gr_alto<<BPP) { yMax=gr_alto<<BPP; }
DWORD *gr_pant=(DWORD*)gr_buffer+(yMin>>BPP)*gr_ypitch;
for (;yMin<yMax;) {
  *runlenscan=SETLEN(gr_ancho+1);
  *(runlenscan+1)=0;
  
  for (i=VALUES;i!=0;--i) {
    while (heapIHY()>>16==yMin)
      { addactive(&segmentos[remIHY()&0xffff]); }
    rl=runlenscan;
    for (jj=&activelist[1];jj+1<activelast;jj+=2) {
        coverpixels(((*jj)->x)>>FBASE,((*(jj+1))->x)>>FBASE);
        }
    yMin++;
    // quita los que se terminaron
    remactive();
    // avanza y ordena
    for(jj=&activelist[1];jj<activelast;jj++) {
        (*jj)->x+=(*jj)->deltax;sortactive(jj); 
        }
    }              
  while (*rl!=0) rl++;*(rl-1)=0;  // quito el ultimo espacio
  runlen(gr_pant);  
  gr_pant+=gr_ypitch;  
  }
initIHY();
}
