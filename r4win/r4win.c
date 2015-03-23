/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2005,2006,2007,2008 
 * Pablo Hugo Reda <pabloreda@gmail.com>, 
 * Mar del Plata, Argentina
 * All rights reserved.
*/
//  Reda4 interprete y compilador  
//  Version DDRAW
//
// --- versiones
// PHREDA 29/12/2005 Primera version
// SEBAS Desimone Correcciones Linux
// Charles Melice improve speed
// PHREDA 23/4/2007 Error en debug.txt
// PHRADA 23/8/2007 AND? NAND? *>>
// PHREDA 3/3/2008 orden error, new irq

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <math.h>
#include <mem.h>
#include <time.h>
#include <fmod.h>
#include "graf.h"
#include "socket.h"
#include <dinput.h>

//#define ULTIMOMACRO 6
//char *macrose[]={ ";","LIT","ADR","CALL","JMP","JMPR" };
char *macros[]={// directivas del compilador     
";","(",")",")(","[","]",
"0?","+?","-?","1?","=?","<?",">?","<=?",">=?","<>?",
"AND?","NAND?",
"EXEC",
"DUP","DROP","OVER","PICK2","PICK3","PICK4","SWAP","NIP","ROT", //--- pila
"2DUP","2DROP","3DROP","4DROP","2OVER","2SWAP",
">R","R>","R","R+","R@+","R!+","RDROP",//--- pila direcciones
"AND","OR","XOR","NOT", //--- logicas
"+","-","*","/","*/","*>>","/MOD","MOD","ABS", //--- aritmeticas
"NEG","1+","4+","1-","2/","2*","<<",">>",
"@","C@","W@","!","C!","W!","+!","C+!","W+!", //--- memoria
"@+","!+","C@+","C!+","W@+","W!+",
"MSEC","TIME","DATE","END","RUN",//--- sistema
"BPP","SW","SH","CLS","REDRAW","FRAMEV","UPDATE",//--- pantalla

"XYMOUSE","BMOUSE","KEY",
"CNTJOY","AJOY","BJOY",
"IPEN!","IKEY!","IJOY","ISON","INET",//---- nuevas interrups

"PAPER","INK","INK@","ALPHA", //--- color
"OP","CP","LINE","CURVE","PLINE","PCURVE","POLI",//--- dibujo
"MEM","DIR","FILE","FSIZE","VOL","LOAD","SAVE",//--- memoria,bloques
"SLOAD","SPLAY",//--- Sonido
""};

// instrucciones de maquina (son compilables a assembler)
enum {
FIN,LIT,ADR,CALL,JMP,JMPR,//hasta aqui no deberian ser visibles
IF,PIF,NIF,UIF,IFN,IFL,IFG,IFLE,IFGE,IFNO,// condicionales 0 - y +  y no 0
IFAND,IFNAND,
EXEC,
DUP,DROP,OVER,PICK2,PICK3,PICK4,SWAP,NIP,ROT,
DUP2,DROP2,DROP3,DROP4,OVER2,SWAP2,//--- pila
TOR,RFROM,ERRE,ERREM,ERRFM,ERRSM,ERRDR,//--- pila direcciones
AND,OR,XOR,NOT,//--- logica
SUMA,RESTA,MUL,DIV,MULDIV,MULSHR,DIVMOD,MOD,ABS,
NEG,INC,INC4,DEC,DIV2,MUL2,SHL,SHR,//--- aritmetica
FECH,CFECH,WFECH,STOR,CSTOR,WSTOR,INCSTOR,CINCSTOR,WINCSTOR,//--- memoria
FECHPLUS,STOREPLUS,CFECHPLUS,CSTOREPLUS,WFECHPLUS,WSTOREPLUS,
MSEC,TIME,IDATE,SISEND,SISRUN,//--- sistema
BPP,WIDTH,HEIGHT,CLS,REDRAW,FRAMEV,UPDATE,//--- pantalla
XYMOUSE,BMOUSE,KEY,
CNTJOY,AJOY,BJOY,
IRMOU,IRKEY,IRJOY,IRSON,IRNET,//---- nuevas interrups
COLORF,COLOR,COLORA,ALPHA,//--- color
OP,CP,LINE,CURVE,PLINE,PCURVE,POLI,//--- dibujo
MEM,PATH,BFILE,BFSIZE,VOL,LOAD,SAVE,//--- bloques de memoria, bloques
SLOAD,SPLAY,//--- sonido
//--- sockets
ULTIMAPRIMITIVA// de aqui en mas.. apila los numeros 0..255-ULTIMAPRIMITIVA
};
//---------------------- Memoria de reda4
//---- dato y programa
int cntdato;
BYTE dato[1024*256];// KB de datos
int cntprog;
BYTE prog[1024*256];// KB de programa
BYTE data[1024*1024*16];// MB de datos
BYTE *bootaddr;
FILE *file;

