#include <windows.h>

//---- eventos teclado y raton
int SYSXYM=0;
int SYSBM=0;
int SYSKEY=0;
int APPACTIVE;
HWND        hWnd;
WNDCLASSA   wc;
HDC         hDC;
MSG         msg;
DEVMODE     screenSettings;  
DWORD       dwExStyle, dwStyle; 
RECT        rec; 
static const char wndclass[] = ":r4";

///////////////////////////////////////////////////////////////////////
//...............................................................................
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
switch (message) {     // handle message
    case WM_MOUSEMOVE:
         if (SYSXYM==lParam) break;
         SYSXYM=lParam;
         break;
    case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:
    case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:         
         SYSBM=wParam;//&3;
         break;
    case WM_MOUSEWHEEL:         
         SYSBM=((short)HIWORD(wParam)<0)?4:5;
         break;
    case WM_KEYUP:        // (lparam>>24)     ==1 keypad
         SYSKEY=((lParam>>16)&0x7f)|0x80;
         break;
    case WM_KEYDOWN:
         SYSKEY=(lParam>>16)&0x7f;
         break;
    case WM_ACTIVATEAPP:
         APPACTIVE=wParam&0xff;
         if (APPACTIVE==WA_INACTIVE)
            {
            ChangeDisplaySettings(NULL,0);
            ShowWindow(hWnd,SW_MINIMIZE);
         } else {
            ShowWindow(hWnd,SW_NORMAL);//SW_RESTORE);
            UpdateWindow(hWnd);
            }
         break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
  default:
       return DefWindowProc(hWnd,message,wParam,lParam);
  }
return 0;
	// salvapantallas
//	if( uMsg==WM_SYSCOMMAND && (wParam==SC_SCREENSAVE || wParam==SC_MONITORPOWER) )	return( 0 );
}
//...............................................................................

void mimemset(char *p,char v,int c)
{
for (;c>0;c--,p++) *p=v;
}

///////////////////////////////////////////////////////////////////////////////////////////
//----------------- PRINCIPAL
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
int w=800,h=600,fullscreen=0,silent=0;
int i=0;
/*
char *aa=(char*)lpCmdLine;
while (*aa!=0) {
      if ('i'==*aa) { compilastr=aa+1; }
      if ('c'==*aa) { bootstr=aa+1;exestr=""; }
      if ('x'==*aa) { exestr=aa+1; }
      if ('w'==*aa) { esnumero(aa+1);w=numero; }
      if ('h'==*aa) { esnumero(aa+1);h=numero; }
      if ('f'==*aa) { fullscreen=1; }      
      if ('s'==*aa) { silent=1; }
      if ('?'==*aa) { print_usage();return 0; }
      while (*aa!=32) aa++;
      if (32==*aa) *aa=0;
      aa++; }
*/    
mimemset((char*)&wc,0,sizeof(WNDCLASSA));
wc.style         = 0; //CS_OWNDC;
wc.lpfnWndProc   = WndProc;
wc.hInstance     = GetModuleHandle(0);
wc.lpszClassName = wndclass;
if(!RegisterClass((WNDCLASSA*)&wc)) return -1;

if(fullscreen==1)    {
    mimemset((char*)&screenSettings,0,sizeof(screenSettings));
#if _MSC_VER < 1400
    screenSettings.dmSize=148;
#else
    screenSettings.dmSize=156;
#endif
    screenSettings.dmFields=0x1c0000;
    screenSettings.dmBitsPerPel=32;screenSettings.dmPelsWidth=w;screenSettings.dmPelsHeight=h; 
    if(ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return -4;
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle   = WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
} else {
    dwExStyle = WS_EX_APPWINDOW;// | WS_EX_WINDOWEDGE;
    dwStyle   = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    }
ShowCursor(0);
rec.left=rec.top=0;rec.right=w;rec.bottom=h;
AdjustWindowRect(&rec,dwStyle,0);
hWnd=CreateWindowEx( dwExStyle,wc.lpszClassName, wc.lpszClassName,dwStyle,
     (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,(GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
     rec.right-rec.left, rec.bottom-rec.top,0,0,wc.hInstance,0);
if(!hWnd) return -2;
if(!(hDC=GetDC(hWnd)))  return -3;

/*
if (gr_init(w,h)<0) return -1;

InitJoystick(hWnd);
if (sound_open(hWnd)!=0) return -4;
strcpy(pathdata,".//");  // SEBAS win-linux
loaddir();

//--------------------------------------------------------------------------
recompila:

bootaddr=0;
if (exestr[0]!=0) {
   #ifdef LOGMEM		
   ldebug("LOAD IMA:");ldebug(exestr);
   #endif
   loadimagen(exestr);
   } 
if (bootaddr==0 && bootstr[0]!=0){
   #ifdef LOGMEM
   ldebug("BOOTSTR:");ldebug(bootstr);
   #endif
   strcpy(linea,bootstr);
   cntindiceex=cntnombreex=cntincludes=0;// espacio de nombres reset
   cntdato=cntprog=0;cntindice=cntnombre=0;
   if (compilafile(linea)!=COMPILAOK) { 
      grabalinea();
//    return 1;
      if (!strcmp(linea,NDEBUG)) return 1;
      exestr="debug.r4x";goto recompila;
      }
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
//    return 1;
   if (!strcmp(linea,NDEBUG)) return 1;
   exestr="debug.r4x";goto recompila;//   strcpy(linea,NDEBUG);
   }
#ifdef LOGMEM		
dumpex();dumplocal("BOOT");
#endif
memlibre=data+cntdato; // comienzo memoria libre
if (silent!=1 && interprete(bootaddr)==1) goto recompila;
//--------------------------------------------------------------------------
ReleaseJoystick();
closeSocket();
sound_close();
gr_fin();

*/
ReleaseDC(hWnd,hDC);
DestroyWindow(hWnd);
ExitProcess(0);
return 0;
}
