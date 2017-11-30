;---:r4 compiler cod.asm
w0: ; ::: sinp ::: uso:-1 dD:0
;----------------
;----------------
and eax,$7FFF
sub eax,$4000
mov dword [esi-4],eax
mov dword [esi-12],eax
cdq
imul dword [esi-12]
shrd eax,edx,$10
mov dword [esi-8],eax
mov ebx,$4A67B2
cdq
imul ebx
shrd eax,edx,$10
sub eax,$292F99
mov ebx,eax
mov eax,dword [esi-8]
cdq
imul ebx
shrd eax,edx,$10
add eax,$64879
mov ebx,eax
mov eax,dword [esi-4]
cdq
imul ebx
shrd eax,edx,$10
ret

w1: ; ::: cos ::: uso:-1 dD:0 
;----------------
; BL 16 (3-4)0
;----------------
add eax,$8000
test eax,$8000
jnz _1
jmp w0
_1: call w0
neg eax
ret

w2: ; ::: sin ::: uso:-1 dD:0 
;----------------
; BL 16 (3-4)0
;----------------
add eax,$4000
test eax,$8000
jnz _2
jmp w0
_2: call w0
neg eax
ret

w18: ; ::: move ::: uso:-3 dD:-3 
;----------------
; BL 2 (3-4)0
;----------------
_3: or eax,eax
jz _4
sub eax,1
push rax
mov eax,dword [esi]
mov ebx,dword [eax]
add eax,4
mov ecx,dword [esi+4]
mov dword [ecx],ebx
add ecx,4
pop rbx
mov dword [esi+4],ecx
mov dword [esi],eax
mov eax,ebx
jmp _3
_4: lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w19: ; ::: acpx!+ ::: uso:-2 dD:-2 
;----------------
;----------------
mov ebx,eax
and ebx,$FF00FF
mov ecx,dword [ebp]
mov edx,ecx
and edx,$FF00FF
sub edx,ebx
imul edx,dword [esi]
sar edx,$8
add edx,ebx
and edx,$FF00FF
push rdx
and eax,$FF00
and ecx,$FF00
sub ecx,eax
imul ecx,dword [esi]
sar ecx,$8
add eax,ecx
and eax,$FF00
pop rbx
or eax,ebx
mov dword [ebp],eax
add ebp,4
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w1A: ; ::: gr_mix ::: uso:-3 dD:-2 
;----------------
;----------------
push rax
mov eax,dword [esi]
and eax,$FF00FF
mov ebx,dword [esi+4]
and ebx,$FF00FF
sub ebx,eax
mov ecx,dword [esp]
imul ebx,ecx
sar ebx,$8
add eax,ebx
and eax,$FF00FF
mov ebx,dword [esi]
and ebx,$FF00
mov ecx,dword [esi+4]
and ecx,$FF00
sub ecx,ebx
pop rdx
imul ecx,edx
sar ecx,$8
add ebx,ecx
and ebx,$FF00
or eax,ebx
lea esi,dword[esi+8]
ret

w1B: ; ::: mixcolor ::: uso:-1 dD:0 
;----------------
; BL 16 (2-3)0
; BL 16 (4-5)0
;----------------
cmp eax,$1
jge _5
mov eax,dword [w4]
ret
_5: cmp eax,$FE
jle _6
mov eax,dword [w3]
ret
_6: lea esi,dword[esi-8]
mov ebx,dword [w3]
mov dword [esi+4],ebx
mov ebx,dword [w4]
mov dword [esi],ebx
jmp w1A

w1C: ; ::: wvline ::: uso:-2 dD:-2 
;----------------
; BL 16 (2-3)0
; BL 16 (4-5)0
; BL 0 (9-9)0
; BL 16 (9-9)0
; BL 16 (E-E)0
; BL 2 (11-13)0
;----------------
or eax,eax
jns _7
mov eax,dword [esi]
mov dword [wD],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_7: cmp eax,XRES
jl _8
mov eax,dword [esi]
mov dword [wD],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_8: mov ebx,dword [wD]
mov ecx,dword [esi]
mov dword [wD],ecx
cmp ebx,ecx
lea esi,dword[esi-4]
mov dword [esi+4],ecx
mov dword [esi],eax
mov eax,ebx
jge _9
xchg dword [esi+4],eax
_9: or eax,eax
jns _A
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_A: mov ebx,YRES
sub ebx,1
sub eax,ebx
mov ecx,eax
sar ecx,$1F
and eax,ecx
add ebx,eax
mov eax,dword [esi+4]
cmp eax,YRES
jl _B
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_B: mov ecx,eax
neg ecx
sar ecx,$1F
and eax,ecx
sub ebx,eax
shl eax,10
add eax,dword [esi]
lea ebp,dword[SYSFRAME+eax*4]
add ebx,1
lea esi,dword[esi+8]
mov eax,ebx
_C: or eax,eax
jz _D
sub eax,1
mov ebx,dword [w5]
mov dword [ebp],ebx
add ebp,4
mov ebx,XRES
sub ebx,1
lea ebp,dword[ebp+ebx*4]
jmp _C
_D: lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w1D: ; ::: whline ::: uso:-2 dD:-2 
;----------------
; BL 16 (2-3)0
; BL 16 (4-5)0
; BL 0 (9-9)0
; BL 16 (9-9)0
; BL 16 (E-E)0
; BL 2 (11-12)0
;----------------
or eax,eax
jns _E
mov eax,dword [esi]
mov dword [wC],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_E: cmp eax,YRES
jl _F
mov eax,dword [esi]
mov dword [wC],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_F: mov ebx,dword [wC]
mov ecx,dword [esi]
mov dword [wC],ecx
cmp ebx,ecx
lea esi,dword[esi-4]
mov dword [esi+4],ecx
mov dword [esi],eax
mov eax,ebx
jge _10
xchg dword [esi+4],eax
_10: or eax,eax
jns _11
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_11: sub eax,XRES
mov ebx,eax
sar ebx,$1F
and eax,ebx
add eax,XRES
mov ebx,dword [esi+4]
cmp ebx,XRES
jl _12
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_12: mov ecx,ebx
neg ecx
sar ecx,$1F
and ebx,ecx
sub eax,ebx
mov ecx,dword [esi]
shl ecx,10
add ecx,ebx
lea ebp,dword[SYSFRAME+ecx*4]
add eax,1
lea esi,dword[esi+8]
_13: or eax,eax
jz _14
sub eax,1
mov ebx,dword [w5]
mov dword [ebp],ebx
add ebp,4
jmp _13
_14: lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w1E: ; ::: clip1 ::: uso:-5 dD:0 
;----------------
; BL 1 (6-9)0
; BL 1 (E-12)0
; BL 1 (10-12)0
;----------------
cmp eax,$8
jge _15
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
jmp _16
_15: mov ebx,YRES
sub ebx,$2
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
_16: push rax
mov eax,dword [esi+8]
sub eax,dword [esi+16]
mov ebx,dword [esp]
sub ebx,dword [esi+16]
mov ecx,dword [esi+4]
sub ecx,dword [esi+12]
xchg eax,ebx
cdq
imul ecx
idiv ebx
add eax,dword [esi+12]
pop rcx
or eax,eax
lea esi,dword[esi+8]
xchg dword [esi],ecx
mov dword [esi+8],ecx
mov edx,dword [esi-4]
mov dword [esi+4],edx
jns _17
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$1
jmp _18
_17: cmp eax,XRES
jl _19
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$2
jmp _1A
_19: lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
_1A: _18: push rax
pop rax
mov ebx,dword [esi+12]
mov ecx,dword [esi+8]
mov edx,dword [esi+4]
mov edi,dword [esi]
mov dword [esi+12],edx
mov dword [esi+8],edi
mov dword [esi+4],ebx
mov dword [esi],ecx
ret

w1F: ; ::: clip2 ::: uso:-5 dD:0 
;----------------
; BL 1 (6-9)0
; BL 1 (E-12)0
; BL 1 (10-12)0
;----------------
cmp eax,$8
jge _1B
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
jmp _1C
_1B: mov ebx,YRES
sub ebx,$2
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
_1C: push rax
mov eax,dword [esi+8]
sub eax,dword [esi+16]
mov ebx,dword [esi+4]
sub ebx,dword [esi+12]
mov ecx,dword [esp]
sub ecx,dword [esi+8]
xchg eax,ecx
cdq
imul ebx
idiv ecx
add eax,dword [esi+4]
pop rbx
or eax,eax
lea esi,dword[esi+8]
mov dword [esi],ebx
jns _1D
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$1
jmp _1E
_1D: cmp eax,XRES
jl _1F
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$2
jmp _20
_1F: lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
_20: _1E: ret

w20: ; ::: clip3 ::: uso:-5 dD:0 
;----------------
; BL 1 (6-8)0
;----------------
cmp eax,$1
jnz _21
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
jmp _22
_21: mov ebx,XRES
sub ebx,1
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
_22: push rax
mov eax,dword [esi+8]
sub eax,dword [esi+16]
mov ebx,dword [esi+4]
sub ebx,dword [esi+12]
mov ecx,dword [esp]
sub ecx,dword [esi+4]
xchg eax,ecx
cdq
imul ecx
idiv ebx
add eax,dword [esi+8]
pop rbx
lea esi,dword[esi+4]
mov dword [esi+4],eax
mov dword [esi],ebx
mov eax,$0
ret

w21: ; ::: clip4 ::: uso:-5 dD:0 
;----------------
; BL 1 (6-8)0
;----------------
cmp eax,$1
jnz _23
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
jmp _24
_23: mov ebx,XRES
sub ebx,1
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
_24: push rax
mov eax,dword [esi+8]
sub eax,dword [esi+16]
mov ebx,dword [esi+4]
sub ebx,dword [esi+12]
mov ecx,dword [esp]
sub ecx,dword [esi+12]
xchg eax,ecx
cdq
imul ecx
idiv ebx
add eax,dword [esi+16]
pop rbx
lea esi,dword[esi+4]
mov dword [esi+12],eax
mov dword [esi+8],ebx
mov eax,$0
ret

w22: ; ::: clipline ::: uso:-4 dD:1 
;----------------
; BL 1 (5-8)0
; BL 1 (6-8)0
; BL 1 (9-B)0
; BL 0 (A-B)0
; BL 1 (C-F)0
; BL 1 (D-F)0
; BL 1 (10-12)0
; BL 0 (11-12)0
; BL 16 (14-14)0
; BL 16 (16-16)0
; BL 0 (17-1C)0
; BL 0 (1D-22)0
; BL 16 (24-24)0
; BL 16 (26-26)0
; BL 0 (26-2B)0
; BL 0 (2B-30)0
;----------------
mov ebx,YRES
sub ebx,1
cmp eax,ebx
jl _25
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$8
jmp _26
_25: or eax,eax
jns _27
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$4
jmp _28
_27: lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
_28: _26: push rax
mov eax,dword [esi+4]
cmp eax,XRES
lea esi,dword[esi+4]
mov ebx,dword [esi-4]
mov dword [esi],ebx
jl _29
add dword [esp],$2
jmp _2A
_29: or eax,eax
jns _2B
add dword [esp],$1
_2B: _2A: mov ebx,YRES
sub ebx,1
mov ecx,dword [esi+4]
cmp ecx,ebx
mov dword [esi+4],eax
mov ebx,dword [esi+8]
mov edx,dword [esi]
mov dword [esi+8],edx
mov dword [esi],ebx
mov eax,ecx
jl _2C
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$8
jmp _2D
_2C: or eax,eax
jns _2E
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$4
jmp _2F
_2E: lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
_2F: _2D: push rax
mov eax,dword [esi+4]
cmp eax,XRES
lea esi,dword[esi+4]
mov ebx,dword [esi-4]
mov dword [esi],ebx
jl _30
add dword [esp],$2
jmp _31
_30: or eax,eax
jns _32
add dword [esp],$1
_32: _31: pop rbx
pop rcx
mov edx,ebx
and edx,ecx
or edx,edx
jz _33
or ebx,ecx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
ret
_33: mov edx,ebx
or edx,ecx
or edx,edx
jnz _34
or ebx,ecx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
ret
_34: push rcx
test ebx,$C
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _35
call w1F
_35: pop rbx
push rax
test ebx,$C
mov eax,ebx
jz _36
call w1E
_36: pop rbx
mov ecx,eax
and ecx,ebx
or ecx,ecx
jz _37
or eax,ebx
ret
_37: mov ecx,eax
or ecx,ebx
or ecx,ecx
jnz _38
or eax,ebx
ret
_38: push rbx
or eax,eax
jz _39
call w21
_39: pop rbx
push rax
or ebx,ebx
mov eax,ebx
jz _3A
call w20
_3A: pop rbx
or eax,ebx
ret