void saveimagen(char *nombre)
{
file=fopen(nombre,"wb");if (file==NULL) return;
fwrite(&bootaddr,sizeof(int),1,file); // -cntprog
fwrite(&cntdato,sizeof(int),1,file);
fwrite(&cntprog,sizeof(int),1,file);
fwrite((void*)prog,1,cntprog,file);
fwrite((void*)dato,1,cntdato,file);
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
fread((void*)dato,1,cntdato,file);
fclose(file);
}

//----- PILAS
int PSP[2048];// 2k pila de datos
BYTE *RSP[2048];// 2k pila de direcciones
int gx1=0,gy1=0,gx2=0,gy2=0,gxc=0,gyc=0;// coordenadas de linea
char pathdata[128],error[128];
//---- eventos
char linea[1024];// 1k linea

//----- Directorio 
char mindice[8192];// 8k de index 1024 archivos con nombres de 8 caracteres
char *indexdir[1024];
int sizedir[1024];
int cntindex;
char *subdirs[255]; 
int cntsubdirs;
struct stat nbuf;
struct dirent *ep;
DIR *dp;

int SYSEVENT=0;
int SYSXYM=0,SYSBM=0;
int SYSKEY=0;
int active;

int SYSirqmouse=0;
int SYSirqteclado=0;
int SYSirqsonido=0;
int SYSirqred=0;
int SYSirqjoystick=0;

//---------- joystick
int CJOY;
#define MAX_JOYSTICKS	8
static DIDEVICEINSTANCE joystick[MAX_JOYSTICKS];
static LPDIRECTINPUT dinput = NULL;
//LPDIRECTINPUT8 di;

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,VOID* pContext )
{
memcpy(&joystick[CJOY], pdidInstance, sizeof(DIDEVICEINSTANCE));
CJOY++;
if( CJOY >= MAX_JOYSTICKS ) return DIENUM_STOP;
return DIENUM_CONTINUE;
}

