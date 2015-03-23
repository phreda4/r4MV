;=========================================================;
; GraphicFunctions                               00/00/05 ;
;---------------------------------------------------------;
; Dex4u Lib's                                             ;
; by Craig Bamford.                                       ;
;=========================================================; 

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; Draw Window.                                       ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;       EAX = START X                                ;
 ;       EBX = START Y                                ;
 ;       ECX = BOX Y SIZE                             ;
 ;       EDX = BOX X SIZE                             ;
 ;       ESI = COLOR                                  ;
 ;                                                    ;
 ; Output:                                            ;
 ;                                                    ;
 ;....................................................;
DrawWindow:
	pushad
	mov   [ImageTBaddress],edi
	mov   [WinColor],esi
	mov   [WinX],eax
	mov   [WinY],ebx
	mov   [WinL],ecx
	mov   [WinW],edx
	mov   esi,[WinColor] 
	mov   eax,[WinX] 
	mov   ebx,[WinY] 
	add   ebx,20
	mov   edx,[WinW] 
	mov   ecx,[WinL] 
	sub   ecx,20
	call  DrawFilledBoxVesa
	mov   esi,0x00ece8d8 ;0xc0c0c0c0
	mov   eax,[WinX] 
	add   eax,4
	mov   ebx,[WinY] 
	add   ebx,20
	mov   edx,[WinW] 
	sub   edx,8
	mov   ecx,[WinL] 
	sub   ecx,24
	call  DrawFilledBoxVesa
	mov   esi,0x00083270 
	mov   edi,0x00083270 
	mov   eax,[WinX] 
	mov   ebx,[WinY] 
	add   ebx,20
	mov   edx,[WinW] 
	mov   ecx,[WinL] 
	sub   ecx,20
	call  DrawBoxVesa
	mov   esi,0x00083270 
	mov   edi,0x00083270 
	mov   eax,[WinX] 
	add   eax,4
	mov   ebx,[WinY] 
	add   ebx,24 
	mov   edx,[WinW] 
	sub   edx,8 
	mov   ecx,[WinL] 
	sub   ecx,28 
	call  DrawBoxVesa
	call  PutImageTB
	popad
	ret

 ;----------------------------------------------------;
 ; Fade screen                                        ;
 ;----------------------------------------------------;
Fade_screen:
	pushad
	call  fade_screen32
wehavedone1_SF:
	popad
	ret 
 
 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; Fade screen 32bit             ; fades screen 32bit ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;                                                    ;
 ;                                                    ;
 ; Output:                                            ;
 ;                                                    ;
 ;....................................................;
fade_screen32:
	mov  edi,VesaBuffer  
	mov  eax,0x00000000 
	mov  byte[count],150 
	xor  ecx,ecx
dolop1:    
	mov  cx,[ModeInfo_XResolution]
	shl  ecx,1
	inc  al
	cli
	rep  stosd
	sti
	sub  byte[count],1
	cmp  byte[count],0
	jne  dolop1
	mov   byte[count],150 
dolop11:    
	mov  cx,[ModeInfo_XResolution]
	shl  ecx,1
	dec  al
	cli
	rep  stosd
	sti
	sub  byte[count],1
	cmp  byte[count],0
	jne  dolop11
	ret

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; Fade screen 24bit             ; fades screen 24bit ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;                                                    ;
 ;                                                    ;
 ; Output:                                            ;
 ;                                                    ;
 ;....................................................;
fade_screen24:
	mov  edi,VesaBuffer 
	mov  eax,0x00000000 
	mov  byte[count],120  
dolop2:    
	mov  ecx,640*2
	inc  ah
	inc  ah
	cli
dolop2a:
	stosd
	dec  edi
	loop dolop2a
	sti
	sub byte[count],1
	cmp  byte[count],0
	jne  dolop2

	mov  byte[count],120
dolop22:    
	mov  ecx,640*2
	dec  ah
	dec  ah
	cli
dolop22a:
	stosd
	dec  edi
	loop dolop22a
	sti
	sub byte[count],1
	cmp  byte[count],0
	jne  dolop22
	ret

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; DrawFilledBoxVesa                    ;Draws a line ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;       EAX = START X                                ;
 ;       EBX = START Y                                ;
 ;       ECX = BOX Y SIZE                             ;
 ;       EDX = BOX X SIZE                             ;
 ;       ESI = COLOR                                  ;
 ;                                                    ;
 ; Output:                                            ;
 ;                                                    ;
 ;....................................................;
