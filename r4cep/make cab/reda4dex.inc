;=========================================================;
; Include para compilar :REDa4
; para SO Dex4U, Thanks Dex and all the crew !!
;=========================================================;
use32
	ORG   0x200000                                 ; where our program is loaded to
	jmp   start                                    ; jump to the start of program.
	db    'DEX1'                                   ; We check for this, to make shore it a valid Dex4u file.
start:
	mov   ax,18h
	mov   ds,ax
	mov   es,ax
 ;----------------------------------------------------;
 ; Get calltable address.                             ;
 ;----------------------------------------------------;
	mov   edi,Functions                           ; this is the interrupt
	mov   al,0                                    ; we use to load the DexFunction.inc
	mov   ah,0x0a                                 ; with the address to dex4u functions.
	int   40h 
 ;----------------------------------------------------;
 ; Load vesa info.                                    ;
 ;----------------------------------------------------;
	call [LoadVesaInfo]
	mov   edi,VESA_Info
	mov   ecx,193	; <-- modo de vesa
	cld
	cli
	rep   movsd
	sti
 ;----------------------------------------------------;
 ; Do realmode int (vesa).                            ;
 ;----------------------------------------------------;
	call  [SetVesaMode]
	cmp   ah,1
	je    VesaError1
	ret

 ;----------------------------------------------------;
 ; Display Vesa Error message.                        ;
 ;----------------------------------------------------;
VesaError1:
	ret
	
       
 ;----------------------------------------------------;
 ; Llamadas del sistema                               ;
 ;----------------------------------------------------;
        
MSEC:
	ret
TIME:
	ret
DATE:
	ret
RUN:
	ret
	
;----------------------------------------------------;	
RESET:
	call  [SetDex4uFonts]                   ;Dex4u set text mode
	ret
	
DIR:
	ret
FILE:
	ret
LOAD:
	ret
SAVE:
	ret

;----------------------------------------------------;
REDRAW:
	pushad
	push  es
	mov   ax,8h
	mov   es,ax
	mov   edi,[ModeInfo_PhysBasePtr]
	mov   esi,VesaBuffer 
	mov   ecx,640*480
	cld
	cli
	rep   movsd
	sti
	pop   es
	popad
	ret

;----------------------------------------------------;
UPDATE:
    call  PutBackSave
    call  PrintDateGui  
    call  PrintTimeGui
    call  PrintMenuMsg
    call  BuffToScreen
    hlt
    call  [KeyPressedScanNW]
	ret


;----------------------------------------------------;
; Data.                                              ;
;----------------------------------------------------;
BPP		dd 32
SW		dd 1024
SH		dd 768
FRAMEV	rd 1024*768*4

FREE_MEM: 

include 'DexFunctions.inc'                                ; Here is where we includ our "DexFunctions.inc" file