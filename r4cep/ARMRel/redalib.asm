	TTL	C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\redalib.cpp

	AREA	|.drectve|, DRECTVE
	DCB	"-defaultlib:coredll.lib "
	DCB	"-defaultlib:corelibc.lib "

	EXPORT	|?hInst@@3PAUHINSTANCE__@@A| [ DATA ]	; hInst
	EXPORT	|?hWnd@@3PAUHWND__@@A| [ DATA ]		; hWnd
	EXPORT	|?mxpos@@3GA| [ DATA ]			; mxpos
	EXPORT	|?mypos@@3GA| [ DATA ]			; mypos
	EXPORT	|?mbutton@@3_NA| [ DATA ]		; mbutton
	EXPORT	|?tecla@@3HA| [ DATA ]			; tecla
	EXPORT	|?evento@@3HA| [ DATA ]			; evento
	EXPORT	|?SYSirqlapiz@@3HA| [ DATA ]		; SYSirqlapiz
	EXPORT	|?SYSirqteclado@@3HA| [ DATA ]		; SYSirqteclado
	EXPORT	|?SYSirqsonido@@3HA| [ DATA ]		; SYSirqsonido
	EXPORT	|?SYSirqred@@3HA| [ DATA ]		; SYSirqred
	EXPORT	|?SYSirqjoystick@@3HA| [ DATA ]		; SYSirqjoystick
	EXPORT	|?kl@@3UGXKeyList@@A| [ DATA ]		; kl

	AREA	|.bss|, NOINIT
|?hInst@@3PAUHINSTANCE__@@A| % 0x4			; hInst
|?hWnd@@3PAUHWND__@@A| % 0x4				; hWnd
|?mxpos@@3GA| %	0x2					; mxpos
|?mypos@@3GA| %	0x2					; mypos
|?mbutton@@3_NA| % 0x1					; mbutton
|?tecla@@3HA| %	0x4					; tecla
|?evento@@3HA| % 0x4					; evento
|?SYSirqlapiz@@3HA| % 0x4				; SYSirqlapiz
|?SYSirqteclado@@3HA| % 0x4				; SYSirqteclado
|?SYSirqsonido@@3HA| % 0x4				; SYSirqsonido
|?SYSirqred@@3HA| % 0x4					; SYSirqred
|?SYSirqjoystick@@3HA| % 0x4				; SYSirqjoystick
|?kl@@3UGXKeyList@@A| % 0x60				; kl

	AREA	|.rdata|, DATA, READONLY
|wincls| DCB	"r", 0x0, "e", 0x0, "d", 0x0, "a", 0x0, 0x0, 0x0
	EXPORT	|?taskbar@@YAX_N@Z|			; taskbar
	EXPORT	|??_C@_1BE@FMHB@?$AAH?$AAH?$AAT?$AAa?$AAs?$AAk?$AAb?$AAa?$AAr?$AA?$AA@| [ DATA ] ; `string'
	IMPORT	|MoveWindow|
	IMPORT	|GetWindowRect|
	IMPORT	|ShowWindow|
	IMPORT	|FindWindowW|
	IMPORT	|SHFullScreen|
; File C:\Documents and Settings\Administrador\Escritorio\r4\r4sources\r4cep\redalib.cpp

	AREA	|.text| { |?taskbar@@YAX_N@Z| }, CODE, SELECTION=1 ; comdat noduplicate

	AREA	|.pdata$$?taskbar@@YAX_N@Z|, PDATA, SELECTION=5, ASSOC=|.text| { |?taskbar@@YAX_N@Z| } ; comdat associative
|$T27442| DCD	|?taskbar@@YAX_N@Z|
	DCD	0x40003302

	AREA	|.data| { |??_C@_1BE@FMHB@?$AAH?$AAH?$AAT?$AAa?$AAs?$AAk?$AAb?$AAa?$AAr?$AA?$AA@| }, DATA, SELECTION=2 ; comdat any
|??_C@_1BE@FMHB@?$AAH?$AAH?$AAT?$AAa?$AAs?$AAk?$AAb?$AAa?$AAr?$AA?$AA@| DCB "H"
	DCB	0x0, "H", 0x0, "T", 0x0, "a", 0x0, "s", 0x0, "k", 0x0, "b"
	DCB	0x0, "a", 0x0, "r", 0x0, 0x0, 0x0	; `string'

	AREA	|.text| { |?taskbar@@YAX_N@Z| }, CODE, SELECTION=1 ; comdat noduplicate