w23: ; ::: nline21 ::: uso:-3 dD:-3 
;----------------
; BL 2 (6-13)0
; BL 0 (8-A)0
;----------------
sal eax,$10
cdq
idiv dword [esi]
lea esi,dword[esi-4]
xchg dword [esi+4],eax
mov dword [esi],$0
_3B: or eax,eax
jz _3C
sub eax,1
push rax
mov eax,dword [esi]
add eax,dword [esi+4]
test eax,(-65536)
lea esi,dword[esi+4]
jz _3D
and eax,$FFFF
mov ebx,dword [esi+4]
lea ebp,dword[ebp+ebx*4]
mov dword [esi+4],ebx
_3D: lea ebp,dword[ebp+XRES*4]
mov ebx,eax
sar ebx,$8
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],ebx
mov eax,dword [w5]
call w19
mov ebx,dword [esi+8]
sub ebx,1
lea ebp,dword[ebp+ebx*4]
xor eax,$FF
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,dword [w5]
call w19
mov ebx,dword [esi+4]
neg ebx
sub ebx,1
lea ebp,dword[ebp+ebx*4]
pop rbx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jmp _3B
_3C: lea esi,dword[esi+16]
mov eax,dword [esi-4]
ret

w24: ; ::: LINE ::: uso:-2 dD:-2 
;----------------
; BL 16 (3-3)0
; BL 16 (4-4)0
; BL 0 (B-B)0
; BL 16 (B-B)0
; BL 16 (C-C)0
; BL 16 (11-11)0
; BL 16 (13-13)0
; BL 1 (15-17)0
; BL 16 (18-18)0
; BL 2 (1B-28)0
; BL 0 (1D-1F)0
;----------------
cmp eax,dword [wD]
jnz _3E
jmp w1D
_3E: mov ebx,dword [esi]
cmp ebx,dword [wC]
jnz _3F
mov dword [esi],eax
mov eax,ebx
jmp w1C
_3F: mov ecx,dword [wD]
mov dword [wD],eax
mov edx,dword [wC]
mov dword [wC],ebx
cmp ecx,eax
lea esi,dword[esi-8]
mov dword [esi+8],ebx
mov dword [esi+4],eax
mov dword [esi],edx
mov eax,ecx
jge _40
xchg dword [esi+4],eax
mov ebx,dword [esi+8]
mov ecx,dword [esi]
mov dword [esi+8],ecx
mov dword [esi],ebx
_40: or eax,eax
jns _41
lea esi,dword[esi+16]
mov eax,dword [esi-4]
ret
_41: mov ebx,YRES
sub ebx,1
mov ecx,dword [esi+4]
cmp ecx,ebx
jl _42
lea esi,dword[esi+16]
mov eax,dword [esi-4]
ret
_42: mov dword [esi+4],eax
mov eax,dword [esi+8]
mov ebx,dword [esi]
mov dword [esi+8],ebx
mov dword [esi],eax
mov eax,ecx
call w22
or eax,eax
jz _43
lea esi,dword[esi+20]
mov eax,dword [esi-4]
ret
_43: mov eax,dword [esi]
sub eax,dword [esi+8]
mov ebx,dword [esi+4]
sub ebx,dword [esi+12]
or ebx,ebx
jnz _44
lea esi,dword[esi+20]
mov eax,dword [esi-4]
ret
_44: mov ecx,dword [esi+12]
shl ecx,10
add ecx,dword [esi+8]
lea ebp,dword[SYSFRAME+ecx*4]
mov ecx,dword [w5]
mov dword [ebp],ecx
add ebp,4
lea ebp,dword[ebp+(-1)*4]
or eax,eax
lea esi,dword[esi+12]
mov dword [esi],ebx
jns _45
neg eax
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,(-1)
jmp _46
_45: lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$1
_46: mov ebx,dword [esi]
cmp ebx,dword [esi+4]
jge _47
xchg dword [esi+4],eax
mov dword [esi],eax
mov eax,ebx
jmp w23
_47: mov ecx,dword [esi+4]
sal ecx,$10
mov edx,eax
mov eax,ecx
mov ecx,edx
cdq
idiv ebx
lea esi,dword[esi-4]
mov dword [esi+8],ecx
mov dword [esi+4],eax
mov dword [esi],$0
mov eax,ebx
_48: or eax,eax
jz _49
sub eax,1
push rax
mov eax,dword [esi]
add eax,dword [esi+4]
test eax,(-65536)
lea esi,dword[esi+4]
jz _4A
and eax,$FFFF
lea ebp,dword[ebp+XRES*4]
_4A: mov ebx,dword [esi+4]
lea ebp,dword[ebp+ebx*4]
mov ecx,eax
sar ecx,$8
lea esi,dword[esi-12]
mov dword [esi+16],ebx
mov dword [esi+8],eax
mov dword [esi+4],ecx
mov dword [esi],ecx
mov eax,dword [w5]
call w19
mov ebx,XRES
sub ebx,1
lea ebp,dword[ebp+ebx*4]
xor eax,$FF
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,dword [w5]
call w19
mov ebx,XRES
add ebx,1
neg ebx
lea ebp,dword[ebp+ebx*4]
pop rbx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jmp _48
_49: lea esi,dword[esi+16]
mov eax,dword [esi-4]
ret

w25: ; ::: CURVE ::: uso:-4 dD:-4 
;----------------
; BL 16 (B-B)0
;----------------
mov ebx,dword [esi+8]
add ebx,dword [wE]
mov ecx,dword [esi]
sal ecx,1
sub ebx,ecx
mov edx,ebx
sar edx,31
add ebx,edx
xor ebx,edx
mov ecx,dword [esi+4]
add ecx,dword [wF]
mov edx,eax
sal edx,1
sub ecx,edx
mov edx,ecx
sar edx,31
add ecx,edx
xor ecx,edx
add ebx,ecx
cmp ebx,$4
jge _4B
lea esi,dword[esi+8]
mov eax,dword [esi-4]
jmp w24
_4B: mov ebx,dword [esi+8]
add ebx,dword [esi]
sar ebx,1
mov ecx,dword [esi+4]
add ecx,eax
sar ecx,1
add eax,dword [wD]
sar eax,1
mov edx,dword [esi]
add edx,dword [wC]
sar edx,1
mov edi,ebx
add edi,edx
sar edi,1
; libera !!!1111111:[esi+8] [esi+4] ebx ecx edx eax edi .ecx .eax 
mov [esi-4],ebx
; post !!1111101:[esi+8] [esi+4] [esi-4] ecx edx eax edi .ecx .eax
mov ebx,ecx
add ebx,eax
sar ebx,1
lea esi,dword[esi-16]
xchg dword [esi+12],ecx
mov dword [esi+8],edi
mov dword [esi+4],ebx
mov dword [esi],edx
mov dword [esi+16],ecx
call w25
jmp w25

w26: ; ::: runlenSolid ::: uso:0 dD:0 
;----------------
; BL 2 (2-C)2
; BL 1 (8-C)0
; BL 2 (8-9)0
; BL 1 (9-C)0
; BL 2 (A-C)0
;----------------
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,w17
_4C: mov ebx,dword [eax]
add eax,4
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _4D
mov ebx,eax
sar ebx,$9
and ebx,$7FF
and eax,$1FF
cmp eax,$100
lea esi,dword[esi-4]
mov dword [esi],ebx
jnz _4E
lea esi,dword[esi+4]
mov eax,dword [esi-4]
_4F: or eax,eax
jz _50
sub eax,1
mov ebx,dword [w5]
mov dword [ebp],ebx
add ebp,4
jmp _4F
_50: lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _51
_4E: or eax,eax
jz _52
xor eax,$FF
xchg dword [esi],eax
_53: or eax,eax
jz _54
sub eax,1
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov eax,dword [esi+8]
mov dword [esi+8],eax
mov dword [esi],eax
mov eax,dword [w5]
call w19
jmp _53
_54: lea esi,dword[esi+8]
mov eax,dword [esi-4]
jmp _55
_52: mov eax,dword [esi]
lea ebp,dword[ebp+eax*4]
lea esi,dword[esi+8]
mov eax,dword [esi-4]
_55: _51: jmp _4C
_4D: lea ebp,dword[ebp+(-1)*4]
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w27: ; ::: Ldegfill ::: uso:-1 dD:-1 
;----------------
; BL 2 (1-6)0
;----------------
_56: or eax,eax
jz _57
sub eax,1
mov ebx,dword [wA]
sar ebx,$8
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
call w1B
mov dword [ebp],eax
add ebp,4
mov eax,dword [w8]
add dword [wA],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _56
_57: lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w28: ; ::: Ldegalpha ::: uso:-2 dD:-2 
;----------------
; BL 2 (3-9)0
;----------------
xor eax,$FF
xchg dword [esi],eax
_58: or eax,eax
jz _59
sub eax,1
mov ebx,dword [wA]
sar ebx,$8
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov ecx,dword [esi+8]
mov dword [esi+8],ecx
mov dword [esi],ecx
mov eax,ebx
call w1B
call w19
mov ebx,dword [w8]
add dword [wA],ebx
jmp _58
_59: lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w29: ; ::: runlenLdeg ::: uso:-1 dD:0 
;----------------
; BL 2 (9-12)2
; BL 1 (F-12)0
; BL 1 (F-12)0
;----------------
mov ebx,dword [w6]
neg ebx
imul ebx,dword [w8]
mov ecx,eax
sar ecx,$4
sub ecx,dword [w7]
imul ecx,dword [w9]
sub ebx,ecx
mov dword [wA],ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,w17
_5A: mov ebx,dword [eax]
add eax,4
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _5B
mov ebx,eax
sar ebx,$9
and ebx,$7FF
and eax,$1FF
cmp eax,$100
lea esi,dword[esi-4]
mov dword [esi],ebx
jnz _5C
lea esi,dword[esi+4]
mov eax,dword [esi-4]
call w27
jmp _5D
_5C: or eax,eax
jz _5E
call w28
jmp _5F
_5E: mov eax,dword [esi]
lea ebp,dword[ebp+eax*4]
imul eax,dword [w8]
add dword [wA],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
_5F: _5D: jmp _5A
_5B: lea ebp,dword[ebp+(-1)*4]
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w2A: ; ::: distf ::: uso:-2 dD:-1 
;----------------
; BL 0 (3-3)0
;----------------
cdq
add eax,edx
xor eax,edx
mov ebx,dword [esi]
mov edx,ebx
sar edx,31
add ebx,edx
xor ebx,edx
cmp ebx,eax
mov dword [esi],eax
mov eax,ebx
jge _60
xchg dword [esi],eax
_60: mov ebx,eax
sal ebx,$8
mov ecx,eax
sal ecx,$3
add ebx,ecx
mov ecx,eax
sal ecx,$4
sub ebx,ecx
sal eax,1
sub ebx,eax
mov eax,dword [esi]
sal eax,$7
add ebx,eax
mov eax,dword [esi]
sal eax,$5
sub ebx,eax
mov eax,dword [esi]
sal eax,$3
add ebx,eax
mov eax,dword [esi]
sal eax,1
sub ebx,eax
lea esi,dword[esi+4]
mov eax,ebx
ret

w2B: ; ::: Rdegfill ::: uso:-1 dD:-1 
;----------------
; BL 2 (1-A)0
;----------------
_61: or eax,eax
jz _62
sub eax,1
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov ebx,dword [wA]
mov dword [esi],ebx
mov eax,dword [wB]
call w2A
sar eax,$10
call w1B
mov dword [ebp],eax
add ebp,4
mov eax,dword [w8]
add dword [wA],eax
mov eax,dword [w9]
add dword [wB],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _61
_62: lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w2C: ; ::: Rdegalpha ::: uso:-2 dD:-2 
;----------------
; BL 2 (3-D)0
;----------------
xor eax,$FF
xchg dword [esi],eax
_63: or eax,eax
jz _64
sub eax,1
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov eax,dword [esi+12]
mov dword [esi+12],eax
mov dword [esi+4],eax
mov eax,dword [wA]
mov dword [esi],eax
mov eax,dword [wB]
call w2A
sar eax,$10
call w1B
call w19
mov ebx,dword [w8]
add dword [wA],ebx
mov ebx,dword [w9]
add dword [wB],ebx
jmp _63
_64: lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w2D: ; ::: runlenRdeg ::: uso:-1 dD:0 
;----------------
; BL 2 (10-1C)2
; BL 1 (16-1C)0
; BL 1 (16-1C)0
;----------------
mov ebx,dword [w6]
neg ebx
imul ebx,dword [w8]
mov ecx,eax
sar ecx,$4
sub ecx,dword [w7]
imul ecx,dword [w9]
sub ebx,ecx
mov dword [wA],ebx
mov ebx,dword [w6]
neg ebx
imul ebx,dword [w9]
mov ecx,eax
sar ecx,$4
sub ecx,dword [w7]
imul ecx,dword [w8]
add ebx,ecx
mov dword [wB],ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,w17
_65: mov ebx,dword [eax]
add eax,4
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _66
mov ebx,eax
sar ebx,$9
and ebx,$7FF
and eax,$1FF
cmp eax,$100
lea esi,dword[esi-4]
mov dword [esi],ebx
jnz _67
lea esi,dword[esi+4]
mov eax,dword [esi-4]
call w2B
jmp _68
_67: or eax,eax
jz _69
call w2C
jmp _6A
_69: mov eax,dword [esi]
lea ebp,dword[ebp+eax*4]
mov ebx,eax
imul ebx,dword [w8]
add dword [wA],ebx
imul eax,dword [w9]
add dword [wB],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
_6A: _68: jmp _65
_66: lea ebp,dword[ebp+(-1)*4]
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w2F: ; ::: heap! ::: uso:-1 dD:-1 
;----------------
; BL 2 (4-D)0
; BL 16 (9-B)0
;----------------
mov ebx,dword [w14]
add ebx,1
mov ecx,dword [w14]
mov dword [w14],ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ecx
_6B: or eax,eax
jz _6C
mov ebx,eax
sub ebx,1
sar ebx,1
mov ecx,ebx
sal ecx,$2
add ecx,w13
mov ecx,dword [ecx]
cmp ecx,dword [esi]
jge _6D
sal eax,$2
add eax,w13
mov ebx,dword [esi]
mov dword [eax],ebx
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_6D: sal eax,$2
add eax,w13
mov dword [eax],ecx
mov eax,ebx
jmp _6B
_6C: mov eax,dword [esi]
mov dword [w13],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w30: ; ::: moveDown ::: uso:-2 dD:-2 
;----------------
; BL 2 (2-14)0
; BL 1 (9-E)0
; BL 0 (B-E)0
; BL 16 (F-11)0
;----------------
_6E: mov ebx,dword [w14]
sar ebx,1
cmp eax,ebx
jge _6F
mov ebx,eax
sal ebx,1
add ebx,1
mov ecx,ebx
sal ecx,$2
add ecx,w13
mov ecx,dword [ecx]
mov edx,ebx
add edx,1
cmp edx,dword [w14]
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],ecx
mov eax,edx
jge _70
sal eax,$2
add eax,w13
mov eax,dword [eax]
mov ebx,dword [esi]
cmp ebx,eax
lea esi,dword[esi+4]
mov eax,ebx
jle _71
mov eax,dword [esi]
add eax,1
mov ebx,eax
sal ebx,$2
add ebx,w13
mov ebx,dword [ebx]
mov dword [esi],eax
mov eax,ebx
_71: jmp _72
_70: lea esi,dword[esi+4]
mov eax,dword [esi-4]
_72: cmp eax,dword [esi+8]
jl _73
mov eax,dword [esi+4]
sal eax,$2
add eax,w13
mov ebx,dword [esi+8]
mov dword [eax],ebx
lea esi,dword[esi+16]
mov eax,dword [esi-4]
ret
_73: mov ebx,dword [esi+4]
sal ebx,$2
add ebx,w13
mov dword [ebx],eax
lea esi,dword[esi+8]
mov eax,dword [esi-8]
jmp _6E
_6F: sal eax,$2
add eax,w13
mov ebx,dword [esi]
mov dword [eax],ebx
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w31: ; ::: heap@ ::: uso:0 dD:1 
;----------------
; BL 0 (7-9)0
;----------------
mov ebx,dword [w14]
sub ebx,1
sal ebx,$2
add ebx,w13
mov ebx,dword [ebx]
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi],ebx
mov eax,dword [w13]
mov dword [esi+4],eax
mov eax,$0
call w30
mov ebx,dword [w14]
sub ebx,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jnz _74
mov dword [w13],(-1)
_74: mov dword [w14],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w32: ; ::: PLINEI ::: uso:-2 dD:-2 
;----------------
; BL 16 (3-4)0
; BL 0 (B-B)0
; BL 16 (D-D)0
; BL 16 (E-E)0
; BL 0 (F-11)0
; BL 0 (15-17)0
;----------------
cmp eax,dword [wF]
jnz _75
mov eax,dword [esi]
mov dword [wE],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_75: mov ebx,dword [wF]
mov dword [wF],eax
mov ecx,dword [wE]
mov edx,dword [esi]
mov dword [wE],edx
cmp ebx,eax
lea esi,dword[esi-8]
mov dword [esi+8],edx
mov dword [esi+4],eax
mov dword [esi],ecx
mov eax,ebx
jle _76
xchg dword [esi+4],eax
mov ebx,dword [esi+8]
mov ecx,dword [esi]
mov dword [esi+8],ecx
mov dword [esi],ebx
_76: mov ebx,YRES
sal ebx,$4
cmp eax,ebx
jl _77
lea esi,dword[esi+16]
mov eax,dword [esi-4]
ret
_77: mov ebx,dword [esi+4]
cmp ebx,$0
jg _78
lea esi,dword[esi+16]
mov eax,dword [esi-4]
ret
_78: cmp ebx,dword [w10]
xchg dword [esi],eax
mov dword [esi+4],eax
mov eax,ebx
jle _79
mov dword [w10],eax
_79: push rax
push qword [esi]
mov eax,dword [esi+4]
sal eax,$8
mov ebx,dword [esi+8]
sal ebx,$8
sub ebx,eax
pop rcx
mov edx,dword [esp]
sub edx,ecx
mov edi,eax
mov eax,ebx
mov ebx,edx
cdq
idiv ebx
or ecx,ecx
lea esi,dword[esi+4]
mov dword [esi+4],edi
mov dword [esi],eax
mov eax,ecx
jns _7A
neg eax
imul eax,dword [esi]
add eax,dword [esi+4]
mov dword [esi+4],eax
mov eax,$0
_7A: mov ebx,eax
sal ebx,$10
mov ecx,dword [w12]
sub ecx,w11
sar ecx,$4
or ebx,ecx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
call w2F
mov ebx,dword [w12]
mov dword [ebx],eax
add ebx,4
mov eax,dword [esi]
sar eax,1
add eax,dword [esi+4]
mov dword [ebx],eax
add ebx,4
mov eax,dword [esi]
mov dword [ebx],eax
add ebx,4
pop rax
mov dword [ebx],eax
add ebx,4
mov dword [w12],ebx
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w33: ; ::: searchscan ::: uso:-2 dD:0 
;----------------
; BL 2 (2-7)2
; BL 16 (6-7)0
;----------------
_7B: mov ebx,dword [eax]
add eax,4
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _7C
sar eax,$14
and eax,$FFF
cmp eax,dword [esi+4]
jle _7D
mov eax,dword [esi]
sub eax,$8
lea esi,dword[esi+4]
ret
_7D: lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _7B
_7C: mov eax,dword [esi]
sub eax,$8
lea esi,dword[esi+4]
ret

w34: ; ::: inserta1 ::: uso:-1 dD:-1 
;----------------
; BL 2 (2-2)2
;----------------
push rax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
_7E: mov ebx,dword [esp]
mov ebx,dword [ebx]
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _7F
mov ebx,dword [esi]
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
lea esi,dword[esi+4]
jmp _7E
_7F: mov ebx,dword [esi]
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
pop rbx
mov dword [ebx],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w35: ; ::: inserta2 ::: uso:-1 dD:-1 
;----------------
; BL 2 (3-3)2
;----------------
push rax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
lea esi,dword[esi-4]
mov dword [esi],eax
_80: mov ebx,dword [esp]
mov ebx,dword [ebx]
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _81
mov ebx,dword [esi+4]
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
lea esi,dword[esi+4]
mov ebx,dword [esi-4]
mov dword [esi],ebx
jmp _80
_81: mov ebx,dword [esi+4]
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
mov ebx,dword [esi]
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
pop rbx
mov dword [ebx],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w36: ; ::: add.1 ::: uso:-3 dD:-2 
;----------------
; BL 16 (8-8)0
; BL 16 (B-10)0
; BL 16 (12-17)0
;----------------
push rax
mov eax,dword [eax]
mov ebx,eax
sar ebx,$9
and ebx,$7FF
cmp ebx,$1
jnz _82
add eax,dword [esi+4]
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
pop rax
lea esi,dword[esi+8]
ret
_82: mov ebx,eax
sar ebx,$14
and ebx,$FFF
mov ecx,dword [esi]
cmp ecx,ebx
jnz _83
mov ebx,dword [esp]
lea esi,dword[esi-4]
mov dword [esi+4],eax
mov dword [esi],ecx
mov eax,ebx
call w34
mov eax,dword [esi]
and eax,(-1048065)
add eax,dword [esi+4]
or eax,$200
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esi]
add eax,$100000
sub eax,$200
mov ebx,dword [esp]
mov dword [ebx],eax
pop rax
lea esi,dword[esi+8]
ret
_83: mov ebx,dword [esp]
add ebx,4
mov ebx,dword [ebx]
sar ebx,$14
and ebx,$FFF
sub ebx,1
cmp ecx,ebx
jnz _84
mov ebx,dword [esp]
lea esi,dword[esi-4]
mov dword [esi+4],eax
mov dword [esi],ecx
mov eax,ebx
call w34
mov ebx,dword [esi]
sub ebx,$200
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
sal eax,$14
or eax,$200
mov ebx,dword [esi]
and ebx,$1FF
add ebx,dword [esi+4]
or eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
pop rax
lea esi,dword[esi+8]
ret
_84: mov ebx,dword [esp]
lea esi,dword[esi-4]
mov dword [esi+4],eax
mov dword [esi],ecx
mov eax,ebx
call w35
mov ebx,dword [esi]
and ebx,(-1048065)
mov ecx,dword [esi]
sar ecx,$14
and ecx,$FFF
mov edx,eax
sub edx,ecx
sal edx,$9
or ebx,edx
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
mov ebx,dword [esi]
and ebx,$1FF
add ebx,dword [esi+4]
or ebx,$200
mov ecx,eax
sal ecx,$14
or ebx,ecx
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
add eax,1
mov ebx,dword [esp]
mov ebx,dword [ebx]
mov ecx,ebx
sar ecx,$14
and ecx,$FFF
sar ebx,$9
and ebx,$7FF
add ecx,ebx
sub ecx,eax
sal ecx,$9
sal eax,$14
or ecx,eax
mov eax,dword [esi]
and eax,$1FF
or ecx,eax
mov eax,dword [esp]
mov dword [eax],ecx
pop rax
lea esi,dword[esi+8]
ret

w37: ; ::: add.len ::: uso:-3 dD:-2 
;----------------
; BL 16 (4-6)0
; BL 16 (9-13)0
; BL 16 (14-17)0
;----------------
push rax
mov eax,dword [esi]
cmp eax,$1
jnz _85
pop rax
mov ebx,dword [esi+4]
mov dword [esi],ebx
mov dword [esi+4],$10
jmp w36
_85: mov ebx,dword [esp]
mov ebx,dword [ebx]
sar ebx,$9
and ebx,$7FF
cmp ebx,eax
jle _86
mov ecx,dword [esp]
lea esi,dword[esi-4]
mov dword [esi+4],eax
mov dword [esi],ebx
mov eax,ecx
call w34
mov ebx,dword [esi+4]
sal ebx,$14
mov ecx,dword [esi]
sal ecx,$9
or ebx,ecx
mov ecx,dword [esp]
mov ecx,dword [ecx]
and ecx,$1FF
add ecx,$10
or ebx,ecx
mov ecx,dword [esp]
mov dword [ecx],ebx
add dword [esp],4
sub eax,dword [esi]
sal eax,$9
mov ebx,dword [esi+4]
add ebx,dword [esi]
sal ebx,$14
or eax,ebx
mov ebx,dword [esp]
mov ebx,dword [ebx]
and ebx,$1FF
or eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
pop rax
lea esi,dword[esi+8]
ret
_86: cmp ebx,eax
jge _87
mov ecx,dword [esp]
mov ecx,dword [ecx]
add ecx,$10
mov edx,dword [esp]
mov dword [edx],ecx
add dword [esp],4
mov ecx,dword [esi+4]
add ecx,ebx
sub eax,ebx
pop rbx
mov dword [esi+4],ecx
mov dword [esi],eax
mov eax,ebx
jmp w37
_87: mov eax,dword [esp]
mov eax,dword [eax]
add eax,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
pop rax
lea esi,dword[esi+8]
ret

w38: ; ::: coverpixels ::: uso:-3 dD:-2 
;----------------
; BL 16 (5-5)0
; BL 16 (8-8)0
; BL 16 (B-E)0
; BL 16 (D-E)0
; BL 1 (E-15)0
; BL 16 (13-13)0
; BL 1 (16-1A)0
; BL 1 (1B-1C)0
; BL 0 (1D-1F)0
; BL 16 (1E-1F)0
;----------------
push rax
mov eax,dword [esi+4]
sar eax,$4
or eax,eax
jns _88
pop rax
lea esi,dword[esi+8]
ret
_88: mov ebx,dword [esi]
sar ebx,$4
cmp ebx,XRES
jl _89
pop rax
lea esi,dword[esi+8]
ret
_89: pop rcx
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov dword [esi],ebx
mov eax,ecx
call w33
push rax
mov eax,dword [esi]
cmp eax,dword [esi+4]
jnz _8A
mov ebx,dword [esi+12]
and ebx,$F
mov ecx,dword [esi+8]
and ecx,$F
sub ebx,ecx
or ebx,ebx
jz _8B
pop rcx
lea esi,dword[esi+8]
mov dword [esi+4],ebx
mov dword [esi],eax
mov eax,ecx
jmp w36
_8B: pop rax
lea esi,dword[esi+16]
ret
_8A: or eax,eax
lea esi,dword[esi+4]
js _8C
mov ebx,dword [esi+4]
and ebx,$F
mov ecx,$10
sub ecx,ebx
pop rbx
lea esi,dword[esi-8]
mov dword [esi+4],ecx
mov dword [esi],eax
mov ecx,dword [esi+8]
mov dword [esi+12],ecx
mov dword [esi+8],eax
mov eax,ebx
call w36
push rax
mov eax,dword [esi]
add eax,1
cmp eax,XRES
jl _8D
pop rax
lea esi,dword[esi+12]
ret
_8D: lea esi,dword[esi+4]
jmp _8E
_8C: lea esp,dword[esp+4]
push w17
lea esi,dword[esi+4]
mov eax,dword [esi-4]
mov dword [esi],eax
mov eax,$0
_8E: mov ebx,dword [esi]
cmp ebx,XRES
mov dword [esi],eax
mov eax,ebx
jle _8F
mov ebx,XRES
sub ebx,dword [esi]
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jmp _90
_8F: mov ebx,eax
sub ebx,dword [esi]
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
_90: cmp eax,$0
jle _91
pop rbx
lea esi,dword[esi-4]
mov dword [esi],eax
mov ecx,dword [esi+8]
mov edx,dword [esi+4]
mov dword [esi+8],edx
mov dword [esi+4],ecx
mov eax,ebx
call w37
push rax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _92
_91: lea esi,dword[esi+8]
mov eax,dword [esi-8]
_92: cmp eax,XRES
jge _93
mov ebx,dword [esi]
and ebx,$F
or ebx,ebx
jz _94
pop rcx
lea esi,dword[esi-4]
mov dword [esi+4],ebx
mov dword [esi],eax
mov eax,ecx
jmp w36
_94: mov dword [esi],eax
mov eax,ebx
_93: pop rax
lea esi,dword[esi+4]
ret

w39: ; ::: fillcover ::: uso:0 dD:0 
;----------------
; BL 2 (3-A)0
;----------------
push w17
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,w15
_95: mov ebx,dword [w16]
sub ebx,$4
cmp eax,ebx
jge _96
mov ebx,dword [eax]
add eax,4
add ebx,4
mov ebx,dword [ebx]
sar ebx,$8
mov ecx,dword [eax]
add eax,4
add ecx,4
mov ecx,dword [ecx]
sar ecx,$8
pop rdx
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],ecx
mov dword [esi],ebx
mov eax,edx
call w38
push rax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _95
_96: lea esp,dword[esp+4]
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w3A: ; ::: activosort ::: uso:-3 dD:-3 
;----------------
; BL 2 (3-9)0
; BL 16 (8-8)0
;----------------
_97: cmp eax,w15
jle _98
sub eax,$4
mov ebx,eax
mov ebx,dword [ebx]
mov ecx,ebx
add ecx,4
mov ecx,dword [ecx]
cmp ecx,dword [esi]
jge _99
add eax,4
mov ebx,dword [esi+4]
mov dword [eax],ebx
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_99: mov ecx,eax
add ecx,4
mov dword [ecx],ebx
jmp _97
_98: mov ebx,dword [esi+4]
mov dword [eax],ebx
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w3B: ; ::: deletecopy ::: uso:-2 dD:-1 
;----------------
; BL 2 (3-8)0
; BL 1 (8-8)0
;----------------
mov ebx,eax
add ebx,4
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
_9A: cmp eax,dword [w16]
jge _9B
mov ebx,dword [eax]
add eax,4
mov ecx,ebx
add ecx,$C
mov ecx,dword [ecx]
cmp ecx,dword [esi+4]
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov dword [esi],ebx
mov eax,ecx
jle _9C
mov eax,dword [esi]
mov ebx,dword [esi+8]
mov dword [ebx],eax
add ebx,4
lea esi,dword[esi+8]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _9D
_9C: lea esi,dword[esi+8]
mov eax,dword [esi-4]
_9D: jmp _9A
_9B: mov eax,dword [esi]
mov dword [w16],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w3C: ; ::: deleteline ::: uso:-1 dD:0 
;----------------
; BL 2 (2-7)0
; BL 16 (6-7)0
;----------------
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,w15
_9E: cmp eax,dword [w16]
jge _9F
mov ebx,eax
mov ebx,dword [ebx]
add ebx,$C
mov ebx,dword [ebx]
cmp ebx,dword [esi]
jnz _A0
jmp w3B
_A0: add eax,4
jmp _9E
_9F: lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w3D: ; ::: POLI ::: uso:0 dD:0 
;----------------
; BL 16 (2-8)0
; BL 0 (A-D)0
; BL 2 (15-30)0
; BL 2 (1B-2F)0
; BL 2 (1B-26)0
; BL 2 (28-2F)0
;----------------
mov ebx,dword [w10]
or ebx,ebx
jns _A1
mov dword [w12],w11
mov dword [w10],(-1)
mov dword [w14],$0
ret
_A1: mov ecx,YRES
sal ecx,$4
cmp ebx,ecx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jle _A2
mov ebx,YRES
sal ebx,$4
mov dword [w10],ebx
_A2: mov dword [w16],w15
mov eax,dword [w13]
sar eax,$10
mov ebx,eax
sar ebx,$4
shl ebx,10
lea ebp,dword[SYSFRAME+ebx*4]
lea esi,dword[esi-4]
mov dword [esi],eax
_A3: cmp eax,dword [w10]
jge _A4
mov ebx,XRES
add ebx,1
sal ebx,$9
mov ecx,w17
mov dword [ecx],ebx
add ecx,4
mov dword [ecx],$0
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$10
_A5: or eax,eax
jz _A6
sub eax,1
push rax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
_A7: cmp eax,dword [esi]
jnz _A8
lea esi,dword[esi+4]
call w31
and eax,$FFFF
sal eax,$4
add eax,w11
mov ebx,eax
add ebx,4
mov ebx,dword [ebx]
mov ecx,dword [w16]
add ecx,4
mov edx,dword [w16]
mov dword [w16],ecx
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov dword [esi],ebx
mov eax,edx
call w3A
mov ebx,dword [w13]
sar ebx,$10
lea esi,dword[esi-4]
mov dword [esi],ebx
jmp _A7
_A8: call w39
add eax,1
call w3C
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,w15
_A9: cmp eax,dword [w16]
jge _AA
mov ebx,eax
mov ebx,dword [ebx]
mov ecx,ebx
add ecx,4
mov edx,dword [ecx]
add ecx,4
mov ecx,dword [ecx]
add edx,ecx
mov ecx,ebx
add ecx,4
mov dword [ecx],edx
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],edx
call w3A
add eax,4
jmp _A9
_AA: pop rax
jmp _A5
_A6: lea esi,dword[esi+4]
mov eax,dword [esi-4]
mov ecx,dword [w2E]
call rcx
jmp _A3
_A4: mov dword [w12],w11
mov dword [w10],(-1)
mov dword [w14],$0
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w3E: ; ::: PCURVEI ::: uso:-4 dD:-4 
;----------------
; BL 16 (B-B)0
;----------------
mov ebx,dword [esi+8]
add ebx,dword [wE]
mov ecx,dword [esi]
sal ecx,1
sub ebx,ecx
mov edx,ebx
sar edx,31
add ebx,edx
xor ebx,edx
mov ecx,dword [esi+4]
add ecx,dword [wF]
mov edx,eax
sal edx,1
sub ecx,edx
mov edx,ecx
sar edx,31
add ecx,edx
xor ecx,edx
add ebx,ecx
cmp ebx,$18
jge _AB
lea esi,dword[esi+8]
mov eax,dword [esi-4]
jmp w32
_AB: mov ebx,dword [esi+8]
add ebx,dword [esi]
sar ebx,1
mov ecx,dword [esi+4]
add ecx,eax
sar ecx,1
add eax,dword [wF]
sar eax,1
mov edx,dword [esi]
add edx,dword [wE]
sar edx,1
mov edi,ebx
add edi,edx
sar edi,1
; libera !!!1111111:[esi+8] [esi+4] ebx ecx edx eax edi .ecx .eax 
mov [esi-4],ebx
; post !!1111101:[esi+8] [esi+4] [esi-4] ecx edx eax edi .ecx .eax 
mov ebx,ecx
add ebx,eax
sar ebx,1
lea esi,dword[esi-16]
xchg dword [esi+12],ecx
mov dword [esi+8],edi
mov dword [esi+4],ebx
mov dword [esi],edx
mov dword [esi+16],ecx
call w3E
jmp w3E

