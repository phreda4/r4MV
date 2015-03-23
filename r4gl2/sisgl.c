//
// Rutinas opengl derivadas de 64k intro by RGBA (Iñigo Quiles)
// 
//--------------------------------------------------------------------------//

#ifdef A64BITS
#pragma pack(8) // VERY important, so WNDCLASS get's the correct padding and we don't crash the system
#endif

#include <GL/gl.h>
#include "sisgl.h"

int XRES;
int YRES;
int FRES;

//--------------EVENTOS
int evtbuffer[256];
int actevt,lstevt;

int SYSEVENT;
int SYSXYM;
int SYSBM;
int SYSKEY;

int active;

color32 gr_color1,gr_color2;
BYTE gr_alphav;

//--------------POLIGONOS
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

void mimemset(char *p,char v,int c)
{
for (;c>0;c--,p++) *p=v;
}

///////////////////////////////////////////////////////////////////////////////////
#ifdef linux
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>

typedef struct {
    Display     *hDisplay;
    GLXContext  hRC;
    Window      hWnd;
    int         full;
    char        wndclass[11];	// window class and title :)
} WININFO;

static int doubleBufferVisual[] = {
        GLX_RGBA,           // Needs to support OpenGL
        GLX_DEPTH_SIZE, 24, // Needs to support a 16 bit depth buffer
        GLX_DOUBLEBUFFER,   // Needs to support double-buffering
        None                // end of list
};

static WININFO wininfo = {  0,0,0,1, {':','r','4',0} };

XEvent      event;

#else ///////////////////////////////////////////////// win
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <winbase.h>
#include <mmsystem.h>
#include <gl/gl.h>

static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),    1,
    PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,    32,    0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0,
    32,             // zbuffer
    0,              // stencil!
    0,    PFD_MAIN_PLANE,    0, 0, 0, 0 };

typedef struct {
    HINSTANCE   hInstance;
    HWND        hWnd;
    HDC         hDC;
    HGLRC       hRC;
    int         full;
} WININFO;

static const char wndclass[] = ":r4";
WININFO     wininfo;
DEVMODE     screenSettings;  
MSG         msg;

#endif

///////////////////////////////////////////////////////////////////////////////////
long msys_timerGet(void)
{
#ifdef linux
    double long t;
    struct timeval now, res;
    gettimeofday(&now, 0);
    t=(now.tv_sec*1000)+(now.tv_usec/1000);
    return( (long)t );
#else
    return( timeGetTime() );
#endif
}

///////////////////////////////////////////////////////////////////////////////////
void endgl(void)
{
#ifdef linux       
XDestroyWindow(wininfo.hDisplay,wininfo.hWnd );
XCloseDisplay(wininfo.hDisplay );

#else
if(wininfo.hRC)  {
    wglMakeCurrent(0,0);
    wglDeleteContext(wininfo.hRC);
    }
if(wininfo.hDC) ReleaseDC(wininfo.hWnd,wininfo.hDC);
if(wininfo.hWnd) DestroyWindow(wininfo.hWnd);
UnregisterClass(wndclass,wininfo.hInstance);
if(wininfo.full) {
    ChangeDisplaySettings(0,0);
    ShowCursor(1); 
    }
#endif
}

//-----------eventos
/*
key.........char.scancod.
mmove.......x.y.
mbtn........b.w.

*/

int getevt(void)// 0 = vacio
{
if (actevt==lstevt) return 0;
int r=evtbuffer[actevt];
actevt=(actevt+1)&0xff;
return r;
}

#ifndef linux
//...............................................................................
static LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
switch (message) {     // handle message
    case WM_KEYDOWN:
         evtbuffer[lstevt]=0x10000000|((lParam>>16)&0x7f);
         lstevt=(lstevt+1)&0xff;
         break;
    case WM_KEYUP:         // (lparam>>24)     ==1 keypad
         evtbuffer[lstevt]=0x10000000|0x80|((lParam>>16)&0x7f);
         lstevt=(lstevt+1)&0xff;
         break;
    case WM_MOUSEMOVE:
         if (SYSXYM==lParam) break;
         evtbuffer[lstevt]=0x20000000|lParam;
         lstevt=(lstevt+1)&0xff;
         break;
    case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:         
         evtbuffer[lstevt]=0x30000000|wParam;
         lstevt=(lstevt+1)&0xff;
         break;
    case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:
         evtbuffer[lstevt]=0x31000000|wParam;
         lstevt=(lstevt+1)&0xff;
         break;
    case WM_MOUSEWHEEL:         
         evtbuffer[lstevt]=0x40000000|wParam;
         lstevt=(lstevt+1)&0xff;
         break;
    case WM_ACTIVATEAPP:
         active=wParam&0xff;
         if (active==WA_INACTIVE) {
            ChangeDisplaySettings(NULL,0);
            ShowWindow(hWnd,SW_MINIMIZE);
         } else {
            ShowWindow(hWnd,SW_NORMAL);//SW_RESTORE);
            UpdateWindow(hWnd);
            }
         break;
/*	case WM_SETCURSOR:
        SetCursor(NULL);
		break;*/
    case WM_DESTROY:
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_SYSCOMMAND:
        if (wParam==SC_SCREENSAVE||wParam==SC_MONITORPOWER) return 0;
        break;
  default:
       return DefWindowProc(hWnd,message,wParam,lParam);
  }
return 0;
}
#endif

///////////////////////////////////////////////////////////////////////
void upd_evt(void)
{
#if linux
while (XPending(wininfo.hDisplay)) {
   XNextEvent( wininfo.hDisplay, &event ); // XKeycodeToKeysym( wininfo.hDisplay, event.xkey.keycode, 0 )
   switch(event.type) {
     case KeyPress:
         evtbuffer[lstevt]=0x10000000|((event.xkey.keycode-8)&0x7f);
         lstevt=(lstevt+1)&0xff;
         break;
     case KeyRelease:
         evtbuffer[lstevt]=0x10000000|0x80|((event.xkey.keycode-8)&0x7f);
         lstevt=(lstevt+1)&0xff;
         break;
     case MotionNotify:
         evtbuffer[lstevt]=0x20000000|(event.xmotion.x<<16)|event.xmotion.y;
         lstevt=(lstevt+1)&0xff;
         break;
     case ButtonPress:
         evtbuffer[lstevt]=0x30000000|event.xbutton.button;
         lstevt=(lstevt+1)&0xff;
         break;
     case ButtonRelease:
         evtbuffer[lstevt]=0x31000000|event.xbutton.button;
         lstevt=(lstevt+1)&0xff;
         break;
     case DestroyNotify:
          // algo
         break;
     }
  }

#else
while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {   // TraslateMessage...
     DispatchMessage(&msg);
     while (active==WA_INACTIVE) {
         Sleep(10);
         PeekMessage(&msg,wininfo.hWnd,0,0,PM_REMOVE);
         TranslateMessage(&msg); 
         DispatchMessage(&msg);
         }
     }
#endif

}