DrawFilledBoxVesa:
	pushad
	mov   [VesaColor],esi
	mov   [VesaStartX],eax
	mov   [VesaStartY],ebx
	mov   [VesaLineY],ecx
	mov   [VesaLineX],edx
	call  GetVesaScreenPointer
	mov   [VesaLineStart],edi
	mov   [VesaLineStartTotal],edi
	mov   ecx,[VesaLineY]
	mov   edi,[VesaLineStartTotal]
	xor   edx,edx
	mov   dx,[ModeInfo_XResolution] 
	shl   edx,2 
Line32:
	mov   eax,[VesaColor]
	call  DrawLine32BPP
	add   [VesaLineStartTotal],edx ;c3200
	mov   edi,[VesaLineStartTotal]
	loop  Line32 
wehavedoneDFBV:
	popad
	ret 

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; DrawBoxVesa                          ;Draws a line ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;       EAX = START X                                ;
 ;       EBX = START Y                                ;
 ;       ECX = BOX Y SIZE                             ;
 ;       EDX = BOX X SIZE                             ;
 ;       ESI = COLOR                                  ;
 ;                                                    ;
 ; Output:                                            ;
 ;                                                    ;
 ;....................................................;
DrawBoxVesa:
	pushad
	mov   [VesaColor],edi
	mov   [VesaColor2],esi
	mov   [VesaStartX],eax
	mov   [VesaStartY],ebx
	mov   [VesaLineY],ecx
	mov   [VesaLineX],edx
	call  GetVesaScreenPointer
	mov   [VesaLineStart],edi
	mov   [VesaLineStartTotal],edi
	mov   ecx,[VesaLineY]
	sub   ecx,2
	mov   edi,[VesaLineStartTotal]
	mov   eax,[VesaColor]
	call  DrawLine32BPP
	xor   edx,edx
	mov   dx,[ModeInfo_XResolution] 
	shl   edx,2 
LineV32:
	add   [VesaLineStartTotal],edx 
	mov   edi,[VesaLineStartTotal]
	mov   eax,[VesaColor]
	call  DrawVline32
	loop  LineV32 
	add   [VesaLineStartTotal],edx 
	mov   edi,[VesaLineStartTotal]
	mov   eax,[VesaColor2]
	call  DrawLine32BPP
wehavedoneDBV:
	popad
	ret 

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; DrawFilledBoxTranVesa                              ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;       EAX = START X                                ;
 ;       EBX = START Y                                ;
 ;       ECX = BOX Y SIZE                             ;
 ;       EDX = BOX X SIZE                             ;
 ;       ESI = COLOR                                  ;
 ;                                                    ;
 ; Output:                                            ;
 ;                                                    ;
 ;....................................................;
DrawFilledBoxTranVesa:
	pushad
	mov   [VesaStartX],eax
	mov   [VesaStartY],ebx
	mov   [VesaLineY],ecx
	mov   [VesaLineX],edx
	call  GetVesaScreenPointer
	mov   [VesaLineStart],edi
	mov   [VesaLineStartTotal],edi
	mov   ecx,[VesaLineY]
	mov   edi,[VesaLineStartTotal]
	mov   esi,[VesaLineStartTotal]
	xor   edx,edx
	mov   dx,[ModeInfo_XResolution] 
	shl   edx,2 
LineT32:
	call  DrawLineTrans32BPP
	add   [VesaLineStartTotal],edx 
	mov   edi,[VesaLineStartTotal]
	mov   esi,[VesaLineStartTotal]
	loop  LineT32 
wehavedoneDFBTV:
	popad
	ret 

 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; DrawFilledBoxTranLightVesa                         ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;       EAX = START X                                ;
 ;       EBX = START Y                                ;
 ;       ECX = BOX Y SIZE                             ;
 ;       EDX = BOX X SIZE                             ;
 ;       ESI = COLOR                                  ;
 ;                                                    ;
 ; Output:                                            ;
 ;                                                    ;
 ;....................................................;
DrawFilledBoxTranLightVesa:
	pushad
	mov   [VesaStartX],eax
	mov   [VesaStartY],ebx
	mov   [VesaLineY],ecx
	mov   [VesaLineX],edx
	call  GetVesaScreenPointer
	mov   [VesaLineStart],edi
	mov   [VesaLineStartTotal],edi
	mov   ecx,[VesaLineY]
	mov   edi,[VesaLineStartTotal]
	mov   esi,[VesaLineStartTotal]
	xor   edx,edx
	mov   dx,[ModeInfo_XResolution] 
	shl   edx,2 
