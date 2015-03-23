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
#include <string.h>
#include "graf.h"

//---- variables internas
int gr_ancho,gr_alto;
int gr_sizescreen;	// tamanio de pantalla
DWORD gr_color1,gr_color2,col1,col2;
int gr_ypitch;

int MA,MB,MTX,MTY; // matrix de transformacion

//---- variables para dibujo de poligonos
typedef struct {
       int y,x,yfin,deltax;
       } Segm;

Segm segmentos[1024];
Segm **pact;
Segm *actual[256]; // segmentos actuales

Segm **xquisc;
Segm *xquis[256]; // cada linea

int cntSegm=0;
int yMin,yMax;

#define FBASE 8
#define RED_MASK 0xFF0000
#define GRE_MASK 0xFF00
#define BLU_MASK 0xFF

SDL_Surface *gr_screen;
DWORD *gr_buffer;		// buffer de pantalla
BYTE gr_alphav;

//---- rutinas de inicio
int gr_init(void)
{
gr_ypitch=gr_ancho=gr_screen->w;
gr_alto=gr_screen->h;
gr_sizescreen=(gr_ancho*gr_alto)>>2;// tamanio en DWORD
gr_buffer=(DWORD*)gr_screen->pixels;    
//---- poligonos2
cntSegm=0;
yMin=gr_alto+1;
yMax=-1;
fillSol();
//---- colores
gr_color2=0;gr_color1=0xffffff;
gr_solid();
return 0;
}

void gr_fin(void) { }
void gr_redraw(void) { SDL_Flip(gr_screen); }
void gr_clrscr(void) { SDL_FillRect(gr_screen,NULL,gr_color2); }

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
void gr_alpha(void) {gr_pixel=_gr_pixelsa;gr_pixela=_gr_pixelaa;}

//--------------- DIBUJO DE POLIGONO
void _FlineaSolido(int y,Segm *m1,Segm *m2);
void _FlineaDL(int y,Segm *m1,Segm *m2);
void _FlineaDR(int y,Segm *m1,Segm *m2);

void (*fillpoly)(int y,Segm *m1,Segm *m2);

void fillSol(void) { fillpoly=_FlineaSolido; }
void fillLin(void) { fillpoly=_FlineaDL; }
void fillRad(void) { fillpoly=_FlineaDR; }

//------------------------------------
#define GR_SET(X,Y) gr_pos=(DWORD*)gr_buffer+Y*gr_ypitch+X;
#define GR_X(X) gr_pos+=X;
#define GR_Y(Y) gr_pos+=gr_ypitch*Y;
//------------------------------------

void gr_hlined(int x1,int y1,int x2,const BYTE a1,const BYTE a2)
{
int alpha=a1<<8;
int da=((a2-a1)<<8)/(x2-x1);
if (x1<0) { alpha+=da*(-x1);x1=0; }
if (x2>=gr_ancho) { x2=gr_ancho-1;if (x1>=gr_ancho) return; }
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
if (y2>=gr_alto) { y2=gr_alto-1;if (y1>=gr_alto) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+((y2-y1+1)*gr_ancho);
do {
	gr_pixela(gr_pos,alpha>>8);gr_pos+=gr_ypitch;alpha+=da;
} while (gr_pos<pf);
}

//---- clip
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
//        if (y1<gr_alto-1) { // 640x480 necesita
        GR_Y(1);gr_pixela(gr_pos,ci); 
//                        }
		}
	}
}

inline int abs(int a ) 
{
return (a+(a>>31))^(a>>31);       
}
       

//recta(x1,y1,x2,y2,x3,y3)<1000)
inline int recta(int x1,int y1,int x2,int y2,int x3,int y3)
{
return abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
}

inline int recta2(int x1,int y1,int x2,int y2,int x3,int y3)
{
return abs(x2-x1) + abs(y2-y1) + abs(x3-x2) + abs(y3-y2);
}

