DoMouse:
	pushad
	cmp   [vesaMOUSEoff],1
	je    NoDrawLoop
	mov   [VesaStartXx],cx
	mov   [VesaStartYy],dx
	xor   eax,eax
	mov   ebx,eax
	mov   ax,cx
	mov   bx,dx
	call  ReStoreMouseBAackGround
	call  DrawMouse
NoDrawLoop:
	popad
	ret
	



DrawMouse:
	pushad
	push  es
	push  ds
	push  eax
	mov   ax,8h
	mov   es,ax
	pop   eax
	call  [VesaRes]
	pop  ds
	pop  es
	popad
	ret

; eax = x
; ebx = y
DrawMouse24:
	mov   [VarEax],eax
	mov   [VarEbx],ebx
	xor   edx,edx
	mov   dx,[ModeInfo_BytesPerScanLine]
	imul  ebx,edx				  ; ebx = y * y multiplier MouseBack
	lea   edi,[eax+eax*2]			  ; edi = x*3
	add   edi,[ModeInfo_PhysBasePtr]
	add   edi,ebx				  ; ebx = where to put pixel in memory
	mov   [SaveEdi],edi
	mov   esi,MouseBack
	mov   ecx,20
DrawMouse24Loop1S:
	push  ecx
	mov   ecx,16
	xor   eax,eax
DrawMouse24Loop2S:
	mov   al,byte[es:edi+2]
	shl   eax, 16
	mov   ax,word[es:edi]
	mov   dword[ds:esi],eax
	inc   edi
	inc   edi
	inc   edi
	inc   esi
	inc   esi
	inc   esi
	inc   esi
	loop  DrawMouse24Loop2S
	pop   ecx
	sub   edi,16*3
	add   edi,edx
	loop  DrawMouse24Loop1S
	mov   edi,[SaveEdi]
	mov   esi,mouse3_bmp32
	mov   ecx,20 ;32
DrawMouse24Loop1:
	push  ecx
	mov   ecx,16
DrawMouse24Loop2:
	lodsd
	cmp   eax,0
	je    NoPixel
	mov   [es:edi], ax
	shr   eax, 16
	mov   [es:edi+2], al
NoPixel:
	inc   edi
	inc   edi
	inc   edi
	loop  DrawMouse24Loop2
	pop   ecx
	sub   edi,16*3
	add   edi,edx
	loop  DrawMouse24Loop1
	ret


   
; eax = x
; ebx = y
DrawMouse32:
	mov   [VarEax],eax
	mov   [VarEbx],ebx
	xor   edx,edx
	mov   dx,[ModeInfo_BytesPerScanLine]
	imul  ebx,edx  
	lea   edi,[ebx+eax*4]  
	add   edi,[ModeInfo_PhysBasePtr]   
	mov   [SaveEdi],edi
	mov   esi,MouseBack
	mov   ecx,20
DrawMouse32Loop1S:
	push  ecx
	mov   ecx,16
DrawMouse32Loop2S:
	mov   eax,dword[es:edi]
	mov   dword[ds:esi],eax
	inc   edi
	inc   edi
	inc   edi
	inc   edi
	inc   esi
	inc   esi
	inc   esi
	inc   esi
	loop  DrawMouse32Loop2S
	pop   ecx
	sub   edi,16*4
	add   edi,edx
	loop  DrawMouse32Loop1S
	mov   esi,mouse3_bmp32
	mov   edi,[SaveEdi]
	mov   ecx,20
DrawMouse32Loop1:
	push  ecx
	mov   ecx,16
DrawMouse32Loop2:
	lodsd
	cmp   eax,0
	je    NoPixel32
	mov   [es:edi],eax
NoPixel32:
	inc   edi
	inc   edi
	inc   edi
	inc   edi
	loop  DrawMouse32Loop2
	pop   ecx
	sub   edi,16*4
	add   edi,edx
	loop  DrawMouse32Loop1
	ret

ReStoreMouseBAackGround:
	cmp   [First],0
	je    ItsTheFirst
	pushad
	push  es
	push  ds
	push  eax
	mov   ax,8h
	mov   es,ax
	pop   eax
	call  [VesaResRMBG]
	pop  ds
	pop  es
	popad
ItsTheFirst:
	mov   [First],1
	ret

ReStoreMouseBAackGround24:
	mov   eax,[VarEax]
	mov   ebx,[VarEbx]
	xor   edx,edx
	mov   dx,[ModeInfo_BytesPerScanLine]
	imul  ebx,edx				  ; ebx = y * y multiplier MouseBack
	lea   edi,[eax+eax*2]			  ; edi = x*3
	add   edi,[ModeInfo_PhysBasePtr]
	add   edi,ebx				   ; ebx = where to put pixel in memory
	mov   esi,MouseBack
	mov   ecx,20
RsMouseBg24Loop1:
	push  ecx
	mov   ecx,16