LineTL32:
	call  DrawLineTransL32BPP
	add   [VesaLineStartTotal],edx 
	mov   edi,[VesaLineStartTotal]
	mov   esi,[VesaLineStartTotal]
	loop  LineTL32 
wehavedoneDFBTLV:
	popad
	ret 


 ;'''''''''''''''''''''''''''''''''''''''''''''''''''';
 ; DrawFilledBoxFadeVesa                ;Draws a line ;
 ;----------------------------------------------------;
 ;                                                    ;
 ;  Input:                                            ;
 ;       EAX = START X                                ;
 ;       EBX = START Y                                ;
 ;       ECX = BOX Y SIZE                             ;
 ;       EDX = BOX X SIZE                             ;
 ;       ESI = COLOR                                  ;
 ;                                                    ;
 ; Output:                                            ;
 ;                                                    ;
 ;....................................................;
DrawFilledBoxFadeVesa:
	pushad
	mov   [VesaColor],esi
	mov   [VesaStartX],eax
	mov   [VesaStartY],ebx
	mov   [VesaLineY],ecx
	mov   [VesaLineX],edx
 ;----------------------------------------------------;
 ; Split the color into RGB                           ;
 ;----------------------------------------------------;
	mov   ebx,[VesaColor]
	mov   [Blue],bl
	mov   [Green],bh
	shr   ebx,8
	mov   [Red],bh
	call  GetVesaScreenPointer
	mov   [VesaLineStart],edi
	mov   [VesaLineStartTotal],edi
	xor   edx,edx
	mov   dx,[ModeInfo_XResolution] 
	shl   edx,2 
 ;----------------------------------------------------;
 ; Fade loop 32bit                                    ;
 ;----------------------------------------------------;
L1:
	mov   ecx,[VesaLineY]
	mov   edi,[VesaLineStartTotal]
LineF32:
	mov   eax,[VesaColor]
	call  DrawLine32BPP
	add   [VesaLineStartTotal],edx 
	mov   edi,[VesaLineStartTotal]
	cmp   [Red],3
	jbe   @f
	sub   [Red],4
@@:
	mov   al,[Red]
	shl   eax,8
	cmp   [Green],3
	jbe   @f
	sub   [Green],4
@@:
	mov   al,[Green]
	shl   eax,8
	cmp   [Blue],3
	jbe   @f
	sub   [Blue],4
@@:
	mov   al,[Blue]
	mov   [VesaColor],eax
	loop  LineF32 
wehavedoneDFBFV:
	popad
	ret 

 ;----------------------------------------------------;
 ; DrawLineTrans32BPP.                                ;
 ;----------------------------------------------------;
DrawLineTrans32BPP:
	pushad
	mov   ecx,[VesaLineX]
@@:
	lodsd
	shr   eax,1 
	and   eax,0x7f7f7f
	stosd
	loop  @b 
	popad
	ret

DrawLineTrans24BPP:
	pushad
	mov   ecx,[VesaLineX]
@@:
	lodsb
	shr   al,1 
	and   al,0x7f
	stosb
	lodsw
	shr   ax,1
	and   ax,0x7f7f
	stosw
	loop  @b 
	popad
	ret

 ;----------------------------------------------------;
 ; DrawLineTransL32BPP.                               ;
 ;----------------------------------------------------;
DrawLineTransL32BPP:
	pushad
	mov   ecx,[VesaLineX]
@@:
	lodsd
	shr   eax,1 
	or   eax,0x00000ff ;and
	and  eax,0x007f7fff
	stosd
	loop  @b 
	popad
	ret

DrawLineTransL24BPP:
	pushad
	mov   ecx,[VesaLineX]
@@:
	lodsw
	shr   ax,1
	or   ax,0xff00
	and   ax,0xff7f
	stosw
	lodsb
	shr   al,1 
	and   al,0x7f
	stosb
	loop  @b 
	popad
	ret

 ;----------------------------------------------------;
 ; DrawLine24BPP.                                     ;
 ;----------------------------------------------------;
DrawLine24BPP:
	pushad
	mov   ecx,[VesaLineX]
LineDraw24:
	mov   eax,[VesaColor]
	stosb
	shr   eax,8 ;cccc
	stosw
	loop  LineDraw24
	popad
	ret

 ;----------------------------------------------------;
 ; DrawLine32BPP.                                     ;
 ;----------------------------------------------------;
DrawLine32BPP:
	pushad
	mov   ecx,[VesaLineX]
	rep   stosd
	popad
	ret

 ;----------------------------------------------------;
 ; DrawVline24.                                       ;
 ;----------------------------------------------------;
DrawVline24:
	pushad
	mov   eax,[VesaColor]
	mov   ecx,[VesaLineX]
	sub   ecx,2
	stosb
	shr   eax,8 ;cccc
	stosw
@@:
	add   edi,3
	loop  @b
	mov   eax,[VesaColor2]
	stosb
	shr   eax,8 ;cccc
	stosw
	popad
	ret

 ;----------------------------------------------------;
 ; DrawVline32.                                       ;
 ;----------------------------------------------------;
DrawVline32:
	pushad
	mov   eax,[VesaColor]
	mov   ecx,[VesaLineX]
	sub   ecx,2
	stosd
@@:
	add   edi,4
	loop  @b
	mov   eax,[VesaColor2]
	stosd
	popad
	ret

 ;----------------------------------------------------;
 ; inc_vesa_screen_pointer.                           ;
 ;----------------------------------------------------;
GetVesaScreenPointer:					  
	push  eax					      
	push  ebx
	mov   edi,VesaBuffer				     
	xor   ebx,ebx
	mov   ebx,[VesaStartX]
	shl   ebx,2
@@:	  
	add   edi, ebx
	mov   ebx,[VesaStartY]
	xor   eax,eax
	mov   ax,[ModeInfo_XResolution] 
	shl   eax,2   
@@:
	mul   ebx
	add   edi,eax
	pop   ebx
	pop   eax
	ret

 ;----------------------------------------------------;
 ; BuffToScreen.  ;Puts whats in the buffer to screen ;
 ;----------------------------------------------------;
BuffToScreen:
	mov   [vesaMOUSEoff],1
	cmp   [ModeInfo_BitsPerPixel],24
	jne   Try32
	call  BuffToScreen24
	jmp   wehavedone24
Try32:
	cmp   [ModeInfo_BitsPerPixel],32
	jne   wehavedone24
	call  BuffToScreen32 
wehavedone24:
	mov   [vesaMOUSEoff],0
	int   2Ch
	ret

 ;----------------------------------------------------;
 ; BuffToScreen24                               32bpp ;
 ;----------------------------------------------------;
BuffToScreen32:
	 pushad
	 push  es
	 mov   ax,8h
	 mov   es,ax
	 mov   edi,[ModeInfo_PhysBasePtr]
	 mov   esi,VesaBuffer 
	 xor   eax,eax
	 mov   ecx,eax	
	 mov   ax,[ModeInfo_XResolution]
	 mov   cx,[ModeInfo_YResolution]
	 mul   ecx
	 mov   ecx,eax	
	 cld
	 cli
	 rep   movsd
	 sti
	 pop   es
	 popad
	 ret

 ;----------------------------------------------------;
 ; BuffToScreen24                               24bpp ;
 ;----------------------------------------------------;
BuffToScreen24:
	 pushad
	 push  es
	 mov   ax,8h
	 mov   es,ax
	 xor   eax,eax
	 mov   ecx,eax
	 mov   ebx,eax ;ccc
	 mov   ax,[ModeInfo_YResolution]
	 mov   ebp,eax
	 lea   eax,[ebp*2+ebp]
	 mov   edi,[ModeInfo_PhysBasePtr]
	 mov   esi,VesaBuffer  
	 cld
.l1:
	 mov   cx,[ModeInfo_XResolution]
	 shr   ecx,2	     
.l2:
	 mov   eax,[esi]	 ;eax = -- R1 G1 B1
	 mov   ebx,[esi+4]	 ;ebx = -- R2 G2 B2
	 shl   eax,8		 ;eax = R1 G1 B1 --
	 shrd  eax,ebx,8	 ;eax = B2 R1 G1 B1
	 stosd

	 mov   ax,[esi+8]	 ;eax = -- -- G3 B3
	 shr   ebx,8		 ;ebx = -- -- R2 G2
	 shl   eax,16		 ;eax = G3 B3 -- --
	 or    eax,ebx		 ;eax = G3 B3 R2 G2
	 stosd

	 mov   bl,[esi+10]	 ;ebx = -- -- -- R3
	 mov   eax,[esi+12]	 ;eax = -- R4 G4 B4
	 shl   eax,8		 ;eax = R4 G4 B4 --
	 mov   al,bl		 ;eax = R4 G4 B4 R3
	 stosd

	 add esi,16
	 loop  .l2

	 sub ebp,1
	 ja .l1

	 pop   es
	 popad
	 ret

 ;----------------------------------------------------;
 ; GetWinBufferPointer.                               ;
 ;----------------------------------------------------;
GetWinBufferPointer:					 
	push  eax					      
	push  ebx
	mov   eax,[WinX]  
	add   eax,5
	mov   [WinBuffX],eax
	mov   ebx,[WinY] 
	add   ebx,21
	mov   [WinBuffY],ebx
	mov   edi,[ModeInfo_PhysBasePtr]				 
	xor   ebx,ebx
	mov   ebx,[WinBuffX]
	shl   ebx,2
	cmp   [ModeInfo_BitsPerPixel],24   
	jne   @F
	sub   ebx,[WinBuffX] 
@@:	  
	add   edi, ebx
	mov   ebx,[WinBuffY]
	xor   eax,eax
	mov   ax,[ModeInfo_XResolution] 
	shl   eax,2 
	     
	cmp   [ModeInfo_BitsPerPixel],24    
	jne   @f
	sub   ax,[ModeInfo_XResolution] 
@@:
	mul   ebx
	add   edi,eax
	pop   ebx
	pop   eax
	ret


PutImageTB:
	pushad
	xor   ebx,ebx
	mov   bx,[ModeInfo_XResolution] 
	shl   ebx,2
	mov   [BytesPerScanLine],ebx 
	mov   esi,[ImageTBaddress]
	add   esi,7 ;8
	mov   eax,[WinX] ;155 
	mov   ebx,[WinY] ;65  
	imul  ebx,[BytesPerScanLine]	; ebx = y * y multiplier
	lea   edi,[ebx+eax*4]		; edi = x*4+(y*y multiplier)
	add   edi,VesaBuffer		; ebx = where pixel is in memory
	mov   ecx,36
loop1:
	push  ecx
	mov   ecx,24
loop2:
	lodsd
	shr   eax,8
	and   eax, 0xffffff
	cmp   eax,0x00e55e5e		; pink ;)
	jne   Pixel
	add   edi,4
	jmp   NoPixelTB
Pixel:
	stosd
NoPixelTB:
	dec   esi
	loop  loop2
	push  edi
	mov   ecx,[WinW] ;282
	sub   ecx,48  ;cc
	rep   stosd
	mov   ecx,24
loop3:
	lodsd
	shr   eax,8
	and   eax, 0xffffff
	cmp   eax,0x00e55e5e	      ; pink ;)
	jne   Pixel2
	add   edi,4
	jmp   NoPixelTB2
Pixel2:
	stosd
NoPixelTB2:
	dec   esi
	loop  loop3 
	pop   edi
	add   edi,[BytesPerScanLine]
	sub   edi,24*4
	pop   ecx
	loop  loop1
	popad
	ret
 ;----------------------------------------------------;
 ; FullVertWait                                       ;
 ;----------------------------------------------------; 
FullVertWait:
	pushad
	mov   dx,0x03da
Vr:
	in    al,dx
	test  al,8
	jnz   Vr			 ;wait until Verticle Retrace starts
Nvr:
	in    al,dx
	test  al,8
	jz    Nvr			 ;wait until Verticle Retrace Ends
	popad
	ret

 ;----------------------------------------------------;
 ; DATA                                               ;
 ;----------------------------------------------------;
WinColor		dd 0
WinX			dd 0
WinY			dd 0
WinL			dd 0
WinW			dd 0
count			db 0 
VesaLineY		dd 0
VesaLineX		dd 0
VesaLineStartTotal	dd 0
VesaLineStart		dd 0
VesaStartX		dd 0
VesaStartY		dd 0 
VesaColor		dd 0
VesaColor2		dd 0
Red			db 0
Green			db 0
Blue			db 0 
WinBuffX		dd 0 
WinBuffY		dd 0 
ImageTBaddress		dd 0
BytesPerScanLine	dd 0
