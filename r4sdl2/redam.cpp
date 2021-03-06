/* * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2006, Pablo Hugo Reda <pabloreda@gmail.com>, Mar del Plata, Argentina
 * All rights reserved.
*/
//  Reda4 interprete y compilador  pabloreda@gmail.com
//  Version SDL (winylin)
//
// PHREDA 29/12/2005 Primera version
// SEBAS Desimone Correcciones Linux
// Charles Melice improve speed
// PHREDA 23/4/2007 Error para archivo (comentado)
// PHREDA 23/8/2007 AND? NAND? *>>
// PHREDA 18/3/2008 nuevas irq
// PHREDA 18/7/2008 bug lastcall fix
// PHREDA 1/8/2008  MOVE,MOVE>,CMOVE,CMOVE> por velocidad, decimales fixedpoint
// PHREDA 9/8/2008  separar line para runtime error, manejo de signal
// PHREDA 23/8/2008 switches
// PHREDA 13/12/2008 fuera DLL!! version WINE
// rest in googlecode http://code.google.com/p/reda4/

#include <SDL.h>

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wininet.h>

//#define LOGMEM
//#define OPENGL
//#define RUNER // quita el compilador (6kb)

#define FMOD
#define PRINTER
//#define NET

#include "graf.h"
#include "sound.h"

SDL_Event event;

HWND        hWnd;
WNDCLASSA   wc;
MSG         msg;
DEVMODE     devmodo;
DWORD       dwStyle;
RECT        rec; 
int         active;

#ifdef NET
HINTERNET hOpen, hURL;
char *buffData;
unsigned long readData;
#endif

//----------- printer
DOCINFO di;
int lpError;

HDC	phDC;
LOGFONT plf;
HGDIOBJ hfnt, hfntPrev;
int cWidthPels,cHeightPels;
SIZE tsize;

HDC tmpDC = 0;
BITMAP info = { 0 };
HBITMAP hBmp = 0;	

//---------- SYSTEM word
PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
STARTUPINFO StartupInfo; //This is an [in] parameter

//------------
static const char wndclass[] = ":r4";

char setings[256];
int rebotea;

//#define ULTIMOMACRO 6
//char *macrose[]={ ";","LIT","ADR","CALL","JMP","JMPR" };

//-- mapa de scancode extendido (quien dise�o esto???)
char mapex[]={
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
 48, 49, 50, 51, 52, 69, 70, 71, 56, 73, 74, 75, 76, 77, 78, 79, 
 80, 81, 82, 83, 84, 85, 86,103,104, 89, 90, 91, 92, 93, 94, 95,
 96, 97, 98, 99, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 
 96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127};

char *macros[]={// directivas del compilador
";","(",")",")(","[","]","EXEC",
"0?","+?","-?","1?","=?","<?",">?","<=?",">=?","<>?","AND?","NAND?",
"DUP","DROP","OVER","PICK2","PICK3","PICK4","SWAP","NIP","ROT", //--- pila
"2DUP","2DROP","3DROP","4DROP","2OVER","2SWAP",
">R","R>","R","R+","R@+","R!+","RDROP",//--- pila direcciones
"AND","OR","XOR","NOT",                //--- logicas
"+","-","*","/","*/","*>>","/MOD","MOD","ABS", //--- aritmeticas
"SQRT","CLZ","<</",
"NEG","1+","4+","1-","2/","2*","<<",">>",
"@","C@","W@","!","C!","W!","+!","C+!","W+!", //--- memoria
"@+","!+","C@+","C!+","W@+","W!+",
"MOVE","MOVE>","CMOVE","CMOVE>",//-- movimiento de memoria
"MEM",
"FFIRST","FNEXT",
"LOAD","SAVE","APPEND",//--- memoria,bloques
"UPDATE",
"XYMOUSE","BMOUSE", //"MOUSE",     //-------- mouse
"KEY!", "KEY",          //-------- teclado
"CNTJOY","GETJOY",     //-------- joystick

"MSEC","TIME","DATE","END","RUN",//--- sistema
"SW","SH","CLS","REDRAW","FRAMEV",//--- pantalla
"SETXY","PX+!","PX!+","PX@",
"XFB",">XFB","XFB>",
"PAPER","INK","INK@","ALPHA", //--- color
"OP","LINE","CURVE","CURVE3","PLINE","PCURVE","PCURVE3","POLI",//--- dibujo
"FCOL","FCEN","FMAT","SFILL","LFILL","RFILL","TFILL",
//---------------------
#ifdef FMOD
"SLOAD","SPLAY","SINFO","SSET",    //-------- sonido
#else
"ISON!","SBO","SBI",    // Sound Buffer Ouput/input
#endif
//--------------------- red
#ifdef NET
"OPENURL",
#endif
//"TIMER",            //------- timer
//---------------------
#ifdef PRINTER
"DOCINI","DOCEND","DOCAT","DOCLINE","DOCTEXT","DOCFONT","DOCBIT","DOCRES","DOCSIZE", //-- impresora
#endif
"SYSTEM",
""};

// instrucciones de maquina (son compilables a assembler)
enum {
FIN,LIT,ADR,CALL,JMP,JMPR, EXEC,//hasta JMPR no es visible
IF,PIF,NIF,UIF,IFN,IFL,IFG,IFLE,IFGE,IFNO,IFAND,IFNAND,// condicionales 0 - y +  y no 0
DUP,DROP,OVER,PICK2,PICK3,PICK4,SWAP,NIP,ROT,
DUP2,DROP2,DROP3,DROP4,OVER2,SWAP2,//--- pila
TOR,RFROM,ERRE,ERREM,ERRFM,ERRSM,ERRDR,//--- pila direcciones
AND,OR,XOR,NOT,//--- logica
SUMA,RESTA,MUL,DIV,MULDIV,MULSHR,DIVMOD,MOD,ABS,
CSQRT,CLZ,CDIVSH,
NEG,INC,INC4,DEC,DIV2,MUL2,SHL,SHR,//--- aritmetica
FECH,CFECH,WFECH,STOR,CSTOR,WSTOR,INCSTOR,CINCSTOR,WINCSTOR,//--- memoria
FECHPLUS,STOREPLUS,CFECHPLUS,CSTOREPLUS,WFECHPLUS,WSTOREPLUS,
MOVED,MOVEA,CMOVED,CMOVEA,
MEM, 
FFIRST,FNEXT,
LOAD,SAVE,APPEND,//--- bloques de memoria, bloques
UPDATE,
XYMOUSE,BMOUSE, //MOUSE,
SKEY, KEY,
CNTJOY,GETJOY,
MSEC,TIME,IDATE,SISEND,SISRUN,//--- sistema
WIDTH,HEIGHT,CLS,REDRAW,FRAMEV,//--- pantalla
SETXY,MPX,SPX,GPX,
VXFB,TOXFB,XFBTO,
COLORF,COLOR,COLORA,ALPHA,//--- color
OP,LINE,CURVE,CURVE3,PLINE,PCURVE,PCURVE3,POLI,//--- dibujo
FCOL,FCEN,FMAT,SFILL,LFILL,RFILL,TFILL, //--- pintado

#ifdef FMOD
SLOAD,SPLAY,SINFO,SSET,
#else
IRSON,SBO,SBI,
#endif

#ifdef NET
OPENURL,
#endif

//ITIMER,//--- timer

#ifdef PRINTER  //-- impresora
DOCINI,DOCEND,DOCMOVE,DOCLINE,DOCTEXT,DOCFONT,DOCBIT,DOCRES,DOCSIZE,
#endif
SYSTEM,
ULTIMAPRIMITIVA// de aqui en mas.. apila los numeros 0..255-ULTIMAPRIMITIVA
};

char pilaexec[1024];
char *pilaexecl;

char *compilastr="";
char *bootstr="main.txt";
char *exestr="main.r4x";

//---------------------- Memoria de reda4
int gx1=0,gy1=0;// coordenadas de linea
BYTE *bootaddr;
FILE *file;
//---- eventos