RsMouseBg24Loop2:
	lodsd
	mov   [es:edi],ax
	shr   eax, 16
	mov   [es:edi+2],al
	inc   edi
	inc   edi
	inc   edi
	loop  RsMouseBg24Loop2
	pop   ecx
	sub   edi,16*3
	add   edi,edx
	loop  RsMouseBg24Loop1
	ret

ReStoreMouseBAackGround32:
	mov   eax,[VarEax]
	mov   ebx,[VarEbx]
	xor   edx,edx
	mov   dx,[ModeInfo_BytesPerScanLine]
	imul  ebx,edx  
	lea   edi,[ebx+eax*4]  
	add   edi,[ModeInfo_PhysBasePtr]
	xor   edx,edx
	mov   dx,[ModeInfo_BytesPerScanLine]
	mov   esi,MouseBack
	mov   ecx,20
RsMouseBg32Loop1:
	push  ecx
	mov   ecx,16
RsMouseBg32Loop2: 
	lodsd
	mov   [es:edi],eax
	inc   edi
	inc   edi
	inc   edi
	inc   edi
	loop  RsMouseBg32Loop2
	pop   ecx
	sub   edi,16*4
	add   edi,edx
	loop  RsMouseBg32Loop1
	ret

 ;****************************************************;
 ; Mouse setup Vesa.                                  ;
 ;****************************************************;
SetUpMouseVesa:
	pushad
	cmp   [ModeInfo_BitsPerPixel],24
	jne   Not24 
	mov   edx,DrawMouse24
	mov   [VesaRes],edx
	mov   edx,ReStoreMouseBAackGround24
	mov   [VesaResRMBG],edx  
	jmp   @f 
Not24:
	mov   edx,DrawMouse32
	mov   [VesaRes],edx 
	mov   edx,ReStoreMouseBAackGround32
	mov   [VesaResRMBG],edx  
@@:
	call  [ResetMouse]
	cmp   ax,0xffff
	jne   MouseError
	xor   eax,eax
	mov   ebx,eax
 ;----------------------------------------------------;
 ; Mouse set Min Max XY.                              ;
 ;----------------------------------------------------;  
	mov   ax,[ModeInfo_XResolution]
	mov   bx,[ModeInfo_YResolution]
	sub   bx,4
	sub   ax,10
	call  [SetMouseMaxMinXY]
 ;----------------------------------------------------;
 ; Mouse set start XY.                                ;
 ;----------------------------------------------------; 
	mov   ax,[ModeInfo_XResolution]
	mov   bx,[ModeInfo_YResolution]
	shr   bx,1
	shr   ax,1
	call  [SetMouseXY]
	xor   ecx,ecx
	xor   edx,edx
	call  [GetMousePos]
	mov   [VesaStartXx],cx
	mov   [VesaStartYy],dx
	mov   [VesaStartXold],cx
	mov   [VesaStartYold],dx
 ;----------------------------------------------------;
 ; Hook in mouse IRQ.                                 ;
 ;----------------------------------------------------;
	mov   edi,DoMouse
	mov   eax,5
	call  [SetInt]
	mov   [OldMouseInt],edi
	popad
	clc
	ret

MouseError:
	popad
	stc
	ret



DrawMouse32B:
	pushad
	xor   ebx,ebx
	mov   bx,[ModeInfo_XResolution] 
	shl   ebx,2
	mov   [BytesPerScanLine],ebx
	mov   edx,[BytesPerScanLine]
	mov   eax, [VarEax]
	mov   ebx, [VarEbx]
	mov   [VarEax2],eax
	mov   [VarEbx2],ebx
	imul  ebx,edx  
	lea   edi,[ebx+eax*4]  
	add   edi,VesaBuffer
	mov   [SaveEdi2],edi
	mov   esi,MouseBack2
	mov   ecx,20
DrawMouse32Loop1SB:
	push  ecx
	mov   ecx,16
DrawMouse32Loop2SB:
	mov   eax,dword[es:edi]
	mov   dword[ds:esi],eax
	inc   edi
	inc   edi
	inc   edi
	inc   edi
	inc   esi
	inc   esi
	inc   esi
	inc   esi
	loop  DrawMouse32Loop2SB
	pop   ecx
	sub   edi,16*4
	add   edi,edx
	loop  DrawMouse32Loop1SB
	mov   esi,mouse3_bmp32
	mov   edi,[SaveEdi2]
	mov   ecx,20
DrawMouse32Loop1B:
	push  ecx
	mov   ecx,16
DrawMouse32Loop2B:
	lodsd
	cmp   eax,0
	je    NoPixel32B
	mov   [es:edi],eax
NoPixel32B:
	inc   edi
	inc   edi
	inc   edi
	inc   edi
	loop  DrawMouse32Loop2B
	pop   ecx
	sub   edi,16*4
	add   edi,edx
	loop  DrawMouse32Loop1B
	popad
	ret

 ;****************************************************;
 ; ReStoreMouseBAackGround32B                         ;
 ;****************************************************;