///////////////////////////////////////////////////////////////////////////////////
int inigl(int w,int h,int f)
{
XRES=w;YRES=h;FRES=wininfo.full=f;

#ifdef linux //............................
XVisualInfo *visualInfo;
XSetWindowAttributes winAttr;
int         errorBase;
int         eventBase;
Colormap colorMap;

wininfo.hDisplay = XOpenDisplay( NULL );
if( !wininfo.hDisplay )        return( 0 );
if( !glXQueryExtension( wininfo.hDisplay, &errorBase, &eventBase ) )        return( 0 );
visualInfo = glXChooseVisual( wininfo.hDisplay, DefaultScreen(wininfo.hDisplay), doubleBufferVisual );
if( visualInfo == NULL )        return( 0 );
if ((wininfo.hRC=glXCreateContext(wininfo.hDisplay,visualInfo,NULL,GL_TRUE))==0) return 0;
colorMap=XCreateColormap( wininfo.hDisplay, RootWindow(wininfo.hDisplay, visualInfo->screen),visualInfo->visual, AllocNone );
winAttr.colormap=colorMap;winAttr.border_pixel=0;
winAttr.event_mask=ExposureMask|VisibilityChangeMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|
                     StructureNotifyMask | SubstructureNotifyMask | FocusChangeMask;
wininfo.hWnd = XCreateWindow( wininfo.hDisplay, RootWindow(wininfo.hDisplay, visualInfo->screen), 
                0, 0, XRES, YRES, 0, visualInfo->depth, InputOutput, 
				visualInfo->visual, CWBorderPixel | CWColormap | CWEventMask,
                &winAttr );
if( !wininfo.hWnd )        return( 0 );
    //XSetStandardProperties( wininfo.hDisplay, wininfo.hWnd, wininfo.wndclass, wininfo.wndclass, None, argv, argc, NULL );
char *argv[] = { ":r4", 0 };
XSetStandardProperties( wininfo.hDisplay, wininfo.hWnd, wininfo.wndclass,wininfo.wndclass, None, argv, 1, NULL );
glXMakeCurrent( wininfo.hDisplay, wininfo.hWnd, wininfo.hRC );
XMapWindow( wininfo.hDisplay, wininfo.hWnd );

#else //************************************** win       
unsigned int PixelFormat;DWORD dwExStyle, dwStyle; RECT rec; WNDCLASSA wc;
wininfo.hInstance = GetModuleHandle(0);
mimemset((char*)&wc,0,sizeof(WNDCLASSA));
wc.style         = CS_OWNDC;
wc.lpfnWndProc   = WndProc;
wc.hInstance     = wininfo.hInstance;
wc.lpszClassName = wndclass;
if(!RegisterClass((WNDCLASSA*)&wc)) return(0);
if(wininfo.full)    {
    mimemset((char*)&screenSettings,0,sizeof(screenSettings));
    #if _MSC_VER < 1400
    screenSettings.dmSize=148;
    #else
    screenSettings.dmSize=156;
    #endif
    screenSettings.dmFields=0x1c0000;
    screenSettings.dmBitsPerPel=32;screenSettings.dmPelsWidth=XRES;screenSettings.dmPelsHeight=YRES; 
    if(ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
      return(0);
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle   = WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
//    ShowCursor(0);
} else {
    dwExStyle = WS_EX_APPWINDOW;// | WS_EX_WINDOWEDGE;
    dwStyle   = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    }
rec.left=rec.top=0;rec.right=XRES;rec.bottom=YRES;
AdjustWindowRect(&rec,dwStyle,0);
wininfo.hWnd = CreateWindowEx( dwExStyle,wc.lpszClassName, wc.lpszClassName,dwStyle,
 (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,(GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
       rec.right-rec.left, rec.bottom-rec.top,0,0,wininfo.hInstance,0);
if(!wininfo.hWnd)                                      return( 0 );
if(!(wininfo.hDC=GetDC(wininfo.hWnd)))                 return( 0 );
if(!(PixelFormat=ChoosePixelFormat(wininfo.hDC,&pfd))) return( 0 );
if(!SetPixelFormat(wininfo.hDC,PixelFormat,&pfd))      return( 0 );
if(!(wininfo.hRC=wglCreateContext(wininfo.hDC)) )      return( 0 );
if(!wglMakeCurrent(wininfo.hDC,wininfo.hRC) )          return( 0 );
//SetCursor(NULL);
SetForegroundWindow(wininfo.hWnd);
SetFocus(wininfo.hWnd);
#endif

//....................gl
//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
glViewport(0,0,XRES,YRES);
glMatrixMode(GL_PROJECTION);glLoadIdentity();
glOrtho(0,XRES,YRES,0,-1,1);
//glOrtho(0,XRES,0,YRES,-1,1);
glMatrixMode(GL_MODELVIEW);glLoadIdentity();

glEnable(GL_BLEND);glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
gr_alphav=255;
yMin=YRES+1;
yMax=-1;
cntSegm=0;

actevt=lstevt=0; //clsevt
return( 1 );
}

void clsevt(void)
{
actevt=lstevt=0;
}

//**************************************************
//***** DIBUJO DE POLIGONO
//**************************************************

#define FBASE 8
void linegl(int x1,int y1,int x2,int y2,int col1,int col2)
{
int t;
if (y1==y2) return;
if (y1>y2) { t=x1;x1=x2;x2=t;t=y1;y1=y2;y2=t;t=col1;col1=col2;col2=t; }
if (y1>=YRES || y2<=0) return;
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

void delseg(Segm **inicio)
{
for (;inicio<(pact-1);inicio++)
    *inicio=*(inicio+1);
}

void addlin(Segm *ii) 
{
int xr=ii->x+ii->deltax;
Segm **cursor=(xquisc-1);
while (cursor>=xquis && (*cursor)->x>xr) {
      *(cursor+1)=*cursor;cursor--;
      }
*(cursor+1)=ii;
xquisc++;
}

     
void poligl(void)
{
Segm **ii;
Segm *scopia=segmentos;
pact=actual;
segmentos[cntSegm].y=-1;
if (yMax>YRES) { yMax=YRES; }
for (;yMin<yMax;yMin++) {
    while (scopia->y==yMin) {
          *pact=scopia;pact++;scopia++;
          }
    xquisc=xquis;
    ii=actual;
    while (ii<pact) {
          addlin(*ii);ii++;
          }
    for (ii=xquis;ii+1<xquisc;ii++) {
        glBegin(GL_LINES);
//        glColor4ub(((*ii)->colR>>16)&0xff,((*ii)->colG>>16)&0xff,((*ii)->colB>>16)&0xff,gr_alphav);        
        glVertex2i((*ii)->x>>FBASE,yMin);
        ii++;
//        glColor4ub(((*ii)->colR>>16)&0xff,((*ii)->colG>>16)&0xff,((*ii)->colB>>16)&0xff,gr_alphav);                
        glVertex2i((*ii)->x>>FBASE,yMin);
        glEnd(); 
//        gr_hline((*jj)->x>>FBASE,yMin,(*(jj+1))->x>>FBASE);
//          Flinea2(yMin,*jj,*(jj+1));
          }
    ii=actual;
    while (ii<pact) {
          if ((*ii)->y+1<(*ii)->yfin) {
             (*ii)->x+=(*ii)->deltax;
             (*ii)->y++;
             ii++;
          } else {
             delseg(ii);
             pact--;
             }
          }
    }    
yMin=YRES+1;
yMax=-1;
cntSegm=0;
}

///////////////////////////////////////////////////////////////////////
void swapgl(void)
{
#ifdef linux
glXSwapBuffers( wininfo.hDisplay, wininfo.hWnd );
#else
SwapBuffers( wininfo.hDC );
#endif
}

