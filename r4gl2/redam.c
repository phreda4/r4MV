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
//  :r4 interprete y compilador  pabloreda@gmail.com
//  Version GL
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
// PHREDA MCO 16/11/2008 version opengl
// PHREDA 13/1/2009 sin DLLs


#include "sisgl.h"  // sistema GL
//#include "graf.h"
#include "GL/gl.h"  // sistema GL
//#include "socketwl.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>

//#define LOGMEM 

#ifdef LOGMEM
#define ULTIMOMACRO 6
char *macrose[]={ ";","LIT","ADR","CALL","JMP","JMPR" };
#endif

char *macros[]={// directivas del compilador     
";","(",")",")(","[","]","EXEC",
"0?","+?","-?","1?","=?","<?",">?","<=?",">=?","<>?","AND?","NAND?",
"DUP","DROP","OVER","PICK2","PICK3","PICK4","SWAP","NIP","ROT", //--- pila
"2DUP","2DROP","3DROP","4DROP","2OVER","2SWAP",
">R","R>","R","R+","R@+","R!+","RDROP",//--- pila direcciones
"AND","OR","XOR","NOT", //--- logicas
"+","-","*","/","*/","*>>","/MOD","MOD","ABS", //--- aritmeticas
"NEG","1+","4+","1-","2/","2*","<<",">>",
"@","C@","W@","!","C!","W!","+!","C+!","W+!", //--- memoria
"@+","!+","C@+","C!+","W@+","W!+",
"MOVE","MOVE>","CMOVE","CMOVE>",//-- movimiento de memoria
"MEM","DIR","FILE","FSIZE","VOL","LOAD","SAVE",//--- memoria,bloques
"MSEC","TIME","DATE","END","RUN","IRUN",//--- sistema
"UPDATE",//--- pantalla
"PIXEL!","PIXEL@","SW","SH","CLS","REDRAW", //,"FRAMEV"
"XYMOUSE","BMOUSE","KEY","CNTJOY","AJOY","BJOY",
"IPEN!","IKEY!","IJOY","ISON","INET",//---- nuevas interrups
"PAPER","INK","INK@","ALPHA", //--- color
"OP","CP","LINE","CURVE","PLINE","PCURVE","POLI",//--- dibujo
//"SLOAD","SPLAY",//--- Sonido
""};

// instrucciones de maquina (son compilables a assembler)
enum {
FIN,LIT,ADR,CALL,JMP,JMPR,//hasta aqui no deberian ser visibles
EXEC,
IF,PIF,NIF,UIF,IFN,IFL,IFG,IFLE,IFGE,IFNO,IFAND,IFNAND,// condicionales 0 - y +  y no 0
DUP,DROP,OVER,PICK2,PICK3,PICK4,SWAP,NIP,ROT,
DUP2,DROP2,DROP3,DROP4,OVER2,SWAP2,//--- pila
TOR,RFROM,ERRE,ERREM,ERRFM,ERRSM,ERRDR,//--- pila direcciones
AND,OR,XOR,NOT,//--- logica
SUMA,RESTA,MUL,DIV,MULDIV,MULSHR,DIVMOD,MOD,ABS,
NEG,INC,INC4,DEC,DIV2,MUL2,SHL,SHR,//--- aritmetica
FECH,CFECH,WFECH,STOR,CSTOR,WSTOR,INCSTOR,CINCSTOR,WINCSTOR,//--- memoria
FECHPLUS,STOREPLUS,CFECHPLUS,CSTOREPLUS,WFECHPLUS,WSTOREPLUS,
MOVED,MOVEA,CMOVED,CMOVEA,
MEM,PATH,BFILE,BFSIZE,VOL,LOAD,SAVE,//--- bloques de memoria, bloques
MSEC,TIME,IDATE,SISEND,SISRUN,SISIRUN,//--- sistema
UPDATE,//--- pantalla
XYFRAME,WIDTH,HEIGHT,CLS,REDRAW, //,FRAMEV
XYMOUSE,BMOUSE,KEY,CNTJOY,AJOY,BJOY,
IRMOU,IRKEY,IRJOY,IRSON,IRNET,//---- nuevas interrups
COLORF,COLOR,COLORA,ALPHA,//--- color
OP,CP,LINE,CURVE,PLINE,PCURVE,POLI,//--- dibujo
SLOAD,SPLAY,//--- sonido
//--- sockets
ULTIMAPRIMITIVA// de aqui en mas.. apila los numeros 0..255-ULTIMAPRIMITIVA
};
//----- Comienzo de mapa de memoria