char linea[1024];// 1k linea
char error[1024];
//---- eventos teclado y raton
int SYSXYM=0;
int SYSBM=0;
int SYSKEY=0;

//----- Directorio

//---- Directory
//DIR *dp=0;
//struct dirent *dirp;

WIN32_FIND_DATA ffd;
HANDLE hFind=NULL;

/*
typedef struct _WIN32_FIND_DATA {
  DWORD    dwFileAttributes;    // +0
  FILETIME ftCreationTime;      // +4
  FILETIME ftLastAccessTime;    // +12
  FILETIME ftLastWriteTime;     // +20
  DWORD    nFileSizeHigh;       // +28
  DWORD    nFileSizeLow;        // +32
  DWORD    dwReserved0;         // +36
  DWORD    dwReserved1;         // +40
  TCHAR    cFileName[MAX_PATH]; // +44
  TCHAR    cAlternateFileName[14];
*/


//---- Date & Time
time_t sit;
tm *sitime;
//---- dato y programa
int cntdato;
int cntprog;
BYTE *memlibre;
//----- PILAS
int PSP[1024];// 1k pila de datos
BYTE *RSP[1024];// 1k pila de direcciones
BYTE ultimapalabra[]={ SISEND };
//--- Memoria
BYTE prog[1024*1024];// 1MB de programa
BYTE data[1024*1024*512];// 512 MB de datos

void mimemset(char *p,char v,int c)
{
for (;c>0;c--,p++) *p=v;
}

///////////////////////////////////////////////////////////////////////
//...............................................................................
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
switch (message) {     // handle message
    case WM_MOUSEMOVE:
         SYSXYM=lParam;//         SYSEVENT=SYSirqmouse;
         break;
    case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:
    case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:
         SYSBM=wParam; //        SYSEVENT=SYSirqmouse;
         break;
    case WM_SYSKEYUP:
    case WM_KEYUP:        // (lparam>>24)     ==1 keypad
        lParam>>=16;
        if ((lParam&0x100)!=0) lParam=mapex[lParam&0x7f];
        SYSKEY=(lParam&0x7f)|0x80; //        SYSEVENT=SYSirqteclado;
        break;
    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
        lParam>>=16;
        if ((lParam&0x100)!=0) lParam=mapex[lParam&0x7f];
        SYSKEY=lParam&0x7f; //        SYSEVENT=SYSirqteclado;
        break;
//    case WM_TIMER:
//        SYSEVENT=SYSirqtime;
//        break;
//---------System
   case WM_CLOSE:
        rebotea=2;// no reinicia
   case WM_DESTROY:
        SYSKEY=-1;
        return 1;
  default:
       return DefWindowProc(hWnd,message,wParam,lParam);
  }
return 0;
	// salvapantallas
//	if( uMsg==WM_SYSCOMMAND && (wParam==SC_SCREENSAVE || wParam==SC_MONITORPOWER) )	return( 0 );
}

//---- Graba y carga imagen
#ifndef RUNER
void saveimagen(char *nombre)
{
file=fopen(nombre,"wb");if (file==NULL) return;
fwrite(&bootaddr,sizeof(int),1,file); // -cntprog
fwrite(&cntdato,sizeof(int),1,file);
fwrite(&cntprog,sizeof(int),1,file);
fwrite((void*)prog,1,cntprog,file);
fwrite((void*)data,1,cntdato,file);
fclose(file);
}
#endif

void loadimagen(char *nombre)
{
bootaddr=0;     
file=fopen(nombre,"rb");if (file==NULL) return;
fread(&bootaddr,sizeof(int),1,file); // -cntprog
fread(&cntdato,sizeof(int),1,file);
fread(&cntprog,sizeof(int),1,file);
fread((void*)prog,1,cntprog,file);
fread((void*)data,1,cntdato,file);
memlibre=data+cntdato;
fclose(file);
}

//---- el ultimo recurso
#ifdef LOGMEM
void ldebug(char *n)
{ FILE *stream;
if((stream=fopen("log.txt","a"))==NULL) return;
fputs(n,stream); if(fclose(stream)) return; }

void dumpest(void) {ldebug(linea);}
#endif

#ifdef __GNUC__
#define iclz32(x) __builtin_clz(x)
#else
static inline int popcnt(int x)
{
    x -= ((x >> 1) & 0x55555555);
    x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
    x = (((x >> 4) + x) & 0x0f0f0f0f);
    x += (x >> 8);
    x += (x >> 16);
    return x & 0x0000003f;
}
static inline int iclz32(int x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return 32 - popcnt(x);
}
#endif

// http://www.devmaster.net/articles/fixed-point-optimizations/
static inline int isqrt32(int value)
{
if (value==0) return 0;
int g = 0;
int bshft = (31-iclz32(value))>>1;  // spot the difference!
int b = 1<<bshft;
do {
	int temp = (g+g+b)<<bshft;
	if (value >= temp) { g += b;value -= temp;	}
	b>>=1;
} while (bshft--);
return g;
}

// http://www.cc.utah.edu/~nahaj/factoring/isqrt.legalize.c.html
/* Integer square root by Halleck's method, with Legalize's speedup */
/*
static int isqrt32(int x)
{
if (x<1) return 0;
int squaredbit, remainder, root;
squaredbit  = (long) ((((unsigned long) ~0L) >> 1) & ~(((unsigned long) ~0L) >> 2));
remainder = x;  root = 0;
while (squaredbit > 0) {
 if (remainder >= (squaredbit | root)) {
     remainder -= (squaredbit | root);
     root >>= 1; root |= squaredbit;
 } else {
     root >>= 1;
 }
 squaredbit >>= 2;
}
return root;
}
*/

