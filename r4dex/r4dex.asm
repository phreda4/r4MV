;=========================================================;
; VesaR4                                         02/03/07 ;
;---------------------------------------------------------;
; Vesa/mouse Demo.                                        ;
;                                                         ;
; DexOS V0.01                                             ;
; (c) Craig Bamford, All rights reserved.                 ;                          
;=========================================================;
use32
	ORG   0x400000				       ; where our program is loaded to
	jmp   start				       ; jump to the start of program.
	db    'DEX1'				       ; We check for this, to make shore it a valid Dex4u file.
msg1:	db " Vesa mode not supported",13
	db " Press any key to exit. ",13,0 
	
 ;----------------------------------------------------;
 ; Start of program.                                  ;
 ;----------------------------------------------------;
start:
	mov   ax,18h
	mov   ds,ax
	mov   es,ax
 ;----------------------------------------------------;
 ; Get calltable address.                             ;
 ;----------------------------------------------------;
	mov   edi,Functions			      ; this is the interrupt
	mov   al,0				      ; we use to load the DexFunction.inc
	mov   ah,0x0a				      ; with the address to dex4u functions.
	int   40h
 ;----------------------------------------------------;Some vesa modes 0x4118 0x411B 0x4115 0x4112
 ; Do realmode int (vesa).                            ;
 ;----------------------------------------------------;
	mov   ecx,0x4118			      ;Set vesa mode 1024*768*32BPP
	call  [SetVesaMode]
	cmp   ah,1
	je    VesaError1
 ;----------------------------------------------------;
 ; Load vesa info.                                    ;
 ;----------------------------------------------------;
	call  [LoadVesaInfo]			      ; Load vesa info into the vars in Dex.inc
	mov   edi,VESA_Info
	mov   ecx,193
	cld
	cli
	rep   movsd
	sti
 ;----------------------------------------------------;
 ; start 
 ;----------------------------------------------------;
 	call SYSUPDATE
	call SYSREDRAW
    mov	esi,pila
    xor eax,eax
	jmp inicio
	
;.................compilado.....................
include 'cod.asm'
;.................compilado.....................

;===============================================
SYSEND:
;	mov   edi,[OldMouseInt] 		      ; Unhook mouse IRQ
;	mov   eax,5
;	call  [SetInt]
;MouseError1:
	call  [SetMouseOff]			      ; Turn mouse off
	call  [SetDex4uFonts]			      ; Set text mode
	ret					      ; Return control to DexOS

;===============================================
SYSUPDATE:
			; hlt is neccesary ????
	hlt					      ; This gives CPU a rest. 	
	call  [KeyPressedNoWait]		      ; See if key pressed
	cmp   ax,1
	je   SYSEND			      ; if not loop
	ret

 ;----------------------------------------------------;
 ; Display Vesa Error message.                        ;
 ;----------------------------------------------------;
VesaError1:
	call  [SetDex4uFonts]			      ; We end up here if vesa mode not supported.
	mov   esi,msg1
	call  [PrintString]
	call  [WaitForKeyPress]
	ret

;===============================================
MSEC:
	lea esi,[esi-4]
	mov [esi], eax
;	invoke	GetTickCount 	;mov	[last_tick],eax
	ret
	
;===============================================	
TIME:
	ret
	
;===============================================	
DATE:
	ret
	
;===============================================	
RUN:
	ret


;===============================================
SYSREDRAW: ; BuffToScreen32:
	pushad
	push es
	mov   ax,8h
	mov   es,ax
	mov   edi,[ModeInfo_PhysBasePtr]
	mov   esi,SYSFRAME
	mov   ecx,$c0000
	cld
	cli
	rep   movsd
	sti
	;<--- here draw the mouse if active...
	pop es
	popad
	ret
	
 ;----------------------------------------------------;
 ; Data.                                              ;
 ;----------------------------------------------------;
align 4
include 'Dex.inc'
align 4
  SYSXM		dd 0
  SYSYM		dd 0
  SYSBM		dd 0
  SYSMS		dd 0
  SYSMM		dd 0
  SYSME		dd 0
  SYSBPP	dd 32
  SYSH		dd 768
  SYSW		dd 1024

include 'dat.asm'

align 4

  SYSKEY	rd 255
  ppila		rd 1024
  pila  	rd 1024
  SYSFRAME	rd 1024*768 ; <-- VesaBuffer
  FREE_MEM	rd 1024*4 ; 4M(32bits) 16MB <-- remain free memory.. now test