ReStoreMouseBAackGround32B:
	cmp    [FirstB],0
	je     ItsTheFirstB
	pushad
	xor   ebx,ebx
	mov   bx,[ModeInfo_XResolution] 
	shl   ebx,2
	mov   [BytesPerScanLine],ebx
	mov   edx,[BytesPerScanLine]
	mov   eax,[VarEax2]
	mov   ebx,[VarEbx2]
	imul  ebx,edx  
	lea   edi,[ebx+eax*4]  
	add   edi,VesaBuffer
	mov   esi,MouseBack2
	mov   ecx,20
RsMouseBg32Loop1B:
	push  ecx
	mov   ecx,16
RsMouseBg32Loop2B:
	lodsd
	mov   [es:edi],eax
	inc   edi
	inc   edi
	inc   edi
	inc   edi
	loop  RsMouseBg32Loop2B
	pop   ecx
	sub   edi,16*4
	add   edi,edx
	loop  RsMouseBg32Loop1B
	popad
ItsTheFirstB:
	mov    [FirstB],1
	ret

 ;****************************************************;
 ; TestMbutton.                                       ;
 ;****************************************************;
TestMbutton:
	pushad
	call  [GetMousePos]
	cmp   bl,0
	je    MbuttonExit
	cmp   [StartMenuShow],0
	je    TrySTART
 ;----------------------------------------------------;
 ; Test Boundaries.                                   ;
 ;----------------------------------------------------;
	call  CheckStartBoundaries
	jc    MbuttonExit
	mov   ax,[ModeInfo_YResolution]
	sub   ax,30
	cmp   [VesaStartYy],ax
	ja    MbuttonExit1
	sub   ax,35
	cmp   [VesaStartYy],ax
	jb    MbuttonExit
	jmp   MbuttonExitExit
 ;----------------------------------------------------;
 ; Try START.                                         ;
 ;----------------------------------------------------;
TrySTART:
	mov   ax,[ModeInfo_YResolution]
	sub   ax,30
	cmp   [VesaStartYy],ax
	jb    MbuttonExit
	cmp   [VesaStartXx],170
	ja    MbuttonExit
	mov   [StartMenuShow],1
	call  Fade_screen
	call  FullVertWait
	call  BuffToScreen
 ;----------------------------------------------------;
 ; Check for button release.                          ;
 ;----------------------------------------------------;
MbuttonExitloop1:
	call  [GetMousePos]
	cmp   bl,0
	jne   MbuttonExitloop1
	jmp   MbuttonExit
 ;----------------------------------------------------;
 ; Exit.                                              ;
 ;----------------------------------------------------;
MbuttonExit:
	popad
	clc
	ret

 ;----------------------------------------------------;
 ; Exit and close start menu.                         ;
 ;----------------------------------------------------;
MbuttonExit1:
	mov   [StartMenuShow],0
	call  FullScreen
MbuttonExitloop:
	call  [GetMousePos]
	cmp   bl,0
	jne   MbuttonExitloop
	popad
	clc
	ret
 ;----------------------------------------------------;
 ; Exit gui.                                          ;
 ;----------------------------------------------------;
MbuttonExitExit:
	popad
	stc
	ret

 ;----------------------------------------------------;
 ; check Start boundaries                             ;
 ;----------------------------------------------------;
CheckStartBoundaries:
	pushad
	mov   dx,[VesaStartXx]
	cmp   dx,[StartMenuMin_x]			 ; Check min and max ranges
	ja    CheckMaxX
	jmp   NotInZone
CheckMaxX:
	cmp   dx,[StartMenuMax_x]
	jb    StoreNewX
	jmp   NotInZone
StoreNewX:
	mov   dx,[VesaStartYy]
	cmp   dx,[StartMenuMin_y]			 ; Check min and max ranges
	ja    CheckMaxY
	jmp   NotInZone
	jmp   StoreNewY
CheckMaxY:
	cmp   dx,[StartMenuMax_y]
	jb    StoreNewY
	jmp   NotInZone
StoreNewY:
	popad
	clc
	ret

NotInZone:
	popad
	stc
	ret

FullScreen:
	pushad
	call  Fade_screen
	call  FullVertWait
	call  BuffToScreen
	popad
	ret
 ;----------------------------------------------------;
 ; Data.                                              ;
 ;----------------------------------------------------;
StartMenuShow	db 0
SaveEdi2	dd 0
vesaMOUSEoff	db 0
OldMouseInt	dd 0
VarEax		dd 0
VarEbx		dd 0
VarEax2 	dd 0
VarEbx2 	dd 0
First		db 0
FirstB		db 0
;StartmenuXYmin/max
StartMenuMin_x	dw 0
StartMenuMax_x	dw 0
StartMenuMin_y	dw 0
StartMenuMax_y	dw 0