/* Function to scan the system for joysticks.
 * This function should set SDL_numjoysticks to the number of available
 * joysticks.  Joystick 0 should be the system default joystick.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
void JoystickInit(HINSTANCE hi)
{
HRESULT result;
CJOY = 0;
//result = DirectInputCreate(hi, DIRECTINPUT_VERSION,&dinput, NULL);
// Create a DirectInput device
//result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,IID_IDirectInput8, (VOID**)&dinput, NULL))

//if ( result != DI_OK ) return(-1);
//result = IDirectInput_EnumDevices(dinput,DIDEVTYPE_JOYSTICK,EnumJoysticksCallback,NULL,DIEDFL_ATTACHEDONLY );
}

int JoystickGetAxis(DIDEVICEINSTANCE j,int n)
{
return 0;
}

int JoystickGetButton(DIDEVICEINSTANCE j,int n)
{
return 0;
}

//---- Date & Time
MSG message;
time_t sit;
tm *sitime;
int *punt;

void loaddir(void)
{
cntindex=cntsubdirs=0;
dp=opendir(pathdata);
if (dp==NULL) return;
char *act=mindice;
while ((ep=readdir(dp))!=NULL) 
	{
    strcpy(error,pathdata);strcat(error,ep->d_name);
	stat(error,&nbuf);
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

BYTE ultimapalabra[]={ SISEND };

//---------------------------------------------------------------
int interprete(BYTE *codigo)// 1=recompilar con nombre en linea
{      
if (codigo==NULL) return -1;
register BYTE *IP=codigo;	// lugar del programa
register int TOS;			// Tope de la pila PSP
register int *NOS;			// Next of stack
register BYTE **R;			// return stack
register int W;			// palabra actual y auxiliar
R=RSP;*R=(BYTE*)&ultimapalabra;
NOS=PSP;*NOS=TOS=0;
SYSEVENT=0;
while (1)  {// Charles Melice  suggest next:... goto next; bye !
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
//--- fin condicionales dependiente de bloques    
	case EXEC:W=TOS;TOS=*NOS;NOS--;if (W!=0) { R++;*R=IP;IP=(BYTE*)W; } continue;
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
    case DIV: if (TOS==0) { TOS=*NOS;NOS--;continue; }
	     TOS=*NOS/TOS;NOS--;continue;
	case MULDIV: if (TOS==0) { NOS--;TOS=*NOS;NOS--;continue; }
	     TOS=(*(NOS-1))*(*NOS)/TOS;NOS-=2;continue;
	case MULSHR: TOS=((long long)(*(NOS-1))*(*NOS))>>TOS;NOS-=2;continue;	     
    case DIVMOD: if (TOS==0) { NOS--;TOS=*NOS;NOS--;continue; }
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
//--- sistema
	case MSEC: NOS++;*NOS=TOS;TOS= GetTickCount();continue;
    case IDATE: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_year; //+1900
  NOS++;*NOS=TOS;TOS=sitime->tm_mon;NOS++;*NOS=TOS;TOS=sitime->tm_wday;continue;
    case TIME: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_hour; 
  NOS++;*NOS=TOS;TOS=sitime->tm_min;NOS++;*NOS=TOS;TOS=sitime->tm_sec;continue;
    case SISEND: return 0;  
    case SISRUN: if (TOS!=0) //sprintf(linea,"%s%s",pathdata,(char*)TOS);
//                 else sprintf(linea,"%s%s",pathdata,"debug.txt");  
                strcpy(linea,(char*)TOS);
      return 1;
//--- pantalla
	case BPP: NOS++;*NOS=TOS;TOS=32;continue;
    case WIDTH: NOS++;*NOS=TOS;TOS=SCR_WIDTH;continue;
    case HEIGHT: NOS++;*NOS=TOS;TOS=SCR_HEIGHT;continue;
	case CLS: 
         punt=gr_buffer;
         for (W=0;W<SCR_SIZE;W++,punt++) *punt=gr_color2;
         continue;
    case REDRAW: redraw();continue;
    case FRAMEV: NOS++;*NOS=TOS;TOS=(int)gr_buffer;continue;
	case UPDATE: 
         if (PeekMessage(&message,hWnd,0,0,PM_REMOVE)) // process messages
            {  
            TranslateMessage(&message); DispatchMessage(&message);
            if (SYSEVENT!=0) { R++;*(int*)R=(int)IP;IP=(BYTE*)SYSEVENT;SYSEVENT=0; }
            if (active==WA_INACTIVE) {
               while (active==WA_INACTIVE) {
                Sleep(2);
                PeekMessage(&message,hWnd,0,0,PM_REMOVE);
                TranslateMessage(&message); DispatchMessage(&message);
                }
              gr_restore();
              }
            }
		break;
//-----------------------------------------------		
    case XYMOUSE: NOS++;*NOS=TOS;NOS++;
        *NOS=SYSXYM&0xffff;TOS=(SYSXYM>>16)&0xffff;
        continue;
    case BMOUSE: NOS++;*NOS=TOS;TOS=SYSBM;continue;
    case KEY: NOS++;*NOS=TOS;TOS=SYSKEY;continue;
//----- joy
    case CNTJOY: NOS++;*NOS=TOS;TOS=CJOY;continue;
    case AJOY:TOS=JoystickGetAxis(joystick[TOS], *NOS);NOS--;continue;
    case BJOY:TOS=JoystickGetButton(joystick[TOS],*NOS);NOS--;continue;
   
//---- nuevas interrups
    case IRMOU: SYSirqmouse=TOS;TOS=*NOS;NOS--;continue;
    case IRKEY: SYSirqteclado=TOS;TOS=*NOS;NOS--;continue;
    case IRJOY: SYSirqjoystick=TOS;TOS=*NOS;NOS--;continue;
    case IRSON: SYSirqsonido=TOS;TOS=*NOS;NOS--;continue;
    case IRNET: SYSirqred=TOS;TOS=*NOS;NOS--;continue;
//--- color
	case COLORF: gr_color2=TOS;TOS=*NOS;NOS--;continue;    
    case COLOR: gr_color1=TOS;TOS=*NOS;NOS--;continue;
    case COLORA: NOS++;*NOS=TOS;TOS=gr_color1;continue;
	case ALPHA: if (TOS>254) gr_solid(); else { gr_alphav=(BYTE)(TOS);gr_alpha(); }
		TOS=*NOS;NOS--;continue;
//--- dibujo
    case OP: gy1=TOS;gx1=*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CP: gyc=TOS;gxc=*NOS;NOS--;TOS=*NOS;NOS--;continue;
	case LINE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
		gr_line(gx1,gy1,gx2,gy2);gx1=gx2;gy1=gy2;continue;
    case CURVE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
		gr_spline(gx1,gy1,gxc,gyc,gx2,gy2);gx1=gx2;gy1=gy2;continue;
	case PLINE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
		gr_psegmento(gx1,gy1,gx2,gy2);gx1=gx2;gy1=gy2;continue;
    case PCURVE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
		gr_pspline(gx1,gy1,gxc,gyc,gx2,gy2);gx1=gx2;gy1=gy2;continue;
	case POLI: gr_drawPoli();continue;
//--- bloque de memoria
    case MEM: NOS++;*NOS=TOS;TOS=(int)data;continue; // inicio de n-MB de datos
//--- bloques
	case PATH: if (TOS==0) continue;
         strcpy(pathdata,(char*)TOS);TOS=*NOS;NOS--;loaddir();continue;
    case BFILE: // nro -- "nombre" o 0
         if (TOS>=cntindex || TOS<0) TOS=0; else  TOS=(int)indexdir[TOS];
         continue;
    case BFSIZE: // nro --  0
         if (TOS>=cntindex || TOS<0) TOS=0; else  TOS=(int)sizedir[TOS];
         continue;
	case VOL:// nro -- "nombre" o 0
         if (TOS>=cntsubdirs || TOS<0) TOS=0; else TOS=(int)subdirs[TOS];
         continue;
	case LOAD: // 'from "filename" -- 'to
         if (TOS==0||*NOS==0) { TOS=*NOS;NOS--;continue; }
         sprintf(linea,"%s%s",pathdata,(char*)TOS);
         TOS=*NOS;NOS--;
         file=fopen(linea,"rb");if (file==NULL) continue;
         do { W=fread((void*)TOS,sizeof(char),1024,file); TOS+=W; } while (W==1024);
         fclose(file);continue;
    case SAVE: // 'from cnt "filename" --
         if (TOS==0||*NOS==0) { NOS-=2;TOS=*NOS;NOS--;continue; }
         sprintf(linea,"%s%s",pathdata,(char*)TOS);
         TOS=*NOS;NOS--;
         file=fopen(linea,"wb");if (file==NULL) { NOS--;TOS=*NOS;NOS--;continue; }
         fwrite((void*)*NOS,sizeof(char),TOS,file);
         fclose(file);//loaddir();
         NOS--;TOS=*NOS;NOS--;continue;
    case SLOAD:
          TOS=(int)FSOUND_Sample_Load(FSOUND_FREE,(char *)TOS,FSOUND_NORMAL,0,0);
          continue;
    case SPLAY:
         if (TOS!=0) 
            FSOUND_PlaySound(FSOUND_FREE,(FSOUND_SAMPLE *)TOS);
         else
            FSOUND_StopSound(FSOUND_ALL);
          TOS=*NOS;NOS--;continue;
//    mod = FMUSIC_LoadSong("../../media/invtro94.s3m");
//    FMUSIC_PlaySong(mod);   
//   FMUSIC_FreeSong(mod);

    default: // completa los 8 bits con apila numeros 0...
        NOS++;*NOS=TOS;TOS=W-ULTIMAPRIMITIVA;continue;
	} } };

//----------------------------------------------
struct Indice {	char *nombre;BYTE *codigo;int tipo;	 };
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
int cntpila;
int pila[256];

void apila(int n) { 
//if (cntpila>255) { sprintf(error,"apila error");ldebug(error);return; }
pila[cntpila++]=n; }

int desapila(void) { 
//if (cntpila==0) { sprintf(error,"desapila error");ldebug(error);return 0; }
return pila[--cntpila]; }

//---- espacio de dato
void adato(const char *p) 
{ strcpy((char*)&dato[cntdato],p);cntdato+=strlen(p)+1; } 

void adatonro(int n,int u)
{ BYTE *p=&dato[cntdato];     
switch(u) {
  case 1:*(char *)p=(char)n;break;// char
  case 2:*(short *)p=(short)n;break;// short
  case 4:*(int  *)p=(int)n;break;// int
  };
cntdato+=u;  }

void adatocnt(int n)
{ BYTE *p=&dato[cntdato];
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
	actualex->codigo=(actual->tipo==':')?&prog[cntprog]:&dato[cntdato];
	};
n=&nombre[cntnombre];
strcpy(n,p);cntnombre+=strlen(p)+1;//---- espacio de nombres
actual->nombre=n;
actual->codigo=(actual->tipo==':')?&prog[cntprog]:&dato[cntdato]; }

void endefine(void)
{
Indice *actual=&indice[cntindice-1];     
if (actual->tipo==':') {
  if (lastcall!=NULL) { *lastcall=JMP;lastcall=NULL; }
    else aprog(FIN);
  } else { if (&dato[cntdato]==actual->codigo) adatonro(0,4); } }

void endefinesin(void)
{
Indice *actual=&indice[cntindice-1];     
if (actual->tipo!=':' && &dato[cntdato]==actual->codigo) 
   adatonro(0,4); }

//---- parse de fuente
long numero;

int esnumero(char *p)
{//if (*p=='&') { p++;numero=*p;return 1;} // codigo ascii
int base,dig=0;    
int signo=0;
if (*p=='-') { p++;signo=1; } else if (*p=='+') p++;
switch(*p) {
  case '$': base=16;p++;break;// hexa
  case '%': base=2;p++;break;// binario
  default:  base=10;break; }; 
if (*p==0) return 0;// no es numero
numero=0;
while (*p!=0) {
  if (*p<='9') dig=*p-'0'; else if (*p>='A') dig=*p-'A'+10;
  else return 0;
  if (dig<0 || dig>=base) return 0;
  numero*=base;numero+=dig;
  p++;
  };
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
if((stream=fopen(lineat,"rb"))==NULL) return OPENERROR;
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
      case E_DATO:	adato(palabra);break;
      case E_PROG:	aux=(int)&dato[cntdato];adato(palabra);aprognro(aux);break; 
      };
    }
  else if (*palabra==':'||*palabra=='#')// define codigo y dato
    {
	if (cntpila>0) { sprintf(error,"bloque mal cerrado");goto error; }
	endefinesin();
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
		}
	}
  else if (esnumero(palabra)==1) // numero
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
            if (cntpila>0) aprog(FIN);// anidamiento compilo fin
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
               if (indice[numero].tipo=='#') aprog(ADR);
               else aprog(CALL);
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
               if (indiceex[numero].tipo=='#') aprog(ADR);
               else aprog(CALL);
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
cntindice=cntnombre=0;// espacio de nombres reset
return COMPILAOK;
error:
  sprintf(lineat,"%s|%d|%s",name,nrolinea,error);
  strcpy(error,lineat);
return CODIGOERROR;
}


void grabalinea(void)
{
FILE *stream;
if((stream=fopen("debug.err","w+"))==NULL) return;
fputs(error,stream); 
if(fclose(stream)) return; 
}

void dumpmem(void)
{
printf("\n******* %s *******\n",linea);
printf("pilac: %d  boot: %d\n",cntpila,bootaddr);
//printf("locales cnt:%d nom:%d bytes\n",cntindice,cntnombre);
//for (int i=0;i<cntindice;i++) { printf("%s ",indice[i].nombre); }
printf("palabras cnt:%d nom:%d bytes\n",cntindiceex,cntnombreex);
//for (int i=0;i<cntindiceex;i++) { printf("%s ",indiceex[i].nombre); }
printf("includes:%d\ndato:%d bytes\nprog:%d bytes\n\n",cntincludes,cntdato,cntprog);
//printf("\n====================\n"); 
}

//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
//   case IRMOU: SYSirqmouse=TOS;TOS=*NOS;NOS--;continue;
//    case IRKEY: SYSirqteclado=TOS;TOS=*NOS;NOS--;continue;
//    case IRJOY: SYSirqjoystick=TOS;TOS=*NOS;NOS--;continue;
//    case IRSON: SYSirqsonido=TOS;TOS=*NOS;NOS--;continue;
//    case IRNET: SYSirqred=TOS;TOS=*NOS;NOS--;continue;


//IRMOU,IRKEY,IRJOY,IRSON,IRNET,//---- nuevas interrups
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
switch (message) {     // handle message
    case WM_MOUSEMOVE:
         if (SYSXYM==lParam) break;
         SYSXYM=lParam;
         SYSEVENT=SYSirqmouse;//         SYSEVENT=SYSMM;
         break;
    case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:
    case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:         
         SYSBM=wParam;//&3;
         SYSEVENT=SYSirqmouse;//         SYSEVENT=SYSMS;
         break;
    case WM_MOUSEWHEEL:         
         SYSBM=((short)HIWORD(wParam)<0)?4:5;
         SYSEVENT=SYSirqmouse;//         SYSEVENT=SYSMS;
         break;
    case WM_KEYUP:
         // (lparam>>24)     ==1 keypad
         SYSKEY=((lParam>>16)&0x7f)|0x80;
         SYSEVENT=SYSirqteclado;//         SYSEVENT=SYSKEYM[128+SYSKEY];
         break;
    case WM_KEYDOWN:
         SYSKEY=(lParam>>16)&0x7f;
         SYSEVENT=SYSirqteclado;//         SYSEVENT=SYSKEYM[128+SYSKEY];
         break;
/*
    case WM_SOUND:
         SYSEVENT=SYSirqsonido;
         break;    
    case WM_NET:              
         SYSEVENT=SYSirqred;
         break;
    case WM_JOY:         
         SYSEVENT=SYSirqjoystick;
         break;         
*/
         
    case WM_ACTIVATEAPP:
         active=wParam&0xff;
         if (active==WA_INACTIVE)
            {
            ChangeDisplaySettings(NULL,0);
            ShowWindow(hWnd,SW_MINIMIZE);
            }
         else
            {
            ShowWindow(hWnd,SW_NORMAL);//SW_RESTORE);
            UpdateWindow(hWnd);
            }
         break;