char *compilastr="";
char *bootstr="main.txt";
char *exestr="";

//---------------------- Memoria de reda4
int gx1=0,gy1=0,gx2=0,gy2=0,gxc=0,gyc=0;// coordenadas de linea
color32 col1;
BYTE *bootaddr;
FILE *file;
//---- eventos
char linea[1024];// 1k linea
char error[1024];
char pathdata[256];

//---- eventos teclado y raton
int CJOY;
#ifdef linux  // y esto ?
//int map[]={ 71, 72,73,75,0,77,79,80,81,82,83 }; // viva linux la #$@#
int map[]={
88, 124,125 ,126, 127,0,0,0,
0,  0,  0,  0, 0, 0,   0,   0,
0,  0,  0,  0, 0, 122,   0, 123,
0,  0,  0, 89,120,   0,   0,  90,
91, 92, 93, 94,95, 124, 121,   0
};
#endif
int sysevent[16];
int SYSEVENT;
int SYSKEY;
int SYSXYM;
int SYSBM;
int SYSirqlapiz=0;
int SYSirqteclado=0;
int SYSirqsonido=0;
int SYSirqred=0;
int SYSirqjoystick=0;

//----- Directorio 
char mindice[8192];// 8k de index 1024 archivos con nombres de 8 caracteres
char *indexdir[512];
int sizedir[512];
int cntindex;
char *subdirs[255]; 
int cntsubdirs;
struct stat nbuf;
struct dirent *ep;
DIR *dp;
//---- Date & Time
static struct tm *sitime;
time_t sit;

//---- dato y programa
int cntdato;
int cntprog;
BYTE *memlibre;
//----- PILAS
int PSP[2048];// 2k pila de datos
BYTE *RSP[2048];// 2k pila de direcciones
BYTE ultimapalabra[]={ SISEND };
//--- Memoria
BYTE prog[1024*256];// 256k de programa
BYTE data[1024*1024*16];// 16 MB de datos

//---- Graba y carga imagen
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

void loaddir(void)
{
cntindex=cntsubdirs=0;
dp=opendir(pathdata);
if (dp==NULL) return;
char *act=mindice;
while ((ep=readdir(dp))!=NULL) {
    strcpy(error,pathdata);strcat(error,ep->d_name);
	stat(error,&nbuf); // ep->
	if (S_ISREG(nbuf.st_mode)) { 
		indexdir[cntindex] = act;
		sizedir[cntindex] = nbuf.st_size;
		cntindex++; }
	if (S_ISDIR(nbuf.st_mode)) {
		if (strcmp(ep->d_name,".") && strcmp(ep->d_name,"..")) {
           subdirs[cntsubdirs] = act;
    	   cntsubdirs++; }
		}
	strcpy(act,ep->d_name); 
	while (*act!=0) act++;
	act++;
	}
closedir(dp);
}

