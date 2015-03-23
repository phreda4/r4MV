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
#ifndef MAT_H
#define MAT_H

#include <stdlib.h>

//#define interpola(a,b,t1,t2) ((t2>t1)?(a*t1/t2+b*(t2-t1)/t2):(a*t1/t2+b*(t1-t2)/t2))
// intervalo 0..t2
#define interpola(a,b,t1,t2) (a*t1/t2+b*(t2-t1)/t2)
//#define interpolate(v1,v2,mix) (v1*mix+v2*(1-mix))

inline int distance(int dx,int dy)
{
int min,max;
if (dx<0) dx=-dx;
if (dy<0) dy=-dy;
if (dx<dy) { min=dx;max=dy; } else { min=dy;max=dx; }
return (((max<<8)+(max<<3)-(max<<4)-(max<<1)+(min<<7)-(min<<5)+(min<<3)-(min<<1))>>8);
}

inline int dist(int x1,int y1,int x2,int y2)
{
return distance(x1-x2,y1-y2);
}

inline long recta(int x1,int y1,int x2,int y2,int x3,int y3)
{
int dx1=x2-x1,dy1=y2-y1;
int dx2=x3-x1,dy2=y3-y1;
return abs(dx1*dy2-dx2*dy1);
}

inline int recta2(int x1,int y1,int x2,int y2,int x3,int y3)
{
int dx1=x2-x1,dy1=y2-y1;
int dx2=x3-x1,dy2=y3-y1;
if (abs(dx1)>abs(dx2) || abs(dy1)>abs(dy2))
	return 1000;
return abs(dx1*dy2-dx2*dy1);
}

inline int recta4(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
long dx1=x2-x1,dy1=y2-y1;
long dx2=x3-x1,dy2=y3-y1;
long dx3=x4-x1,dy3=y4-y1;
return abs(dx1*dy2-dx2*dy1)+abs(dx1*dy3-dx3*dy1);
}

inline int teta(int x1,int y1,int x2,int y2)// angulo del vector
{
int dx=x2-x1,ax=abs(dx);
int dy=y2-y1,ay=abs(dy);
if (ax+ay==0) return 0;
int t=(dy*900)/(ax+ay);
if (dx<0) t=(2*900)-t; else if (dy<0) t=(4*900)+t;
return t;
}

inline int angle(int x1,int y1,int x2,int y2,int x3,int y3) // angulo entre vectores
{
return abs(teta(x1,y1,x2,y2)-teta(x2,y2,x3,y3));
}

#endif
