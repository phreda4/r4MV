;=========================================================;
; Small_vesa_Text                                11/12/03 ;
;---------------------------------------------------------;
; Vesa small text functions for uses in programs.         ;
;                                                         ;
; Dex4u V0.01                                             ;
; (c) Craig Bamford, All rights reserved.                 ;
;=========================================================;

 
 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; Draw Char small32bpp ; draws char from al in vesa. ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;      Al Ascii character to write.                  ;
 ;                                                    ;
 ; Output:                                            ;
 ;      None.                                         ;
 ;....................................................;

Draw_Char_small32:
	pushad
	xor   edx,edx
	xor   ebx,ebx
	xor   eax,eax
	xor   ecx,ecx
	mov   dl,[Row]	
	cld
GetData32:	       
	lodsb 
	shl   ax,8		    
	mov   bx,ax	     
	mov   cl,8	    
CheckBit32:		   
	test  bx,8000h	      
	jz    ZeroBit32 
	push  eax      
	mov   eax,[FontColor]  
	stosd
	pop   eax
	jmp   Skip32		
ZeroBit32:
	add   edi,4
Skip32: 		
	shl   bx,1	      
	loop  CheckBit32	 
	add   edi,dword[FontAddOn] ;2528
	dec   dl
	jnz   GetData32
	popad
	ret


 ;----------------------------------------------------;
 ; Converts a string from text to vesa mode8x8 fonts. ;
 ;----------------------------------------------------;
Convert_Text_Small8: 
	push  ebx
	push  eax
	push  esi
	xor   eax,eax
	mov   al,[tchar]
	lea   esi,[Dex8x8+eax*9]  
	mov   [tcolor],0ah
	call  get_vesa_screen_pointer
	call  Draw_Char_small32
	call  inc_vesa_screen_pointer
	pop   esi
	pop   eax
	pop   ebx
	ret

 ;----------------------------------------------------;
 ; Converts a string from text to vesa mode8x16 fonts.;
 ;----------------------------------------------------;
Convert_Text_Small16:
	push  ebx
	push  eax
	push  esi
	xor   eax,eax
	mov   al,[tchar]
	shl   eax,4
	lea   esi,[Dex8x16+eax] 
	mov   [tcolor],0ah
	call  get_vesa_screen_pointer
	call  Draw_Char_small32
	call  inc_vesa_screen_pointer
	pop   esi
	pop   eax
	pop   ebx
	ret


 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; Prints vesa string 8x8fonts                        ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;      es:esi points to asciiz string to write.      ;
 ;                                                    ;
 ; Output:                                            ;
 ;      None.                                         ;
 ;....................................................;
print_vesa_string_small8:				    
	pushad
	push  es
	xor   eax,eax
	mov   ax,[ModeInfo_XResolution]
	shl   eax,2
	sub   eax,8*4
	mov   dword[FontAddOn],eax

	mov   [FontW],6
	mov   byte [Row],9
	;mov   [FontColor],edx
	xor   eax,eax 
abloop8:
	mov   al,[esi]
	mov   [tchar],al
	cmp   al,0					   ; 0x00 = end of string
	je    gbend8
	cmp   al,0x0D					   ; 0x0d = CR ( = \n )
	jne   nbo_cr8
	call  cage_return
	jmp   ab18
nbo_cr8:
	call  Convert_Text_Small8
ab18:	inc   esi
	jmp   abloop8
gbend8:
	pop   es
	popad
	ret

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; Prints vesa string 8x16fonts                       ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;      es:esi points to asciiz string to write.      ;
 ;                                                    ;
 ; Output:                                            ;
 ;      None.                                         ;
 ;....................................................;
print_vesa_string_small16:				     
	pushad
	push  es
	xor   eax,eax
	mov   ax,[ModeInfo_XResolution]
	shl   eax,2
	sub   ax,8*4
	mov   dword[FontAddOn],eax
	mov   [FontW],9
	mov   byte [Row],16
	;mov   [FontColor],edx
	xor   eax,eax 
abloop16:
	mov   al,[esi]
	mov   [tchar],al
	cmp   al,0					   ; 0x00 = end of string
	je    gbend16
	cmp   al,0x0D					   ; 0x0d = CR ( = \n )
	jne   nbo_cr16
	call  cage_return
	jmp   ab116
nbo_cr16:
	call  Convert_Text_Small16
ab116:	inc   esi
	jmp   abloop16
gbend16:
	pop   es
	popad
	ret

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; PrintVesaChar8     ; does what it say's on the box ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;      Prints whats in AL, 8x8 fonts.                ;
 ;                                                    ;
 ; Output:                                            ;
 ;      None.                                         ;
 ;....................................................;