void gr_splineiter(int x1,int y1,int x2,int y2,int x3,int y3)
{
//if (recta2(x1,y1,x2,y2,x3,y3)<(1<<4)) 
if (recta(x1,y1,x2,y2,x3,y3)<1000)
    { gr_line(x1>>4,y1>>4,x3>>4,y3>>4); return; }
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

// poligono
void gr_iteracionSP(long x1,long y1,long x2,long y2,long x3,long y3)
{
//if (recta2(x1,y1,x2,y2,x3,y3)<(1<<7))
if (recta(x1,y1,x2,y2,x3,y3)<1000)
    { gr_psegmento(x1>>4,y1>>4,x3>>4,y3>>4);return; }
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

//**************************************************
//***** DIBUJO DE POLIGONO
//**************************************************
void gr_psegmento(int x1,int y1,int x2,int y2)
{
int t;
if (y1==y2) return;
if (y1>y2) { t=x1;x1=x2;x2=t;t=y1;y1=y2;y2=t; }
if (y1>=gr_alto || y2<=0) return;
x1=x1<<FBASE;
x2=x2<<FBASE;
t=(x2-x1)/(y2-y1);
if (y1<0) { x1+=t*(-y1);y1=0; }
if (yMin>y1) yMin=y1;
if (yMax<y2) yMax=y2;
Segm *ii=&segmentos[cntSegm-1];
while (ii>=segmentos && ii->y>y1 ) {
  *(ii+1)=*(ii);ii--;
  }
ii++;
ii->x=x1+((1<<FBASE)>>1);
ii->y=y1;
ii->yfin=y2;
ii->deltax=t;
cntSegm++;
}

void _FlineaSolido(int y,Segm *m1,Segm *m2)
{
register DWORD *gr_pos;
register int cnt,alpha,da;
int x1,x2,x3,x4;
if (m1->deltax<0)
   { x1=m1->x+m1->deltax;x2=m1->x; }
else
   { x2=m1->x+m1->deltax;x1=m1->x; }
if (m2->deltax<0)
   { x3=m2->x+m2->deltax;x4=m2->x; }
else
   { x4=m2->x+m2->deltax;x3=m2->x; }

int ex1=x1>>FBASE,ex2=x2>>FBASE;
int ex3=x3>>FBASE,ex4=x4>>FBASE;
if (ex4<0 || ex1>gr_ancho ) return;
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)
if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(BYTE)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>gr_ancho) ex2=gr_ancho;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }
if (ex2==ex4) return;
if (ex3>=0) { // lleno
  if (ex3>ex2) {
    if (ex2<0) ex2=0;
    if (ex3>gr_ancho) ex3=gr_ancho;
    cnt=ex3-ex2;if (cnt>0) cnt--;
    while (cnt--) { gr_pixel(gr_pos);gr_pos++; }
   }
  }
if (ex4==ex3) { // punto solo
  gr_pixela(gr_pos,(BYTE)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }    
  if (ex4>gr_ancho) ex4=gr_ancho;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

inline void mixcolor(DWORD col1,DWORD col2,int niv)
{
gr_color1=col1;
//niv=niv&0xff;
//niv=abs(niv);
if (niv<1) { gr_color1=col2;return; }
if (niv>254) return;
gr_color1=gr_mix(col2,niv);
}

void _FlineaDL(int y,Segm *m1,Segm *m2)
{
register DWORD *gr_pos;
register int cnt,alpha,da;
int x1,x2,x3,x4;
if (m1->deltax<0)
   { x1=m1->x+m1->deltax;x2=m1->x; }
else
   { x2=m1->x+m1->deltax;x1=m1->x; }
if (m2->deltax<0)
   { x3=m2->x+m2->deltax;x4=m2->x; }
else
   { x4=m2->x+m2->deltax;x3=m2->x; }

int ex1=x1>>FBASE,ex2=x2>>FBASE;
int ex3=x3>>FBASE,ex4=x4>>FBASE;
if (ex4<0 || ex1>gr_ancho ) return;

int r=MA*(ex2-MTX)-MB*(y-MTY);
mixcolor(col1,col2,r>>8);

if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)
if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(BYTE)((x1+x2)>>1));gr_pos++;
    if (ex2==ex4) return;
  } else { // degrade
    alpha=0;da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>gr_ancho) ex2=gr_ancho;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }
if (ex4==ex2) return;
if (ex3>=0) { // lleno
  if (ex3>ex2) {
    if (ex2<0) { r+=MA*(-ex2);ex2=0; }
    if (ex3>gr_ancho) ex3=gr_ancho;
    cnt=ex3-ex2;if (cnt>0) cnt--;
    while (cnt--) { 
        mixcolor(col1,col2,r>>8);
        gr_pixel(gr_pos);gr_pos++; 
        r+=MA;
        }
   }
  }
if (ex4==ex3) { // punto solo
  gr_pixela(gr_pos,(BYTE)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }    
  if (ex4>gr_ancho) ex4=gr_ancho;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

inline int dist(int dx,int dy)
{
//return abs(dx)+abs(dy);
register int min,max;
dx=abs(dx);dy=abs(dy);
if (dx<dy) { min=dx;max=dy; } else { min=dy;max=dx; }
return ((max<<8)+(max<<3)-(max<<4)-(max<<1)+
        (min<<7)-(min<<5)+(min<<3)-(min<<1));
}

void _FlineaDR(int y,Segm *m1,Segm *m2)
{
register DWORD *gr_pos;
register int cnt,alpha,da;
int x1,x2,x3,x4;
if (m1->deltax<0)
   { x1=m1->x+m1->deltax;x2=m1->x; }
else
   { x2=m1->x+m1->deltax;x1=m1->x; }
if (m2->deltax<0)
   { x3=m2->x+m2->deltax;x4=m2->x; }
else
   { x4=m2->x+m2->deltax;x3=m2->x; }

int ex1=x1>>FBASE,ex2=x2>>FBASE;
int ex3=x3>>FBASE,ex4=x4>>FBASE;
if (ex4<0 || ex1>gr_ancho ) return;
int rx = MA*(ex2-MTX)-MB*(y-MTY);
int ry = MB*(ex2-MTX)+MA*(y-MTY);
mixcolor(col1,col2,dist(rx,ry)>>16);
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)
if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(BYTE)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>gr_ancho) ex2=gr_ancho;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }
if (ex4==ex2) return;
if (ex3>=0) { // lleno
  if (ex3>ex2) {
    if (ex2<0) { rx+=MA*(-ex2);ry+=MB*(-ex2);ex2=0; }
    if (ex3>gr_ancho) ex3=gr_ancho;
    cnt=ex3-ex2;if (cnt>0) cnt--;
    while (cnt--) { 
        mixcolor(col1,col2,dist(rx,ry)>>16);
        gr_pixel(gr_pos);gr_pos++; 
        rx+=MA;
        ry+=MB;
        }
   }
  }
if (ex4==ex3) { // punto solo
  gr_pixela(gr_pos,(BYTE)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }    
  if (ex4>gr_ancho) ex4=gr_ancho;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

//----------------------------------------------------------
void addlin(Segm *ii,int y) 
{
register int xr=ii->x;//+ii->deltax;
if (y==ii->y) xr+=ii->deltax;
Segm **cursor=(xquisc-1);
while (cursor>=xquis && (*cursor)->x>xr) {
      *(cursor+1)=*cursor;cursor--;
      }
*(cursor+1)=ii;
xquisc++;
}

void gr_drawPoli(void)
{
Segm **jj;
Segm *scopia=segmentos;
pact=actual;
segmentos[cntSegm].y=-1;
if (yMax>gr_alto) { yMax=gr_alto; }
for (;yMin<yMax;) {
    while (scopia->y==yMin) {
          *pact=scopia;pact++;scopia++;
          }
    xquisc=xquis;
    jj=actual;
    while (jj<pact) {
          addlin(*jj,yMin);
          jj++;
          }
    for (jj=xquis;jj+1<xquisc;jj+=2) {
//        gr_hline((*jj)->x>>FBASE,yMin,(*(jj+1))->x>>FBASE);
          fillpoly(yMin,*jj,*(jj+1));
          }
    jj=actual;
    yMin++;
    while (jj<pact) {
          if (yMin<(*jj)->yfin) {
             (*jj)->x+=(*jj)->deltax;
             jj++;
          } else {
            *jj=*(pact-1);
             pact--;
             }
          }
    }    
yMin=gr_alto+1;
yMax=-1;
cntSegm=0;
}

void fillcent(int mx,int my)
{
MTX=mx;MTY=my;
}

void fillmat(int a,int b)
{
MA=a;MB=b;
}

void fillcol(DWORD c1,DWORD c2)
{
col1=c1;col2=c2;
}

/*

///* 16 bit assumed... easy to change
void GraphicDevice::fillLineBitmap(FillStyleDef *f, long y, long start, long end)
{
int n;
long x1,y1,dx,dy;
Matrix *m = &f->bitmap_matrix;
Bitmap *b = f->bitmap;
unsigned char *pixels;
unsigned short *p;
Color *cmap;
long pixbpl;
TYPE pixel;
int offset;
unsigned char *alpha_table;
if (!b) return;
if (clip(y,start,end)) return;
start /= FRAC;
end /= FRAC;
n = end - start;
p = (unsigned short *) (this->canvasBuffer + this->bpl*y + start * 2);
//  /* the coordinates in the image are normalized to 16 bits 
x1 = (long) (m->a * start + m->b * y + m->tx);
y1 = (long) (m->c * start + m->d * y + m->ty);
dx = (long) (m->a);
dy = (long) (m->c);
pixels = b->pixels;
pixbpl = b->bpl;
cmap = f->cmap;
    while (n) {
        if (x1 >= 0 && y1 >= 0 && (x1 >> 16) < b->width && (y1 >> 16) < b->height) {
            pixel = cmap[pixels[(y1 >> 16) * pixbpl + (x1 >> 16)]].pixel;
            *p = pixel;
            }
        x1 += dx;
        y1 += dy;
        p++;
        n--;
        }
    }
}


///////////// PLATFORM INDEPENDENT
void GraphicDevice::fillLineRG(Gradient *grad, long y, long start, long end)
{
long X,dx,r,Y,dy;
long dist2;
register long   n;
Color *cp,*ramp;
TYPE *line;							
TYPE *point;							
Matrix *m = &grad->imat;
unsigned int start_alpha,end_alpha;
if (clip(y,start,end)) return;
start_alpha = 255 - ((start & (FRAC-1)) << (8-FRAC_BITS));
end_alpha = (end & (FRAC-1)) << (8-FRAC_BITS);
start /= FRAC;
end /= FRAC;
n = end-start;
X = (long) (m->a * start + m->b * y + m->tx);
Y = (long) (m->c * start + m->d * y + m->ty);
dx = (long) (m->a);
dy = (long) (m->c);
ramp = grad->ramp;
line = (TYPE *)(canvasBuffer + bpl*y);
point = &line[start];
    while (n--) {					
		dist2 = ((X>>16)*(X>>16))+((Y>>16)*(Y>>16));
		if ((unsigned long)dist2 >= 65536) {
            r = 255;					
		} else {						
            r= SQRT[dist2];	
		}
        cp = &ramp[r];
		*point = mix_alpha(*point, cp->pixel, cp->alpha);
		point++;
		X += dx;						
		Y += dy;						
        }		
}
*/