//---------------------------------------------------------------
int interprete(BYTE *codigo)// 1=recompilar con nombre en linea
{      
if (codigo==NULL) return -1;
register BYTE *IP=codigo;	// lugar del programa
register int TOS;			// Tope de la pila PSP
register int *NOS;			// Next of stack
register BYTE **R;			// return stack
register int W,W1;			// palabra actual y auxiliar
R=RSP;*R=(BYTE*)&ultimapalabra;
NOS=PSP;*NOS=TOS=0;

clsevt();

for (W=0;W<16;W++)
    sysevent[W]=0;

SYSEVENT=0;
SYSirqlapiz=0;
SYSirqteclado=0;

while (1)  {// Charles Melice  suggest next:... goto next; bye !
    W=(BYTE)*IP++;

#ifdef LOGMEM
    sprintf((char*)subdirs,"IP:%d [%d] %s %d\n",(int)IP-(int)prog,W,(W<6)?macrose[W]:((W&0xff)<ULTIMAPRIMITIVA)?macros[W&0xff]:"nro",
    (W<18)?*(DWORD*)IP:0);
    ldebug((char*)subdirs);
#endif

	switch (W) {// obtener codigo de ejecucion
	case FIN: IP=*R;R--;continue;
    case LIT: NOS++;*NOS=TOS;TOS=*(DWORD*)IP;IP+=sizeof(int);continue;
    case ADR: NOS++;*NOS=TOS;W=*(DWORD*)IP;IP+=sizeof(int);TOS=*(DWORD*)W;continue;
    case CALL: W=*(DWORD*)IP;IP+=sizeof(int);R++;*R=IP;IP=(BYTE*)W;continue;
	case JMP: W=*(int*)IP;IP=(BYTE*)W;continue;
    case JMPR: W=*(char*)IP;W++;IP+=W;continue;
//-hasta aca solo lo escribe el compilador
	case EXEC:W=TOS;TOS=*NOS;NOS--;if (W!=0) { R++;*R=IP;IP=(BYTE*)W; } continue;
//--- condicionales
	case IF: W=*(char*)IP;IP++;if (TOS!=0) IP+=W; continue;
    case PIF: W=*(char*)IP;IP++;if (TOS<=0) IP+=W; continue;
	case NIF: W=*(char*)IP;IP++;if (TOS>=0) IP+=W; continue;
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
    case DIV: //if (TOS==0) { TOS=*NOS;NOS--;continue; }
	     TOS=*NOS/TOS;NOS--;continue;
	case MULDIV: //if (TOS==0) { NOS--;TOS=*NOS;NOS--;continue; }
	     TOS=(*(NOS-1))*(*NOS)/TOS;NOS-=2;continue;
	case MULSHR: TOS=((long long)(*(NOS-1))*(*NOS))>>TOS;NOS-=2;continue;
    case DIVMOD: //if (TOS==0) { NOS--;TOS=*NOS;NOS--;continue; }
	     W=*NOS%TOS;*NOS=*NOS/TOS;TOS=W;continue;
	case MOD: TOS=*NOS%TOS;NOS--;continue;
    case ABS: W=(TOS>>31);TOS=(TOS+W)^W;continue;
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
//----------- por velocidad         
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
//--- bloque de memoria
    case MEM: NOS++;*NOS=TOS;TOS=(int)memlibre;continue; // inicio de n-MB de datos
//--- bloques
	case PATH: if (TOS!=0) { strcpy(pathdata,(char*)TOS);loaddir(); }
         TOS=*NOS;NOS--;continue;
    case BFILE: // nro -- "nombre" o 0
         if (TOS>=cntindex || TOS<0) TOS=0; else  TOS=(int)indexdir[TOS];
         continue;
    case BFSIZE: // nro --  size o 0
         if (TOS>=cntindex || TOS<0) TOS=0; else  TOS=sizedir[TOS];
         continue;
	case VOL:// nro -- "nombre" o 0
         if (TOS>=cntsubdirs || TOS<0) TOS=0; else TOS=(int)subdirs[TOS];
         continue;
	case LOAD: // 'from "filename" -- 'to
         if (TOS==0||*NOS==0) { TOS=*NOS;NOS--;continue; }
         sprintf(error,"%s%s",pathdata,(char*)TOS);
         TOS=*NOS;NOS--;
         file=fopen(error,"rb");if (file==NULL) continue;
         do { W=fread((void*)TOS,sizeof(char),1024,file); TOS+=W; } while (W==1024);
         fclose(file);continue;
    case SAVE: // 'from cnt "filename" --
         if (TOS==0||*NOS==0) { NOS-=2;TOS=*NOS;NOS--;continue; }
         sprintf(error,"%s%s",pathdata,(char*)TOS);
         TOS=*NOS;NOS--;
         file=fopen(error,"wb");if (file==NULL) { NOS--;TOS=*NOS;NOS--;continue; }
         fwrite((void*)*NOS,sizeof(char),TOS,file);
         fclose(file);//loaddir();
         NOS--;TOS=*NOS;NOS--;continue;
    
//--- sistema
	case MSEC: NOS++;*NOS=TOS;TOS=msys_timerGet();continue;
    case TIME: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_hour; 
               NOS++;*NOS=TOS;TOS=sitime->tm_min;NOS++;*NOS=TOS;TOS=sitime->tm_sec;continue;
    case IDATE: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_year; //+1900
               NOS++;*NOS=TOS;TOS=sitime->tm_mon;NOS++;*NOS=TOS;TOS=sitime->tm_wday;continue;
     case SISEND: return 0;  
    case SISRUN: if (TOS!=0) { bootstr=(char*)TOS;exestr=""; }return 1;
//    case SISIRUN: if (TOS!=0) exestr=(char*)TOS;return 1;
    
	case UPDATE: 
         upd_evt();
         while ((W=getevt())!=0) {
               switch ((W>>28)&0xf) {
                      case 1:SYSKEY=W&0xff;SYSEVENT=SYSirqteclado;break;
                      case 2:SYSXYM=W&0xfffffff;SYSEVENT=SYSirqlapiz;break;
                      case 3:SYSBM=(W&0xf);SYSEVENT=SYSirqlapiz;break;
                 } 
            if (SYSEVENT!=0) { R++;*(int*)R=(int)IP;IP=(BYTE*)SYSEVENT;SYSEVENT=0; }
            }
         continue;
    case XYMOUSE: NOS++;*NOS=TOS;NOS++;*NOS=SYSXYM&0xffff;TOS=(SYSXYM>>16);continue;
    case BMOUSE: NOS++;*NOS=TOS;TOS=SYSBM;continue;
	case KEY: NOS++;*NOS=TOS;TOS=SYSKEY;continue;

//---- nuevas interrups
    case IRMOU: SYSirqlapiz=TOS;TOS=*NOS;NOS--;continue;
    case IRKEY: SYSirqteclado=TOS;TOS=*NOS;NOS--;continue;
    case IRJOY: SYSirqjoystick=TOS;TOS=*NOS;NOS--;continue;
    case IRSON: SYSirqsonido=TOS;TOS=*NOS;NOS--;continue;
    case IRNET: SYSirqred=TOS;TOS=*NOS;NOS--;continue;


    
//--- pantalla
//	case BPP: NOS++;*NOS=TOS;TOS=32;continue;
    case XYFRAME:TOS=TOS*XRES+(*NOS);NOS--;continue;
    case WIDTH: NOS++;*NOS=TOS;TOS=XRES;continue;
    case HEIGHT: NOS++;*NOS=TOS;TOS=YRES;continue;
//    case FRAMEV: NOS++;*NOS=TOS;TOS=(int)gr_buffer;continue;

//--------- opengl
	case CLS: glClear(GL_COLOR_BUFFER_BIT);continue;
    case REDRAW: swapgl();continue;
//--- color
	case COLORF:                                 
         gr_color2.c32=TOS;
         glClearColor(((TOS>>16)&0xFF)*0.003921568627450980392156862745098,
         ((TOS>>8)&0xFF)*0.003921568627450980392156862745098,
         (TOS&0xFF)*0.003921568627450980392156862745098,
         255.0);
         TOS=*NOS;NOS--;continue;    
    case COLOR: 
         gr_color1.c32=TOS;TOS=*NOS;NOS--;continue;
    case COLORA: 
         NOS++;*NOS=TOS;TOS=gr_color1.c32;continue;
	case ALPHA: if (TOS>254) TOS=255;
         gr_alphav=(BYTE)(TOS);TOS=*NOS;NOS--;continue;

//--- dibujo
    case OP: gy1=TOS;gx1=*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CP: gyc=TOS;gxc=*NOS;NOS--;TOS=*NOS;NOS--;continue;
	case LINE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
       glBegin(GL_LINES);
       glColor4ub(col1.b8.r,col1.b8.g,col1.b8.b,gr_alphav); 
       glVertex2i(gx1,gy1);
       glColor4ub(gr_color1.b8.r,gr_color1.b8.g,gr_color1.b8.b,gr_alphav); 
       glVertex2i(gx2,gy2);
	   glEnd();
	   col1=gr_color1;
		//linegl(gx1,gy1,gx2,gy2,col1,gr_color1.c32);
        gx1=gx2;gy1=gy2;continue;
    case CURVE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
       glBegin(GL_LINES);
       glColor4ub(col1.b8.r,col1.b8.g,col1.b8.b,gr_alphav); 
       glVertex2i(gx1,gy1);
       glVertex2i((gx1+gxc)>>1,(gy1+gyc)>>1);
       glVertex2i((gx2+gxc)>>1,(gy2+gyc)>>1);
       glColor4ub(gr_color1.b8.r,gr_color1.b8.g,gr_color1.b8.b,gr_alphav); 
       glVertex2i(gx2,gy2);
	   glEnd();
	   col1=gr_color1;
//		gr_spline(gx1,gy1,gxc,gyc,gx2,gy2);
        gx1=gx2;gy1=gy2;continue;
	case PLINE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
    	linegl(gx1,gy1,gx2,gy2,col1.c32,gr_color1.c32);
    	col1=gr_color1;
		gx1=gx2;gy1=gy2;continue;
    case PCURVE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
//		gr_pspline(gx1,gy1,gxc,gyc,gx2,gy2);
    	linegl(gx1,gy1,gxc,gyc,col1.c32,gr_color1.c32);
   	
    	linegl(gxc,gyc,gx2,gy2,col1.c32,gr_color1.c32);    	
    	col1=gr_color1;
        gx1=gx2;gy1=gy2;continue;
	case POLI: poligl();continue;
//----- joy
    case CNTJOY: NOS++;*NOS=TOS;TOS=CJOY;continue;
    case AJOY:TOS=0;//SDL_JoystickGetAxis(joystick[TOS], *NOS);
         NOS--;continue;
    case BJOY:TOS=0;//SDL_JoystickGetButton(joystick[TOS],*NOS);
         NOS--;continue;
	default: // completa los 8 bits con apila numeros 0...
        NOS++;*NOS=TOS;TOS=W-ULTIMAPRIMITIVA;continue;
	} } };