//---------------------------------------------------------------
int interprete(BYTE *codigo)// 1=recompilar con nombre en linea
{
if (codigo==NULL) return -1;
register int TOS;			// Tope de la pila PSP
register int *NOS;			// Next of stack
register BYTE **R;			// return stack
BYTE *IP=codigo;	// lugar del programa // ebx
int W,W1;			// palabra actual y auxiliar
int *vcursor;

//SYSirqmouse=0;
//SYSirqteclado=0;
//SYSirqjoystick=0;
//SYSirqsonido=0;
//SYSirqred=0;
//SYSEVENT=0;
//kcnt=kcur=0;
//mcnt=1;

vcursor=(int*)gr_buffer;

R=RSP;*R=(BYTE*)&ultimapalabra;
NOS=PSP;*NOS=TOS=0;
while (true)  {// Charles Melice  suggest next:... goto next; bye !
    W=(BYTE)*IP++;
	switch (W) {// obtener codigo de ejecucion
	case FIN: IP=*R;R--;continue;
    case LIT: NOS++;*NOS=TOS;TOS=*(DWORD*)IP;IP+=sizeof(int);continue;
    case ADR: NOS++;*NOS=TOS;W=*(DWORD*)IP;IP+=sizeof(int);TOS=*(DWORD*)W;continue;
    case CALL: W=*(DWORD*)IP;IP+=sizeof(int);R++;*R=IP;IP=(BYTE*)W;continue;
	case JMP: W=*(int*)IP;IP=(BYTE*)W;continue;
    case JMPR: W=*(char*)IP;W++;IP+=W;continue;
//-hasta aca solo lo escribe el compilador
//--- condicionales
	case IF: W=*(char*)IP;IP++;if (TOS!=0) IP+=W; continue;
    case PIF: W=*(char*)IP;IP++;if (TOS&0x80000000) IP+=W; continue;
	case NIF: W=*(char*)IP;IP++;if (!(TOS&0x80000000)) IP+=W; continue;
    case UIF: W=*(char*)IP;IP++;if (TOS==0) IP+=W; continue;
    case IFN: W=*(char*)IP;IP++;if (TOS!=*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
    case IFNO: W=*(char*)IP;IP++;if (TOS==*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFL: W=*(char*)IP;IP++;if (TOS<=*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFG: W=*(char*)IP;IP++;if (TOS>=*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFLE: W=*(char*)IP;IP++;if (TOS<*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFGE: W=*(char*)IP;IP++;if (TOS>*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFAND: W=*(char*)IP;IP++;if (!(TOS&*NOS)) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFNAND: W=*(char*)IP;IP++;if (TOS&*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
//--- fin condicionales dependiente de bloques    
	case EXEC:R++;*R=IP;IP=(BYTE*)TOS;TOS=*NOS;NOS--;continue;
//--- pila de datos
	case DUP: NOS++;*NOS=TOS;continue;
    case DROP: TOS=*NOS;NOS--;continue;
    case OVER: NOS++;*NOS=TOS;TOS=*(NOS-1); continue;
	case PICK2: NOS++;*NOS=TOS;TOS=*(NOS-2); continue;
    case PICK3: NOS++;*NOS=TOS;TOS=*(NOS-3);continue;
    case PICK4: NOS++;*NOS=TOS;TOS=*(NOS-4);continue;
	case SWAP: W=*NOS;*NOS=TOS;TOS=W;continue;
    case NIP: NOS--;continue;
    case ROT: W=TOS;TOS=*(NOS-1);*(NOS-1)=*NOS;*NOS=W;continue;
	case DUP2: W=*NOS;NOS++;*NOS=TOS;NOS++;*NOS=W;continue;// ( a b -- a b a b
    case DROP2: NOS--;TOS=*NOS;NOS--;continue;
    case DROP3: NOS-=2;TOS=*NOS;NOS--;continue;// ( a b c --
    case DROP4: NOS-=3;TOS=*NOS;NOS--;continue;// ( a b c d --
    case OVER2: NOS++;*NOS=TOS;TOS=*(NOS-3);// ( a b c d -- a b c d a b
		NOS++;*NOS=TOS;TOS=*(NOS-3);continue;
    case SWAP2: W=*NOS;*NOS=*(NOS-2);*(NOS-2)=W;// ( a b c d -- c d a b		
       W=TOS;TOS=*(NOS-1);*(NOS-1)=W;continue;
	case TOR: R++;*R=(BYTE*)TOS;TOS=*NOS;NOS--;continue;
    case RFROM: NOS++;*NOS=TOS;TOS=(int)*R;R--;continue;
    case ERRE: NOS++;*NOS=TOS;TOS=(int)*R;continue;
	case ERREM: (*(int*)R)+=TOS;TOS=*NOS;NOS--;continue;
    case ERRFM: NOS++;*NOS=TOS;TOS=**(int**)R;(*(int*)R)+=4;continue;
    case ERRSM: **(int**)R=TOS;TOS=*NOS;NOS--;(*(int*)R)+=4;continue;
    case ERRDR: R--;continue;
	case AND: TOS&=*NOS;NOS--;continue;
    case OR: TOS|=*NOS;NOS--;continue;
	case XOR: TOS^=*NOS;NOS--;continue;
    case NOT: TOS=~TOS;continue;
//--- aritmeticas
	case SUMA: TOS=(*NOS)+TOS;NOS--;continue;
    case RESTA: TOS=(*NOS)-TOS;NOS--;continue;
	case MUL: TOS=(*NOS)*TOS;NOS--;continue;
    case DIV: TOS=*NOS/TOS;NOS--;continue;
	case MULDIV: TOS=(long long)(*(NOS-1))*(*NOS)/TOS;NOS-=2;continue;
	case MULSHR: TOS=((long long)(*(NOS-1))*(*NOS))>>TOS;NOS-=2;continue;
    case CDIVSH: TOS=(((long long)(*(NOS-1))<<TOS)/(*NOS));NOS-=2;continue;
    case DIVMOD: W=*NOS%TOS;*NOS=*NOS/TOS;TOS=W;continue;
	case MOD: TOS=*NOS%TOS;NOS--;continue;
    case ABS: W=(TOS>>31);TOS=(TOS+W)^W;continue;
    case CSQRT: TOS=isqrt32(TOS);continue;
    case CLZ: TOS=iclz32(TOS);continue;
    case NEG: TOS=-TOS;continue;
    case INC: TOS++;continue;	case INC4: TOS+=4;continue; case DEC: TOS--;continue;
    case DIV2: TOS>>=1;continue;	case MUL2: TOS<<=1;continue;
	case SHL: TOS=(*NOS)<<TOS;NOS--;continue;
    case SHR: TOS=(*NOS)>>TOS;NOS--;continue;
//--- memoria
	case FECH: TOS=*(int *)TOS;continue;
    case CFECH: TOS=*(char*)TOS;continue;
    case WFECH: TOS=*(short *)TOS;continue;
	case STOR: *(int *)TOS=(int)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CSTOR: *(char*)TOS=(char)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case WSTOR: *(short *)TOS=(short)*NOS;NOS--;TOS=*NOS;NOS--;continue;
	case INCSTOR: *((int *)TOS)+=(int)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CINCSTOR: *((char*)TOS)+=(char)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case WINCSTOR: *((short *)TOS)+=(short)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case FECHPLUS: NOS++;*NOS=TOS+4;TOS=*(int *)TOS;continue; //@+ | adr -- adr' v
    case STOREPLUS: *(int *)TOS=(int)*NOS;TOS+=4;NOS--;continue;//!+ | v adr -- adr'
    case CFECHPLUS: NOS++;*NOS=TOS+1;TOS=*(char *)TOS;continue;
    case CSTOREPLUS: *(char *)TOS=(char)*NOS;TOS++;NOS--;continue;
    case WFECHPLUS: NOS++;*NOS=TOS+2;TOS=*(short *)TOS;continue;
    case WSTOREPLUS: *(short *)TOS=(short)*NOS;TOS+=2;NOS--;continue;
//--- sistema
	case UPDATE:
        SYSKEY=0;
		while (SDL_PollEvent(&event)) { 
	   	switch(event.type) {
           case SDL_MOUSEMOTION:
                SYSXYM=event.motion.x|event.motion.y<<16;break;
           case SDL_MOUSEBUTTONDOWN:
                SYSBM|=1<<event.button.button;break;
           case SDL_MOUSEBUTTONUP: 
                SYSBM&=~(1<<event.button.button);break;
           case SDL_KEYUP:  
                SYSKEY=(event.key.keysym.scancode&0x7f)|0x80;break;
           case SDL_KEYDOWN:
                SYSKEY=event.key.keysym.scancode&0x7f;break;
           } }; 
		continue;
//---- raton
    case XYMOUSE: NOS++;*NOS=TOS;NOS++;*NOS=SYSXYM&0xffff;TOS=(SYSXYM>>16);continue;
    case BMOUSE: NOS++;*NOS=TOS;TOS=SYSBM;continue;
//----- teclado
    case SKEY: SYSKEY=TOS;TOS=*NOS;NOS--;continue;
	case KEY: NOS++;*NOS=TOS;TOS=SYSKEY&0xff;continue;
//----- joy
    case CNTJOY: NOS++;*NOS=TOS;TOS=SDL_NumJoysticks();continue;
    case GETJOY: TOS=(int)SDL_JoystickOpen(TOS);continue;
    case REDRAW: gr_redraw(); continue;
	case MSEC: NOS++;*NOS=TOS;TOS=SDL_GetTicks();continue;
    case IDATE: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_year+1900;
        NOS++;*NOS=TOS;TOS=sitime->tm_mon+1;NOS++;*NOS=TOS;TOS=sitime->tm_mday;continue;
    case TIME: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_sec; 
        NOS++;*NOS=TOS;TOS=sitime->tm_min;NOS++;*NOS=TOS;TOS=sitime->tm_hour;continue;
    case SISEND: 
         return 0;
    case SISRUN:
        exestr="";
        if (TOS==0) { rebotea=1;return 0; }
        strcpy(pilaexecl,(char*)TOS);
        while (*pilaexecl!=0) pilaexecl++;
        pilaexecl++;
        return 1;
//--- pantalla
    case WIDTH: NOS++;*NOS=TOS;TOS=gr_ancho;continue;
    case HEIGHT: NOS++;*NOS=TOS;TOS=gr_alto;continue;
	case CLS: gr_clrscr();continue;
    case FRAMEV: NOS++;*NOS=TOS;TOS=(int)gr_buffer;continue;
	case SETXY:
#ifdef NOMUL
       vcursor=(int*)setxyf((*NOS),TOS);   // faster????
#else
       vcursor=(int*)gr_buffer+TOS*gr_ancho+(*NOS); 
#endif
        NOS--;TOS=*NOS;NOS--;continue;
	case MPX:vcursor+=TOS;TOS=*NOS;NOS--;continue;
	case SPX:*(int*)(vcursor++)=TOS;TOS=*NOS;NOS--;continue;
	case GPX:NOS++;*NOS=TOS;TOS=*(int*)(vcursor);continue;

    case VXFB: NOS++;*NOS=TOS;TOS=(int)XFB;continue;
    case TOXFB:gr_toxfb();continue;
    case XFBTO:gr_xfbto();continue;
//--- color
	case COLORF: gr_color2=TOS;TOS=*NOS;NOS--;continue;
    case COLOR: gr_color1=TOS;TOS=*NOS;NOS--;continue;
    case COLORA: NOS++;*NOS=TOS;TOS=gr_color1;continue;
	case ALPHA: gr_alpha(TOS);TOS=*NOS;NOS--;continue;
//--- dibujo
    case OP: gy1=TOS;gx1=*NOS;NOS--;TOS=*NOS;NOS--;continue;
	case LINE:
		gr_line(gx1,gy1,*NOS,TOS);gx1=*NOS;gy1=TOS;
        NOS--;TOS=*NOS;NOS--;continue;
    case CURVE: 
		gr_spline(gx1,gy1,*NOS,TOS,*(NOS-2),*(NOS-1));gx1=*(NOS-2);gy1=*(NOS-1);
		NOS-=3;TOS=*NOS;NOS--;continue;
    case CURVE3: 
		gr_spline3(gx1,gy1,*NOS,TOS,*(NOS-2),*(NOS-1),*(NOS-4),*(NOS-3));gx1=*(NOS-4);gy1=*(NOS-3);
		NOS-=5;TOS=*NOS;NOS--;continue;
	case PLINE:
		gr_pline(gx1,gy1,*NOS,TOS);gx1=*NOS;gy1=TOS;
        NOS--;TOS=*NOS;NOS--;continue;
    case PCURVE:
		gr_pcurve(gx1,gy1,*NOS,TOS,*(NOS-2),*(NOS-1));gx1=*(NOS-2);gy1=*(NOS-1);
		NOS-=3;TOS=*NOS;NOS--;continue;
    case PCURVE3:
		gr_pcurve3(gx1,gy1,*NOS,TOS,*(NOS-2),*(NOS-1),*(NOS-4),*(NOS-3));gx1=*(NOS-4);gy1=*(NOS-3);
		NOS-=5;TOS=*NOS;NOS--;continue;

	case POLI: gr_drawPoli();continue;
    case FCOL: fillcol(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case FCEN: fillcent(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case FMAT: fillmat(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case SFILL: fillSol();continue;
    case LFILL: fillLin();continue;
    case RFILL: fillRad();continue;
    case TFILL: mTex=(int*)TOS;fillTex();TOS=*NOS;NOS--;continue;

//------- sonido
#ifdef FMOD
    case SLOAD: // "" -- pp
        TOS=(int)FSOUND_Sample_Load(FSOUND_FREE,(char *)TOS,FSOUND_NORMAL,0,0);
        continue;
    case SPLAY: // pp --
        if (TOS!=0) FSOUND_PlaySound(FSOUND_FREE,(FSOUND_SAMPLE *)TOS);
        else FSOUND_StopSound(FSOUND_ALL);
        TOS=*NOS;NOS--;
        continue;
/*    case MLOAD: // "" -- mm
        TOS=(int)FMUSIC_LoadSong((char*)TOS);
        continue;*/
    case SINFO: // "" -- mm
//        if (TOS==-1) {        
         TOS=0;
         for(int i=0;i<FSOUND_GetMaxChannels();i++) TOS|=FSOUND_IsPlaying(i); 
//        } else { 
//           TOS=(int)FSOUND_IsPlaying(TOS); }
        continue;
    case SSET: // pan vol frec mm --
         if (TOS!=0) FSOUND_Sample_SetDefaults((FSOUND_SAMPLE *)TOS,int(*NOS),int(*(NOS-1)),int(*(NOS-2)),-1);
        TOS=*(NOS-3);NOS-=4;continue;
#else
    //case IRSON: SYSirqsonido=TOS;TOS=*NOS;NOS--;continue;
    case SBO: NOS++;*NOS=TOS;TOS=(int)bosound();continue;
    case SBI: NOS++;*NOS=TOS;TOS=(int)bisound();continue;
#endif

//--- bloque de memoria
    case MEM: NOS++;*NOS=TOS;TOS=(int)memlibre;continue; // inicio de n-MB de datos
//--- bloques

    case FFIRST: // "" -- fdd/0
         if (hFind!=NULL) FindClose(hFind);
         strcpy(error,(char*)TOS);strcat(error,"\\*");
         hFind=FindFirstFile(error, &ffd);
         if (hFind == INVALID_HANDLE_VALUE) TOS=0; else TOS=(int)&ffd;
         continue;
    case FNEXT: // -- fdd/0
         NOS++;*NOS=TOS;
         if (FindNextFile(hFind, &ffd)==0) TOS=0; else TOS=(int)&ffd;
         continue ;

	case LOAD: // 'from "filename" -- 'to
         if (TOS==0||*NOS==0) { TOS=*NOS;NOS--;continue; }
         file=fopen((char*)TOS,"rb");
         TOS=*NOS;NOS--;
         if (file==NULL) continue;
         do { W=fread((void*)TOS,sizeof(char),1024,file); TOS+=W; } while (W==1024);
         fclose(file);continue;
    case SAVE: // 'from cnt "filename" --
         if (TOS==0||*NOS==0) { DeleteFile((char*)TOS);
                              NOS-=2;TOS=*NOS;NOS--;continue; }
         file=fopen((char*)TOS,"wb");
         TOS=*NOS;NOS--;
         if (file==NULL) { NOS--;TOS=*NOS;NOS--;continue; }
         fwrite((void*)*NOS,sizeof(char),TOS,file);
         fclose(file);
         NOS--;TOS=*NOS;NOS--;continue;
    case APPEND: // 'from cnt "filename" --
         if (TOS==0||*NOS==0) { NOS-=2;TOS=*NOS;NOS--;continue; }
         file=fopen((char*)TOS,"ab");
         TOS=*NOS;NOS--;
         if (file==NULL) { NOS--;TOS=*NOS;NOS--;continue; }
         fwrite((void*)*NOS,sizeof(char),TOS,file);
         fclose(file);
         NOS--;TOS=*NOS;NOS--;continue;
                  
// por velocidad         
    case MOVED: // | de sr cnt --
         W=*(NOS-1);W1=*NOS;
         while (TOS--) { *(int *)W=*(int *)W1;W+=4;W1+=4; }
         NOS-=2;TOS=*NOS;NOS--;
         continue;
    case MOVEA: // | de sr cnt --
         W=(*(NOS-1))+(TOS<<2);W1=(*NOS)+(TOS<<2);
         while (TOS--) { W-=4;W1-=4;*(int *)W=*(int *)W1; }         
         NOS-=2;TOS=*NOS;NOS--;
         continue;
    case CMOVED: // | de sr cnt --
         W=*(NOS-1);W1=*NOS;
         while (TOS--) { *(char*)W++=*(char*)W1++; }
         NOS-=2;TOS=*NOS;NOS--;
         continue;
    case CMOVEA: // | de sr cnt --
         W=(*(NOS-1))+TOS;W1=(*NOS)+TOS;
         while (TOS--) { *(char*)--W=*(char*)--W1; }         
         NOS-=2;TOS=*NOS;NOS--;         
         continue;
//--- red
#ifdef NET
    case OPENURL: // url header buff -- buff/0
         buffData=(char*)TOS;
         hOpen = InternetOpen("InetURL/1.0",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0); //INTERNET_FLAG_ASYNC
         hURL = InternetOpenUrl(hOpen,(char*)(*(NOS-1)),(char*)(*NOS),0,INTERNET_FLAG_RELOAD,0);
         NOS-=2;
         do {
            InternetReadFile(hURL,buffData,2048,&readData);
            buffData+=readData;
         } while (readData!=0);
         InternetCloseHandle(hURL);
         InternetCloseHandle(hOpen);
         TOS=(int)buffData;
         continue;   
#endif

//---- timer
//    case ITIMER: // vector msecs --
//        SetTimer(hWnd,0,TOS,0);
//        SYSirqtime=*NOS;NOS--;TOS=*(NOS);NOS--;
//        continue;
#ifdef PRINTER
//---- printer
    case DOCINI:
        lpError = StartDoc(phDC,&di);
        lpError = StartPage(phDC);
        continue;
    case DOCEND:
        lpError = EndPage(phDC);
        lpError = EndDoc(phDC);
        continue;
    case DOCMOVE: // x y --
        MoveToEx(phDC,*NOS,TOS,(LPPOINT) NULL);
        NOS--;TOS=*(NOS);NOS--;
        continue;
    case DOCLINE: // x y --
        LineTo(phDC,*NOS,TOS); 
        NOS--;TOS=*(NOS);NOS--;        
        continue;
    case DOCTEXT: // "tt" --
        TextOutA(phDC,0,0,(char*)(TOS),strlen((char*)(TOS)));
        TOS=*(NOS);NOS--;
        continue;
    case DOCSIZE: // "tt" -- w h
        GetTextExtentPoint(phDC,(char*)(TOS),strlen((char*)(TOS)),&tsize);
        NOS++;*(NOS)=tsize.cx;TOS=tsize.cy;
        continue;
    case DOCFONT: // size angle "font" --
        SelectObject(phDC, hfntPrev);
        DeleteObject(hfnt);
        strcpy(plf.lfFaceName,(char*)TOS);
        plf.lfWeight = FW_NORMAL;
        plf.lfEscapement = *NOS;
        plf.lfHeight= -MulDiv(*(NOS-1), GetDeviceCaps(phDC, LOGPIXELSY), 72);
        hfnt = CreateFontIndirect(&plf);
        hfntPrev = SelectObject(phDC, hfnt);
        NOS-=2;TOS=*(NOS);NOS--;
        continue;
    case DOCBIT: // bitmap x y --
        hBmp = (HBITMAP) LoadImage(0,(char*)(*(NOS-1)),IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION );
        tmpDC = CreateCompatibleDC( phDC );
        SelectObject( tmpDC, hBmp );
        GetObject( hBmp, sizeof( info ), &info );
        BitBlt( phDC,(*NOS),TOS, info.bmWidth, info.bmHeight, tmpDC, 0, 0, SRCCOPY );
        DeleteDC( tmpDC );
        DeleteObject(hBmp);
        NOS-=2;TOS=*(NOS);NOS--;
        continue;
    case DOCRES: // -- xmax ymax
        NOS++;*NOS=TOS;TOS=cWidthPels;
        NOS++;*NOS=TOS;TOS=cHeightPels;
        continue;
#endif
    case SYSTEM: // "" -- st
         if (TOS==0) {
            if (ProcessInfo.hProcess!=0) {
               TerminateProcess(ProcessInfo.hProcess,0);
               CloseHandle(ProcessInfo.hThread);
               CloseHandle(ProcessInfo.hProcess);
               ProcessInfo.hProcess=0;
               }
            TOS=-1;
            continue;
            }
         if (TOS==-1) {
            if (ProcessInfo.hProcess==0) continue;
            W=WaitForSingleObject(ProcessInfo.hProcess,0);
            if (W==WAIT_TIMEOUT) TOS=0; else TOS=-1;
            continue;
            }
        ZeroMemory(&StartupInfo, sizeof(StartupInfo));
        StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field
        TOS=CreateProcess(NULL,(char*)TOS,NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,NULL,&StartupInfo,&ProcessInfo);
        continue;
	default: // completa los 8 bits con apila numeros 0...
        NOS++;*NOS=TOS;TOS=W-ULTIMAPRIMITIVA;continue;
	} } };

long numero;

int esnumero(char *p)
{//if (*p=='&') { p++;numero=*p;return 1;} // codigo ascii
int base,dig=0,signo=0;
if (*p=='-') { p++;signo=1; } else if (*p=='+') p++;
if (*p==0) return 0;// no es numero
switch(*p) {
  case '$': base=16;p++;break;// hexa
  case '%': base=2;p++;break;// binario
  default:  base=10;break; }; 
numero=0;if (*p==0) return 0;// no es numero
while (*p!=0) {
  if (*p<='9') dig=*p-'0'; else if (*p>='A') dig=*p-'A'+10;
  else return 0;
  if (dig<0 || dig>=base) return 0;
  numero*=base;numero+=dig;
  p++;
  };
if (signo==1) numero=-numero;  
return 1; };

int esnumerof(char *p)         // decimal punto fijo 16.16
{
int parte0,dig=0,signo=0;
if (*p=='-') { p++;signo=1; } else if (*p=='+') p++;
if (*p==0) return 0;// no es numero
numero=0;
while (*p!=0) {
  if (*p=='.') { parte0=numero;numero=1;if (numero==0 && *(p+1)<33) return 0; } else 
  {
  if (*p<='9') dig=*p-'0'; else dig=-1;
  if (dig<0 || dig>=10) return 0;
  numero=(numero*10)+dig;
  }
  p++;
  };  
int decim=1,num=numero;
while (num>1) { decim*=10;num/=10; }
num=0x10000*numero/decim;
numero=(num&0xffff)|(parte0<<16);
if (signo==1) numero=-numero;
return 1; };

#ifndef RUNER
//----------------------------------------------
struct Indice {	char *nombre;BYTE *codigo;int tipo;	 };
//---- diccionario local
int cntindice;
Indice indice[2048];
int cntnombre;
char nombre[1024*16];
//---- diccionario exportados
int cntindiceex;
Indice indiceex[4096];
int cntnombreex;
char nombreex[1024*32];
//---- includes
int cntincludes;
Indice includes[100];
//---- pila de compilador
int cntpilaA;
int cntpila;
int pila[256];

void apila(int n) { //if (cntpila>255) { sprintf(error,"apila error");ldebug(error);return; }
pila[cntpila++]=n; }

int desapila(void) {//if (cntpila==0) { sprintf(error,"desapila error");ldebug(error);return 0; }
return pila[--cntpila]; }

void iniA(void) { cntpilaA=0; }
void pushA(int n) { PSP[cntpilaA++]=n; }
int popA(void) { return PSP[--cntpilaA]; }

#ifdef LOGMEM
void dumplocal(char *nombre)
{
FILE *stream;
if((stream=fopen("log.txt","a"))==NULL) return;
fprintf(stream,"**** %s ****\n", nombre);
for (int i=0;i<cntindice;i++)
    fprintf(stream,"%s %d\n",indice[i].nombre,indice[i].codigo-prog);
if(fclose(stream)) return;
}

void dumpex(void)
{
FILE *stream;
if((stream=fopen("log.txt","a"))==NULL) return;
fprintf(stream,"------- %d\n",cntindiceex);
for (int i=0;i<cntindiceex;i++)
    fprintf(stream,"%s %d\n",indiceex[i].nombre,indiceex[i].codigo-prog);
fprintf(stream,"-------\n");    
if(fclose(stream)) return;
}    
#endif
//---- espacio de dato
void adato(const char *p) 
{ strcpy((char*)&data[cntdato],p);cntdato+=strlen(p)+1; } 

void adatonro(int n,int u)
{ BYTE *p=&data[cntdato];
switch(u) {
  case 1:*(char *)p=(char)n;break;// char
  case 2:*(short *)p=(short)n;break;// short
  case 4:*(int  *)p=(int)n;break;// int
  };
cntdato+=u;  }

void adatocnt(int n)
{ BYTE *p=&data[cntdato];
for (int i=0;i<n;i++,p++) *p=0;
cntdato+=n; }

//---- espacio de codigo
BYTE *lastcall=NULL;

void aprognro(int n) // graba nro como literal
{ BYTE *p=&prog[cntprog];lastcall=NULL;
if (n>=0 && n<255-ULTIMAPRIMITIVA) { 
  *p=ULTIMAPRIMITIVA+n;cntprog++;
} else {
  *p=LIT;p++;*(int *)p=(int)n;
  cntprog+=5; } }

void aprog(int n) // grabo primitiva
{ BYTE *p=&prog[cntprog];*p=(BYTE)n;
if (n==CALL) lastcall=p; else lastcall=NULL;
cntprog++; }

void aprogint(int n)
{ BYTE *p=&prog[cntprog];*(DWORD*)p=(DWORD)&prog[n];cntprog+=4; }

void aprogaddr(int n) // grabo direccion
{ BYTE *p=&prog[cntprog];*(DWORD*)p=(DWORD)indice[n].codigo;cntprog+=4; }

void aprogaddrex(int n) // grabo direccion exportada
{ BYTE *p=&prog[cntprog];*(DWORD*)p=(DWORD)indiceex[n].codigo;cntprog+=4; }

//---- definicion
void define(char *p) 
{
Indice *actualex,*actual=&indice[cntindice++];
char *n;
actual->tipo=*p;
p++;
if (*p==':') { p++;// nombre exportado
    actualex=&indiceex[cntindiceex++];
	n=&nombreex[cntnombreex];
	strcpy(n,p);cntnombreex+=strlen(p)+1;
	actualex->tipo=actual->tipo;
	actualex->nombre=n;
	actualex->codigo=(actual->tipo==':')?&prog[cntprog]:&data[cntdato];
	};
n=&nombre[cntnombre];
strcpy(n,p);cntnombre+=strlen(p)+1;//---- espacio de nombres
actual->nombre=n;
actual->codigo=(actual->tipo==':')?&prog[cntprog]:&data[cntdato]; }

void compilofin(void)
{
if (lastcall!=NULL) { *lastcall=JMP;lastcall=NULL; }
    else aprog(FIN);
}

void endefine(void)
{
Indice *actual=&indice[cntindice-1];     
if (actual->tipo==':') {
   compilofin();
//  if (lastcall!=NULL) { *lastcall=JMP;lastcall=NULL; } else aprog(FIN);
  } else { if (&data[cntdato]==actual->codigo) adatonro(0,4); } }

void endefinesin(void)
{
Indice *actual=&indice[cntindice-1];
//if (cntPilaA>0)
if (actual->tipo!=':' && &data[cntdato]==actual->codigo) adatonro(0,4); 
}

//---- parse de fuente

int esmacro(char *p)
{    
numero=0;
char **m=macros;
while (**m!=0) {
  if (!strcmp(*m,p)) return 1;
  *m++;numero++; }    
return 0;  }

int espalabra(char *p)
{
numero=cntindice-1;
Indice *actual=&indice[numero];
while (actual>=indice) {
  if (!strcmp(actual->nombre,p)) return 1;
  actual--;numero--;  }
return 0;  }

int espalabraex(char *p)
{
numero=cntindiceex-1;
Indice *actual=&indiceex[numero];
while (actual>=indiceex) {
  if (!strcmp(actual->nombre,p)) return 1;
  actual--;numero--; }
return 0; }

//----- Include
int estainclude(char *palabra)
{
if (cntincludes==0) return 0;
Indice *actual=&includes[cntincludes-1];
while (actual>=includes) {
	if (!strcmp(actual->nombre,palabra)) return 1;
	actual--; }
return 0; }

void agregainclude(char *palabra)
{
Indice *act=&includes[cntincludes++];
char *n=&nombreex[cntnombreex];
strcpy(n,palabra);cntnombreex+=strlen(palabra)+1;
act->nombre=n; }

//-------------------------------
#define E_DATO 1
#define E_PROG 2

#define COMPILAOK 0
#define OPENERROR 1
#define CLOSEERROR 2
#define CODIGOERROR 3

char tolower(char c)
{
if (c>0x40 && c<0x5b) c+=0x20;
return c;
}

char toupper(char c)
{
if (c>0x60 && c<0x7b) c-=0x20;
return c;
}

//---------------------------------------------------------------
// compila el archivo
int compilafile(char *name)
{
FILE *stream;
char *ahora,*palabra,*copia;
char lineat[512];
// SEBAS: 2006-10-14 
ahora=name;
while (*ahora>32) { *ahora=tolower(*ahora);ahora++; }

strcpy(lineat,name);
if((stream=fopen(lineat,"rb"))==NULL) {
  sprintf(error,"%s|0|0|no existe %s",linea,lineat);
  return OPENERROR;
  }
int estado=E_PROG;int unidad=4;int salto=0;
int aux,nrolinea=0;// convertir a nro de linea local
cntpila=0;
while(!feof(stream)) {
  *lineat=0;fgets(lineat,512,stream);ahora=lineat; // ldebug(ahora);

otrapalabra:
  while (*ahora!=0 && *ahora<33) ahora++;
  if (*ahora==0) goto otralinea;
  palabra=ahora;
  if (*ahora=='"') { ahora++;copia=ahora;
     while (*copia!=0) { 
           if (*copia=='"') { if (*(copia+1)!='"') break; copia++; }
           *ahora=*copia;ahora++;copia++; }
     if (ahora!=copia) { *ahora=0;ahora=copia; } }
  else { while (*ahora>32) { *ahora=toupper(*ahora);ahora++; } }
  if (*ahora==0) *(ahora+1)=0;
  *ahora=0;
  if (*palabra=='|') { // comentario
     if (strnicmp(palabra,"|WIN|",5)==0)
       ahora=palabra+5;
     else
       *(ahora+1)=0;
     }
  else if (*palabra=='"') // string
    { 
    palabra++;// graba str
    switch (estado) {
      case E_DATO:
            adato(palabra);break;
//              pushA((int)&data[cntdato]);
//              adato(palabra);break;
      case E_PROG:	aux=(int)&data[cntdato];adato(palabra);aprognro(aux);break; 
      };
    }
  else if (*palabra==':'||*palabra=='#')// define codigo y dato
    {
	if (cntpila>0) { sprintf(error,"bloque mal cerrado");goto error; }
	endefinesin();
	iniA();
	if (*(palabra+1)==0) { bootaddr=&prog[cntprog]; // : con espacio
    } else {
    	if (esnumero(palabra)==1) { sprintf(error,"nro invalido");goto error; }
	  // avisa palabra repetida?
       define(palabra); }
   estado=(*palabra==':')?E_PROG:E_DATO;unidad=4;
    }
  else if (*palabra=='^')// include
	{
	palabra++;
	if (estainclude(palabra)==0) {// si esta en la lista no se incluye
		agregainclude(palabra);// agrega a la lista
		aux=compilafile(palabra);// inclusion recursiva
#ifdef LOGMEM		
//		dumplocal(palabra);
#endif
        if (aux==OPENERROR) { sprintf(error,"no existe %s",palabra);goto error; } 
		if (aux!=COMPILAOK) { return aux; }
		cntindice=cntnombre=0;// espacio de nombres reset
		}
	}
  else if (esnumero(palabra)==1 || esnumerof(palabra)==1) // numero
    {
    switch (estado) {
      case E_DATO: 
        if (unidad==0) adatocnt(numero); else adatonro(numero,unidad);
        break; // graba numero 
      case E_PROG: 
		aprognro(numero);break; // compila apila numero
      };
    }    
  else if (esmacro(palabra)==1)  // macro
    {
    switch (estado) {
      case E_DATO:
        switch (numero) {
          case 0: endefine();break;// fin de dato
          case 1: apila(unidad);unidad=1;break;	 // { cuenta bytes
          case 2: unidad=desapila();break;		 // }
          case 3: unidad=0;break;				 // }{ cantidad bytes
 		  case 4: apila(unidad);unidad=2;break;	 // [ cuenta words
		  case 5: unidad=desapila();break;		 // ]
          default: 
			sprintf(error,"palabra %s en dato ?",palabra);goto error;  }
        break; // graba numero
      case E_PROG:// ? ( . )( . )  ( . ? )  ( . ? )( . )  ( . ) 
        switch (numero) {
          case 0:// ; fin de dato
            if (cntpila>0) compilofin();// anidamiento compilo fin
            else { endefine(); }// termino palabra
            break;
          case 1: // (
            if (salto==1)
              { apila(cntprog);apila(1);cntprog++;salto=0; }
            else 
              { apila(cntprog);apila(2); } 
            break;
          case 2: // )
            aux=desapila();lastcall=NULL;
            if (aux==1) {
              aux=desapila();
//              if (salto==0) { prog[aux]=cntprog-aux-1; } //sin control
              if (salto==0) { if ((cntprog-aux-1)==(char)(cntprog-aux-1)) prog[aux]=cntprog-aux-1; 
                 else { sprintf(error,"bloque muy largo ");goto error; } }
                else { sprintf(error,"? ) no valido ");goto error; }
            } else if (aux==2) { // repeticion
              aux=desapila();
              if (salto==1) { if ((aux-cntprog-1)==(char)(aux-cntprog-1)) { prog[cntprog]=aux-cntprog-1;cntprog++;salto=0; }
                 else { sprintf(error,"bloque muy largo ");goto error; } } 
                else { // repeat
                  aprog(JMPR);prog[cntprog]=aux-cntprog-1;cntprog++;
                   }
            } else if (aux==3) { // rep cond
              aux=desapila();
              if (salto==0) { 
                  aprog(JMPR);
                  if ((aux-cntprog-1)==(char)(aux-cntprog-1)) { prog[cntprog]=aux-cntprog-1;cntprog++; }
                  else { sprintf(error,"bloque muy largo ");goto error; }
                  aux=desapila();
                  if ((cntprog-aux-1)==(char)(cntprog-aux-1)) { prog[aux]=cntprog-aux-1; }
                  else { sprintf(error,"bloque muy largo ");goto error; }
                  } 
                else { sprintf(error,") mal cerrado");goto error; }
              } else
                { sprintf(error,") mal cerrado");goto error; }
            break;
          case 3: // )(
            aux=desapila();
		    if (aux==1) { // else del if
				aux=desapila();// direccion
				if (salto==0) { 
                  aprog(JMPR);apila(cntprog);apila(1);cntprog++;
                  if ((cntprog-aux-1)==(char)(cntprog-aux-1)) { prog[aux]=cntprog-aux-1; }
                  else { sprintf(error,"bloque muy largo ");goto error; }
                 } else { sprintf(error,"? )( no valido");goto error; }
            } else if (aux==2) {
                aux=desapila();
                if (salto==1)  
                   { apila(cntprog);cntprog++;apila(aux);apila(3);salto=0; }
                else { sprintf(error,")( falta condicion");goto error; }
            } else
                { sprintf(error,")( mal cerrado");goto error; }
            break;               
		  case 4:// [ palabra anonima
			aprog(LIT);aprogint(cntprog+4+2);
			aprog(JMPR);apila(cntprog);apila(4);cntprog++;
		    break;
		  case 5:// ]
			if (desapila()!=4) { sprintf(error,"[] mal cerrado");goto error; }
			aux=desapila();
			if ((cntprog-aux-1)==(char)(cntprog-aux-1)) { prog[aux]=cntprog-aux-1; }
            else { sprintf(error,"bloque muy largo ");goto error; }
		    break;
		  default:
		    aprog(numero);// compila primitiva
            if (numero>=IF && numero<=IFNAND) salto=1; else salto=0;
		    break;
          };
        break; 
        };
  } else { // palabra
    aux=0;if (*palabra=='\'') { 
		palabra++;aux=1;// aux=direccion de
		if (esnumero(palabra)==1) { strcpy(error,"nro ?");goto error; }
		}
    if (espalabra(palabra)==1) {
      switch (estado) {
        case E_DATO: // siempre es direcion
             adatonro((int)indice[numero].codigo,4);
             break;
        case E_PROG:
             if (aux==0) {
               if (indice[numero].tipo=='#') aprog(ADR); else aprog(CALL);
             } else aprog(LIT);// apila direccion
             aprogaddr(numero);
             break;
        };
    } else if (espalabraex(palabra)==1) {
	  switch (estado) {
        case E_DATO: // siempre es direcion
             adatonro((int)indiceex[numero].codigo,4);
             break;
        case E_PROG:
             if (aux==0) {
               if (indiceex[numero].tipo=='#') aprog(ADR); else aprog(CALL);
             } else aprog(LIT);// apila direccion
             aprogaddrex(numero);
             break;
		};
	} else { sprintf(error,"no existe %s",palabra);goto error;} }    
  ahora++; goto otrapalabra;
otralinea:
  nrolinea++; }
if (prog[cntprog-1]!=FIN) aprog(FIN);
if (fclose(stream)) return CLOSEERROR;
return COMPILAOK;

error:
  sprintf(lineat,"%s|%d|%d|%s",name,nrolinea,ahora-lineat,error);
  strcpy(error,lineat);
return CODIGOERROR;
}
#endif

void grabalinea(void)
{
FILE *stream;
if((stream=fopen("debug.err","w+"))==NULL) return;
fputs(error,stream);
if(fclose(stream)) return; 
}

//----------------- PRINCIPAL
#ifndef RUNER
 #ifdef WIN32
/*
FILE *stream;
 
int imprime(int v)
{
if (v>(int)(&prog) && v<=(int)(&prog)+cntprog)
   fprintf(stream,"$%x ",v-(int)&prog);
else
   fprintf(stream,"%d ",v);

}

LONG WINAPI MyUnhandledExceptionFilter(LPEXCEPTION_POINTERS e) 
{
int i,j;     

stream=fopen("runtime.err","w+");
fprintf(stream,"%s\r",linea);

fprintf(stream,"IP: $%x + %d \r",((int)e->ContextRecord->Edx)-(int)&prog,(int)&prog);// ebx=IP
fprintf(stream,"D: ");
i=(int)PSP;
j=(int)e->ContextRecord->Esi;
if ((j-i)>32) 
   {
   i=j-32;
   }
for (;i<j;i+=4)
    fprintf(stream,"%d ",*(int*)i);
fprintf(stream,"%d )\r",e->ContextRecord->Edi);    // edi=TOS    
fprintf(stream,"R: ");
i=(int)RSP;
j=*(int*)(e->ContextRecord->Ebp-16); // es variable local 
if ((j-i)>32) 
   {
   i=j-32;
   }
for (;i<=j;i+=4)
    imprime(*(int*)i);
fprintf(stream,")\r");

fprintf(stream,"code:%d cnt:$%x\r",&prog,cntprog);
fprintf(stream,"data:%d cnt:$%x\r",&data,cntdato);

//fprintf(stream,"Esi:%d\r",(int)e->ContextRecord->Esi);
//fprintf(stream,"Edi:%d\r",(int)e->ContextRecord->Edi);
//fprintf(stream,"Eax:%d\r",(int)e->ContextRecord->Eax);
//fprintf(stream,"Ebx:%d\r",(int)e->ContextRecord->Ebx);
//fprintf(stream,"Ecx:%d\r",(int)e->ContextRecord->Ecx);
//fprintf(stream,"Edx:%d\r",(int)e->ContextRecord->Edx);
//fprintf(stream,"local:%d\r",*(int*)(e->ContextRecord->Ebp-16));
//fprintf(stream,"PSP:%d\r",(int)PSP);
//fprintf(stream,"RSP:%d\r",(int)RSP);

fprintf(stream,"IND:%d NOM:%d LOC:%d EXP:%d INC:%d \r",cntindice,cntnombre,cntindiceex,cntnombreex,cntincludes);
fclose(stream);
//SYSEVENT=(int)&ultimapalabra;
return SHUTDOWN_NORETRY; //return EXCEPTION_CONTINUE_SEARCH;
}
*/
#endif

#endif

static void print_usage(void) {
  printf(":R4 console\n"
  "  c<CODIGO> compile\n"
  "  i<IMAGEN> build\n"
  "  x<IMAGEN> exec\n"
  "  w<SCRW>\n"
  "  h<SCRH>\n"
  "  f fullscreen \n"
  "  s without screen\n"
  "  ? help\n" , "r4");
}

//char *NDEBUG="debug.txt";
char *DEBUGR4X="debug.r4x";

///////////////////////////////////////////////////////////////////////////////////////////

//----------------- PRINCIPAL
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifndef RUNER
//SetUnhandledExceptionFilter(&MyUnhandledExceptionFilter);
#endif

int w=640,h=480,silent=0;
int noborde,i=0;
char printername[32];
char *aa=(char*)lpCmdLine;

// pila de ejecucion
pilaexecl=pilaexec;
strcpy(pilaexecl,"main.txt");
while (*pilaexecl!=0) pilaexecl++;
pilaexecl++;

devmodo.dmSize = sizeof(devmodo);
EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmodo);

mimemset((char*)&wc,0,sizeof(WNDCLASSA));
wc.style         = 0; //CS_OWNDC;
wc.lpfnWndProc   = WndProc;
wc.hInstance     = GetModuleHandle(0);
wc.lpszClassName = wndclass;
if(!RegisterClass((WNDCLASSA*)&wc)) return -1;

reboot: rebotea=0;
#ifdef LOGMEM
ldebug("ini..");

//testssort();exit(0);

#endif

if (*aa==0) {
    file=fopen("r4.ini","rb");// cargar r4.ini
    if (file!=NULL) { fread(setings,sizeof(char),1024,file);fclose(file);aa=setings; }
    } 
    
noborde=0;	
while (*aa!=0) {
      if ('i'==*aa) { compilastr=aa+1; }
      if ('c'==*aa) { 
        exestr="";
        strcpy(pilaexec,aa+1);pilaexecl=pilaexec; 
        while (*pilaexecl>32) pilaexecl++; 
        *pilaexecl=0;pilaexecl++;
        }
      if ('x'==*aa) { exestr=aa+1; }
      if ('w'==*aa) { esnumero(aa+1);w=numero; }
      if ('h'==*aa) { esnumero(aa+1);h=numero; }
      if ('b'==*aa) { noborde=1; }
      if ('f'==*aa) { w=devmodo.dmPelsWidth;h=devmodo.dmPelsHeight;noborde=1; }
      if ('s'==*aa) { silent=1; }
      if ('p'==*aa) { strcpy(printername,(aa+1)); } // pPrimo PDF
      if ('?'==*aa) { print_usage();return 0; }
      while (*aa!=32&&*aa!=0) aa++;
      if (32==*aa) *aa=0;
      aa++; }

/*
if (noborde==0)
   dwStyle=WS_VISIBLE|WS_CAPTION|WS_SYSMENU;
else
   dwStyle=WS_VISIBLE|WS_POPUP;
if (silent==1)  dwStyle&=~WS_VISIBLE;
ShowCursor(0);

rec.left=rec.top=0;rec.right=w;rec.bottom=h;
AdjustWindowRect(&rec,dwStyle,0);
hWnd=CreateWindowEx(WS_EX_APPWINDOW,wc.lpszClassName, wc.lpszClassName,dwStyle,
     (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,(GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
     rec.right-rec.left, rec.bottom-rec.top,0,0,wc.hInstance,0);

if(!hWnd) return -2;
*/
if (gr_init(w,h)<0) return -1;

//ShowWindow(hWnd,SW_NORMAL);
//--------------------------------------------------------------------------

phDC=CreateDC("winspool", printername , NULL, NULL );
mimemset((char*)&di,0,sizeof (DOCINFO));
di.cbSize = sizeof (DOCINFO);
di.lpszDocName = "r4doc";

cWidthPels = GetDeviceCaps(phDC, HORZRES);
cHeightPels = GetDeviceCaps(phDC, VERTRES);

SetBkMode(phDC, TRANSPARENT);
strcpy(plf.lfFaceName,"Arial");
plf.lfWeight = FW_NORMAL;
plf.lfEscapement = 0; 
hfnt = CreateFontIndirect(&plf); 
hfntPrev = SelectObject(phDC, hfnt);
SetTextAlign(phDC,TA_UPDATECP);

//loaddir(".//");
//WSAStartup(2, &wsaData);

#ifdef FMOD
    if (!FSOUND_Init(44100, 32, 0)) return -4;
#else
    if (sound_open(hWnd)!=0) return -4;
#endif

//--------------------------------------------------------------------------
recompila:

bootstr=pilaexecl-2;
while (*bootstr!=0 && bootstr>pilaexec)
    bootstr--;
if (bootstr>pilaexec) bootstr++;
 
debugerr:

bootaddr=0;
if (exestr[0]!=0) {
   #ifdef LOGMEM
   ldebug("LOAD IMA:");ldebug(exestr);
   #endif
   loadimagen(exestr);
   exestr="";
    }

#ifndef RUNER

if (bootaddr==0 && bootstr[0]!=0){
   #ifdef LOGMEM
   ldebug("BOOTSTR:");ldebug(bootstr);
   #endif
   strcpy(linea,bootstr);
   cntindiceex=cntnombreex=cntincludes=0;// espacio de nombres reset
   cntdato=cntprog=0;cntindice=cntnombre=0;

   #ifdef LOGMEM
   ldebug("compila...");
   #endif

   if (compilafile(linea)!=COMPILAOK) {
      #ifdef LOGMEM
      ldebug("NO COMPILA");ldebug(linea);
      sprintf(linea,"\r%d %d %d %d %d \r",cntindice,cntnombre,cntindiceex,cntnombreex,cntincludes);ldebug(linea);

      #endif
      grabalinea();
//        return 1;
      if (exestr==DEBUGR4X) return 1;
      exestr=DEBUGR4X;goto debugerr; 
      }
      #ifdef LOGMEM
      ldebug("fin compila...");
      sprintf(linea,"\r%d %d %d %d %d \r",cntindice,cntnombre,cntindiceex,cntnombreex,cntincludes);ldebug(linea);
      #endif

   if (compilastr[0]!=0) {
      #ifdef LOGMEM
      ldebug("SAVE IMA:");ldebug(compilastr);
      #endif
      saveimagen(compilastr);
      }
   }
if (bootaddr==0) {
   sprintf(error,"%s|0|0|NO BOOT",linea);
   grabalinea();
    if (exestr==DEBUGR4X) return 1;
   exestr=DEBUGR4X;goto recompila;//   strcpy(linea,NDEBUG);
   }

#endif

#ifdef LOGMEM
//dumpex();dumplocal("BOOT");
#endif
memlibre=data+cntdato; // comienzo memoria libre
if (silent!=1 && interprete(bootaddr)==1) goto recompila;

if (rebotea==0) 
    {
    pilaexecl--;pilaexecl--;
    while (*pilaexecl!=0 && pilaexecl>pilaexec)
       pilaexecl--;
    if (*pilaexecl==0) { pilaexecl++; goto recompila; }
    }

//--------------------------------------------------------------------------
#ifdef FMOD
   FSOUND_Close();
#else
   sound_close();
#endif

SelectObject(phDC, hfntPrev);
DeleteObject(hfnt);
DeleteDC(phDC);

gr_fin();

if (rebotea==1)  {
   *aa=0;
#ifdef LOGMEM
       ldebug("REBOOT..");
       sprintf(linea," %d *****\r",rebotea);ldebug(linea);
#endif

//   DestroyWindow(hWnd);
   goto reboot;
   }


//DestroyWindow(hWnd);
//ExitProcess(0);
return 0;
}