|?taskbar@@YAX_N@Z| PROC				; taskbar

; 28   : {

	stmdb     sp!, {r4 - r6, lr}  ; stmfd
	sub       sp, sp, #0x18  ; 0x18 = 24
|$M27440|

; 29   : RECT rc;
; 30   : GetWindowRect(hWnd,&rc);

	ldr       r4, [pc, #0x70]  ;  pc+8+112 = 00000080
	mov       r6, r0
	add       r1, sp, #8
	ldr       r0, [r4]
	bl        GetWindowRect  ; 00000020

; 31   : HWND hWndTB=FindWindow(TEXT("HHTaskbar"),NULL);

	ldr       r0, [pc, #0x58]  ;  pc+8+88 = 0000007C
	mov       r1, #0
	bl        FindWindowW  ; 0000002C

; 32   : if (show)

	ands      r3, r6, #0xFF  ; 0xFF = 255
	mov       r5, r0

; 33   : 	{
; 34   : 	SHFullScreen(hWnd,SHFS_SHOWTASKBAR | SHFS_SHOWSIPBUTTON + SHFS_SHOWSTARTICON);

	ldr       r0, [r4]
	beq       |$L27337|  ; 00000084
	mov       r1, #0x15  ; 0x15 = 21
	bl        SHFullScreen  ; 00000044

; 35   : 	ShowWindow(hWndTB,SW_SHOW );

	mov       r1, #5
	mov       r0, r5
	bl        ShowWindow  ; 00000050

; 36   : 	MoveWindow(hWnd,rc.left,rc.top + MENU_HEIGHT,rc.right,rc.bottom - 2 * MENU_HEIGHT,TRUE);

	mov       r3, #1
	ldr       r2, [sp, #0xC]  ; 0xC = 12
	str       r3, [sp, #4]
	ldr       r3, [sp, #0x14]  ; 0x14 = 20
	add       r2, r2, #0x1A  ; 0x1A = 26
	ldr       r1, [sp, #8]
	sub       r3, r3, #0x34  ; 0x34 = 52
	ldr       r0, [r4]
	str       r3, [sp]
	ldr       r3, [sp, #0x10]  ; 0x10 = 16
	bl        MoveWindow  ; 0000007C

; 37   : 	}
; 38   : else

	b         |$L27338|  ; 000000C4
|$L27443|
	DCD       |??_C@_1BE@FMHB@?$AAH?$AAH?$AAT?$AAa?$AAs?$AAk?$AAb?$AAa?$AAr?$AA?$AA@|
	DCD       |?hWnd@@3PAUHWND__@@A|
|$L27337|

; 39   : 	{
; 40   : 	SHFullScreen(hWnd, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON + SHFS_HIDESTARTICON);

	mov       r1, #0x2A  ; 0x2A = 42
	bl        SHFullScreen  ; 00000090

; 41   : 	ShowWindow(hWndTB, SW_HIDE );

	mov       r1, #0
	mov       r0, r5
	bl        ShowWindow  ; 0000009C

; 42   : 	MoveWindow(hWnd,rc.left,rc.top - MENU_HEIGHT,rc.right,rc.bottom + MENU_HEIGHT,TRUE);

	mov       r3, #1
	ldr       r2, [sp, #0xC]  ; 0xC = 12
	str       r3, [sp, #4]
	ldr       r3, [sp, #0x14]  ; 0x14 = 20
	sub       r2, r2, #0x1A  ; 0x1A = 26
	ldr       r1, [sp, #8]
	add       r3, r3, #0x1A  ; 0x1A = 26
	ldr       r0, [r4]
	str       r3, [sp]
	ldr       r3, [sp, #0x10]  ; 0x10 = 16
	bl        MoveWindow  ; 000000C8
|$L27338|

; 43   : 	}
; 44   : }

	add       sp, sp, #0x18  ; 0x18 = 24
	ldmia     sp!, {r4 - r6, pc}  ; ldmfd
|$M27441|

	ENDP  ; |?taskbar@@YAX_N@Z|, taskbar

	EXPORT	|?update@@YAXXZ|			; update
	IMPORT	|GetMessageW|
	IMPORT	|PeekMessageW|
	IMPORT	|TranslateMessage|
	IMPORT	|DispatchMessageW|

	AREA	|.text| { |?update@@YAXXZ| }, CODE, SELECTION=1 ; comdat noduplicate

	AREA	|.pdata$$?update@@YAXXZ|, PDATA, SELECTION=5, ASSOC=|.text| { |?update@@YAXXZ| } ; comdat associative
|$T27450| DCD	|?update@@YAXXZ|
	DCD	0x40001d02

	AREA	|.text| { |?update@@YAXXZ| }, CODE, SELECTION=1 ; comdat noduplicate

|?update@@YAXXZ| PROC					; update

; 49   : {

	stmdb     sp!, {r4, lr}  ; stmfd
	sub       sp, sp, #0x20  ; 0x20 = 32
|$M27448|

; 50   : MSG msg;
; 51   : while (PeekMessage(&msg,0,0,0,PM_NOREMOVE)==TRUE) {

	mov       r4, #0
	mov       r3, #0
	str       r4, [sp]
	mov       r2, #0
	mov       r1, #0
	add       r0, sp, #4
	bl        PeekMessageW  ; 00000028
	b         |$L27447|  ; 00000064
|$L27343|

; 52   : 	GetMessage(&msg,0,0,0);

	mov       r3, #0
	mov       r2, #0
	mov       r1, #0
	add       r0, sp, #4
	bl        GetMessageW  ; 00000040

; 53   : 	TranslateMessage(&msg);

	add       r0, sp, #4
	bl        TranslateMessage  ; 00000048

; 54   : 	DispatchMessage(&msg);

	add       r0, sp, #4
	bl        DispatchMessageW  ; 00000050
	mov       r3, #0
	str       r4, [sp]
	mov       r2, #0
	mov       r1, #0
	add       r0, sp, #4
	bl        PeekMessageW  ; 00000068
|$L27447|

; 50   : MSG msg;
; 51   : while (PeekMessage(&msg,0,0,0,PM_NOREMOVE)==TRUE) {

	cmp       r0, #1
	beq       |$L27343|  ; 00000028

; 55   : 	}
; 56   : }

	add       sp, sp, #0x20  ; 0x20 = 32
	ldmia     sp!, {r4, pc}  ; ldmfd
|$M27449|

	ENDP  ; |?update@@YAXXZ|, update

	EXPORT	|?WndProc@@YAJPAUHWND__@@IIJ@Z|		; WndProc
	IMPORT	|DefWindowProcW|
	IMPORT	|__imp_?GXCloseDisplay@@YAHXZ|
	IMPORT	|__imp_?GXCloseInput@@YAHXZ|
	IMPORT	|__imp_?GXSuspend@@YAHXZ|
	IMPORT	|__imp_?GXResume@@YAHXZ|
	IMPORT	|PostQuitMessage|

	AREA	|.text| { |?WndProc@@YAJPAUHWND__@@IIJ@Z| }, CODE, SELECTION=1 ; comdat noduplicate

	AREA	|.pdata$$?WndProc@@YAJPAUHWND__@@IIJ@Z|, PDATA, SELECTION=5, ASSOC=|.text| { |?WndProc@@YAJPAUHWND__@@IIJ@Z| } ; comdat associative
|$T27460| DCD	|?WndProc@@YAJPAUHWND__@@IIJ@Z|
	DCD	0x40006b01

	AREA	|.text| { |?WndProc@@YAJPAUHWND__@@IIJ@Z| }, CODE, SELECTION=1 ; comdat noduplicate

|?WndProc@@YAJPAUHWND__@@IIJ@Z| PROC			; WndProc

; 61   : {

	stmdb     sp!, {lr}  ; stmfd
|$M27458|

; 62   : switch (message) 
; 63   : 	{

	mov       lr, #1, 24  ; 0x100 = 256
	cmp       r1, lr
	bhi       |$L27452|  ; 000000E0
	beq       |$L27365|  ; 000000CC
	cmp       r1, #2
	beq       |$L27366|  ; 00000098
	cmp       r1, #6
	beq       |$L27369|  ; 00000064
	cmp       r1, #7
	beq       |$L27368|  ; 0000004C
	cmp       r1, #8
	bne       |$L27373|  ; 0000011C

; 79   :     case WM_KILLFOCUS:
; 80   :         GXSuspend();break;

	ldr       r3, [pc, #0xC]  ;  pc+8+12 = 00000048
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3
	b         |$L27352|  ; 0000019C
|$L27461|
	DCD       |__imp_?GXSuspend@@YAHXZ|
|$L27368|

; 81   :     case WM_SETFOCUS:
; 82   :         GXResume();break;

	ldr       r3, [pc, #0xC]  ;  pc+8+12 = 00000060
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3
	b         |$L27352|  ; 0000019C
|$L27462|
	DCD       |__imp_?GXResume@@YAHXZ|
|$L27369|

; 83   : 	case WM_ACTIVATE:
; 84   : 		if (LOWORD(wParam) == WA_INACTIVE) GXSuspend(); else GXResume();

	mov       r3, r2, lsl #16
	movs      r3, r3, lsr #16
	bne       |$L27371|  ; 00000084
	ldr       r3, [pc, #-0x30]  ;  pc+8-48 = 00000048
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3
	b         |$L27352|  ; 0000019C
|$L27371|
	ldr       r3, [pc, #-0x2C]  ;  pc+8-44 = 00000060
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3

; 85   : 		break;

	b         |$L27352|  ; 0000019C
|$L27366|

; 76   :     case WM_DESTROY:
; 77   :         GXCloseInput();GXCloseDisplay();//taskbar(true);

	ldr       r3, [pc, #0x28]  ;  pc+8+40 = 000000C8
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3
	ldr       r3, [pc, #0x14]  ;  pc+8+20 = 000000C4
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3

; 78   :         PostQuitMessage(0);break;

	mov       r0, #0
	bl        PostQuitMessage  ; 000000C4
	b         |$L27352|  ; 0000019C
|$L27463|
	DCD       |__imp_?GXCloseDisplay@@YAHXZ|
	DCD       |__imp_?GXCloseInput@@YAHXZ|
|$L27365|

; 74   : 	case WM_KEYDOWN:
; 75   : 		tecla&=~wParam;evento=SYSirqteclado;break;

	ldr       r0, [pc, #8]  ;  pc+8+8 = 000000DC
	ldr       r1, [r0]
	bic       r1, r1, r2
	b         |$L27453|  ; 00000188
|$L27464|
	DCD       |?tecla@@3HA|
|$L27452|

; 62   : switch (message) 
; 63   : 	{

	mov       lr, #1, 24  ; 0x100 = 256
	orr       lr, lr, #1
	cmp       r1, lr
	beq       |$L27364|  ; 0000017C
	mov       lr, #2, 24  ; 0x200 = 512
	cmp       r1, lr
	beq       |$L27355|  ; 0000015C
	mov       lr, #2, 24  ; 0x200 = 512
	orr       lr, lr, #1
	cmp       r1, lr
	beq       |$L27359|  ; 00000138
	mov       lr, #2, 24  ; 0x200 = 512
	orr       lr, lr, #2
	cmp       r1, lr
	beq       |$L27363|  ; 00000124
|$L27373|

; 86   : 	default:
; 87   : 		return DefWindowProc(hWnd, message, wParam, lParam);

	bl        DefWindowProcW  ; 00000124
	b         |$L27350|  ; 000001A0
|$L27363|

; 70   : 	case WM_LBUTTONUP:
; 71   : 		mbutton=false;evento=SYSirqlapiz;break;

	mov       r1, #0
|$L27457|
	ldr       r0, [pc, #4]  ;  pc+8+4 = 00000134
	strb      r1, [r0]
	b         |$L27455|  ; 00000170
|$L27465|
	DCD       |?mbutton@@3_NA|
|$L27359|

; 67   : 	case WM_LBUTTONDOWN:
; 68   : 		mxpos=LOWORD(lParam);mypos=HIWORD(lParam);mbutton=true;

	ldr       r0, [pc, #0x18]  ;  pc+8+24 = 00000158
	mov       r1, r3, lsr #16
	strh      r3, [r0]
	ldr       r0, [pc, #8]  ;  pc+8+8 = 00000154
	strh      r1, [r0]
	mov       r1, #1

; 69   : 		evento=SYSirqlapiz;break;

	b         |$L27457|  ; 00000128
|$L27466|
	DCD       |?mypos@@3GA|
	DCD       |?mxpos@@3GA|
|$L27355|

; 64   : 	case WM_MOUSEMOVE:
; 65   : 		mxpos=LOWORD(lParam);mypos=HIWORD(lParam);

	ldr       r0, [pc, #-0xC]  ;  pc+8-12 = 00000158
	mov       r1, r3, lsr #16
	strh      r3, [r0]
	ldr       r0, [pc, #-0x1C]  ;  pc+8-28 = 00000154
	strh      r1, [r0]
|$L27455|

; 66   : 		evento=SYSirqlapiz;break;

	ldr       r0, [pc]  ;  pc+8+0 = 00000178
	b         |$L27454|  ; 00000190
|$L27467|
	DCD       |?SYSirqlapiz@@3HA|
|$L27364|

; 72   : 	case WM_KEYUP:
; 73   : 		tecla|=wParam;evento=SYSirqteclado;break;

	ldr       r0, [pc, #-0xA8]  ;  pc+8-168 = 000000DC
	ldr       r1, [r0]
	orr       r1, r1, r2
|$L27453|
	str       r1, [r0]
	ldr       r0, [pc, #0x14]  ;  pc+8+20 = 000001A8
|$L27454|
	ldr       r0, [r0]
	ldr       r1, [pc, #8]  ;  pc+8+8 = 000001A4
	str       r0, [r1]
|$L27352|

; 88   :    }
; 89   : return 0;

	mov       r0, #0
|$L27350|

; 90   : }

	ldmia     sp!, {pc}  ; ldmfd
|$L27468|
	DCD       |?evento@@3HA|
	DCD       |?SYSirqteclado@@3HA|
|$M27459|

	ENDP  ; |?WndProc@@YAJPAUHWND__@@IIJ@Z|, WndProc

	EXPORT	|?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z| ; MyRegisterClass
	IMPORT	|LoadIconW|
	IMPORT	|GetStockObject|
	IMPORT	|RegisterClassW|

	AREA	|.text| { |?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z| }, CODE, SELECTION=1 ; comdat noduplicate

	AREA	|.pdata$$?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z|, PDATA, SELECTION=5, ASSOC=|.text| { |?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z| } ; comdat associative
|$T27472| DCD	|?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z|
	DCD	0x40001902

	AREA	|.text| { |?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z| }, CODE, SELECTION=1 ; comdat noduplicate

|?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z| PROC		; MyRegisterClass

; 93   : {

	stmdb     sp!, {r4, lr}  ; stmfd
	sub       sp, sp, #0x28  ; 0x28 = 40
|$M27470|

; 94   : WNDCLASS wcls;
; 95   : wcls.style			= 0;
; 96   : wcls.lpfnWndProc	= (WNDPROC)WndProc;

	ldr       r3, [pc, #0x50]  ;  pc+8+80 = 00000060
	mov       r4, #0

; 97   : wcls.cbClsExtra		= 0;
; 98   : wcls.cbWndExtra		= 0;
; 99   : wcls.hInstance		= hInstance;
; 100  : wcls.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(1));

	mov       r1, #1
	str       r4, [sp]
	str       r3, [sp, #4]
	str       r4, [sp, #8]
	str       r4, [sp, #0xC]  ; 0xC = 12
	str       r0, [sp, #0x10]  ; 0x10 = 16
	bl        LoadIconW  ; 00000030
	str       r0, [sp, #0x14]  ; 0x14 = 20

; 101  : wcls.hCursor		= 0;
; 102  : wcls.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);

	mov       r0, #4
	str       r4, [sp, #0x18]  ; 0x18 = 24
	bl        GetStockObject  ; 00000040
	str       r0, [sp, #0x1C]  ; 0x1C = 28

; 103  : wcls.lpszMenuName	= 0;
; 104  : wcls.lpszClassName	= wincls;

	ldr       r0, [pc, #0x14]  ;  pc+8+20 = 0000005C
	str       r4, [sp, #0x20]  ; 0x20 = 32
	str       r0, [sp, #0x24]  ; 0x24 = 36

; 105  : return RegisterClass(&wcls);

	add       r0, sp, #0
	bl        RegisterClassW  ; 00000058

; 106  : }

	add       sp, sp, #0x28  ; 0x28 = 40
	ldmia     sp!, {r4, pc}  ; ldmfd
|$L27473|
	DCD       |wincls|
	DCD       |?WndProc@@YAJPAUHWND__@@IIJ@Z|
|$M27471|

	ENDP  ; |?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z|, MyRegisterClass

	EXPORT	|?InitInstance@@YAHPAUHINSTANCE__@@H@Z|	; InitInstance
	IMPORT	|UpdateWindow|
	IMPORT	|CreateWindowExW|

	AREA	|.text| { |?InitInstance@@YAHPAUHINSTANCE__@@H@Z| }, CODE, SELECTION=1 ; comdat noduplicate

	AREA	|.pdata$$?InitInstance@@YAHPAUHINSTANCE__@@H@Z|, PDATA, SELECTION=5, ASSOC=|.text| { |?InitInstance@@YAHPAUHINSTANCE__@@H@Z| } ; comdat associative
|$T27477| DCD	|?InitInstance@@YAHPAUHINSTANCE__@@H@Z|
	DCD	0x40002402

	AREA	|.text| { |?InitInstance@@YAHPAUHINSTANCE__@@H@Z| }, CODE, SELECTION=1 ; comdat noduplicate

|?InitInstance@@YAHPAUHINSTANCE__@@H@Z| PROC		; InitInstance

; 109  : {

	stmdb     sp!, {r4, r5, lr}  ; stmfd
	sub       sp, sp, #0x20  ; 0x20 = 32
|$M27475|
	mov       r5, r1

; 110  : hInst=hi;

	ldr       r1, [pc, #0x78]  ;  pc+8+120 = 0000008C

; 111  : hWnd=CreateWindowEx(WS_EX_TOPMOST,wincls,wincls,WS_VISIBLE,0,0,240,320,NULL,NULL,hi,NULL);

	mov       r3, #5, 26  ; 0x140 = 320
	ldr       r2, [pc, #0x6C]  ;  pc+8+108 = 00000088
	str       r0, [r1]
	mov       r1, #0
	str       r3, [sp, #0xC]  ; 0xC = 12
	mov       r3, #0xF0  ; 0xF0 = 240
	str       r1, [sp, #0x1C]  ; 0x1C = 28
	str       r0, [sp, #0x18]  ; 0x18 = 24
	mov       r0, #8
	str       r1, [sp, #0x14]  ; 0x14 = 20
	str       r1, [sp, #0x10]  ; 0x10 = 16
	str       r3, [sp, #8]
	mov       r3, #1, 4  ; 0x10000000 = 268435456
	str       r1, [sp, #4]
	str       r1, [sp]
	mov       r1, r2
	bl        CreateWindowExW  ; 00000058
	ldr       r4, [pc, #0x28]  ;  pc+8+40 = 00000084
	cmp       r0, #0
	str       r0, [r4]

; 112  : if (!hWnd) return FALSE;

	moveq     r0, #0
	beq       |$L27386|  ; 0000007C

; 113  : ShowWindow(hWnd, nCmdShow);

	mov       r1, r5
	bl        ShowWindow  ; 00000074

; 114  : UpdateWindow(hWnd);

	ldr       r0, [r4]
	bl        UpdateWindow  ; 0000007C

; 115  : return TRUE;

	mov       r0, #1
|$L27386|

; 116  : }

	add       sp, sp, #0x20  ; 0x20 = 32
	ldmia     sp!, {r4, r5, pc}  ; ldmfd
|$L27478|
	DCD       |?hWnd@@3PAUHWND__@@A|
	DCD       |wincls|
	DCD       |?hInst@@3PAUHINSTANCE__@@A|
|$M27476|

	ENDP  ; |?InitInstance@@YAHPAUHINSTANCE__@@H@Z|, InitInstance

	EXPORT	|WinMain|
	IMPORT	|?gr_init@@YAHXZ|			; gr_init
	IMPORT	|?gr_fin@@YAXXZ|			; gr_fin
	IMPORT	|__imp_?GXOpenDisplay@@YAHPAUHWND__@@K@Z|
	IMPORT	|__imp_?GXOpenInput@@YAHXZ|
	IMPORT	|__imp_?GXGetDefaultKeys@@YA?AUGXKeyList@@H@Z|
	IMPORT	|DestroyWindow|
	IMPORT	|main|

	AREA	|.text| { |WinMain| }, CODE, SELECTION=1 ; comdat noduplicate

	AREA	|.pdata$$WinMain|, PDATA, SELECTION=5, ASSOC=|.text| { |WinMain| } ; comdat associative
|$T27489| DCD	|WinMain|
	DCD	0x40004602

	AREA	|.text| { |WinMain| }, CODE, SELECTION=1 ; comdat noduplicate

|WinMain| PROC

; 123  : {

	stmdb     sp!, {r4, r5, lr}  ; stmfd
	sub       sp, sp, #0x60  ; 0x60 = 96
|$M27487|
	mov       r4, r0
	mov       r5, r3

; 124  : //taskbar(false);
; 125  : if (!MyRegisterClass(hInstance)) return FALSE;

	bl        |?MyRegisterClass@@YAGPAUHINSTANCE__@@@Z|  ; 00000018
	mov       r3, r0, lsl #16
	movs      r3, r3, lsr #16
	beq       |$L27486|  ; 000000EC

; 126  : if (!InitInstance(hInstance, nCmdShow)) return FALSE;

	mov       r1, r5
	mov       r0, r4
	bl        |?InitInstance@@YAHPAUHINSTANCE__@@H@Z|  ; 00000030
	movs      r3, r0
	beq       |$L27486|  ; 000000EC

; 127  : GXOpenDisplay(hWnd,GX_FULLSCREEN);

	ldr       r4, [pc, #0xD8]  ;  pc+8+216 = 00000114
	mov       r1, #1
	ldr       r3, [pc, #0xCC]  ;  pc+8+204 = 00000110
	ldr       r0, [r4]
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3

; 128  : GXOpenInput();

	ldr       r3, [pc, #0xB4]  ;  pc+8+180 = 0000010C
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3

; 129  : kl=GXGetDefaultKeys(GX_NORMALKEYS);

	ldr       r3, [pc, #0xA0]  ;  pc+8+160 = 00000108
	mov       r1, #2
	add       r0, sp, #0
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3
	add       r3, sp, #0
	mov       r2, #0x60  ; 0x60 = 96
|$L27484|
	ldrb      r1, [r0], #1
	subs      r2, r2, #1
	strb      r1, [r3], #1
	bgt       |$L27484|  ; 00000080
	ldr       r0, [pc, #0x6C]  ;  pc+8+108 = 00000104
	add       r3, sp, #0
	mov       r2, #0x60  ; 0x60 = 96
|$L27485|
	ldrb      r1, [r3], #1
	subs      r2, r2, #1
	strb      r1, [r0], #1
	bgt       |$L27485|  ; 0000009C

; 130  : mbutton=false;

	ldr       r0, [pc, #0x4C]  ;  pc+8+76 = 00000100
	mov       r1, #0
	strb      r1, [r0]

; 131  : //srand(clock());
; 132  : gr_init();

	bl        |?gr_init@@YAHXZ|  ; 000000C0

; 133  : //---------------------------------------------------------------------
; 134  : main();

	bl        main  ; 000000C4

; 135  : //---------------------------------------------------------------------
; 136  : gr_fin();

	bl        |?gr_fin@@YAXXZ|  ; 000000C8

; 137  : GXCloseInput();

	ldr       r3, [pc, #0x30]  ;  pc+8+48 = 000000FC
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3

; 138  : GXCloseDisplay();

	ldr       r3, [pc, #0x1C]  ;  pc+8+28 = 000000F8
	ldr       r3, [r3]
	mov       lr, pc
	mov       pc, r3

; 139  : //taskbar(true);
; 140  : DestroyWindow(hWnd);

	ldr       r0, [r4]
	bl        DestroyWindow  ; 000000F0
|$L27486|

; 141  : return 0;

	mov       r0, #0

; 142  : }

	add       sp, sp, #0x60  ; 0x60 = 96
	ldmia     sp!, {r4, r5, pc}  ; ldmfd
|$L27490|
	DCD       |__imp_?GXCloseDisplay@@YAHXZ|
	DCD       |__imp_?GXCloseInput@@YAHXZ|
	DCD       |?mbutton@@3_NA|
	DCD       |?kl@@3UGXKeyList@@A|
	DCD       |__imp_?GXGetDefaultKeys@@YA?AUGXKeyList@@H@Z|
	DCD       |__imp_?GXOpenInput@@YAHXZ|
	DCD       |__imp_?GXOpenDisplay@@YAHPAUHWND__@@K@Z|
	DCD       |?hWnd@@3PAUHWND__@@A|
|$M27488|

	ENDP  ; |WinMain|

	END
