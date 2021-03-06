/*
 * Copyright (C) 2013 r4 for Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2013, Pablo Hugo Reda <pabloreda@gmail.com>, Mar del Plata, Argentina
 * All rights reserved.
 */

#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "graf.h"
#include "sound.h"

// ----------------------------------------------------------------------
/* Set to 1 to enable debug log traces. */
///#define DEBUG 0

static void logsd(char *s)
		{
	LOGE(s);
	FILE *fo=fopen("/sdcard/r4/log.txt","a");
	fwrite(s,1,strlen(s),fo);
	fclose(fo);
		}

// ----------------------------------------------------------------------
struct engine {
    struct android_app* app;
    int animating;
};

struct engine engine;
struct android_poll_source* source;
int events;

//----------------------------------------------------------------------------
char *macros[]={// directivas del compilador
";","(",")",")(","[","]","EXEC",
"0?","+?","-?","1?","=?","<?",">?","<=?",">=?","<>?","AND?","NAND?",
"DUP","DROP","OVER","PICK2","PICK3","PICK4","SWAP","NIP","ROT", //--- pila
"2DUP","2DROP","3DROP","4DROP","2OVER","2SWAP",
">R","R>","R","R+","R@+","R!+","RDROP",//--- pila direcciones 40
"AND","OR","XOR","NOT",                //--- logicas
"+","-","*","/","*/","*>>","/MOD","MOD","ABS", //--- aritmeticas
"SQRT","CLZ","<</",
"NEG","1+","4+","1-","2/","2*","<<",">>",
"@","C@","W@","!","C!","W!","+!","C+!","W+!", //--- memoria
"@+","!+","C@+","C!+","W@+","W!+", // 79
"MOVE","MOVE>","CMOVE","CMOVE>",//-- movimiento de memoria
"MEM", "FFIRST","FNEXT",
"LOAD","SAVE","APPEND",//--- memoria,bloques
"UPDATE",
"XYMOUSE","BMOUSE","INFOIN",      //-------- mouse
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
"SLOAD","SPLAY","SINFO","SSET",    //-------- sonido
//--------------------- red
"OPENURL",
//---------------------
"DOCINI","DOCEND","DOCAT","DOCLINE","DOCTEXT","DOCFONT","DOCBIT","DOCRES","DOCSIZE", //-- impresora
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
MEM, FFIRST,FNEXT,
LOAD,SAVE,APPEND,//--- bloques de memoria, bloques
UPDATE,
XYMOUSE,BMOUSE,INFOIN,
SKEY, KEY,
CNTJOY,GETJOY,
MSEC,TIME,IDATE,SISEND,SISRUN,//--- sistema
WIDTH,HEIGHT,CLS,REDRAW,FRAMEV,//--- pantalla
SETXY,MPX,SPX,GPX,
VXFB,TOXFB,XFBTO,
COLORF,COLOR,COLORA,ALPHA,//--- color
OP,LINE,CURVE,CURVE3,PLINE,PCURVE,PCURVE3,POLI,//--- dibujo
FCOL,FCEN,FMAT,SFILL,LFILL,RFILL,TFILL, //--- pintado
SLOAD,SPLAY,SINFO,SSET,
OPENURL,
DOCINI,DOCEND,DOCMOVE,DOCLINE,DOCTEXT,DOCFONT,DOCBIT,DOCRES,DOCSIZE,
SYSTEM,
ULTIMAPRIMITIVA// de aqui en mas.. apila los numeros 0..255-ULTIMAPRIMITIVA
};

//---------------------- Memoria de r4

int gx1=0,gy1=0;// coordenadas de linea
unsigned char *bootaddr;
FILE *file;

char linea[1024];// 1k linea
char error[1024];

//---- dato y programa
int cntdato;
int cntprog;
unsigned char *memlibre;
//--- Memoria
unsigned char prog[1024*1024];// 1MB de programa
unsigned char data[1024*1024*4];// 4MB de datos
//----- PILAS
int PSP[1024];// 1k pila de datos
unsigned char *RSP[1024];// 1k pila de direcciones
unsigned char ultimapalabra[]={ SISEND };