w3F: ; ::: PCURVE ::: uso:-4 dD:-4 
;----------------
;----------------
push rax
push qword [esi]
push qword [rsi+4]
mov eax,dword [esi+8]
sal eax,$4
pop rbx
sal ebx,$4
pop rcx
sal ecx,$4
pop rdx
sal edx,$4
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],ecx
mov eax,edx
jmp w3E

w4B: ; ::: gc2win ::: uso:0 dD:0 
;----------------
;----------------
mov ebx,dword [w43]
sar ebx,1
mov ecx,dword [w41]
sub ecx,ebx
mov dword [w45],ecx
add ecx,dword [w43]
mov dword [w47],ecx
mov ebx,dword [w44]
sar ebx,1
mov ecx,dword [w42]
sub ecx,ebx
mov dword [w46],ecx
add ecx,dword [w44]
mov dword [w48],ecx
ret

w4C: ; ::: scr ::: uso:0 dD:0 
;----------------
;----------------
mov dword [w47],XRES
mov dword [w43],XRES
mov ebx,XRES
sar ebx,1
mov dword [w41],ebx
mov dword [w48],YRES
mov dword [w44],YRES
mov ebx,YRES
sar ebx,1
mov dword [w42],ebx
mov dword [w45],$0
mov dword [w46],$0
ret

w4D: ; ::: ?ukey ::: uso:-2 dD:-2 
;----------------
; BL 16 (4-4)0
;----------------
or eax,$80
cmp eax,dword [SYSKEY]
jnz _AC
push qword [esi]
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_AC: lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w4E: ; ::: ?key ::: uso:-2 dD:-2 
;----------------
; BL 16 (3-3)0
;----------------
cmp eax,dword [SYSKEY]
jnz _AD
push qword [esi]
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_AD: lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w52: ; ::: empty ::: uso:0 dD:0 
;----------------
; BL 1 (3-7)0
;----------------
mov ebx,dword [w51]
cmp ebx,w50
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jnz _AE
mov eax,dword [FREE_MEM]
jmp _AF
_AE: sub eax,$4
mov dword [w51],eax
mov eax,dword [eax]
_AF: mov dword [w4F],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w53: ; ::: ,w ::: uso:-1 dD:-1 
;----------------
; BL 2 (2-5)2
;----------------
lea esi,dword[esi-4]
mov ebx,dword [w4F]
mov dword [esi],ebx
_B0: movsx ebx,byte [eax]
add eax,1
and ebx,$FF
cmp ebx,$20
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jle _B1
mov ebx,dword [esi+4]
mov byte [ebx],al
add ebx,1
lea esi,dword[esi+4]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _B0
_B1: mov eax,dword [esi+4]
mov dword [w4F],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w54: ; ::: c0 ::: uso:-2 dD:-1 
;----------------
; BL 16 (2-2)0
; BL 2 (2-7)2
; BL 16 (4-4)0
; BL 16 (5-5)0
;----------------
mov ebx,dword [esi]
or ebx,ebx
jnz _B2
lea esi,dword[esi+4]
ret
_B2: mov dword [esi],eax
mov eax,ebx
_B3: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _B4
cmp eax,$7C
jnz _B5
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_B5: cmp eax,$7E
jnz _B6
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_B6: mov ebx,dword [w4F]
mov byte [ebx],al
add ebx,1
mov dword [w4F],ebx
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _B3
_B4: lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w55: ; ::: c1 ::: uso:-2 dD:-1 
;----------------
; BL 16 (2-2)0
; BL 2 (2-8)2
; BL 16 (4-4)0
; BL 16 (5-5)0
; BL 16 (6-6)0
;----------------
mov ebx,dword [esi]
or ebx,ebx
jnz _B7
lea esi,dword[esi+4]
ret
_B7: mov dword [esi],eax
mov eax,ebx
_B8: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _B9
cmp eax,$5F
jnz _BA
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_BA: cmp eax,$7C
jnz _BB
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_BB: cmp eax,$7E
jnz _BC
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_BC: mov ebx,dword [w4F]
mov byte [ebx],al
add ebx,1
mov dword [w4F],ebx
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _B8
_B9: lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w57: ; ::: ,b ::: uso:-1 dD:-1 
;----------------
; BL 3 (3-8)0
; BL 2 (9-A)2
;----------------
mov ebx,w56
add ebx,$22
lea esi,dword[esi-4]
mov dword [esi],ebx
_BD: mov ebx,eax
and ebx,$1
add ebx,$30
mov ecx,dword [esi]
mov byte [ecx],bl
sub ecx,1
sar eax,1
and eax,$7FFFFFFF
or eax,eax
mov dword [esi],ecx
jnz _BD
mov eax,dword [esi]
add eax,1
mov ebx,dword [w4F]
mov dword [esi],ebx
_BE: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _BF
mov ebx,dword [esi+4]
mov byte [ebx],al
add ebx,1
lea esi,dword[esi+4]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _BE
_BF: mov eax,dword [esi+4]
mov dword [w4F],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w58: ; ::: c2 ::: uso:-2 dD:-1 
;----------------
;----------------
xchg dword [esi],eax
jmp w57

w59: ; ::: c3 ::: uso:-2 dD:-1 
;----------------
; BL 16 (2-2)0
; BL 2 (3-4)2
;----------------
mov ebx,dword [esi]
or ebx,ebx
jnz _C0
lea esi,dword[esi+4]
ret
_C0: lea esi,dword[esi-4]
mov dword [esi+4],eax
mov ecx,dword [w4F]
mov dword [esi],ecx
mov eax,ebx
_C1: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _C2
mov ebx,dword [esi+4]
mov byte [ebx],al
add ebx,1
lea esi,dword[esi+4]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _C1
_C2: mov eax,dword [esi+4]
mov dword [w4F],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w5A: ; ::: ,d ::: uso:-1 dD:-1 
;----------------
; BL 0 (1-8)0
; BL 16 (1-5)0
; BL 2 (3-4)2
; BL 3 (A-D)0
; BL 2 (E-F)2
;----------------
or eax,eax
jns _C3
neg eax
or eax,eax
jns _C4
lea esi,dword[esi-4]
mov eax,dword [w4F]
mov dword [esi],eax
mov eax,str0
_C5: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _C6
mov ebx,dword [esi+4]
mov byte [ebx],al
add ebx,1
lea esi,dword[esi+4]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _C5
_C6: mov eax,dword [esi+4]
mov dword [w4F],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_C4: mov ebx,dword [w4F]
mov byte [ebx],$2D
add ebx,1
mov dword [w4F],ebx
_C3: mov ebx,w56
add ebx,$22
lea esi,dword[esi-4]
mov dword [esi],ebx
_C7: mov ebx,$A
cdq
idiv ebx
add edx,$30
mov ecx,dword [esi]
mov byte [ecx],dl
sub ecx,1
or eax,eax
mov dword [esi],ecx
jnz _C7
mov eax,dword [esi]
add eax,1
mov ebx,dword [w4F]
mov dword [esi],ebx
_C8: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _C9
mov ebx,dword [esi+4]
mov byte [ebx],al
add ebx,1
lea esi,dword[esi+4]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _C8
_C9: mov eax,dword [esi+4]
mov dword [w4F],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w5B: ; ::: c4 ::: uso:-2 dD:-1 
;----------------
;----------------
xchg dword [esi],eax
jmp w5A

w5C: ; ::: c5 ::: uso:0 dD:0 
;----------------
;----------------
mov ebx,dword [w4F]
mov byte [ebx],$25
add ebx,1
mov dword [w4F],ebx
ret

w5D: ; ::: ,df ::: uso:-1 dD:-1 
;----------------
; BL 3 (3-6)0
; BL 2 (8-9)2
;----------------
mov ebx,w56
add ebx,$22
lea esi,dword[esi-4]
mov dword [esi],ebx
_CA: mov ebx,$A
cdq
idiv ebx
add edx,$30
mov ecx,dword [esi]
mov byte [ecx],dl
sub ecx,1
or eax,eax
mov dword [esi],ecx
jnz _CA
mov eax,dword [esi]
add eax,$2
mov ebx,dword [w4F]
mov dword [esi],ebx
_CB: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _CC
mov ebx,dword [esi+4]
mov byte [ebx],al
add ebx,1
lea esi,dword[esi+4]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _CB
_CC: mov eax,dword [esi+4]
mov dword [w4F],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w5E: ; ::: ,f ::: uso:-1 dD:-1 
;----------------
; BL 0 (1-4)0
;----------------
or eax,eax
jns _CD
neg eax
mov ebx,dword [w4F]
mov byte [ebx],$2D
add ebx,1
mov dword [w4F],ebx
_CD: mov ebx,eax
sar ebx,$10
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
call w5A
mov ebx,dword [w4F]
mov byte [ebx],$2E
add ebx,1
mov dword [w4F],ebx
and eax,$FFFF
mov ebx,$2710
cdq
imul ebx
shrd eax,edx,$10
add eax,$2710
jmp w5D

w5F: ; ::: c6 ::: uso:-2 dD:-1 
;----------------
;----------------
xchg dword [esi],eax
jmp w5E

w60: ; ::: c7 ::: uso:-2 dD:-1 
;----------------
; BL 16 (2-2)0
;----------------
mov ebx,dword [esi]
or ebx,ebx
jnz _CE
lea esi,dword[esi+4]
ret
_CE: mov dword [esi],eax
mov eax,ebx
jmp w53

w61: ; ::: ,h ::: uso:-1 dD:-1 
;----------------
; BL 3 (3-B)0
; BL 0 (7-8)0
; BL 2 (C-D)2
;----------------
mov ebx,w56
add ebx,$22
lea esi,dword[esi-4]
mov dword [esi],ebx
_CF: mov ebx,eax
and ebx,$F
add ebx,$30
cmp ebx,$39
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jle _D0
add eax,$7
_D0: mov ebx,dword [esi+4]
mov byte [ebx],al
sub ebx,1
mov eax,dword [esi]
sar eax,$4
and eax,$FFFFFFF
or eax,eax
lea esi,dword[esi+4]
mov dword [esi],ebx
jnz _CF
mov eax,dword [esi]
add eax,1
mov ebx,dword [w4F]
mov dword [esi],ebx
_D1: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _D2
mov ebx,dword [esi+4]
mov byte [ebx],al
add ebx,1
lea esi,dword[esi+4]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _D1
_D2: mov eax,dword [esi+4]
mov dword [w4F],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w62: ; ::: c8 ::: uso:-2 dD:-1 
;----------------
;----------------
xchg dword [esi],eax
jmp w61