/*	case WM_SETCURSOR:
        SetCursor(NULL);
		break;*/
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
  default:
       return DefWindowProc(hWnd,message,wParam,lParam);
  }
return 0;
}

//void clearkeymap()
//{ int *mk=SYSKEYM;for (int i=0;i<255;i++) { *mk++=0; } }

char *znam="R4win";
char *NDEBUG="debug.txt";

/*
char inifile[8192];

void cargaini(void)
{
FILE *file=fopen("r4.ini","rb");
if (file==NULL) return;
fread((void*)inifile,sizeof(char),8192,file);
fclose(file);
}
*/

//cargaini();
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
wc.style		= 0;//CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;    //CS_BYTEALIGNCLIENT |   CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_OWNDC;
wc.lpszClassName= znam;
wc.cbSize       = sizeof(WNDCLASSEX);
wc.lpfnWndProc	= WndProc;
wc.hInstance	= hInstance;
wc.hIcon		= 0;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DDICON));//LoadIcon(NULL, IDI_APPLICATION);
wc.hIconSm      = 0;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DDICON));//LoadIcon(NULL, IDI_APPLICATION);
wc.hCursor		= LoadCursor(NULL, IDC_ARROW);
wc.hbrBackground= 0;
wc.lpszMenuName	= NULL;
wc.cbClsExtra	= 0;
wc.cbWndExtra	= 0;
if(!RegisterClassEx(&wc))	return(0);
hWnd=CreateWindowEx(0,znam,znam,WS_POPUP|WS_VISIBLE,0,0,SCR_WIDTH,SCR_HEIGHT,NULL,NULL,hInstance,NULL);
if (hWnd==NULL)	return 0;
ShowWindow(hWnd,nCmdShow);
UpdateWindow(hWnd);
//void OpenSockets(void) 
WORD wVersionRequested = MAKEWORD(2,0);
WSADATA wsaData;
WSAStartup(wVersionRequested, &wsaData);