//---- eventos teclado y raton
struct infoi {
	int SYSINFO;
	int SYSXM,SYSYM,SYSBM;
	int SYSXM1,SYSYM1,SYSBM1;
	int SYSXM2,SYSYM2,SYSBM2;
	int SYSXM3,SYSYM3,SYSBM3;
	int SYSXM4,SYSYM4,SYSBM4;
};

struct infoi infoi;

int SYSKEY=0;

//---- Date & Time
struct timespec times;
struct timeval Time;
time_t sit;
struct tm *sitime;
//---- Directory
DIR *dp=0;
struct dirent *dirp=0;
//---- stackrun
char pilaexec[1024];
char *pilaexecl;
char *rootpath="/sdcard/r4";
char *bootstr;
int rebotea;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		infoi.SYSINFO=AMotionEvent_getPointerCount(event);
    	int32_t action=AMotionEvent_getAction(event);

    	infoi.SYSXM=(int)AMotionEvent_getX(event, 0);infoi.SYSYM=(int)AMotionEvent_getY(event, 0);
    	infoi.SYSBM=(action==AMOTION_EVENT_ACTION_UP)?0:1;
		if (infoi.SYSINFO>1) {
		infoi.SYSXM1=(int)AMotionEvent_getX(event, 1);infoi.SYSYM1=(int)AMotionEvent_getY(event, 1);
		infoi.SYSBM1=(action==(0x100|AMOTION_EVENT_ACTION_POINTER_UP))?0:1;
		infoi.SYSXM2=(int)AMotionEvent_getX(event, 2);infoi.SYSYM2=(int)AMotionEvent_getY(event, 2);
		infoi.SYSBM2=(action==(0x200|AMOTION_EVENT_ACTION_POINTER_UP))?0:1;
		infoi.SYSXM3=(int)AMotionEvent_getX(event, 3);infoi.SYSYM3=(int)AMotionEvent_getY(event, 3);
		infoi.SYSBM3=(action==(0x300|AMOTION_EVENT_ACTION_POINTER_UP))?0:1;
		infoi.SYSXM4=(int)AMotionEvent_getX(event, 4);infoi.SYSYM4=(int)AMotionEvent_getY(event, 4);
		infoi.SYSBM4=(action==(0x400|AMOTION_EVENT_ACTION_POINTER_UP))?0:1;
		}
		//LOGI("SYSXMY: %d %d %d",SYSXM,SYSYM,SYSBM);
        return 1; }
if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) {
    	SYSKEY=AKeyEvent_getAction(event)<<7|AKeyEvent_getKeyCode(event);
        LOGI("Key event: action=%d keyCode=%d metaState=0x%x",
                AKeyEvent_getAction(event), AKeyEvent_getKeyCode(event), AKeyEvent_getMetaState(event));
        }
