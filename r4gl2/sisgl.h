#ifndef SISGL_H
#define SISGL_H

#ifndef linux
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#endif

extern int XRES;
extern int YRES;
extern int FRES;

int inigl(int w,int h,int f);
void endgl(void);
void swapgl(void);


//extern DWORD *gr_buffer;		// buffer de pantalla

typedef union {
        struct { unsigned char r,g,b,a; } b8;
        unsigned int c32;
} color32;

extern color32 gr_color1,gr_color2;
extern BYTE gr_alphav;

void linegl(int x1,int y1,int x2,int y2,int col1,int col2);
void poligl(void);

void upd_evt(void); 
void clsevt(void);
int getevt(void); // 0 = vacio

long msys_timerGet(void);

#endif