gr_ini();
//---------------------------------
if (!FSOUND_Init(44100, 32, 0)) return 1;
//---------------------------------
JoystickInit(hInstance);
//---------------------------------
strcpy(pathdata,".//");  // SEBAS win-linux
loaddir();
strcpy(linea,"main.txt");
//strcpy(lanterior,"");
recompila:
//   clearkeymap();//update();
   cntindiceex=cntnombreex=cntincludes=0;
   cntdato=cntprog=0;cntindice=cntnombre=0;// espacio de nombres reset
   bootaddr=NULL;//   ldebug("\ncompila:");ldebug(linea);   
   if (compilafile(linea)!=COMPILAOK) { 
      grabalinea(); //return 1;
      if (!strcmp(linea,NDEBUG)) return 1;
      strcpy(linea,NDEBUG);
      goto recompila; 
      }
if (bootaddr==NULL) {
   sprintf(error,"%s|0|NO BOOT",linea);                    
   grabalinea();
   if (!strcmp(linea,NDEBUG)) return 1;
   strcpy(linea,NDEBUG);
   goto recompila; 
   }
//update();	//ldebug("\nexec:");ldebug(linea);
//dumpmem();	
//saveimagen("test.img");          
if (interprete(bootaddr)==1) goto recompila;
//----------------------------------CLOSE
gr_fin();
//FinJoystick();   // joystick
WSACleanup();   // socket
FSOUND_Close(); // sonido

UnregisterClass(znam,wc.hInstance);
return 0;
}