//----------------------------------------------
typedef struct { char *nombre;BYTE *codigo;int tipo;	 } Indice ;
//---- diccionario local
int cntindice;
Indice indice[2048];
int cntnombre;
char nombre[1024*16];
//---- diccionario exportados
int cntindiceex;
Indice indiceex[2048];
int cntnombreex;
char nombreex[1024*32];
//---- includes
int cntincludes;
Indice includes[25];
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
int i;
for (i=0;i<cntindice;i++)
    fprintf(stream,"%s %d\n",indice[i].nombre,indice[i].codigo-prog);
if(fclose(stream)) return; 
}    

void dumpex(void)
{
FILE *stream;
if((stream=fopen("log.txt","a"))==NULL) return;
fprintf(stream,"-------\n");
int i;
for (i=0;i<cntindiceex;i++)
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
{ BYTE *p=&data[cntdato];int i;
for (i=0;i<n;i++,p++) *p=0;
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
{ BYTE *p=&prog[cntprog];*(unsigned int*)p=(unsigned int)&prog[n];cntprog+=4; }

void aprogaddr(int n) // grabo direccion
{ BYTE *p=&prog[cntprog];*(unsigned int*)p=(unsigned int)indice[n].codigo;cntprog+=4; }

void aprogaddrex(int n) // grabo direccion exportada
{ BYTE *p=&prog[cntprog];*(unsigned int*)p=(unsigned int)indiceex[n].codigo;cntprog+=4; }

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
  } else { if (&data[cntdato]==actual->codigo) adatonro(0,4); } }