PrintVesaChar8: 				  
	pushad
	mov   [FontW],6
	mov   byte [Row],9
	mov   [FontColor],edx
	mov   [tchar],al 
	xor   eax,eax
	mov   ax,[ModeInfo_XResolution]
	shl   eax,2
	sub   ax,8*4
	mov   dword[FontAddOn],eax  
	call  Convert_Text_Small8
	popad
	ret

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; PrintVesaChar8     ; does what it say's on the box ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;      Prints whats in AL, 8x8 fonts.                ;
 ;                                                    ;
 ; Output:                                            ;
 ;      None.                                         ;
 ;....................................................;

PrintVesaChar16:				   
	pushad
	mov   [FontW],9
	mov   byte [Row],16
	mov   [FontColor],edx
	mov   [tchar],al  
	xor   eax,eax
	mov   ax,[ModeInfo_XResolution]
	shl   eax,2
	sub   ax,8*4
	mov   dword[FontAddOn],eax   
	call  Convert_Text_Small16
	popad
	ret

 ;----------------------------------------------------;
 ; render's graphic screen.                           ;
 ;----------------------------------------------------;

render_screen:
	mov   edi,[ModeInfo_PhysBasePtr]     
	mov   ecx,640*480
	mov   eax, [color]
	cld
	cli
bbe:
	stosd
	cmp   [ModeInfo_BitsPerPixel],24
	jne   @f
	sub   edi,1
@@:
	loop  bbe      
	sti
	ret

 ;----------------------------------------------------;
 ; inc_vesa_screen_pointer.                           ;
 ;----------------------------------------------------;

;get_vesa_screen_pointer:
	push  eax					   
	push  ebx
	mov   edi,VesaBuffer
	xor   ebx,ebx
	mov   ebx,[vesa_fontsmall_x]
	shl   ebx,2
	add   edi, ebx
	mov   ebx,[vesa_fontsmall_y]
	xor   eax,eax
	mov   ax,[ModeInfo_XResolution]
	shl   eax,2	 
	mul   ebx
	add   edi,eax
	pop   ebx
	pop   eax
	ret

;---------------------
get_vesa_screen_pointer:
	push  eax					   
	push  ebx
	xor   eax,eax
	xor   ebx,ebx
	mov   bx,[ModeInfo_XResolution] 
	shl   ebx,2
	mov   [BytesPerScanLine],ebx

	mov   eax,[vesa_fontsmall_x]

	mov   ebx,[vesa_fontsmall_y] ;[WinY] ;65

	imul  ebx,[BytesPerScanLine]	; ebx = y * y multiplier
	lea   edi,[ebx+eax*4]		; edi = x*4+(y*y multiplier)
	add   edi,VesaBuffer		; ebx = where pixel is in memory
	pop   ebx
	pop   eax
	ret

;----------------------

 ;----------------------------------------------------;
 ; inc_vesa_screen_pointer.                           ;
 ;----------------------------------------------------;
inc_vesa_screen_pointer:
	push  ecx
	push  eax
	cld
	mov   eax,[vesa_fontsmall_x] 
	mov   cx,[ModeInfo_XResolution]
	sub   cx,10
	cmp   ax,cx
	jb    no4_incy
	call  cage_return
	jmp   d1end
no4_incy:
	add   eax,[FontW] 
	mov   [vesa_fontsmall_x],eax
d1end:	pop   eax
	pop   ecx
	ret

 ;----------------------------------------------------;
 ; cage_return.                                       ;
 ;----------------------------------------------------;
cage_return:
	push  eax
	push  ebx
	mov   [vesa_fontsmall_x], dword 0
	mov   eax,[vesa_fontsmall_y]
	xor   ebx,ebx
	mov   bx,[ModeInfo_YResolution]
	sub   bx,13
	cmp   eax,ebx ;467
	jb    no_scrl
	mov   [vesa_fontsmall_x],0
	mov   [vesa_fontsmall_y],0
	add   [vesa_fontsmall_y],1
	jmp   cend1
no_scrl:
	add   eax,12	
	mov   [vesa_fontsmall_y],eax

cend1:	pop   ebx
	pop   eax
	ret

 ;----------------------------------------------------;
 ; DATA.                                              ;
 ;----------------------------------------------------;

vesa_fontsmall_x   dd 0 			     
vesa_fontsmall_y   dd 0 			     
textx		   dw 0
texty		   dw 0
Row		   db 0
tcolor		   db 0
FontColor	   dd 0
FontAddOn	   dd 0
tchar		   db 0
color		   dd 0  
red		   dd 0
blue		   dd 0  
bpp		   dd 0
FontCopy	   dw 0
FontW		   dd 0
chel		   db 0