w63: ; ::: c9 ::: uso:-2 dD:-1 
;----------------
;----------------
mov ebx,dword [esi]
sar ebx,$10
mov dword [esi],eax
mov eax,ebx
jmp w5A

w64: ; ::: ca ::: uso:-2 dD:-1 
;----------------
;----------------
mov ebx,dword [esi]
and ebx,$FFFF
mov dword [esi],eax
mov eax,ebx
jmp w5A

w65: ; ::: cb ::: uso:-2 dD:-1 
;----------------
;----------------
mov ebx,dword [esi]
mov ecx,dword [w4F]
mov byte [ecx],bl
add ecx,1
mov dword [w4F],ecx
lea esi,dword[esi+4]
ret

w66: ; ::: cc ::: uso:-2 dD:-1 
;----------------
; BL 16 (2-2)0
; BL 2 (2-6)2
; BL 16 (4-4)0
;----------------
mov ebx,dword [esi]
or ebx,ebx
jnz _D3
lea esi,dword[esi+4]
ret
_D3: mov dword [esi],eax
mov eax,ebx
_D4: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _D5
cmp eax,$D
jnz _D6
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret
_D6: mov ebx,dword [w4F]
mov byte [ebx],al
add ebx,1
mov dword [w4F],ebx
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _D4
_D5: lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w67: ; ::: cd ::: uso:0 dD:0 
;----------------
;----------------
ret

w68: ; ::: ce ::: uso:0 dD:0 
;----------------
;----------------
mov ebx,dword [w4F]
mov byte [ebx],$D
add ebx,1
mov dword [w4F],ebx
ret

w69: ; ::: ,o ::: uso:-1 dD:-1 
;----------------
; BL 0 (1-5)0
; BL 0 (1-2)0
; BL 3 (7-C)0
; BL 2 (D-E)2
;----------------
or eax,eax
jns _D7
neg eax
or eax,eax
jns _D8
mov eax,$0
_D8: mov ebx,dword [w4F]
mov byte [ebx],$2D
add ebx,1
mov dword [w4F],ebx
_D7: mov ebx,w56
add ebx,$22
lea esi,dword[esi-4]
mov dword [esi],ebx
_D9: mov ebx,eax
and ebx,$7
add ebx,$30
mov ecx,dword [esi]
mov byte [ecx],bl
sub ecx,1
sar eax,$3
or eax,eax
mov dword [esi],ecx
jnz _D9
mov eax,dword [esi]
add eax,1
mov ebx,dword [w4F]
mov dword [esi],ebx
_DA: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _DB
mov ebx,dword [esi+4]
mov byte [ebx],al
add ebx,1
lea esi,dword[esi+4]
mov dword [esi],ebx
mov eax,dword [esi-4]
jmp _DA
_DB: mov eax,dword [esi+4]
mov dword [w4F],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w6A: ; ::: cf ::: uso:-2 dD:-1 
;----------------
;----------------
xchg dword [esi],eax
jmp w69

w6C: ; ::: ,emit ::: uso:-2 dD:-1 
;----------------
; BL 16 (3-5)0
;----------------
cmp eax,$25
jz _DC
mov ebx,dword [w4F]
mov byte [ebx],al
add ebx,1
mov dword [w4F],ebx
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret
_DC: mov eax,dword [esi]
movsx ebx,byte [eax]
add eax,1
and ebx,$F
sal ebx,$2
add ebx,w6B
mov ebx,dword [ebx]
push rbx
lea esi,dword[esi+4]
ret

w6F: ; ::: mprint ::: uso:-1 dD:0 
;----------------
; BL 0 (2-5)0
; BL 1 (8-A)0
; BL 2 (C-E)2
;----------------
mov ebx,dword [w4F]
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jnz _DD
mov ebx,dword [FREE_MEM]
mov dword [w4F],ebx
mov eax,ebx
_DD: mov ebx,dword [w51]
mov dword [ebx],eax
add ebx,4
mov dword [w51],ebx
mov eax,dword [esi]
cmp eax,w6D
lea esi,dword[esi+4]
jnz _DE
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,w6E
jmp _DF
_DE: lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,w6D
_DF: mov dword [w4F],eax
push rax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
_E0: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _E1
call w6C
jmp _E0
_E1: mov ebx,dword [w4F]
mov byte [ebx],al
add ebx,1
mov dword [w4F],ebx
lea esi,dword[esi+8]
mov eax,dword [esi-4]
call w52
pop rbx
lea esi,dword[esi-4]
mov eax,ebx
ret

w77: ; ::: mtrans ::: uso:-3 dD:-3 
;----------------
;----------------
push qword [w76]
mov ebx,dword [esp]
add ebx,$30
mov ebx,dword [ebx]
mov ecx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
add eax,$30
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
add eax,$30
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
mov eax,dword [eax]
add eax,dword [esi+4]
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
add eax,$20
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
add eax,$20
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
add eax,$20
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
mov eax,dword [eax]
add eax,dword [esi]
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
add eax,$10
mov eax,dword [eax]
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
add eax,$10
mov eax,dword [eax]
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
add eax,$10
mov eax,dword [eax]
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov ebx,dword [ebx]
add eax,ebx
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
pop rax
add dword [eax],ecx
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w78: ; ::: mtransi ::: uso:-3 dD:-3 
;----------------
;----------------
push qword [w76]
mov ebx,dword[esp]
mov ebx,dword[ebx]
add dword [esp],4
mov ecx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword[esp]
mov ebx,dword[ebx]
add dword [esp],4
mov edx,eax
mov eax,dword [esi]
mov edi,edx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov eax,dword [eax]
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword[esp]
mov ebx,dword[ebx]
add dword [esp],4
mov edx,eax
mov eax,dword [esi]
mov edi,edx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov eax,dword [eax]
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword[esp]
mov ebx,dword[ebx]
add dword [esp],4
mov edx,eax
mov eax,dword [esi]
mov edi,edx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov eax,dword [eax]
add edi,eax
pop rax
mov dword [eax],edi
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w79: ; ::: mscalei ::: uso:-3 dD:-3 
;----------------
;----------------
push qword [w76]
mov ebx,dword [esp]
mov ebx,dword [ebx]
mov ecx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
add dword [esp],$4
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
add dword [esp],$4
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,eax
mov eax,dword [esi]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword [esp]
mov dword [ebx],eax
add dword [esp],4
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
pop rbx
mov dword [ebx],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w7A: ; ::: mrotx ::: uso:-1 dD:-1 
;----------------
;----------------
mov ebx,dword [w76]
add ebx,$10
push rbx
lea esi,dword[esi-4]
mov dword [esi],eax
call w2
xchg dword [esi],eax
call w1
mov ebx,dword [esp]
mov ebx,dword [ebx]
mov ecx,dword [esp]
add ecx,$10
mov ecx,dword [ecx]
mov dword [esi-4],eax
cdq
imul ebx
shrd eax,edx,$10
mov edx,eax
mov eax,dword [esi]
mov edi,edx
cdq
imul ecx
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,ecx
cdq
imul dword [esi-4]
shrd eax,edx,$10
push rax
mov eax,dword [esi]
neg eax
mov edx,eax
mov eax,ebx
mov ebx,edx
cdq
imul ebx
shrd eax,edx,$10
pop rbx
add eax,ebx
mov ebx,dword [esp]
add ebx,$C
mov dword [ebx],eax
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,dword [esp]
add ebx,$10
mov ebx,dword [ebx]
mov edx,eax
mov eax,dword [esi-4]
mov edi,edx
cdq
imul edi
shrd eax,edx,$10
mov edx,eax
mov eax,dword [esi]
; libera !!!1111111:[esi] [esi-4] edi ebx edx eax .ebx $10 
mov [esi-12],edi
; post !!1101111:[esi] [esi-4] [esi-12] ebx edx eax .ebx $10 
mov edi,edx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,ebx
cdq
imul dword [esi-4]
shrd eax,edx,$10
push rax
mov eax,dword [esi]
neg eax
mov edx,eax
mov eax,dword [esi-12]
mov edi,edx
cdq
imul edi
shrd eax,edx,$10
pop rdx
add eax,edx
mov edx,dword [esp]
add edx,$C
mov dword [edx],eax
mov eax,dword [esp]
mov eax,dword [eax]
mov edx,dword [esp]
add edx,$10
mov edx,dword [edx]
mov edi,eax
mov eax,dword [esi-4]
; libera !!!1111111:[esi] [esi-4] edi edx eax .edi $10 
mov [esi-12],edi
; post !!1101111:[esi] [esi-4] [esi-12] edx eax .[esi-12] $10 
mov edi,edx
cdq
imul dword [esi-12]
shrd eax,edx,$10
mov edx,eax
mov eax,dword [esi]
; libera !!!1111111:[esi] [esi-4] [esi-12] edi edx eax .edi $10 
mov [esi-16],edi
; post !!1101111:[esi] [esi-4] [esi-12] [esi-16] edx eax .[esi-16] $10 
mov edi,edx
cdq
imul dword [esi-16]
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,dword [esi-16]
cdq
imul dword [esi-4]
shrd eax,edx,$10
push rax
mov eax,dword [esi]
neg eax
mov edx,eax
mov eax,dword [esi-12]
mov edi,edx
cdq
imul edi
shrd eax,edx,$10
pop rdx
add eax,edx
mov edx,dword [esp]
add edx,$C
mov dword [edx],eax
mov eax,dword [esp]
mov eax,dword [eax]
mov edx,dword [esp]
add edx,$10
mov edx,dword [edx]
mov edi,eax
mov eax,dword [esi-4]
; libera !!!1111111:[esi] [esi-4] edi edx eax .edi $10 
mov [esi-12],edi
; post !!1101111:[esi] [esi-4] [esi-12] edx eax .[esi-12] $10 
mov edi,edx
cdq
imul dword [esi-12]
shrd eax,edx,$10
mov edx,eax
mov eax,dword [esi]
; libera !!!1111111:[esi] [esi-4] [esi-12] edi edx eax .edi $10 
mov [esi-16],edi
; post !!1101111:[esi] [esi-4] [esi-12] [esi-16] edx eax .[esi-16] $10 
mov edi,edx
cdq
imul dword [esi-16]
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,dword [esi-16]
cdq
imul dword [esi-4]
shrd eax,edx,$10
push rax
mov eax,dword [esi]
cdq
imul dword [esi-12]
shrd eax,edx,$10
pop rdx
add eax,edx
pop rdx
add edx,$C
mov dword [edx],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w7B: ; ::: mroty ::: uso:-1 dD:-1 
;----------------
;----------------
push qword [w76]
lea esi,dword[esi-4]
mov dword [esi],eax
call w2
xchg dword [esi],eax
call w1
mov ebx,dword [esp]
mov ebx,dword [ebx]
mov ecx,dword [esp]
add ecx,$20
mov ecx,dword [ecx]
mov dword [esi-4],eax
cdq
imul ebx
shrd eax,edx,$10
mov edx,eax
mov eax,dword [esi]
mov edi,edx
cdq
imul ecx
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,ecx
cdq
imul dword [esi-4]
shrd eax,edx,$10
push rax
mov eax,dword [esi]
neg eax
mov edx,eax
mov eax,ebx
mov ebx,edx
cdq
imul ebx
shrd eax,edx,$10
pop rbx
add eax,ebx
mov ebx,dword [esp]
add ebx,$1C
mov dword [ebx],eax
mov eax,dword [esp]
mov eax,dword [eax]
mov ebx,dword [esp]
add ebx,$20
mov ebx,dword [ebx]
mov edx,eax
mov eax,dword [esi-4]
mov edi,edx
cdq
imul edi
shrd eax,edx,$10
mov edx,eax
mov eax,dword [esi]
; libera !!!1111111:[esi] [esi-4] edi ebx edx eax .ebx $10 
mov [esi-12],edi
; post !!1101111:[esi] [esi-4] [esi-12] ebx edx eax .ebx $10 
mov edi,edx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,ebx
cdq
imul dword [esi-4]
shrd eax,edx,$10
push rax
mov eax,dword [esi]
neg eax
mov edx,eax
mov eax,dword [esi-12]
mov edi,edx
cdq
imul edi
shrd eax,edx,$10
pop rdx
add eax,edx
mov edx,dword [esp]
add edx,$1C
mov dword [edx],eax
mov eax,dword [esp]
mov eax,dword [eax]
mov edx,dword [esp]
add edx,$20
mov edx,dword [edx]
mov edi,eax
mov eax,dword [esi-4]
; libera !!!1111111:[esi] [esi-4] edi edx eax .edi $10 
mov [esi-12],edi
; post !!1101111:[esi] [esi-4] [esi-12] edx eax .[esi-12] $10 
mov edi,edx
cdq
imul dword [esi-12]
shrd eax,edx,$10
mov edx,eax
mov eax,dword [esi]
; libera !!!1111111:[esi] [esi-4] [esi-12] edi edx eax .edi $10 
mov [esi-16],edi
; post !!1101111:[esi] [esi-4] [esi-12] [esi-16] edx eax .[esi-16] $10 
mov edi,edx
cdq
imul dword [esi-16]
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,dword [esi-16]
cdq
imul dword [esi-4]
shrd eax,edx,$10
push rax
mov eax,dword [esi]
neg eax
mov edx,eax
mov eax,dword [esi-12]
mov edi,edx
cdq
imul edi
shrd eax,edx,$10
pop rdx
add eax,edx
mov edx,dword [esp]
add edx,$1C
mov dword [edx],eax
mov eax,dword [esp]
mov eax,dword [eax]
mov edx,dword [esp]
add edx,$20
mov edx,dword [edx]
mov edi,eax
mov eax,dword [esi-4]
; libera !!!1111111:[esi] [esi-4] edi edx eax .edi $10 
mov [esi-12],edi
; post !!1101111:[esi] [esi-4] [esi-12] edx eax .[esi-12] $10 
mov edi,edx
cdq
imul dword [esi-12]
shrd eax,edx,$10
mov edx,eax
mov eax,dword [esi]
; libera !!!1111111:[esi] [esi-4] [esi-12] edi edx eax .edi $10 
mov [esi-16],edi
; post !!1101111:[esi] [esi-4] [esi-12] [esi-16] edx eax .[esi-16] $10 
mov edi,edx
cdq
imul dword [esi-16]
shrd eax,edx,$10
add edi,eax
mov eax,dword [esp]
mov dword [eax],edi
add dword [esp],4
mov eax,dword [esi-16]
cdq
imul dword [esi-4]
shrd eax,edx,$10
push rax
mov eax,dword [esi]
neg eax
mov edx,eax
mov eax,dword [esi-12]
mov edi,edx
cdq
imul edi
shrd eax,edx,$10
pop rdx
add eax,edx
pop rdx
add edx,$1C
mov dword [edx],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w7C: ; ::: transform ::: uso:-3 dD:0 
;----------------
;----------------
push qword [w76]
mov ebx,dword[esp]
mov ebx,dword[ebx]
add dword [esp],4
mov ecx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword[esp]
mov ebx,dword[ebx]
add dword [esp],4
mov edx,eax
mov eax,dword [esi]
mov edi,edx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
add edi,eax
pop rax
push rdi
push rax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword[esp]
mov ebx,dword[ebx]
add dword [esp],4
mov edx,eax
mov eax,dword [esi]
mov edi,edx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
add edi,eax
pop rax
push rdi
push rax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,dword [esi+4]
cdq
imul ebx
shrd eax,edx,$10
mov ebx,dword[esp]
mov ebx,dword[ebx]
add dword [esp],4
mov edx,eax
mov eax,dword [esi]
mov edi,edx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
mov eax,dword[esp]
mov eax,dword[eax]
add dword [esp],4
mov ebx,eax
mov eax,ecx
cdq
imul ebx
shrd eax,edx,$10
add edi,eax
pop rax
mov eax,dword [eax]
add edi,eax
pop rax
pop rbx
mov dword [esi+4],ebx
mov dword [esi],eax
mov eax,edi
ret

w7D: ; ::: Omode ::: uso:0 dD:0 
;----------------
;----------------
mov ebx,XRES
sar ebx,1
mov dword [w72],ebx
mov ebx,YRES
sar ebx,1
mov dword [w73],ebx
mov ebx,YRES
sub ebx,XRES
mov ecx,ebx
sar ecx,$1F
and ebx,ecx
add ebx,XRES
mov dword [w70],ebx
mov dword [w71],ebx
mov dword [w76],w75
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],w75
mov dword [esi],w74
mov eax,$10
jmp w18

w7E: ; ::: project3d ::: uso:-3 dD:-1 
;----------------
; BL 16 (6-8)0
;----------------
call w7C
or eax,eax
jnz _E2
lea esi,dword[esi+4]
mov eax,dword [w72]
mov dword [esi],eax
mov eax,dword [w73]
ret
_E2: push rax
mov eax,dword [esp]
mov ebx,eax
mov eax,dword [esi]
cdq
imul dword [w71]
idiv ebx
add eax,dword [w73]
pop rbx
mov ecx,eax
mov eax,dword [esi+4]
cdq
imul dword [w70]
idiv ebx
add eax,dword [w72]
lea esi,dword[esi+4]
mov dword [esi],eax
mov eax,ecx
ret

w84: ; ::: a0 ::: uso:-1 dD:-1 
;----------------
;----------------
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w85: ; ::: ab ::: uso:-1 dD:-1 
;----------------
;----------------
sar eax,$4
mov dword [w5],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w86: ; ::: ac ::: uso:-1 dD:-1 
;----------------
;----------------
sar eax,$4
mov dword [w7F],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w87: ; ::: ad ::: uso:-1 dD:-1 
;----------------
;----------------
sar eax,$4
mov dword [w5],eax
mov dword [w2E],w26
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp w3D

w88: ; ::: ae ::: uso:-1 dD:-1 
;----------------
;----------------
sar eax,$4
mov ebx,dword [w7F]
mov dword [w4],ebx
mov dword [w3],eax
mov dword [w2E],w29
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp w3D

w89: ; ::: af ::: uso:-1 dD:-1 
;----------------
;----------------
sar eax,$4
mov ebx,dword [w7F]
mov dword [w4],ebx
mov dword [w3],eax
mov dword [w2E],w2D
lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp w3D

w8A: ; ::: 3d>xy ::: uso:-1 dD:1 
;----------------
;----------------
mov ebx,eax
sar ebx,$12
sal ebx,$3
sal eax,$E
sar eax,$12
sal eax,$3
lea esi,dword[esi-8]
mov dword [esi+4],ebx
mov dword [esi],eax
mov eax,$0
jmp w7E

w8B: ; ::: ad1 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
mov ebx,eax
sal ebx,$4
mov dword [wF],ebx
mov ebx,dword [esi]
sal ebx,$4
mov dword [wE],ebx
mov dword [wD],eax
mov eax,dword [esi]
mov dword [wC],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w8C: ; ::: ad2 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
mov dword [w83],eax
mov eax,dword [esi]
mov dword [w82],eax
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w8D: ; ::: ad3 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
sal eax,$4
mov ebx,dword [esi]
sal ebx,$4
mov dword [esi],ebx
jmp w32

w8E: ; ::: ad4 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov eax,dword [w82]
mov dword [esi],eax
mov eax,dword [w83]
jmp w3F

w8F: ; ::: ad5 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
jmp w24

w90: ; ::: ad6 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov eax,dword [w82]
mov dword [esi],eax
mov eax,dword [w83]
jmp w25

w91: ; ::: ad7 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
mov ebx,w80
mov dword [ebx],eax
add ebx,4
mov ecx,dword [esi]
mov dword [ebx],ecx
mov dword [w7],eax
mov dword [w6],ecx
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w92: ; ::: ad8 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
mov ebx,dword [w81]
sub ebx,dword [esi]
mov ecx,dword [w80]
sub ecx,eax
mov eax,ebx
imul eax,eax
mov edx,ecx
imul edx,edx
add eax,edx
mov edx,eax
sub edx,$1
mov edi,edx
sar edi,$1F
and edx,edi
sub eax,edx
push rax
neg ebx
mov eax,dword [esp]
mov edx,eax
mov eax,ebx
mov ebx,edx
cdq
shld edx,eax,$10
shl eax,$10
idiv ebx
pop rbx
mov edx,eax
mov eax,ecx
mov ecx,edx
cdq
shld edx,eax,$10
shl eax,$10
idiv ebx
mov dword [w9],eax
mov dword [w8],ecx
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w93: ; ::: ad9 ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov eax,dword [w82]
mov dword [esi],eax
mov eax,dword [w83]
jmp w3F

w94: ; ::: ada ::: uso:-1 dD:-1 
;----------------
;----------------
call w8A
sal eax,$4
mov ebx,dword [esi]
sal ebx,$4
mov dword [esi],ebx
jmp w32

w96: ; ::: 3dnsprite ::: uso:-1 dD:-1 
;----------------
; BL 2 (1-6)2
;----------------
_E3: mov ebx,dword [eax]
add eax,4
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _E4
mov ebx,eax
and ebx,$F
sal ebx,$2
add ebx,w95
mov ebx,dword [ebx]
push rbx
pop rcx
call rcx
jmp _E3
_E4: mov dword [w2E],w26
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

w98: ; ::: charsize8i ::: uso:-1 dD:0 
;----------------
;----------------
mov eax,$8
ret

w99: ; ::: char8i ::: uso:-1 dD:-1 
;----------------
; BL 2 (9-F)0
; BL 2 (B-E)0
; BL 1 (C-E)0
;----------------
mov ebx,dword [w4A]
shl ebx,10
add ebx,dword [w49]
lea ebp,dword[SYSFRAME+ebx*4]
sal eax,$3
mov ebx,eax
sar ebx,1
add eax,ebx
add eax,w97
mov ebx,XRES
sub ebx,$8
lea esi,dword[esi-8]
mov dword [esi+4],ebx
mov dword [esi],eax
mov eax,$C
_E5: or eax,eax
jz _E6
sub eax,1
mov ebx,dword [esi]
movsx ecx,byte [ebx]
add ebx,1
lea esi,dword[esi-8]
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],ecx
mov eax,$80
_E7: or eax,eax
jz _E8
test eax,dword [esi]
jz _E9
mov ebx,dword [w5]
mov dword [ebp],ebx
add ebp,4
jmp _EA
_E9: lea ebp,dword[ebp+$1*4]
_EA: sar eax,1
jmp _E7
_E8: mov eax,dword [esi+12]
lea ebp,dword[ebp+eax*4]
lea esi,dword[esi+8]
mov dword [esi+4],eax
mov ebx,dword [esi]
mov ecx,dword [esi-4]
mov dword [esi],ecx
mov eax,ebx
jmp _E5
_E6: lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

w9D: ; ::: ccxmax! ::: uso:0 dD:0 
;----------------
; BL 16 (3-4)0
;----------------
mov ebx,dword [w49]
cmp ebx,dword [w9C]
jle _EB
mov dword [w9C],ebx
ret
_EB: ret

w9E: ; ::: emit ::: uso:-1 dD:-1 
;----------------
; BL 16 (2-6)0
; BL 16 (7-9)0
; BL 16 (A-E)0
; BL 16 (10-10)0
; BL 16 (12-12)0
;----------------
cmp eax,$9
jnz _EC
mov eax,dword [w49]
and eax,(-32)
add eax,$20
mov dword [w49],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret
_EC: cmp eax,$A
jnz _ED
mov eax,dword [w45]
mov dword [w49],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret
_ED: cmp eax,$D
jnz _EE
lea esi,dword[esi+4]
mov eax,dword [esi-4]
call w9D
add dword [w4A],$C
mov ebx,dword [w45]
mov dword [w49],ebx
ret
_EE: mov ebx,dword [w4A]
cmp ebx,dword [w48]
jl _EF
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret
_EF: mov ebx,dword [w49]
cmp ebx,dword [w47]
jl _F0
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret
_F0: and eax,$FF
push w98
lea esi,dword[esi-4]
mov dword [esi],eax
pop rcx
call rcx
add eax,dword [w49]
push w99
xchg dword [esi],eax
pop rcx
call rcx
mov dword [w49],eax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

w9F: ; ::: filcol ::: uso:0 dD:0 
;----------------
;----------------
mov ebx,dword [w48]
sub ebx,dword [w46]
mov ecx,eax
mov eax,ebx
mov ebx,$C
cdq
idiv ebx
mov dword [w9A],eax
mov eax,dword [w47]
sub eax,dword [w45]
mov ebx,$8
cdq
idiv ebx
mov dword [w9B],eax
mov eax,ecx
ret

wA4: ; ::: show ::: uso:0 dD:0 
;----------------
; BL 2 (A-11)2
; BL 1 (D-11)0
;----------------
call SYSMSEC
mov ebx,wA0
mov dword [ebx],eax
add ebx,4
mov dword [ebx],eax
mov dword [wA1],$0
mov dword [wA2],(-1)
mov dword [wA3],(-1)
lea esi,dword[esi+4]
mov eax,dword [esi-4]
_F1: mov ebx,dword [wA1]
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jnz _F2
mov eax,$A
call SYSUPDATE
mov eax,dword [esp]
push rax
lea esi,dword[esi+4]
mov eax,dword [esi-4]
pop rcx
call rcx
mov ebx,dword [wA3]
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _F3
call SYSREDRAW
jmp _F4
_F3: mov dword [wA3],$1
mov dword [wA2],(-1)
_F4: lea esi,dword[esi+4]
mov eax,dword [esi-4]
jmp _F1
_F2: lea esp,dword[esp+4]
mov dword [wA3],$0
mov dword [wA1],$0
mov [SYSKEY],$0
lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

wAB: ; ::: guistart ::: uso:0 dD:0 
;----------------
;----------------
mov ebx,dword [wA9]
mov dword [wAA],ebx
mov ebx,dword [wA5]
mov dword [wA6],ebx
mov dword [wA8],$0
mov dword [wA9],$0
mov dword [wA5],$0
ret

wAC: ; ::: exit ::: uso:0 dD:0 
;----------------
;----------------
mov dword [wA1],(-1)
mov dword [wA2],(-1)
mov dword [wA7],$0
ret

wB4: ; ::: printpalo ::: uso:-1 dD:-1 
;----------------
; BL 16 (2-5)0
; BL 2 (4-5)2
; BL 16 (6-9)0
; BL 2 (8-9)2
; BL 16 (A-D)0
; BL 2 (C-D)2
; BL 16 (E-11)0
; BL 2 (10-11)2
;----------------
cmp eax,$0
jnz _F5
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,str1
call w6F
_F6: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _F7
call w9E
jmp _F6
_F7: lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_F5: cmp eax,$1
jnz _F8
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,str2
call w6F
_F9: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _FA
call w9E
jmp _F9
_FA: lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_F8: cmp eax,$2
jnz _FB
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,str3
call w6F
_FC: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _FD
call w9E
jmp _FC
_FD: lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_FB: cmp eax,$3
jnz _FE
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,str4
call w6F
_FF: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _100
call w9E
jmp _FF
_100: lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret
_FE: lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

wB5: ; ::: intercambia ::: uso:-2 dD:-2 
;----------------
;----------------
mov ebx,dword [esi]
imul ebx,$4
add ebx,wB2
mov ebx,dword [ebx]
mov ecx,eax
imul ecx,$4
add ecx,wB2
mov ecx,dword [ecx]
mov edx,dword [esi]
imul edx,$4
add edx,wB2
mov dword [edx],ecx
mov ecx,eax
imul ecx,$4
add ecx,wB2
mov dword [ecx],ebx
mov ebx,dword [esi]
imul ebx,$4
add ebx,wB3
mov ebx,dword [ebx]
mov ecx,eax
imul ecx,$4
add ecx,wB3
mov ecx,dword [ecx]
mov edx,dword [esi]
imul edx,$4
add edx,wB3
mov dword [edx],ecx
mov ecx,eax
imul ecx,$4
add ecx,wB3
mov dword [ecx],ebx
lea esi,dword[esi+8]
mov eax,dword [esi-4]
ret

wB6: ; ::: mezclar ::: uso:0 dD:0 
;----------------
; BL 2 (2-D)0
;----------------
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
_101: cmp eax,$64
jge _102
mov ebx,dword [w40]
imul ebx,(-1153374675)
add ebx,1
mov dword [w40],ebx
mov ecx,eax
mov eax,ebx
mov ebx,$28
cdq
idiv ebx
mov eax,edx
cdq
add eax,edx
xor eax,edx
mov ebx,dword [w40]
imul ebx,(-1153374675)
add ebx,1
mov dword [w40],ebx
mov edx,eax
mov eax,ebx
mov ebx,edx
mov edi,$28
cdq
idiv edi
mov eax,edx
cdq
add eax,edx
xor eax,edx
lea esi,dword[esi-8]
mov dword [esi+4],ecx
mov dword [esi],ebx
call wB5
add eax,1
jmp _101
_102: lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

wC5: ; ::: drawcarta ::: uso:-2 dD:-2 
;----------------
; BL 2 (E-1C)2
;----------------
mov ebx,dword [w76]
add ebx,$40
mov ecx,dword [w76]
mov dword [w76],ebx
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],ecx
mov eax,$10
call w18
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,wAF
call w96
sub eax,1
sal eax,$2
add eax,wC4
mov eax,dword [eax]
mov ebx,dword [eax]
add eax,4
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],ebx
mov eax,$0
call w79
_103: mov ebx,dword [eax]
add eax,4
cmp ebx,(-1)
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _104
mov ebx,dword [w76]
add ebx,$40
mov ecx,dword [w76]
mov dword [w76],ebx
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],ecx
mov eax,$10
call w18
mov ebx,dword [esi]
mov ebx,dword [ebx]
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov dword [esi],ebx
mov eax,$0
call w78
lea esi,dword[esi-4]
mov dword [esi],eax
mov ebx,dword [esi+4]
mov dword [esi+4],ebx
mov eax,ebx
call w96
mov ebx,dword [w76]
sub ebx,$40
mov dword [w76],ebx
add eax,4
jmp _103
_104: mov eax,dword [w76]
sub eax,$40
mov dword [w76],eax
lea esi,dword[esi+12]
mov eax,dword [esi-4]
ret

wC7: ; ::: drawcartam ::: uso:-1 dD:-1 
;----------------
;----------------
imul eax,$4
mov ebx,eax
add ebx,wB3
mov ebx,dword [ebx]
sal ebx,$2
add ebx,wC6
mov ebx,dword [ebx]
add eax,wB2
mov eax,dword [eax]
lea esi,dword[esi-4]
mov dword [esi],ebx
jmp wC5

wC8: ; ::: printmazog ::: uso:0 dD:1 
;----------------
; BL 2 (6-E)0
; BL 2 (7-B)0
;----------------
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],(-327680)
mov dword [esi],(-196608)
mov eax,$0
call w78
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov dword [esi],$0
mov eax,$4
_105: or eax,eax
jz _106
sub eax,1
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$A
_107: or eax,eax
jz _108
sub eax,1
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],$10000
mov dword [esi],$0
mov eax,$0
call w78
lea esi,dword[esi-4]
xchg dword [esi+4],eax
mov ebx,dword [esi+8]
mov dword [esi+8],eax
mov dword [esi],ebx
mov eax,ebx
call wC7
add eax,1
xchg dword [esi+4],eax
xchg dword [esi],eax
jmp _107
_108: lea esi,dword[esi-8]
mov dword [esi+4],(-655360)
mov dword [esi],$20000
mov eax,$0
call w78
jmp _105
_106: lea esi,dword[esi+4]
mov eax,dword [esi-4]
ret

wC9: ; ::: freelook ::: uso:0 dD:0 
;----------------
;----------------
mov ecx,dword[SYSXYM]
mov ebx,ecx
and ebx,$ffff
shr ecx,16
mov edx,YRES
sar edx,1
sub ecx,edx
sal ecx,$7
mov edx,XRES
sar edx,1
sub ebx,edx
neg ebx
sal ebx,$7
neg ecx
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov dword [esi],ebx
mov eax,ecx
call w7A
jmp w7B

wCA: ; ::: _aa0 ::: uso:0 dD:0 
;----------------
;----------------
jmp wB6

wCB: ; ::: datos ::: uso:0 dD:1 
;----------------
; BL 2 (B-C)2
; BL 2 (E-F)2
; BL 2 (11-12)2
; BL 2 (17-24)1
; BL 2 (1E-1F)2
;----------------
call wA4
call SYSCLS
call w4C
call w4B
mov ebx,dword [w45]
mov dword [w9C],ebx
mov dword [w49],ebx
mov ebx,dword [w46]
mov dword [w4A],ebx
call w9F
call wAB
mov dword [w5],$FF00
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,str5
call w6F
_109: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _10A
call w9E
jmp _109
_10A: lea esi,dword[esi+4]
mov eax,wB7
call w6F
_10B: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _10C
call w9E
jmp _10B
_10C: lea esi,dword[esi+4]
mov eax,str6
call w6F
_10D: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _10E
call w9E
jmp _10D
_10E: lea esi,dword[esi+8]
mov eax,dword [esi-4]
call w9D
add dword [w4A],$C
mov ebx,dword [w45]
mov dword [w49],ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,$0
_10F: cmp eax,$28
jge _110
mov ebx,eax
imul ebx,$4
mov ecx,ebx
add ecx,wB2
mov ecx,dword [ecx]
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],ebx
mov dword [esi],ecx
mov eax,str7
call w6F
_111: movsx ebx,byte [eax]
add eax,1
or ebx,ebx
lea esi,dword[esi-4]
mov dword [esi],eax
mov eax,ebx
jz _112
call w9E
jmp _111
_112: mov eax,dword [esi+4]
add eax,wB3
mov eax,dword [eax]
lea esi,dword[esi+8]
call wB4
call w9D
add dword [w4A],$C
mov ebx,dword [w45]
mov dword [w49],ebx
add eax,1
jmp _10F
_110: lea esi,dword[esi+4]
mov eax,dword [esi-4]
call w7D
call wC9
lea esi,dword[esi-12]
mov dword [esi+8],eax
mov dword [esi+4],$0
mov dword [esi],$0
mov eax,$A0000
call w77
call wC8
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov dword [esi],wCA
mov eax,$3B
call w4E
lea esi,dword[esi-8]
mov dword [esi+4],eax
mov dword [esi],wAC
mov eax,$1
jmp w4D

inicio: ; :::  ::: uso:0 dD:1 
;----------------
;----------------
jmp wCB

 