return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
switch (cmd) {
   case APP_CMD_SAVE_STATE:
	  LOGI("SAVE STATE");
	  // the OS asked us to save the state of the app
      break;
   case APP_CMD_INIT_WINDOW:
      // get the window ready for showing
	  LOGI("INI WIN");
      break;
   case APP_CMD_TERM_WINDOW:
      // clean up the window because it is being hidden/closed
	  LOGI("TERM WIN");
      break;
   case APP_CMD_LOST_FOCUS:
      // if the app lost focus, avoid unnecessary processing (like monitoring the accelerometer)
	  LOGI("LOST FOC");
	  engine.animating=0;
      break;
   case APP_CMD_GAINED_FOCUS:
      // bring back a certain functionality, like monitoring the accelerometer
	  LOGI("GAIN FOC %d",engine.app->window);
	  engine.animating=1;
      break;
   case APP_CMD_CONFIG_CHANGED:
     /* Handle rotation / orientation change */
     LOGI("handle_cmd: APP_CMD_CONFIG_CHANGED");
	 gr_size(app);
     break;
   case APP_CMD_WINDOW_RESIZED:
     LOGI("handle_cmd: APP_CMD_WINDOW_RESIZED");
     break;
   }
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#ifdef __GNUC__
#define iclz32(x) __builtin_clz(x)
#else
static inline int popcnt(int x)
{
x -= ((x >> 1) & 0x55555555);
x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
x = (((x >> 4) + x) & 0x0f0f0f0f);
x += (x >> 8);x += (x >> 16);
return x & 0x0000003f;
}
static inline int iclz32(int x)
{
x |= (x >> 1);x |= (x >> 2);x |= (x >> 4);x |= (x >> 8);x |= (x >> 16);
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


//---------------------------------------------------------------
static int interprete(unsigned char *codigo)// 1=recompilar con nombre en linea
{
if (codigo==NULL) return -1;
register int TOS;			// Tope de la pila PSP
register int *NOS;			// Next of stack
register unsigned char **R;			// return stack
unsigned char *IP=codigo;	// lugar del programa // ebx
unsigned int W,W1;			// palabra actual y auxiliar
unsigned int *vcursor=gr_buffer;

R=RSP;*R=(unsigned char*)&ultimapalabra;
NOS=PSP;*NOS=TOS=0;
while (1)  {// Charles Melice  suggest next:... goto next; bye !
    W=(unsigned char)*IP++;
    //LOGI("w:%d IP:%d r:%d",W,IP,(int)R);
	switch (W) {// obtener codigo de ejecucion
	case FIN: IP=*R;R--;continue;
    case LIT: NOS++;*NOS=TOS;TOS=*(int*)IP;IP+=sizeof(int);continue;
    case ADR: NOS++;*NOS=TOS;W=*(int*)IP;IP+=sizeof(int);TOS=*(int*)W;continue;
    case CALL: W=*(int*)IP;IP+=sizeof(int);R++;*R=IP;IP=(unsigned char*)W;continue;
	case JMP: W=*(int*)IP;IP=(unsigned char*)W;continue;
    case JMPR: W=*(int8_t*)IP;W++;IP+=W;continue;
//-hasta aca solo lo escribe el compilador
//--- condicionales
	case IF: W=*(int8_t*)IP;IP++;if (TOS!=0) IP+=W; continue;
    case PIF: W=*(int8_t*)IP;IP++;if (TOS<=0) IP+=W; continue;
	case NIF: W=*(int8_t*)IP;IP++;if (TOS>=0) IP+=W; continue;
    case UIF: W=*(int8_t*)IP;IP++;if (TOS==0) IP+=W; continue;
    case IFN: W=*(int8_t*)IP;IP++;if (TOS!=*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
    case IFNO: W=*(int8_t*)IP;IP++;if (TOS==*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
    case IFL: W=*(int8_t*)IP;IP++;if (TOS<=*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
    case IFG: W=*(int8_t*)IP;IP++;if (TOS>=*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
    case IFLE: W=*(int8_t*)IP;IP++;if (TOS<*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
    case IFGE: W=*(int8_t*)IP;IP++;if (TOS>*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
    case IFAND: W=*(int8_t*)IP;IP++;if (!(TOS&*NOS)) IP+=W;
		TOS=*NOS;NOS--;continue;
    case IFNAND: W=*(int8_t*)IP;IP++;if (TOS&*NOS) IP+=W;
		TOS=*NOS;NOS--;continue;
//--- fin condicionales dependiente de bloques
//	case EXEC:W=TOS;TOS=*NOS;NOS--;if (W!=0) { R++;*R=IP;IP=(unsigned char*)W; } continue;
	case EXEC:R++;*R=IP;IP=(unsigned char*)TOS;TOS=*NOS;NOS--;continue;
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
	case TOR: R++;*R=(unsigned char*)TOS;TOS=*NOS;NOS--;continue;
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
    case CFECH: TOS=*(int8_t*)TOS;continue;
    case WFECH: TOS=*(short *)TOS;continue;
	case STOR: *(int *)TOS=(int)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CSTOR: *(int8_t*)TOS=(int8_t)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case WSTOR: *(short *)TOS=(short)*NOS;NOS--;TOS=*NOS;NOS--;continue;
	case INCSTOR: *((int *)TOS)+=(int)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CINCSTOR: *((int8_t*)TOS)+=(int8_t)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case WINCSTOR: *((short *)TOS)+=(short)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case FECHPLUS: NOS++;*NOS=TOS+4;TOS=*(int *)TOS;continue; //@+ | adr -- adr' v
    case STOREPLUS: *(int *)TOS=(int)*NOS;TOS+=4;NOS--;continue;//!+ | v adr -- adr'
    case CFECHPLUS: NOS++;*NOS=TOS+1;TOS=*(int8_t*)TOS;continue;
    case CSTOREPLUS: *(int8_t*)TOS=(int8_t)*NOS;TOS++;NOS--;continue;
    case WFECHPLUS: NOS++;*NOS=TOS+2;TOS=*(short *)TOS;continue;
    case WSTOREPLUS: *(short *)TOS=(short)*NOS;TOS+=2;NOS--;continue;
//--- sistema
	case UPDATE:
		if (ALooper_pollAll(engine.animating?0:-1,NULL,&events,(void**)&source)>=0) { // while come eventos? animating??
			if (source != NULL) { source->process(engine.app, source); }
			if (engine.app->destroyRequested != 0) {
	                LOGI("Engine thread destroy requested!");
	                rebotea=1;
	                return 0;
	            }
	        }
		break;
//---- raton

    case XYMOUSE: NOS++;*NOS=TOS;NOS++;*NOS=infoi.SYSXM;TOS=infoi.SYSYM;continue;
    case BMOUSE: NOS++;*NOS=TOS;TOS=infoi.SYSBM;continue;
    case INFOIN: NOS++;*NOS=TOS;TOS=(int)&infoi;continue;

//----- teclado
    case SKEY: SYSKEY=TOS;TOS=*NOS;NOS--;continue;
	case KEY: NOS++;*NOS=TOS;TOS=SYSKEY&0xff;continue;
//----- joy
    case CNTJOY: NOS++;*NOS=TOS;TOS=0;continue;
    case GETJOY: TOS=0;continue;
    case REDRAW: gr_swap(engine.app);continue;
    case MSEC:
		NOS++;*NOS=TOS;
	    gettimeofday( &Time, NULL );
	    TOS=Time.tv_sec*1000+Time.tv_usec/1000;
		//clock_gettime(CLOCK_MONOTONIC,&times);
	    //TOS=times.tv_sec*1000+times.tv_nsec/1000000;
		continue;
    case IDATE:
    	sit=time(NULL);sitime=localtime(&sit);
    	NOS++;*NOS=TOS;TOS=sitime->tm_year+1900;
        NOS++;*NOS=TOS;TOS=sitime->tm_mon+1;
        NOS++;*NOS=TOS;TOS=sitime->tm_mday;continue;
    case TIME: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_sec;
        NOS++;*NOS=TOS;TOS=sitime->tm_min;NOS++;*NOS=TOS;TOS=sitime->tm_hour;continue;
    case SISEND:
         return 0;
    case SISRUN:
    	if (TOS==0) { rebotea=1;return 0; }
    	strcpy(pilaexecl,(char*)TOS);
//    	LOGE((char*)TOS);
    	while (*pilaexecl!=0) pilaexecl++;
    	pilaexecl++;
        return 1;
//--- pantalla
    case WIDTH: NOS++;*NOS=TOS;TOS=buffergr.width;continue;
    case HEIGHT: NOS++;*NOS=TOS;TOS=buffergr.height;continue;
	case CLS: gr_clrscr();continue;
    case FRAMEV: NOS++;*NOS=TOS;TOS=(int)gr_buffer;continue;
	case SETXY: vcursor=gr_buffer+((TOS*buffergr.width)+*NOS);NOS--;TOS=*NOS;NOS--;continue;
	case MPX:vcursor+=TOS;TOS=*NOS;NOS--;continue;
	case SPX:*vcursor++=TOS;TOS=*NOS;NOS--;continue;
	case GPX:NOS++;*NOS=TOS;TOS=*vcursor;continue;

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
    case SLOAD: // "" -- pp
    	TOS=createAudioPlayer((char *)TOS);
        continue;
    case SPLAY: // pp --
    	SNDplay(TOS);
        TOS=*NOS;NOS--;
        continue;
    case SINFO: // "" -- mm
        TOS=(int)isPlaying(TOS);
        continue;
    case SSET: // pan vol frec ss --
       	setRate(TOS,*(NOS));
//		SNDset(TOS,*(NOS),*(NOS-1),*(NOS-2));
        TOS=*(NOS-3);NOS-=4;continue;

//--- bloque de memoria
    case MEM: NOS++;*NOS=TOS;TOS=(int)memlibre;continue; // inicio de n-MB de datos
//--- bloques

    case FFIRST: // "" -- fdd/0
    	if (dp!=NULL) closedir(dp);
    	strcpy(error,rootpath);
    	strcat(error,"/");
    	strcat(error,(char*)TOS);
    	dp=opendir(error);
    	if (dp!=NULL) dirp=readdir(dp); else dirp=0;
        TOS=(int)dirp;
         continue;
    case FNEXT: // -- fdd/0
         NOS++;*NOS=TOS;
         if (dp!=NULL) dirp=readdir(dp); else dirp=0;
         TOS=(int)dirp;
         continue ;
	case LOAD: // 'from "filename" -- 'to
         if (TOS==0||*NOS==0) { TOS=*NOS;NOS--;continue; }
         strcpy(error,rootpath);
         strcat(error,"/");
         strcat(error,(char*)TOS);
         file=fopen(error,"rb");
         TOS=*NOS;NOS--;
         if (file==NULL) continue;
         do { W=fread((void*)TOS,sizeof(char),1024,file); TOS+=W; } while (W==1024);
         fclose(file);continue;
    case SAVE: // 'from cnt "filename" --
    	 strcpy(error,rootpath);
    	 strcat(error,"/");
    	 strcat(error,(char*)TOS);
         if (TOS==0||*NOS==0) { remove(error);NOS-=2;TOS=*NOS;NOS--;continue; }
         file=fopen(error,"wb");
         TOS=*NOS;NOS--;
         if (file==NULL) { NOS--;TOS=*NOS;NOS--;continue; }
         fwrite((void*)*NOS,sizeof(char),TOS,file);
         fclose(file);
         NOS--;TOS=*NOS;NOS--;continue;
    case APPEND: // 'from cnt "filename" --
         if (TOS==0||*NOS==0) { NOS-=2;TOS=*NOS;NOS--;continue; }
    	 strcpy(error,rootpath);
    	 strcat(error,"/");
    	 strcat(error,(char*)TOS);
         file=fopen(error,"ab");
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
         while (TOS--) { *(int8_t*)W++=*(int8_t*)W1++; }
         NOS-=2;TOS=*NOS;NOS--;
         continue;
    case CMOVEA: // | de sr cnt --
         W=(*(NOS-1))+TOS;W1=(*NOS)+TOS;
         while (TOS--) { *(int8_t*)--W=*(int8_t*)--W1; }
         NOS-=2;TOS=*NOS;NOS--;
         continue;
    case OPENURL: // url header buff -- buff/0
         NOS-=2;
         TOS=0;
         continue;
    case DOCINI:
        continue;
    case DOCEND:
        continue;
    case DOCMOVE: // x y --
        NOS--;TOS=*(NOS);NOS--;
        continue;
    case DOCLINE: // x y --
        NOS--;TOS=*(NOS);NOS--;
        continue;
    case DOCTEXT: // "tt" --
        TOS=*(NOS);NOS--;
        continue;
    case DOCSIZE: // "tt" -- w h
        NOS++;*(NOS)=0;TOS=0;
        continue;
    case DOCFONT: // size angle "font" --
        NOS-=2;TOS=*(NOS);NOS--;
        continue;
    case DOCBIT: // bitmap x y --
        NOS-=2;TOS=*(NOS);NOS--;
        continue;
    case DOCRES: // -- xmax ymax
        NOS++;*NOS=TOS;TOS=0;
        NOS++;*NOS=TOS;TOS=0;
        continue;
    case SYSTEM: // "" --
        //if (TOS!=0)
        //system((int8_t*)TOS);
        TOS=(*NOS);NOS--;
        continue;
	default: // completa los 8 bits con apila numeros 0...
        NOS++;*NOS=TOS;TOS=W-ULTIMAPRIMITIVA;continue;
	} }
};

//----------------------------------------------------------------------------
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

//----------------------------------------------
struct Indice {	char *nombre;unsigned char *codigo;int tipo; };
//---- diccionario local
int cntindice;
struct Indice indice[2048];
int cntnombre;
char nombre[1024*16];
//---- diccionario exportados
int cntindiceex;
struct Indice indiceex[4096];
int cntnombreex;
char nombreex[1024*32];
//---- includes
int cntincludes;
struct Indice includes[100];
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

//---- espacio de dato
void adato(const char *p)
{ strcpy((int8_t*)&data[cntdato],p);cntdato+=strlen(p)+1; }

void adatonro(int n,int u)
{ unsigned char *p=&data[cntdato];
switch(u) {
  case 1:*(char *)p=(char)n;break;// char
  case 2:*(short *)p=(short)n;break;// short
  case 4:*(int  *)p=(int)n;break;// int
  };
cntdato+=u;  }

void adatocnt(int n)
{ unsigned char *p=&data[cntdato];
int i;
for (i=0;i<n;i++,p++) *p=0;
cntdato+=n; }

//---- espacio de codigo
unsigned char *lastcall=NULL;

void aprognro(int n) // graba nro como literal
{ unsigned char *p=&prog[cntprog];lastcall=NULL;
if (n>=0 && n<255-ULTIMAPRIMITIVA) {
  *p=ULTIMAPRIMITIVA+n;cntprog++;
} else {
  *p=LIT;p++;*(int *)p=(int)n;
  cntprog+=5; } }

void aprog(int n) // grabo primitiva
{ unsigned char *p=&prog[cntprog];*p=(unsigned char)n;
if (n==CALL) lastcall=p; else lastcall=NULL;
cntprog++; }

void aprogint(int n)
{ unsigned char *p=&prog[cntprog];*(unsigned int*)p=(unsigned int)&prog[n];cntprog+=4; }

void aprogaddr(int n) // grabo direccion
{ unsigned char *p=&prog[cntprog];*(unsigned int*)p=(unsigned int)indice[n].codigo;cntprog+=4; }

void aprogaddrex(int n) // grabo direccion exportada
{ unsigned char *p=&prog[cntprog];*(unsigned int*)p=(unsigned int)indiceex[n].codigo;cntprog+=4; }

//---- definicion
void define(char *p)
{
struct Indice *actualex,*actual=&indice[cntindice++];
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
struct Indice *actual=&indice[cntindice-1];
if (actual->tipo==':') {
   compilofin();
//  if (lastcall!=NULL) { *lastcall=JMP;lastcall=NULL; } else aprog(FIN);
  } else { if (&data[cntdato]==actual->codigo) adatonro(0,4); } }

void endefinesin(void)
{
struct Indice *actual=&indice[cntindice-1];
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
struct Indice *actual=&indice[numero];
while (actual>=indice) {
  if (!strcmp(actual->nombre,p)) return 1;
  actual--;numero--;  }
return 0;  }

int espalabraex(char *p)
{
numero=cntindiceex-1;
struct Indice *actual=&indiceex[numero];
while (actual>=indiceex) {
  if (!strcmp(actual->nombre,p)) return 1;
  actual--;numero--; }
return 0; }

//----- Include
int estainclude(char *palabra)
{
if (cntincludes==0) return 0;
struct Indice *actual=&includes[cntincludes-1];
while (actual>=includes) {
	if (!strcmp(actual->nombre,palabra)) return 1;
	actual--; }
return 0; }

void agregainclude(char *palabra)
{
	struct Indice *act=&includes[cntincludes++];
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

int strnicmp(const char* s1, const char* s2, int n)
{
do {
   if (tolower(*s1) != tolower(*s2++)) return (int)tolower(*s1)-(int)tolower(*--s2);
   if (*s1++ == 0) break;
} while (--n != 0);
return 0;
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

strcpy(lineat,rootpath);
strcat(lineat,"/");
strcat(lineat,name);
if((stream=fopen(lineat,"rb"))==NULL) {
//if((stream=fopen(name,"rb"))==NULL) {

  sprintf(error,"%s|0|0|no existe %s",linea,lineat);
  return OPENERROR;
  }
int estado=E_PROG;int unidad=4;int salto=0;
int aux,nrolinea=0;// convertir a nro de linea local
cntpila=0;
while(!feof(stream)) {
  *lineat=0;fgets(lineat,512,stream);ahora=lineat; // ldebug(ahora);
//  LOGI(lineat);
//  logsd(lineat);
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
     if (strnicmp(palabra,"|AND|",5)==0)
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

static void makeFolder(char *path)
{
const char *namea;
struct AAssetManager *aaM=engine.app->activity->assetManager;
struct AAssetDir *aaD;
struct AAsset *aaS;
FILE *f;
long size;
char namep[256];
char namef[256];
char buff[1025];
strcpy(namep,rootpath);
strcat(namep,path);
//LOGI("FOLDER: %s",namep);
mkdir(namep, 0777);

// copiar archivos
aaD=AAssetManager_openDir(aaM,((*path)==0)?path:path+1);
namea=AAssetDir_getNextFileName(aaD);
while  (namea!=0) {
//	LOGE(namea);
	if (*path!=0) { strcpy(namef,path+1);strcat(namef,"/"); } else *namef=0;
	strcat(namef,namea);
//	LOGI(namef);
	aaS=AAssetManager_open(aaM,namef,AASSET_MODE_BUFFER);

	strcpy(namef,namep);strcat(namef,"/");strcat(namef,namea);
//	LOGW("%s %d",namef,aaS);

	f=fopen(namef, "wb");
	while ((size = AAsset_read(aaS, buff,1024)) > 0)
	  fwrite(buff,size,1,f);
	fclose(f);

	AAsset_close(aaS);
	namea=AAssetDir_getNextFileName(aaD);
	}
AAssetDir_close(aaD);
}

static void buildFileSystem(void)
{
struct stat st = {0};
LOGW("prebuild");

if (stat(rootpath, &st) != -1) return; // ya existe la carpeta

LOGW("creando");

makeFolder("");
makeFolder("/inc");
makeFolder("/inc/rft");
makeFolder("/inc/ric");
makeFolder("/inc/gesto");
makeFolder("/mem");
makeFolder("/r4");
makeFolder("/r4/apps");
makeFolder("/r4/demos");
makeFolder("/r4/demos/test");
makeFolder("/r4/dev");
makeFolder("/r4/dev/games");
makeFolder("/r4/dev/graficos");
makeFolder("/r4/dev/editors");
makeFolder("/r4/games");
makeFolder("/r4/lib");
makeFolder("/r4/lib/fonts");
makeFolder("/r4/lib/hershey");
makeFolder("/r4/system");
}

//----------------------------------------------------------------------------
void android_main(struct android_app* state)
{
app_dummy();

memset(&engine, 0, sizeof(engine));
state->userData = &engine;
state->onAppCmd = engine_handle_cmd;
state->onInputEvent = engine_handle_input;
engine.app = state;

buildFileSystem();

// eventos para inicializar
while (ALooper_pollAll(engine.animating?0:-1,NULL,&events,(void**)&source)>=0) {
	if (source != NULL) { source->process(state, source); }
	if (state->destroyRequested != 0) return;
    }

gr_init(engine.app);
SOUNDinit();
// pila de ejecucion
pilaexecl=pilaexec;
strcpy(pilaexecl,"main.txt");
while (*pilaexecl!=0) pilaexecl++;
pilaexecl++;

//........................................................
recompila:

SOUNDreset();

bootstr=pilaexecl-2;
while (*bootstr!=0 && bootstr>pilaexec) bootstr--;
if (bootstr>pilaexec) bootstr++;

cntindiceex=cntnombreex=cntincludes=0;// espacio de nombres reset
cntdato=cntprog=0;cntindice=cntnombre=0;

LOGI("compilando %s..",bootstr);
if (compilafile(bootstr)!=COMPILAOK) { /*logsd(error);*/gr_fin();exit(0);return ; }
LOGI("ok");
memlibre=data+cntdato; // comienzo memoria libre
if (interprete(bootaddr)==1) goto recompila;
if (rebotea==0)
    {
    pilaexecl--;pilaexecl--;
    while (*pilaexecl!=0 && pilaexecl>pilaexec) pilaexecl--;
    if (*pilaexecl==0) { pilaexecl++; goto recompila; }
    }
//........................................................
LOGI("FIN OK.");
SOUNDend();
gr_fin();
exit(0);
}
