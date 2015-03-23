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
	mov   [First],0
	mov   [StartMenuShow],0
 ;----------------------------------------------------;
 ; FillScreen.                                        ;
 ;----------------------------------------------------;     
	call  Fade_screen			      ; Fade off screen buffer
	call  PrintMenuMsg			      ; print string to offscreen buffer
 ;----------------------------------------------------;
 ; Draw window end.                                   ;
 ;----------------------------------------------------;
	call  BuffToScreen			      ; Move offscree buffer to screen
	call  SetUpMouseVesa			      ; Set mouse up
	jc    MouseError1
	int   2Ch
 ;----------------------------------------------------;
 ; Main loop.                                         ;
 ;----------------------------------------------------;
GetAnotherChar1:				      ; Main loop
	hlt					      ; This gives CPU a rest.
 ;----------------------------------------------------;
 ; Check mouse click.                                 ;
 ;----------------------------------------------------;
	call  [KeyPressedNoWait]		      ; See if key pressed
	cmp   ax,1
	jne   GetAnotherChar1			      ; if not loop
DemoEnd:
 ;----------------------------------------------------;
 ; Exit gui.                                          ;
 ;----------------------------------------------------;
	mov   edi,[OldMouseInt] 		      ; Unhook mouse IRQ
	mov   eax,5
	call  [SetInt]
MouseError1:
	call  [SetMouseOff]			      ; Turn mouse off
	call  [SetDex4uFonts]			      ; Set text mode
	ret					      ; Return control to DexOS

 ;----------------------------------------------------;
 ; Display Vesa Error message.                        ;
 ;----------------------------------------------------;
VesaError1:
	call  [SetDex4uFonts]			      ; We end up here if vesa mode not supported.
	mov   esi,msg1
	call  [PrintString]
	call  [WaitForKeyPress]
	ret

 ;----------------------------------------------------;
 ; PrintMenuMsg.                                      ;
 ;----------------------------------------------------;
PrintMenuMsg:
	pushad
	mov   [vesa_fontsmall_x],10
	xor   eax,eax
	mov   ax,[ModeInfo_YResolution]
	sub   ax,22
	mov   [vesa_fontsmall_y],eax
	mov   [FontColor] ,0x00efefff
	mov   esi,Msg1
	call  print_vesa_string_small16
	popad
	ret
 ;----------------------------------------------------;
 ; Data.                                              ;
 ;----------------------------------------------------;

Msg1 db " Press anykey to exit ",0
align 4
include 'VesaText.inc'
align 4
include 'MouseData.inc'
align 4
include 'MouseDraw.inc'
align 4
include 'Graphic.inc'
align 4
include 'Font8.inc'
align 4
include 'Font16.inc'
align 4
include 'Dex.inc'
align 4
VesaBuffer:
