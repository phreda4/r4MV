/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>

#include "sisgl.h"  // sistema GL

int main(int argc, char **argv)
{
if (inigl(800,600,0)<0) return -1;
int W,salir=0;
upd_evt();
while (salir==0) 
      {
      upd_evt();W=getevt();
      if (((W>>28)&0xf)==1) salir=1;
//                      case 1:SYSKEY=W&0xff;SYSEVENT=SYSirqteclado;break;
      glClear(GL_COLOR_BUFFER_BIT);

       linegl(100,100,200,300,0xff0000,0xffffff);
       linegl(200,300,0,200,0xffffff,0x0000);
       linegl(0,200,100,100,0x0000,0xff0000);
       poligl();
       
//       xop(100,100,0,0xffff00);
//       xline(200,200,0,0xffffff);
//       xline(0,200,0,0xff00ff);
//       xpoli();     

      swapgl();
      }

endgl();
return 0;
}