void endefinesin(void)
{
Indice *actual=&indice[cntindice-1];     
//if (cntPilaA>0)
if (actual->tipo!=':' && &data[cntdato]==actual->codigo) adatonro(0,4); 
}

//---- parse de fuente
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

sprintf(lineat,"%s%s",pathdata,name);
if((stream=fopen(lineat,"rb"))==NULL) {
  sprintf(error,"%s|0|0|no existe %s",linea,lineat);
  return OPENERROR;
  }
int estado=E_PROG;int unidad=4;int salto=0;
int aux,nrolinea=1;// convertir a nro de linea local
cntpila=0;
while(!feof(stream)) {
  *lineat=0;fgets(lineat,512,stream);ahora=lineat;// ldebug(ahora);  
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
  if (*palabra=='|') *(ahora+1)=0;// comentario
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
        if (aux==OPENERROR) { sprintf(error,"no existe %s",palabra);goto error; } 
		if (aux!=COMPILAOK) { return aux; }
#ifdef LOGMEM		
		dumplocal(palabra);
#endif
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
          case 1: apila(unidad);unidad=1;break;	 // { cuenta unsigned chars
          case 2: unidad=desapila();break;		 // }
          case 3: unidad=0;break;				 // }{ cantidad unsigned chars
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
              if (salto==0) { prog[aux]=cntprog-aux-1; }  
                else { sprintf(error,"? ) no valido ");goto error; }
            } else if (aux==2) { // repeticion
              aux=desapila();
              if (salto==1) { prog[cntprog]=aux-cntprog-1;cntprog++;salto=0; } 
                else { // repeat
                  aprog(JMPR);prog[cntprog]=aux-cntprog-1;cntprog++;
                   }
            } else if (aux==3) { // rep cond
              aux=desapila();
              if (salto==0) { 
                  aprog(JMPR);prog[cntprog]=aux-cntprog-1;cntprog++; 
                  aux=desapila();prog[aux]=cntprog-aux-1;
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
                  prog[aux]=cntprog-aux-1;
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
			aux=desapila();prog[aux]=cntprog-aux-1;
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

/*
void dumpmem(void)
{char buffl[100];     
sprintf(buffl,"\n******* %s *******\n",linea);ldebug(buffl);
sprintf(buffl,"pila compilador %d\n",cntpila);ldebug(buffl);
sprintf(buffl,"boot: %d\n",bootaddr);ldebug(buffl);
sprintf(buffl,"** locales cnt:%d nom:%d unsigned chars\n",cntindice,cntnombre);ldebug(buffl);
int i;
//for (i=0;i<cntindice;i++) { sprintf(buffl,"%s ",indice[i].nombre);ldebug(buffl);}
sprintf(buffl,"\n** export cnt:%d nom:%d unsigned chars\n",cntindiceex,cntnombreex);ldebug(buffl);
//for (i=0;i<cntindiceex;i++) {sprintf(buffl,"%s ",indiceex[i].nombre);ldebug(buffl);}
sprintf(buffl,"\nincludes:%d\ndato:%d unsigned chars\nprog:%d unsigned chars",cntincludes,cntdato,cntprog);ldebug(buffl);
ldebug("\n====================\n"); }
*/

void grabalinea(void)
{
FILE *stream;
if((stream=fopen("debug.err","w+"))==NULL) return;
fputs(error,stream); 
if(fclose(stream)) return; 
}


 #ifdef WIN32
LONG WINAPI MyUnhandledExceptionFilter(LPEXCEPTION_POINTERS e) 
{
int i;     
//SDL_Quit();
FILE *stream;
stream=fopen("runtime.err","w+");
fprintf(stream,"%s\r",linea);

fprintf(stream,"IP: %d %d\r",(int)e->ContextRecord->Ebx-(int)prog,(int)e->ContextRecord->Ecx);// ebx=IP
fprintf(stream,"P: ");
i=(int)PSP;
if (((int)e->ContextRecord->Esi-i)>32) 
   {
   fprintf(stream,"... ");
   i=((int)e->ContextRecord->Esi)-32;
   }
for (;i<(int)e->ContextRecord->Esi;i+=4)
    fprintf(stream,"%d ",*(int*)i);
fprintf(stream,"%d )\r",e->ContextRecord->Edi);    // edi=TOS    
fprintf(stream,"R: ");
i=(int)RSP;
if (((int)e->ContextRecord->Edx-i)>32) 
   {
   fprintf(stream,"... ");
   i=((int)e->ContextRecord->Edx)-32;
   }
for (;i<=(int)e->ContextRecord->Edx;i+=4)
    fprintf(stream,"%d ",*(int*)i);
fprintf(stream,")\r");
/*
//fprintf(stream,"Esi: %d ",(int)e->ContextRecord->Esi);
//fprintf(stream,"PSP: %d ",(int)PSP);
//fprintf(stream,"Eax: %d \r",(int)e->ContextRecord->Eax);
//fprintf(stream,"Ecx: %d \r",(int)e->ContextRecord->Ecx);
//fprintf(stream,"Edx: %d \r",(int)e->ContextRecord->Edx);
//fprintf(stream,"RSP: %d \r",(int)RSP);
*/
fclose(stream); 
return SHUTDOWN_NORETRY; //return EXCEPTION_CONTINUE_SEARCH;
}
#endif

char *NDEBUG="debug.txt";

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


//----------------- PRINCIPAL
int main(int argc, char **argv)
{
#ifdef _WIN32
SetUnhandledExceptionFilter(&MyUnhandledExceptionFilter);
#endif

int w=800,h=600,fullscreen=0,silent=0;
int i=0;
while (i<argc && argv[i]!=0) {
      if ('i'==argv[i][0]) { compilastr=&argv[i][1]; }
      if ('c'==argv[i][0]) { bootstr=&argv[i][1];exestr=""; }
      if ('x'==argv[i][0]) { exestr=&argv[i][1]; }
      if ('w'==argv[i][0]) { esnumero(&argv[i][1]);w=numero; }
      if ('h'==argv[i][0]) { esnumero(&argv[i][1]);h=numero; }
      if ('f'==argv[i][0]) { fullscreen=1; }      
      if ('s'==argv[i][0]) { silent=1; }
      if ('?'==argv[i][0]) { print_usage();return 0; }
      i++; }
    
if (silent==0) {
   if (inigl(w,h,fullscreen)<0) return -1;

//   CJOY=SDL_NumJoysticks();
//   for (int i=0;i<CJOY;i++)
//     joystick[i] = SDL_JoystickOpen(i);
   }
strcpy(pathdata,".//");  // SEBAS win-linux
loaddir();
upd_evt();
//--------------------------------------------------------------------------
recompila:
if (exestr[0]!=0) {
   #ifdef LOGMEM		
   ldebug("LOAD IMA:");ldebug(exestr);
   #endif
   loadimagen(exestr);
} else {
   #ifdef LOGMEM		       
   ldebug("BOOTSTR:");ldebug(bootstr);
   #endif
   strcpy(linea,bootstr);
   cntindiceex=cntnombreex=cntincludes=0;// espacio de nombres reset
   cntdato=cntprog=0;cntindice=cntnombre=0;
   bootaddr=NULL;
   if (compilafile(linea)!=COMPILAOK) { 
      grabalinea();
      return 1;
      if (!strcmp(linea,NDEBUG)) return 1;
      exestr="debug.r4x";
//      strcpy(linea,NDEBUG);
      goto recompila; 
      }
   if (compilastr[0]!=0) {
      #ifdef LOGMEM		                                
      ldebug("SAVE IMA:");ldebug(compilastr);
      #endif
      saveimagen(compilastr);
      }
   }       
if (bootaddr==NULL) {
   sprintf(error,"%s|0|0|NO BOOT",linea);                    
   grabalinea();
   return 1;
   if (!strcmp(linea,NDEBUG)) return 1;
   exestr="debug.r4x";
//   strcpy(linea,NDEBUG);
   goto recompila; 
   }
#ifdef LOGMEM		
//dumpex();
//dumplocal("BOOT");
#endif
memlibre=data+cntdato; // comienzo memoria libre      
upd_evt();
if (interprete(bootaddr)==1) goto recompila;
//--------------------------------------------------------------------------
if (silent==0) {
   endgl();
   }
return 0;
}

