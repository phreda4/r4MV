	.file	"r4win.c"
	.section .rdata,"dr"
LC0:
	.ascii "debug.txt\0"
.globl _NDEBUG
	.data
	.align 4
_NDEBUG:
	.long	LC0
	.section .rdata,"dr"
LC1:
	.ascii "R4win\0"
.globl _znam
	.data
	.align 4
_znam:
	.long	LC1
.globl _numero
	.bss
	.align 4
_numero:
	.space 4
.globl _lastcall
	.align 4
_lastcall:
	.space 4
.globl _pila
	.align 32
_pila:
	.space 1024
.globl _cntpila
	.align 4
_cntpila:
	.space 4
.globl _includes
	.align 32
_includes:
	.space 300
.globl _cntincludes
	.align 4
_cntincludes:
	.space 4
.globl _nombreex
	.align 32
_nombreex:
	.space 32768
.globl _cntnombreex
	.align 4
_cntnombreex:
	.space 4
.globl _indiceex
	.align 32
_indiceex:
	.space 24576
.globl _cntindiceex
	.align 4
_cntindiceex:
	.space 4
.globl _nombre
	.align 32
_nombre:
	.space 16384
.globl _cntnombre
	.align 4
_cntnombre:
	.space 4
.globl _indice
	.align 32
_indice:
	.space 24576
.globl _cntindice
	.align 4
_cntindice:
	.space 4
.globl _ultimapalabra
	.data
_ultimapalabra:
	.byte	77
.globl _punt
	.bss
	.align 4
_punt:
	.space 4
.globl _sitime
	.align 4
_sitime:
	.space 4
.globl _sit
	.align 4
_sit:
	.space 4
.globl _message
	.align 4
_message:
	.space 28
.globl _ep
	.align 4
_ep:
	.space 4
.globl _dp
	.align 4
_dp:
	.space 4
.globl _nsc
	.align 4
_nsc:
	.space 4
.globl _cntindex
	.align 4
_cntindex:
	.space 4
.globl _indexdir
	.align 32
_indexdir:
	.space 4096
.globl _mindice
	.align 32
_mindice:
	.space 8192
.globl _linea
	.align 32
_linea:
	.space 1024
.globl _error
	.align 32
_error:
	.space 128
.globl _pathdata
	.align 32
_pathdata:
	.space 128
.globl _file
	.align 4
_file:
	.space 4
.globl _bootaddr
	.align 4
_bootaddr:
	.space 4
.globl _gyc
	.align 4
_gyc:
	.space 4
.globl _gxc
	.align 4
_gxc:
	.space 4
.globl _gy2
	.align 4
_gy2:
	.space 4
.globl _gx2
	.align 4
_gx2:
	.space 4
.globl _gy1
	.align 4
_gy1:
	.space 4
.globl _gx1
	.align 4
_gx1:
	.space 4
.globl _RSP
	.align 32
_RSP:
	.space 8192
.globl _PSP
	.align 32
_PSP:
	.space 8192
.globl _data
	.align 32
_data:
	.space 8388608
.globl _prog
	.align 32
_prog:
	.space 131072
.globl _cntprog
	.align 4
_cntprog:
	.space 4
.globl _dato
	.align 32
_dato:
	.space 131072
.globl _cntdato
	.align 4
_cntdato:
	.space 4
	.section .rdata,"dr"
LC2:
	.ascii ";\0"
LC3:
	.ascii "(\0"
LC4:
	.ascii ")\0"
LC5:
	.ascii ")(\0"
LC6:
	.ascii "[\0"
LC7:
	.ascii "]\0"
LC8:
	.ascii "0?\0"
LC9:
	.ascii "+?\0"
LC10:
	.ascii "-?\0"
LC11:
	.ascii "1?\0"
LC12:
	.ascii "=?\0"
LC13:
	.ascii "<?\0"
LC14:
	.ascii ">?\0"
LC15:
	.ascii "<=?\0"
LC16:
	.ascii ">=?\0"
LC17:
	.ascii "<>?\0"
LC18:
	.ascii "EXEC\0"
LC19:
	.ascii "DUP\0"
LC20:
	.ascii "DROP\0"
LC21:
	.ascii "OVER\0"
LC22:
	.ascii "PICK2\0"
LC23:
	.ascii "PICK3\0"
LC24:
	.ascii "PICK4\0"
LC25:
	.ascii "SWAP\0"
LC26:
	.ascii "NIP\0"
LC27:
	.ascii "ROT\0"
LC28:
	.ascii "2DUP\0"
LC29:
	.ascii "2DROP\0"
LC30:
	.ascii "3DROP\0"
LC31:
	.ascii "4DROP\0"
LC32:
	.ascii "2OVER\0"
LC33:
	.ascii "2SWAP\0"
LC34:
	.ascii ">R\0"
LC35:
	.ascii "R>\0"
LC36:
	.ascii "R\0"
LC37:
	.ascii "R+\0"
LC38:
	.ascii "R@+\0"
LC39:
	.ascii "R!+\0"
LC40:
	.ascii "RDROP\0"
LC41:
	.ascii "AND\0"
LC42:
	.ascii "OR\0"
LC43:
	.ascii "XOR\0"
LC44:
	.ascii "NOT\0"
LC45:
	.ascii "+\0"
LC46:
	.ascii "-\0"
LC47:
	.ascii "*\0"
LC48:
	.ascii "/\0"
LC49:
	.ascii "*/\0"
LC50:
	.ascii "/MOD\0"
LC51:
	.ascii "MOD\0"
LC52:
	.ascii "ABS\0"
LC53:
	.ascii "NEG\0"
LC54:
	.ascii "1+\0"
LC55:
	.ascii "4+\0"
LC56:
	.ascii "1-\0"
LC57:
	.ascii "2/\0"
LC58:
	.ascii "2*\0"
LC59:
	.ascii "<<\0"
LC60:
	.ascii ">>\0"
LC61:
	.ascii "@\0"
LC62:
	.ascii "C@\0"
LC63:
	.ascii "W@\0"
LC64:
	.ascii "!\0"
LC65:
	.ascii "C!\0"
LC66:
	.ascii "W!\0"
LC67:
	.ascii "+!\0"
LC68:
	.ascii "C+!\0"
LC69:
	.ascii "W+!\0"
LC70:
	.ascii "@+\0"
LC71:
	.ascii "!+\0"
LC72:
	.ascii "C@+\0"
LC73:
	.ascii "C!+\0"
LC74:
	.ascii "W@+\0"
LC75:
	.ascii "W!+\0"
LC76:
	.ascii "MSEC\0"
LC77:
	.ascii "TIME\0"
LC78:
	.ascii "DATE\0"
LC79:
	.ascii "END\0"
LC80:
	.ascii "RUN\0"
LC81:
	.ascii "BPP\0"
LC82:
	.ascii "SW\0"
LC83:
	.ascii "SH\0"
LC84:
	.ascii "CLS\0"
LC85:
	.ascii "REDRAW\0"
LC86:
	.ascii "FRAMEV\0"
LC87:
	.ascii "UPDATE\0"
LC88:
	.ascii "XYMOUSE\0"
LC89:
	.ascii "BMOUSE\0"
LC90:
	.ascii "KEY\0"
LC91:
	.ascii "START!\0"
LC92:
	.ascii "MOTION!\0"
LC93:
	.ascii "END!\0"
LC94:
	.ascii "KEYMAP\0"
LC95:
	.ascii "UKEYMAP\0"
LC96:
	.ascii "PAPER\0"
LC97:
	.ascii "INK\0"
LC98:
	.ascii "INK@\0"
LC99:
	.ascii "ALPHA\0"
LC100:
	.ascii "OP\0"
LC101:
	.ascii "CP\0"
LC102:
	.ascii "LINE\0"
LC103:
	.ascii "CURVE\0"
LC104:
	.ascii "PLINE\0"
LC105:
	.ascii "PCURVE\0"
LC106:
	.ascii "POLI\0"
LC107:
	.ascii "MEM\0"
LC108:
	.ascii "DIR\0"
LC109:
	.ascii "FILE\0"
LC110:
	.ascii "LOAD\0"
LC111:
	.ascii "SAVE\0"
LC112:
	.ascii "SLOAD\0"
LC113:
	.ascii "SPLAY\0"
LC114:
	.ascii "\0"
.globl _macros
	.data
	.align 32
_macros:
	.long	LC2
	.long	LC3
	.long	LC4
	.long	LC5
	.long	LC6
	.long	LC7
	.long	LC8
	.long	LC9
	.long	LC10
	.long	LC11
	.long	LC12
	.long	LC13
	.long	LC14
	.long	LC15
	.long	LC16
	.long	LC17
	.long	LC18
	.long	LC19
	.long	LC20
	.long	LC21
	.long	LC22
	.long	LC23
	.long	LC24
	.long	LC25
	.long	LC26
	.long	LC27
	.long	LC28
	.long	LC29
	.long	LC30
	.long	LC31
	.long	LC32
	.long	LC33
	.long	LC34
	.long	LC35
	.long	LC36
	.long	LC37
	.long	LC38
	.long	LC39
	.long	LC40
	.long	LC41
	.long	LC42
	.long	LC43
	.long	LC44
	.long	LC45
	.long	LC46
	.long	LC47
	.long	LC48
	.long	LC49
	.long	LC50
	.long	LC51
	.long	LC52
	.long	LC53
	.long	LC54
	.long	LC55
	.long	LC56
	.long	LC57
	.long	LC58
	.long	LC59
	.long	LC60
	.long	LC61
	.long	LC62
	.long	LC63
	.long	LC64
	.long	LC65
	.long	LC66
	.long	LC67
	.long	LC68
	.long	LC69
	.long	LC70
	.long	LC71
	.long	LC72
	.long	LC73
	.long	LC74
	.long	LC75
	.long	LC76
	.long	LC77
	.long	LC78
	.long	LC79
	.long	LC80
	.long	LC81
	.long	LC82
	.long	LC83
	.long	LC84
	.long	LC85
	.long	LC86
	.long	LC87
	.long	LC88
	.long	LC89
	.long	LC90
	.long	LC91
	.long	LC92
	.long	LC93
	.long	LC94
	.long	LC95
	.long	LC96
	.long	LC97
	.long	LC98
	.long	LC99
	.long	LC100
	.long	LC101
	.long	LC102
	.long	LC103
	.long	LC104
	.long	LC105
	.long	LC106
	.long	LC107
	.long	LC108
	.long	LC109
	.long	LC110
	.long	LC111
	.long	LC112
	.long	LC113
	.long	LC114
	.section .rdata,"dr"
LC115:
	.ascii "LIT\0"
LC116:
	.ascii "ADR\0"
LC117:
	.ascii "CALL\0"
LC118:
	.ascii "JMP\0"
LC119:
	.ascii "JMPR\0"
.globl _macrose
	.data
	.align 4
_macrose:
	.long	LC2
	.long	LC115
	.long	LC116
	.long	LC117
	.long	LC118
	.long	LC119
.globl _active
	.bss
	.align 4
_active:
	.space 4
.globl _SYSKEYM
	.align 32
_SYSKEYM:
	.space 1024
.globl _SYSME
	.align 4
_SYSME:
	.space 4
.globl _SYSMM
	.align 4
_SYSMM:
	.space 4
.globl _SYSMS
	.align 4
_SYSMS:
	.space 4
.globl _SYSKEY
	.align 4
_SYSKEY:
	.space 4
.globl _SYSBM
	.align 4
_SYSBM:
	.space 4
.globl _SYSXYM
	.align 4
_SYSXYM:
	.space 4
.globl _SYSEVENT
	.align 4
_SYSEVENT:
	.space 4
	.text
	.align 2
	.p2align 4,,15
.globl __Z7loaddirv
	.def	__Z7loaddirv;	.scl	2;	.type	32;	.endef
__Z7loaddirv:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	%eax, _cntindex
	movl	$_mindice, %ebx
	movl	$_pathdata, (%esp)
	call	_opendir
	movl	%eax, _dp
	testl	%eax, %eax
	je	L1
	movl	%eax, (%esp)
	call	_readdir
	movl	%eax, _ep
	testl	%eax, %eax
	je	L16
	.p2align 4,,15
L8:
	movl	%ebx, (%esp)
	addl	$8, %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	movl	_cntindex, %edx
	movl	%ebx, _indexdir(,%edx,4)
	incl	%edx
	movl	%edx, _cntindex
	jmp	L14
	.p2align 4,,7
L17:
	incl	%ebx
L14:
	cmpb	$0, (%ebx)
	jne	L17
	movl	_dp, %eax
	incl	%ebx
	movl	%eax, (%esp)
	call	_readdir
	movl	%eax, _ep
	testl	%eax, %eax
	jne	L8
L16:
	movl	_dp, %ecx
	movl	%ecx, (%esp)
	call	_closedir
L1:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC120:
	.ascii "%s%s\0"
LC122:
	.ascii "wb\0"
LC121:
	.ascii "rb\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z10interpretePh
	.def	__Z10interpretePh;	.scl	2;	.type	32;	.endef
__Z10interpretePh:
	pushl	%ebp
	movl	$-1, %eax
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %edx
	testl	%edx, %edx
	je	L18
	movl	%edx, -16(%ebp)
	xorl	%eax, %eax
	movl	$_ultimapalabra, %edx
	movl	$_RSP, -20(%ebp)
	movl	$_PSP, %esi
	xorl	%edi, %edi
	movl	%edx, _RSP
	movl	%eax, _PSP
L207:
	movl	-16(%ebp), %ecx
	movzbl	(%ecx), %eax
	incl	%ecx
	movl	%ecx, -16(%ebp)
	cmpl	$111, %eax
	jbe	L209
L182:
	addl	$4, %esi
	movl	%edi, (%esi)
	leal	-112(%eax), %edi
	movl	-16(%ebp), %ecx
	movzbl	(%ecx), %eax
	incl	%ecx
	movl	%ecx, -16(%ebp)
	cmpl	$111, %eax
	ja	L182
L209:
	jmp	*L183(,%eax,4)
	.section .rdata,"dr"
	.align 4
L183:
	.long	L23
	.long	L24
	.long	L25
	.long	L26
	.long	L27
	.long	L28
	.long	L29
	.long	L31
	.long	L33
	.long	L35
	.long	L37
	.long	L41
	.long	L43
	.long	L45
	.long	L47
	.long	L39
	.long	L49
	.long	L51
	.long	L52
	.long	L53
	.long	L54
	.long	L55
	.long	L56
	.long	L57
	.long	L58
	.long	L59
	.long	L60
	.long	L61
	.long	L62
	.long	L63
	.long	L64
	.long	L65
	.long	L66
	.long	L67
	.long	L68
	.long	L69
	.long	L70
	.long	L71
	.long	L72
	.long	L73
	.long	L74
	.long	L75
	.long	L76
	.long	L77
	.long	L78
	.long	L79
	.long	L80
	.long	L82
	.long	L84
	.long	L86
	.long	L87
	.long	L89
	.long	L90
	.long	L91
	.long	L92
	.long	L93
	.long	L94
	.long	L95
	.long	L96
	.long	L97
	.long	L98
	.long	L99
	.long	L100
	.long	L101
	.long	L102
	.long	L103
	.long	L104
	.long	L105
	.long	L106
	.long	L107
	.long	L108
	.long	L109
	.long	L110
	.long	L111
	.long	L112
	.long	L114
	.long	L113
	.long	L115
	.long	L116
	.long	L118
	.long	L119
	.long	L120
	.long	L121
	.long	L126
	.long	L127
	.long	L128
	.long	L134
	.long	L135
	.long	L136
	.long	L137
	.long	L138
	.long	L139
	.long	L140
	.long	L141
	.long	L142
	.long	L143
	.long	L144
	.long	L145
	.long	L148
	.long	L149
	.long	L150
	.long	L151
	.long	L152
	.long	L153
	.long	L154
	.long	L155
	.long	L156
	.long	L166
	.long	L169
	.long	L176
	.long	L180
	.long	L181
	.text
L181:
	movl	%edi, 4(%esp)
	movl	$-1, (%esp)
	call	_FSOUND_PlaySound@8
	movl	(%esi), %edi
	subl	$8, %esp
	subl	$4, %esi
	jmp	L207
L180:
	movl	%edi, 4(%esp)
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movl	%ecx, 16(%esp)
	movl	$304, %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$-1, (%esp)
	call	_FSOUND_Sample_Load@20
	subl	$20, %esp
	movl	%eax, %edi
	jmp	L207
L176:
	testl	%edi, %edi
	je	L207
	movl	(%esi), %ecx
	testl	%ecx, %ecx
	je	L207
	movl	%edi, 12(%esp)
	movl	$_pathdata, %eax
	movl	$LC120, %edi
	movl	%edi, 4(%esp)
	movl	$LC122, %ebx
	movl	%eax, 8(%esp)
	movl	$_linea, (%esp)
	call	_sprintf
	movl	%ebx, 4(%esp)
	movl	(%esi), %edi
	subl	$4, %esi
	movl	$_linea, (%esp)
	call	_fopen
	movl	%eax, _file
	testl	%eax, %eax
	je	L207
	movl	%edi, 8(%esp)
	movl	(%esi), %ecx
	movl	$1, %ebx
	movl	%eax, 12(%esp)
	movl	%ebx, 4(%esp)
	movl	%ecx, (%esp)
	call	_fwrite
	movl	_file, %edx
	movl	%edx, (%esp)
	call	_fclose
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
	.p2align 4,,7
L169:
	testl	%edi, %edi
	je	L207
	movl	(%esi), %eax
	testl	%eax, %eax
	je	L207
	movl	%edi, 12(%esp)
	movl	$_pathdata, %ecx
	movl	$LC120, %edi
	movl	%ecx, 8(%esp)
	movl	%edi, 4(%esp)
	movl	$_linea, (%esp)
	call	_sprintf
	movl	$_linea, (%esp)
	movl	$LC121, %edx
	movl	(%esi), %edi
	movl	%edx, 4(%esp)
	call	_fopen
	movl	%eax, _file
	subl	$4, %esi
	testl	%eax, %eax
	je	L207
	jmp	L202
	.p2align 4,,7
L190:
	movl	_file, %eax
L202:
	movl	%eax, 12(%esp)
	movl	$1, %ebx
	movl	$1024, %eax
	movl	%edi, (%esp)
	movl	%eax, 8(%esp)
	movl	%ebx, 4(%esp)
	call	_fread
	addl	%eax, %edi
	cmpl	$1024, %eax
	je	L190
	movl	_file, %edx
	movl	%edx, (%esp)
	call	_fclose
	jmp	L207
	.p2align 4,,7
L166:
	cmpl	_cntindex, %edi
	movl	%edi, %ecx
	setge	%bl
	shrl	$31, %ecx
	orb	%cl, %bl
	je	L167
	xorl	%edi, %edi
	jmp	L207
L156:
	testl	%edi, %edi
	je	L207
	movl	%edi, 4(%esp)
	xorl	%ebx, %ebx
	movl	$_pathdata, (%esp)
	call	_strcpy
	movl	%ebx, _cntindex
	movl	(%esi), %edi
	subl	$4, %esi
	movl	$_pathdata, (%esp)
	call	_opendir
	movl	%eax, _dp
	testl	%eax, %eax
	movl	$_mindice, %ebx
	je	L207
L201:
	movl	%eax, (%esp)
	call	_readdir
	movl	%eax, _ep
	testl	%eax, %eax
	je	L210
	movl	%ebx, (%esp)
	addl	$8, %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	movl	_cntindex, %eax
	movl	%ebx, _indexdir(,%eax,4)
	incl	%eax
	movl	%eax, _cntindex
	jmp	L206
L211:
	incl	%ebx
L206:
	cmpb	$0, (%ebx)
	jne	L211
	movl	_dp, %eax
	incl	%ebx
	jmp	L201
L154:
	call	__Z11gr_drawPoliv
	jmp	L207
L153:
	movl	%edi, _gy2
	movl	(%esi), %edx
	movl	_gy2, %ecx
	movl	_gyc, %eax
	movl	_gxc, %ebx
	movl	%edx, _gx2
	movl	-4(%esi), %edi
	subl	$8, %esi
	movl	%ecx, 20(%esp)
	movl	_gy1, %ecx
	movl	%edx, 16(%esp)
	movl	_gx1, %edx
	movl	%eax, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	call	__Z10gr_psplineiiiiii
	movl	_gx2, %eax
	movl	_gy2, %ebx
	movl	%eax, _gx1
	movl	%ebx, _gy1
	jmp	L207
L155:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	$_data, %edi
	jmp	L207
L152:
	movl	%edi, _gy2
	movl	(%esi), %edx
	movl	_gy2, %ecx
	movl	_gy1, %eax
	movl	_gx1, %ebx
	movl	%edx, _gx2
	movl	-4(%esi), %edi
	subl	$8, %esi
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	__Z12gr_psegmentoiiii
	movl	_gx2, %ecx
	movl	_gy2, %edx
	movl	%ecx, _gx1
	movl	%edx, _gy1
	jmp	L207
L151:
	movl	%edi, _gy2
	movl	(%esi), %ebx
	movl	_gy2, %eax
	movl	_gyc, %ecx
	movl	_gxc, %edx
	movl	%ebx, _gx2
	movl	-4(%esi), %edi
	subl	$8, %esi
	movl	%eax, 20(%esp)
	movl	_gy1, %eax
	movl	%ebx, 16(%esp)
	movl	_gx1, %ebx
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	__Z9gr_splineiiiiii
	movl	_gx2, %ecx
	movl	_gy2, %edx
	movl	%ecx, _gx1
	movl	%edx, _gy1
	jmp	L207
L150:
	movl	%edi, _gy2
	movl	(%esi), %ebx
	movl	_gy2, %eax
	movl	_gy1, %ecx
	movl	_gx1, %edx
	movl	%ebx, _gx2
	movl	-4(%esi), %edi
	subl	$8, %esi
	movl	%eax, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	call	__Z7gr_lineiiii
	movl	_gx2, %eax
	movl	_gy2, %ebx
	movl	%eax, _gx1
	movl	%ebx, _gy1
	jmp	L207
L149:
	movl	%edi, _gyc
	movl	(%esi), %ecx
	movl	-4(%esi), %edi
	subl	$8, %esi
	movl	%ecx, _gxc
	jmp	L207
L148:
	movl	%edi, _gy1
	movl	(%esi), %edx
	movl	-4(%esi), %edi
	subl	$8, %esi
	movl	%edx, _gx1
	jmp	L207
L145:
	cmpl	$254, %edi
	jle	L146
	call	__Z8gr_solidv
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L144:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_gr_color1, %edi
	jmp	L207
L143:
	movl	%edi, _gr_color1
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L142:
	movl	%edi, _gr_color2
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L141:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	$_SYSKEYM+512, %edi
	jmp	L207
L140:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	$_SYSKEYM, %edi
	jmp	L207
L139:
	movl	%edi, _SYSME
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L138:
	movl	%edi, _SYSMM
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L137:
	movl	%edi, _SYSMS
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L136:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_SYSKEY, %edi
	jmp	L207
L135:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_SYSBM, %edi
	jmp	L207
L134:
	movl	%edi, 4(%esi)
	movl	_SYSXYM, %ebx
	addl	$8, %esi
	movzwl	%bx,%edi
	movl	%edi, (%esi)
	movl	%ebx, %edi
	shrl	$16, %edi
	jmp	L207
L128:
	movl	$_message, (%esp)
	movl	_hWnd, %eax
	xorl	%edx, %edx
	movl	%edx, 12(%esp)
	movl	$1, %ecx
	xorl	%ebx, %ebx
	movl	%ecx, 16(%esp)
	movl	%ebx, 8(%esp)
	movl	%eax, 4(%esp)
	call	_PeekMessageA@20
	subl	$20, %esp
	testl	%eax, %eax
	je	L207
	movl	$_message, (%esp)
	call	_TranslateMessage@4
	subl	$4, %esp
	movl	$_message, (%esp)
	call	_DispatchMessageA@4
	movl	_SYSEVENT, %eax
	subl	$4, %esp
	testl	%eax, %eax
	je	L130
	addl	$4, -20(%ebp)
	movl	-16(%ebp), %edx
	movl	%eax, -16(%ebp)
	movl	-20(%ebp), %ebx
	xorl	%eax, %eax
	movl	%edx, (%ebx)
	movl	%eax, _SYSEVENT
	jmp	L130
	.p2align 4,,7
L212:
	movl	$5, (%esp)
	call	_Sleep@4
	movl	_hWnd, %eax
	subl	$4, %esp
	movl	$1, %ecx
	movl	%ecx, 16(%esp)
	xorl	%edx, %edx
	xorl	%ebx, %ebx
	movl	%edx, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$_message, (%esp)
	call	_PeekMessageA@20
	subl	$20, %esp
	movl	$_message, (%esp)
	call	_TranslateMessage@4
	subl	$4, %esp
	movl	$_message, (%esp)
	call	_DispatchMessageA@4
	subl	$4, %esp
L130:
	movl	_active, %ecx
	testl	%ecx, %ecx
	je	L212
	call	__Z10gr_restorev
	jmp	L207
	.p2align 4,,7
L127:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	$_gr_buffer, %edi
	jmp	L207
L121:
	movl	_gr_color2, %ebx
	movl	$_gr_buffer, %ecx
	movl	$786431, %eax
	movl	%ecx, _punt
	.p2align 4,,15
L125:
	movl	%ebx, (%ecx)
	leal	4(%ecx), %edx
	decl	%eax
	movl	%edx, %ecx
	jns	L125
	movl	%edx, _punt
	jmp	L207
L120:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	$768, %edi
	jmp	L207
L119:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	$1024, %edi
	jmp	L207
L118:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	$32, %edi
	jmp	L207
L126:
	call	__Z6redrawv
	jmp	L207
L116:
	testl	%edi, %edi
	jne	L213
L117:
	movl	$1, %eax
L18:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L115:
	xorl	%eax, %eax
	jmp	L18
L113:
	movl	$_sit, (%esp)
	call	_time
	movl	$_sit, (%esp)
	call	_localtime
	movl	%edi, 4(%esi)
	movl	20(%eax), %ebx
	movl	%eax, _sitime
	movl	%ebx, 8(%esi)
	movl	16(%eax), %edi
	addl	$12, %esi
	movl	%edi, (%esi)
	movl	24(%eax), %edi
	jmp	L207
L114:
	movl	$_sit, (%esp)
	call	_time
	movl	$_sit, (%esp)
	call	_localtime
	movl	%edi, 4(%esi)
	movl	8(%eax), %ecx
	movl	%eax, _sitime
	movl	%ecx, 8(%esi)
	movl	4(%eax), %edx
	addl	$12, %esi
	movl	%edx, (%esi)
	movl	(%eax), %edi
	jmp	L207
L112:
	addl	$4, %esi
	movl	%edi, (%esi)
	call	_GetTickCount@0
	movl	%eax, %edi
	jmp	L207
L111:
	movl	(%esi), %eax
	subl	$4, %esi
	movw	%ax, (%edi)
	addl	$2, %edi
	jmp	L207
L110:
	leal	2(%edi), %ecx
	movswl	(%edi),%edi
	addl	$4, %esi
	movl	%ecx, (%esi)
	jmp	L207
L109:
	movl	(%esi), %edx
	subl	$4, %esi
	movb	%dl, (%edi)
	incl	%edi
	jmp	L207
L108:
	leal	1(%edi), %ebx
	addl	$4, %esi
	movl	%ebx, (%esi)
	movsbl	(%edi),%edi
	jmp	L207
L107:
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, (%edi)
	addl	$4, %edi
	jmp	L207
L106:
	leal	4(%edi), %ecx
	addl	$4, %esi
	movl	%ecx, (%esi)
	movl	(%edi), %edi
	jmp	L207
L105:
	movzwl	(%edi), %ebx
	movl	(%esi), %edx
	addl	%edx, %ebx
	movw	%bx, (%edi)
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L104:
	movzbl	(%edi), %eax
	addb	(%esi), %al
	movb	%al, (%edi)
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L103:
	movl	(%esi), %ecx
	addl	%ecx, (%edi)
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L102:
	movl	(%esi), %edx
	movw	%dx, (%edi)
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L101:
	movl	(%esi), %ebx
	movb	%bl, (%edi)
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L100:
	movl	(%esi), %eax
	movl	%eax, (%edi)
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L99:
	movswl	(%edi),%edi
	jmp	L207
L98:
	movsbl	(%edi),%edi
	jmp	L207
L97:
	movl	(%edi), %edi
	jmp	L207
L96:
	movl	(%esi), %edx
	movl	%edi, %ecx
	subl	$4, %esi
	sarl	%cl, %edx
	movl	%edx, %edi
	jmp	L207
L95:
	movl	(%esi), %ebx
	movl	%edi, %ecx
	subl	$4, %esi
	sall	%cl, %ebx
	movl	%ebx, %edi
	jmp	L207
L94:
	addl	%edi, %edi
	jmp	L207
L93:
	sarl	%edi
	jmp	L207
L92:
	decl	%edi
	jmp	L207
L91:
	addl	$4, %edi
	jmp	L207
L90:
	incl	%edi
	jmp	L207
L89:
	negl	%edi
	jmp	L207
L87:
	testl	%edi, %edi
	jns	L207
	negl	%edi
	jmp	L207
	.p2align 4,,7
L86:
	movl	(%esi), %eax
	subl	$4, %esi
	cltd
	idivl	%edi
	movl	%edx, %edi
	jmp	L207
L84:
	testl	%edi, %edi
	jne	L85
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L82:
	testl	%edi, %edi
	jne	L83
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L80:
	testl	%edi, %edi
	jne	L81
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L72:
	subl	$4, -20(%ebp)
	jmp	L207
L76:
	notl	%edi
	jmp	L207
L75:
	movl	(%esi), %ebx
	subl	$4, %esi
	xorl	%ebx, %edi
	jmp	L207
L74:
	movl	(%esi), %eax
	subl	$4, %esi
	orl	%eax, %edi
	jmp	L207
L73:
	movl	(%esi), %ecx
	subl	$4, %esi
	andl	%ecx, %edi
	jmp	L207
L78:
	movl	(%esi), %ecx
	subl	$4, %esi
	subl	%edi, %ecx
	movl	%ecx, %edi
	jmp	L207
L77:
	movl	(%esi), %edx
	subl	$4, %esi
	addl	%edx, %edi
	jmp	L207
L79:
	movl	(%esi), %eax
	subl	$4, %esi
	imull	%eax, %edi
	jmp	L207
L68:
	movl	-20(%ebp), %ebx
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	(%ebx), %edi
	jmp	L207
L67:
	movl	-20(%ebp), %eax
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	(%eax), %edi
	subl	$4, %eax
	movl	%eax, -20(%ebp)
	jmp	L207
L66:
	addl	$4, -20(%ebp)
	movl	-20(%ebp), %ecx
	movl	%edi, (%ecx)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L65:
	movl	(%esi), %ebx
	movl	%edi, %eax
	movl	-8(%esi), %edx
	movl	-4(%esi), %edi
	movl	%ebx, -8(%esi)
	movl	%edx, (%esi)
	movl	%eax, -4(%esi)
	jmp	L207
L70:
	movl	-20(%ebp), %ecx
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	(%ecx), %eax
	movl	(%eax), %edi
	addl	$4, %eax
	movl	%eax, (%ecx)
	jmp	L207
L69:
	movl	-20(%ebp), %edx
	addl	%edi, (%edx)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L71:
	movl	-20(%ebp), %ebx
	movl	(%ebx), %edx
	movl	%edi, (%edx)
	movl	(%esi), %edi
	addl	$4, %edx
	movl	%edx, (%ebx)
	subl	$4, %esi
	jmp	L207
L64:
	movl	%edi, 4(%esi)
	movl	-8(%esi), %edi
	addl	$8, %esi
	movl	%edi, (%esi)
	movl	-12(%esi), %edi
	jmp	L207
L63:
	movl	-12(%esi), %edi
	subl	$16, %esi
	jmp	L207
L62:
	movl	-8(%esi), %edi
	subl	$12, %esi
	jmp	L207
L61:
	movl	-4(%esi), %edi
	subl	$8, %esi
	jmp	L207
L60:
	movl	%edi, 4(%esi)
	movl	(%esi), %ecx
	addl	$8, %esi
	movl	%ecx, (%esi)
	jmp	L207
L59:
	movl	%edi, %ebx
	movl	(%esi), %edx
	movl	-4(%esi), %edi
	movl	%ebx, (%esi)
	movl	%edx, -4(%esi)
	jmp	L207
L58:
	subl	$4, %esi
	jmp	L207
L57:
	movl	(%esi), %eax
	movl	%edi, (%esi)
	movl	%eax, %edi
	jmp	L207
L56:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-16(%esi), %edi
	jmp	L207
L55:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-12(%esi), %edi
	jmp	L207
L54:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-8(%esi), %edi
	jmp	L207
L53:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-4(%esi), %edi
	jmp	L207
L52:
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L51:
	addl	$4, %esi
	movl	%edi, (%esi)
	jmp	L207
L49:
	movl	%edi, %eax
	movl	(%esi), %edi
	subl	$4, %esi
	testl	%eax, %eax
	je	L207
	addl	$4, -20(%ebp)
	movl	-16(%ebp), %ecx
	movl	%eax, -16(%ebp)
	movl	-20(%ebp), %edx
	movl	%ecx, (%edx)
	jmp	L207
L39:
	movl	-16(%ebp), %eax
	movsbl	(%eax),%edx
	incl	%eax
	movl	%eax, -16(%ebp)
	movl	(%esi), %eax
	cmpl	%edi, %eax
	je	L214
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L207
L47:
	movl	-16(%ebp), %ebx
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	cmpl	%edi, %eax
	movl	%ebx, -16(%ebp)
	jge	L48
	addl	%edx, -16(%ebp)
L48:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L207
L45:
	movl	-16(%ebp), %ecx
	movl	(%esi), %eax
	movsbl	(%ecx),%edx
	incl	%ecx
	cmpl	%edi, %eax
	movl	%ecx, -16(%ebp)
	jle	L46
	addl	%edx, %ecx
	movl	%ecx, -16(%ebp)
L46:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L207
L43:
	movl	-16(%ebp), %ecx
	movl	(%esi), %eax
	movsbl	(%ecx),%edx
	incl	%ecx
	cmpl	%edi, %eax
	movl	%ecx, -16(%ebp)
	jg	L44
	addl	%edx, -16(%ebp)
L44:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L207
L41:
	movl	-16(%ebp), %ecx
	movl	(%esi), %eax
	movsbl	(%ecx),%edx
	incl	%ecx
	cmpl	%edi, %eax
	movl	%ecx, -16(%ebp)
	jl	L42
	addl	%edx, %ecx
	movl	%ecx, -16(%ebp)
L42:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L207
L37:
	movl	-16(%ebp), %ecx
	movl	(%esi), %eax
	movsbl	(%ecx),%edx
	incl	%ecx
	cmpl	%edi, %eax
	movl	%ecx, -16(%ebp)
	je	L38
	addl	%edx, %ecx
	movl	%ecx, -16(%ebp)
L38:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L207
L35:
	movl	-16(%ebp), %edx
	movsbl	(%edx),%eax
	incl	%edx
	testl	%edi, %edi
	movl	%edx, -16(%ebp)
	jne	L207
	addl	%eax, %edx
	movl	%edx, -16(%ebp)
	jmp	L207
L33:
	movl	-16(%ebp), %ecx
	movsbl	(%ecx),%eax
	incl	%ecx
	testl	%edi, %edi
	movl	%ecx, -16(%ebp)
	js	L207
	addl	%eax, %ecx
	movl	%ecx, -16(%ebp)
	jmp	L207
L31:
	movl	-16(%ebp), %edx
	movsbl	(%edx),%eax
	incl	%edx
	testl	%edi, %edi
	movl	%edx, -16(%ebp)
	jg	L207
	addl	%eax, %edx
	movl	%edx, -16(%ebp)
	jmp	L207
	.p2align 4,,7
L29:
	movl	-16(%ebp), %ecx
	movsbl	(%ecx),%eax
	incl	%ecx
	testl	%edi, %edi
	movl	%ecx, -16(%ebp)
	je	L207
	addl	%eax, %ecx
	movl	%ecx, -16(%ebp)
	jmp	L207
L28:
	movl	-16(%ebp), %ebx
	movsbl	(%ebx),%ecx
	leal	1(%ecx,%ebx), %eax
	movl	%eax, -16(%ebp)
	jmp	L207
L27:
	movl	-16(%ebp), %edx
	movl	(%edx), %ebx
	movl	%ebx, -16(%ebp)
	jmp	L207
L26:
	addl	$4, -20(%ebp)
	movl	-16(%ebp), %ecx
	movl	-20(%ebp), %edx
	movl	(%ecx), %ebx
	movl	%ecx, %eax
	addl	$4, %eax
	movl	%eax, (%edx)
	movl	%ebx, -16(%ebp)
	jmp	L207
L25:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-16(%ebp), %edi
	movl	(%edi), %ecx
	addl	$4, %edi
	movl	%edi, -16(%ebp)
	movl	(%ecx), %edi
	jmp	L207
L23:
	movl	-20(%ebp), %eax
	subl	$4, -20(%ebp)
	movl	(%eax), %ebx
	movl	%ebx, -16(%ebp)
	jmp	L207
L24:
	movl	-16(%ebp), %edx
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	(%edx), %edi
	addl	$4, %edx
	movl	%edx, -16(%ebp)
	jmp	L207
L81:
	movl	(%esi), %ebx
	subl	$4, %esi
	movl	%ebx, %eax
	cltd
	idivl	%edi
	movl	%eax, %edi
	jmp	L207
L85:
	movl	(%esi), %eax
	cltd
	idivl	%edi
	movl	%edx, %edi
	movl	%eax, (%esi)
	jmp	L207
L83:
	movl	(%esi), %eax
	movl	-4(%esi), %ecx
	subl	$8, %esi
	movl	%eax, %ebx
	imull	%ecx, %ebx
	movl	%ebx, %eax
	cltd
	idivl	%edi
	movl	%eax, %edi
	jmp	L207
L146:
	movl	%edi, %eax
	movb	%al, _gr_alphav
	call	__Z8gr_alphav
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L207
L167:
	movl	_indexdir(,%edi,4), %edi
	jmp	L207
L214:
	addl	%edx, -16(%ebp)
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L207
L213:
	movl	%edi, 4(%esp)
	movl	$_linea, (%esp)
	call	_strcpy
	jmp	L117
L210:
	movl	_dp, %edx
	movl	%edx, (%esp)
	call	_closedir
	jmp	L207
	.align 2
	.p2align 4,,15
.globl __Z5apilai
	.def	__Z5apilai;	.scl	2;	.type	32;	.endef
__Z5apilai:
	pushl	%ebp
	movl	_cntpila, %eax
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
	movl	%edx, _pila(,%eax,4)
	incl	%eax
	movl	%eax, _cntpila
	ret
	.align 2
	.p2align 4,,15
.globl __Z8desapilav
	.def	__Z8desapilav;	.scl	2;	.type	32;	.endef
__Z8desapilav:
	pushl	%ebp
	movl	_cntpila, %eax
	movl	%esp, %ebp
	popl	%ebp
	decl	%eax
	movl	%eax, _cntpila
	movl	_pila(,%eax,4), %eax
	ret
	.align 2
	.p2align 4,,15
.globl __Z5adatoPKc
	.def	__Z5adatoPKc;	.scl	2;	.type	32;	.endef
__Z5adatoPKc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	_cntdato, %eax
	movl	8(%ebp), %ebx
	addl	$_dato, %eax
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	call	_strlen
	movl	_cntdato, %edx
	addl	%edx, %eax
	incl	%eax
	movl	%eax, _cntdato
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8adatonroii
	.def	__Z8adatonroii;	.scl	2;	.type	32;	.endef
__Z8adatonroii:
	pushl	%ebp
	movl	_cntdato, %eax
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %ecx
	cmpl	$2, %edx
	je	L221
	jle	L224
	cmpl	$4, %edx
	je	L225
L219:
	popl	%ebp
	addl	%edx, %eax
	movl	%eax, _cntdato
	ret
	.p2align 4,,7
L224:
	cmpl	$1, %edx
	jne	L219
	popl	%ebp
	movb	%cl, _dato(%eax)
	addl	%edx, %eax
	movl	%eax, _cntdato
	ret
	.p2align 4,,7
L221:
	popl	%ebp
	movw	%cx, _dato(%eax)
	addl	%edx, %eax
	movl	%eax, _cntdato
	ret
	.p2align 4,,7
L225:
	popl	%ebp
	movl	%ecx, _dato(%eax)
	addl	%edx, %eax
	movl	%eax, _cntdato
	ret
	.align 2
	.p2align 4,,15
.globl __Z8adatocnti
	.def	__Z8adatocnti;	.scl	2;	.type	32;	.endef
__Z8adatocnti:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	pushl	%ebx
	movl	_cntdato, %ebx
	testl	%eax, %eax
	leal	_dato(%ebx), %ecx
	jle	L232
	movl	%eax, %edx
	.p2align 4,,15
L230:
	movb	$0, (%ecx)
	incl	%ecx
	decl	%edx
	jne	L230
L232:
	leal	(%ebx,%eax), %eax
	popl	%ebx
	movl	%eax, _cntdato
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8aprognroi
	.def	__Z8aprognroi;	.scl	2;	.type	32;	.endef
__Z8aprognroi:
	pushl	%ebp
	movl	_cntprog, %edx
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	leal	_prog(%edx), %ecx
	cmpl	$142, %eax
	ja	L236
	popl	%ebp
	addb	$112, %al
	movb	%al, _prog(%edx)
	leal	1(%edx), %eax
	movl	%eax, _cntprog
	ret
	.p2align 4,,7
L236:
	movb	$1, _prog(%edx)
	movl	%eax, 1(%ecx)
	leal	5(%edx), %eax
	popl	%ebp
	movl	%eax, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z5aprogi
	.def	__Z5aprogi;	.scl	2;	.type	32;	.endef
__Z5aprogi:
	pushl	%ebp
	movl	_cntprog, %edx
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	leal	_prog(%edx), %ecx
	cmpl	$3, %eax
	movb	%al, _prog(%edx)
	je	L242
	xorl	%ecx, %ecx
L242:
	popl	%ebp
	movl	%ecx, _lastcall
	leal	1(%edx), %ecx
	movl	%ecx, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z8aproginti
	.def	__Z8aproginti;	.scl	2;	.type	32;	.endef
__Z8aproginti:
	pushl	%ebp
	movl	_cntprog, %eax
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
	addl	$_prog, %edx
	movl	%edx, _prog(%eax)
	addl	$4, %eax
	movl	%eax, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z9aprogaddri
	.def	__Z9aprogaddri;	.scl	2;	.type	32;	.endef
__Z9aprogaddri:
	pushl	%ebp
	movl	_cntprog, %edx
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	leal	(%eax,%eax,2), %ecx
	movl	_indice+4(,%ecx,4), %eax
	movl	%eax, _prog(%edx)
	addl	$4, %edx
	movl	%edx, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z11aprogaddrexi
	.def	__Z11aprogaddrexi;	.scl	2;	.type	32;	.endef
__Z11aprogaddrexi:
	pushl	%ebp
	movl	_cntprog, %edx
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	leal	(%eax,%eax,2), %ecx
	movl	_indiceex+4(,%ecx,4), %eax
	movl	%eax, _prog(%edx)
	addl	$4, %edx
	movl	%edx, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z6definePc
	.def	__Z6definePc;	.scl	2;	.type	32;	.endef
__Z6definePc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %ecx
	movl	%edi, -4(%ebp)
	movl	%ebx, -12(%ebp)
	movl	_cntindice, %ebx
	leal	1(%ecx), %edi
	leal	(%ebx,%ebx,2), %edx
	incl	%ebx
	leal	_indice(,%edx,4), %esi
	movl	%ebx, _cntindice
	movsbl	(%ecx),%eax
	movl	%eax, 8(%esi)
	cmpb	$58, 1(%ecx)
	je	L252
L247:
	movl	_cntnombre, %ebx
	movl	%edi, 4(%esp)
	addl	$_nombre, %ebx
	movl	%ebx, (%esp)
	call	_strcpy
	movl	%edi, (%esp)
	call	_strlen
	movl	%ebx, (%esi)
	movl	_cntnombre, %edi
	addl	%edi, %eax
	incl	%eax
	cmpl	$58, 8(%esi)
	movl	%eax, _cntnombre
	je	L253
	movl	_cntdato, %eax
	addl	$_dato, %eax
	movl	%eax, 4(%esi)
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
L253:
	movl	_cntprog, %eax
	addl	$_prog, %eax
	movl	%eax, 4(%esi)
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
L252:
	leal	2(%ecx), %edi
	movl	_cntindiceex, %ecx
	movl	_cntnombreex, %eax
	leal	(%ecx,%ecx,2), %ebx
	sall	$2, %ebx
	incl	%ecx
	movl	%ecx, _cntindiceex
	leal	_indiceex(%ebx), %edx
	addl	$_nombreex, %eax
	movl	%edx, -16(%ebp)
	movl	%eax, -20(%ebp)
	movl	%edi, 4(%esp)
	movl	%eax, (%esp)
	call	_strcpy
	movl	%edi, (%esp)
	call	_strlen
	movl	_cntnombreex, %ecx
	movl	-16(%ebp), %edx
	addl	%ecx, %eax
	incl	%eax
	movl	8(%esi), %ecx
	movl	%eax, _cntnombreex
	movl	-20(%ebp), %eax
	cmpl	$58, %ecx
	movl	%ecx, 8(%edx)
	movl	%eax, _indiceex(%ebx)
	je	L254
	movl	_cntdato, %eax
	addl	$_dato, %eax
L249:
	movl	-16(%ebp), %ebx
	movl	%eax, 4(%ebx)
	jmp	L247
L254:
	movl	_cntprog, %eax
	addl	$_prog, %eax
	jmp	L249
	.align 2
	.p2align 4,,15
.globl __Z8endefinev
	.def	__Z8endefinev;	.scl	2;	.type	32;	.endef
__Z8endefinev:
	pushl	%ebp
	movl	_cntindice, %edx
	movl	%esp, %ebp
	leal	(%edx,%edx,2), %eax
	leal	_indice-12(,%eax,4), %ecx
	cmpl	$58, 8(%ecx)
	je	L270
	movl	_cntdato, %edx
	leal	_dato(%edx), %eax
	cmpl	4(%ecx), %eax
	je	L271
	popl	%ebp
	ret
	.p2align 4,,7
L270:
	movl	_lastcall, %eax
	testl	%eax, %eax
	je	L257
	movb	$4, (%eax)
	xorl	%ecx, %ecx
	popl	%ebp
	movl	%ecx, _lastcall
	ret
	.p2align 4,,7
L257:
	popl	%ebp
	xorl	%edx, %edx
	movl	_cntprog, %eax
	movl	%edx, _lastcall
	movb	$0, _prog(%eax)
	incl	%eax
	movl	%eax, _cntprog
	ret
	.p2align 4,,7
L271:
	popl	%ebp
	xorl	%eax, %eax
	leal	4(%edx), %ecx
	movl	%eax, _dato(%edx)
	movl	%ecx, _cntdato
	ret
	.align 2
	.p2align 4,,15
.globl __Z11endefinesinv
	.def	__Z11endefinesinv;	.scl	2;	.type	32;	.endef
__Z11endefinesinv:
	pushl	%ebp
	movl	_cntindice, %edx
	movl	%esp, %ebp
	leal	(%edx,%edx,2), %eax
	leal	_indice-12(,%eax,4), %ecx
	cmpl	$58, 8(%ecx)
	je	L272
	movl	_cntdato, %edx
	leal	_dato(%edx), %eax
	cmpl	4(%ecx), %eax
	je	L280
L272:
	popl	%ebp
	ret
	.p2align 4,,7
L280:
	popl	%ebp
	xorl	%eax, %eax
	leal	4(%edx), %ecx
	movl	%eax, _dato(%edx)
	movl	%ecx, _cntdato
	ret
	.align 2
	.p2align 4,,15
.globl __Z8esnumeroPc
	.def	__Z8esnumeroPc;	.scl	2;	.type	32;	.endef
__Z8esnumeroPc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	xorl	%edi, %edi
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %ebx
	movzbl	(%ebx), %edx
	cmpb	$45, %dl
	je	L308
	cmpb	$43, %dl
	je	L309
L283:
	xorl	%ecx, %ecx
	testb	%dl, %dl
	je	L281
	cmpb	$36, %dl
	je	L287
	cmpb	$37, %dl
	movl	$10, %esi
	je	L310
L286:
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	movl	%eax, _numero
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L281
	jmp	L298
	.p2align 4,,7
L312:
	movsbl	%al,%edx
	leal	-48(%edx), %ecx
L294:
	movl	%ecx, %edx
	shrl	$31, %edx
	cmpl	%esi, %ecx
	setge	%al
	orb	%dl, %al
	jne	L295
	movl	_numero, %eax
	incl	%ebx
	imull	%esi, %eax
	leal	(%eax,%ecx), %edx
	movl	%edx, _numero
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L311
L298:
	cmpb	$57, %al
	jle	L312
	cmpb	$64, %al
	jle	L295
	movsbl	%al,%eax
	leal	-55(%eax), %ecx
	jmp	L294
L295:
	xorl	%ecx, %ecx
	.p2align 4,,15
L281:
	popl	%ebx
	movl	%ecx, %eax
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L308:
	incl	%ebx
	movl	$1, %edi
	movzbl	(%ebx), %edx
	jmp	L283
	.p2align 4,,7
L309:
	incl	%ebx
	movzbl	(%ebx), %edx
	jmp	L283
L287:
	movl	$16, %esi
	incl	%ebx
	jmp	L286
	.p2align 4,,7
L311:
	decl	%edi
	je	L313
	movl	$1, %ecx
L314:
	popl	%ebx
	movl	%ecx, %eax
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L310:
	movl	$2, %esi
	incl	%ebx
	jmp	L286
L313:
	negl	%edx
	movl	$1, %ecx
	movl	%edx, _numero
	jmp	L314
	.align 2
	.p2align 4,,15
.globl __Z7esmacroPc
	.def	__Z7esmacroPc;	.scl	2;	.type	32;	.endef
__Z7esmacroPc:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	%eax, _numero
	movl	_macros, %eax
	movl	$_macros, %ebx
	movl	8(%ebp), %esi
	cmpb	$0, (%eax)
	je	L321
	.p2align 4,,15
L326:
	movl	%esi, 4(%esp)
	movl	(%ebx), %edx
	movl	%edx, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L325
	incl	_numero
	addl	$4, %ebx
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	jne	L326
L321:
	addl	$16, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L325:
	addl	$16, %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z9espalabraPc
	.def	__Z9espalabraPc;	.scl	2;	.type	32;	.endef
__Z9espalabraPc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	_cntindice, %esi
	movl	8(%ebp), %edi
	decl	%esi
	leal	(%esi,%esi,2), %eax
	movl	%esi, _numero
	leal	_indice(,%eax,4), %ebx
	cmpl	$_indice, %ebx
	jb	L333
	.p2align 4,,15
L338:
	movl	%edi, 4(%esp)
	movl	(%ebx), %edx
	movl	%edx, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L337
	leal	-1(%esi), %ecx
	subl	$12, %ebx
	movl	%ecx, %esi
	movl	%ecx, _numero
	cmpl	$_indice, %ebx
	jae	L338
L333:
	addl	$12, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L337:
	addl	$12, %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11espalabraexPc
	.def	__Z11espalabraexPc;	.scl	2;	.type	32;	.endef
__Z11espalabraexPc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	_cntindiceex, %esi
	movl	8(%ebp), %edi
	decl	%esi
	leal	(%esi,%esi,2), %eax
	movl	%esi, _numero
	leal	_indiceex(,%eax,4), %ebx
	cmpl	$_indiceex, %ebx
	jb	L345
	.p2align 4,,15
L350:
	movl	%edi, 4(%esp)
	movl	(%ebx), %edx
	movl	%edx, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L349
	leal	-1(%esi), %ecx
	subl	$12, %ebx
	movl	%ecx, %esi
	movl	%ecx, _numero
	cmpl	$_indiceex, %ebx
	jae	L350
L345:
	addl	$12, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L349:
	addl	$12, %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11estaincludePc
	.def	__Z11estaincludePc;	.scl	2;	.type	32;	.endef
__Z11estaincludePc:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	_cntincludes, %edx
	movl	8(%ebp), %esi
	testl	%edx, %edx
	je	L351
	leal	(%edx,%edx,2), %eax
	leal	_includes-12(,%eax,4), %ebx
	cmpl	$_includes, %ebx
	jb	L358
	.p2align 4,,15
L363:
	movl	%esi, 4(%esp)
	movl	(%ebx), %edx
	movl	%edx, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L359
	subl	$12, %ebx
	cmpl	$_includes, %ebx
	jae	L363
L358:
	xorl	%eax, %eax
L351:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L359:
	addl	$16, %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z13agregaincludePc
	.def	__Z13agregaincludePc;	.scl	2;	.type	32;	.endef
__Z13agregaincludePc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%edi, -4(%ebp)
	movl	_cntincludes, %eax
	movl	_cntnombreex, %edi
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	addl	$_nombreex, %edi
	movl	%ebx, -12(%ebp)
	leal	(%eax,%eax,2), %ebx
	incl	%eax
	movl	%esi, 4(%esp)
	sall	$2, %ebx
	movl	%edi, (%esp)
	movl	%eax, _cntincludes
	call	_strcpy
	movl	%esi, (%esp)
	call	_strlen
	movl	%edi, _includes(%ebx)
	movl	_cntnombreex, %edx
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	addl	%edx, %eax
	movl	-4(%ebp), %edi
	incl	%eax
	movl	%eax, _cntnombreex
	movl	%ebp, %esp
	popl	%ebp
	ret
	.section .rdata,"dr"
LC123:
	.ascii "no existe %s\0"
LC125:
	.ascii "%s|%d|%s\0"
LC124:
	.ascii "palabra %s en dato ?\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z11compilafilePc
	.def	__Z11compilafilePc;	.scl	2;	.type	32;	.endef
__Z11compilafilePc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$620, %esp
	movl	8(%ebp), %ebx
	movzbl	(%ebx), %eax
	cmpb	$32, %al
	jle	L712
	.p2align 4,,15
L822:
	movsbl	%al,%eax
	movl	%eax, (%esp)
	call	_tolower
	movb	%al, (%ebx)
	incl	%ebx
	movzbl	(%ebx), %eax
	cmpb	$32, %al
	jg	L822
L712:
	movl	8(%ebp), %eax
	leal	-536(%ebp), %ecx
	movl	$_pathdata, %ebx
	movl	%ecx, (%esp)
	movl	$LC120, %edi
	movl	$LC121, %esi
	movl	%ebx, 8(%esp)
	movl	%eax, 12(%esp)
	movl	%edi, 4(%esp)
	call	_sprintf
	movl	%esi, 4(%esp)
	leal	-536(%ebp), %edx
	movl	%edx, (%esp)
	call	_fopen
	movl	%eax, -540(%ebp)
	testl	%eax, %eax
	movl	$1, %edx
	je	L365
	movl	$2, %ebx
	movl	$4, %edi
	xorl	%ecx, %ecx
	movl	%ebx, -544(%ebp)
	movl	$1, %esi
	xorl	%edx, %edx
	movl	%edi, -548(%ebp)
	movl	%ecx, -552(%ebp)
	movl	%esi, -556(%ebp)
	movl	%edx, _cntpila
L783:
	testb	$16, 12(%eax)
	je	L823
	movl	_cntprog, %eax
	cmpb	$0, _prog-1(%eax)
	je	L706
	movb	$0, _prog(%eax)
	xorl	%edi, %edi
	incl	%eax
	movl	%edi, _lastcall
	movl	%eax, _cntprog
L706:
	movl	-540(%ebp), %esi
	movl	%esi, (%esp)
	call	_fclose
	testl	%eax, %eax
	movl	$2, %edx
	jne	L365
	xorl	%ecx, %ecx
	xorl	%ebx, %ebx
	xorl	%edx, %edx
	movl	%ecx, _cntnombre
	movl	%ebx, _cntindice
L365:
	addl	$620, %esp
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L823:
L373:
	movb	$0, -536(%ebp)
	movl	-540(%ebp), %esi
	movl	$512, %edx
	movl	%edx, 4(%esp)
	leal	-536(%ebp), %eax
	leal	-536(%ebp), %edi
	movl	%esi, 8(%esp)
	movl	%eax, (%esp)
	call	_fgets
	movzbl	(%edi), %ecx
	testb	%cl, %cl
	setne	%al
	cmpb	$32, %cl
	setle	%bl
	testb	%bl, %al
	je	L824
	.p2align 4,,15
L392:
	incl	%edi
L830:
	movzbl	(%edi), %ecx
	testb	%cl, %cl
	setne	%al
	cmpb	$32, %cl
	setle	%bl
	testb	%bl, %al
	jne	L392
L824:
	testb	%cl, %cl
	je	L378
	cmpb	$34, %cl
	movl	%edi, %esi
	je	L825
	cmpb	$32, %cl
	jle	L386
	.p2align 4,,15
L826:
	movsbl	%cl,%edx
	movl	%edx, (%esp)
	call	_toupper
	movb	%al, (%edi)
	incl	%edi
	movzbl	(%edi), %ecx
	cmpb	$32, %cl
	jg	L826
L386:
	testb	%cl, %cl
	jne	L390
	movb	$0, 1(%edi)
L390:
	movb	$0, (%edi)
	movzbl	(%esi), %ecx
	cmpb	$124, %cl
	je	L827
	cmpb	$34, %cl
	je	L828
	cmpb	$58, %cl
	sete	%dl
	cmpb	$35, %cl
	sete	%al
	orb	%al, %dl
	je	L403
	movl	_cntpila, %ecx
	testl	%ecx, %ecx
	jg	L736
	movl	_cntindice, %eax
	leal	(%eax,%eax,2), %ebx
	leal	_indice-12(,%ebx,4), %ecx
	cmpl	$58, 8(%ecx)
	je	L413
	movl	_cntdato, %edx
	leal	_dato(%edx), %ebx
	cmpl	4(%ecx), %ebx
	je	L829
L413:
	cmpb	$0, 1(%esi)
	jne	L414
	movl	_cntprog, %edx
	addl	$_prog, %edx
	movl	%edx, _bootaddr
L415:
	xorl	%eax, %eax
	cmpb	$58, (%esi)
	movl	$4, %ecx
	movl	%ecx, -548(%ebp)
	sete	%al
	incl	%eax
	movl	%eax, -544(%ebp)
	incl	%edi
	jmp	L830
L403:
	cmpb	$94, %cl
	je	L831
	xorl	%eax, %eax
	cmpb	$45, %cl
	movl	%esi, %ebx
	movl	%eax, -572(%ebp)
	je	L832
	cmpb	$43, %cl
	je	L833
L454:
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L452
	cmpb	$36, %al
	je	L459
	movl	$10, %edx
	cmpb	$37, %al
	movl	%edx, -568(%ebp)
	je	L834
L458:
	xorl	%eax, %eax
	movl	%eax, _numero
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L452
	jmp	L470
L836:
	movsbl	%al,%edx
	leal	-48(%edx), %ecx
L466:
	movl	%ecx, %edx
	shrl	$31, %edx
	cmpl	-568(%ebp), %ecx
	setge	%al
	orb	%dl, %al
	jne	L452
	movl	_numero, %edx
	incl	%ebx
	movl	-568(%ebp), %eax
	imull	%edx, %eax
	leal	(%eax,%ecx), %edx
	movl	%edx, _numero
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L835
L470:
	cmpb	$57, %al
	jle	L836
	cmpb	$64, %al
	jle	L452
	movsbl	%al,%eax
	leal	-55(%eax), %ecx
	jmp	L466
L825:
	incl	%edi
	movl	%edi, %edx
	movzbl	(%edi), %eax
	jmp	L784
	.p2align 4,,7
L382:
	movb	%al, (%edi)
	incl	%edx
	incl	%edi
	movzbl	(%edx), %eax
L784:
	testb	%al, %al
	je	L381
	cmpb	$34, %al
	jne	L382
	cmpb	$34, 1(%edx)
	jne	L381
	incl	%edx
	movzbl	(%edx), %eax
	jmp	L382
L381:
	cmpl	%edx, %edi
	je	L735
	movb	$0, (%edi)
	movl	%edx, %edi
L735:
	movzbl	(%edi), %ecx
	jmp	L386
L828:
	cmpl	$1, -544(%ebp)
	leal	1(%esi), %ebx
	je	L395
	cmpl	$2, -544(%ebp)
	jne	L392
	movl	%ebx, 4(%esp)
	movl	_cntdato, %esi
	addl	$_dato, %esi
	movl	%esi, (%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	call	_strlen
	movl	_cntdato, %ebx
	movl	_cntprog, %edx
	addl	%ebx, %eax
	incl	%eax
	cmpl	$142, %esi
	movl	%eax, _cntdato
	leal	_prog(%edx), %eax
	ja	L399
	movl	%esi, %eax
L811:
	addb	$112, %al
	movb	%al, _prog(%edx)
	leal	1(%edx), %eax
L797:
	movl	%eax, _cntprog
	incl	%edi
	jmp	L830
L452:
	movl	_macros, %eax
	xorl	%ecx, %ecx
	movl	$_macros, %ebx
	movl	%ecx, _numero
	cmpb	$0, (%eax)
	je	L728
	.p2align 4,,15
L837:
	movl	%esi, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L742
	incl	_numero
	addl	$4, %ebx
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	jne	L837
L728:
	xorl	%edx, %edx
	movl	%edx, -592(%ebp)
	cmpb	$39, (%esi)
	je	L838
L624:
	movl	_cntindice, %ebx
	decl	%ebx
	leal	(%ebx,%ebx,2), %ecx
	movl	%ebx, _numero
	leal	_indice(,%ecx,4), %ebx
	cmpl	$_indice, %ebx
	jb	L732
L839:
	movl	%esi, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L746
	decl	_numero
	subl	$12, %ebx
	cmpl	$_indice, %ebx
	jae	L839
L732:
	movl	_cntindiceex, %eax
	decl	%eax
	leal	(%eax,%eax,2), %edx
	movl	%eax, _numero
	leal	_indiceex(,%edx,4), %ebx
	jmp	L792
	.p2align 4,,7
L840:
	movl	%esi, 4(%esp)
	movl	(%ebx), %ecx
	movl	%ecx, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L747
	decl	_numero
	subl	$12, %ebx
L792:
	cmpl	$_indiceex, %ebx
	jae	L840
	movl	%esi, 8(%esp)
L801:
	movl	$LC123, %eax
	movl	%eax, 4(%esp)
L807:
	movl	$_error, (%esp)
	call	_sprintf
L405:
	movl	8(%ebp), %ebx
	leal	-536(%ebp), %edx
	movl	$_error, %edi
	movl	$LC125, %eax
	movl	%ebx, 16(%esp)
	movl	-556(%ebp), %esi
	movl	%edx, (%esp)
	movl	%edi, 8(%esp)
	movl	%esi, 12(%esp)
	movl	%eax, 4(%esp)
	call	_sprintf
	movl	$_error, (%esp)
	leal	-536(%ebp), %ecx
	movl	%ecx, 4(%esp)
	call	_strcpy
	addl	$620, %esp
	movl	$3, %edx
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L414:
	xorl	%ecx, %ecx
	movl	%esi, %ebx
	movl	%ecx, -564(%ebp)
	movzbl	(%esi), %eax
	cmpb	$45, %al
	je	L841
	cmpb	$43, %al
	je	L842
L418:
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L748
	cmpb	$36, %al
	je	L423
	movl	$10, %edx
	cmpb	$37, %al
	movl	%edx, -560(%ebp)
	je	L843
L422:
	xorl	%ecx, %ecx
	movl	%ecx, _numero
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L748
	jmp	L434
L845:
	movsbl	%al,%eax
	leal	-48(%eax), %ecx
L430:
	movl	%ecx, %edx
	shrl	$31, %edx
	cmpl	-560(%ebp), %ecx
	setge	%al
	orb	%dl, %al
	jne	L748
	movl	_numero, %edx
	incl	%ebx
	movl	-560(%ebp), %eax
	imull	%edx, %eax
	leal	(%eax,%ecx), %edx
	movl	%edx, _numero
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L844
L434:
	cmpb	$57, %al
	jle	L845
	cmpb	$64, %al
	jle	L748
	movsbl	%al,%edx
	leal	-55(%edx), %ecx
	jmp	L430
L748:
	movl	%esi, (%esp)
	call	__Z6definePc
	jmp	L415
L831:
	incl	%esi
	movl	%esi, -584(%ebp)
	movl	_cntincludes, %esi
	testl	%esi, %esi
	je	L749
	leal	(%esi,%esi,2), %edx
	leal	_includes-12(,%edx,4), %ebx
	cmpl	$_includes, %ebx
	jb	L749
L846:
	movl	-584(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	(%ebx), %ecx
	movl	%ecx, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L392
	subl	$12, %ebx
	cmpl	$_includes, %ebx
	jae	L846
L749:
	leal	1(%esi), %edx
	movl	-584(%ebp), %eax
	leal	(%esi,%esi,2), %ebx
	movl	%edx, _cntincludes
	movl	_cntnombreex, %esi
	sall	$2, %ebx
	movl	%eax, 4(%esp)
	addl	$_nombreex, %esi
	movl	%esi, (%esp)
	call	_strcpy
	movl	-584(%ebp), %ecx
	movl	%ecx, (%esp)
	call	_strlen
	movl	%esi, _includes(%ebx)
	movl	_cntnombreex, %edx
	movl	-584(%ebp), %esi
	addl	%edx, %eax
	incl	%eax
	movl	%eax, _cntnombreex
	movl	%esi, (%esp)
	call	__Z11compilafilePc
	cmpl	$1, %eax
	je	L740
	testl	%eax, %eax
	je	L392
	movl	%eax, %edx
	jmp	L365
	.p2align 4,,7
L832:
	movl	$1, %ecx
	leal	1(%esi), %ebx
	movl	%ecx, -572(%ebp)
	jmp	L454
L834:
	movl	$2, %eax
L817:
	movl	%eax, -568(%ebp)
	incl	%ebx
	jmp	L458
L423:
	movl	$16, %eax
L816:
	movl	%eax, -560(%ebp)
	incl	%ebx
	jmp	L422
L827:
	movb	$0, 1(%edi)
	incl	%edi
	jmp	L830
L833:
	leal	1(%esi), %ebx
	jmp	L454
L841:
	movl	$1, %eax
	leal	1(%esi), %ebx
	movl	%eax, -564(%ebp)
	jmp	L418
L838:
	xorl	%eax, %eax
	movl	$1, %ecx
	incl	%esi
	movl	%ecx, -592(%ebp)
	movl	%esi, %ebx
	movl	%eax, -580(%ebp)
	movzbl	(%esi), %eax
	cmpb	$45, %al
	je	L847
	cmpb	$43, %al
	je	L848
L627:
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L624
	cmpb	$36, %al
	je	L632
	movl	$10, %ecx
	cmpb	$37, %al
	movl	%ecx, -576(%ebp)
	je	L849
L631:
	xorl	%eax, %eax
	movl	%eax, _numero
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L624
	jmp	L643
L851:
	movsbl	%al,%edx
	leal	-48(%edx), %ecx
L639:
	movl	%ecx, %edx
	shrl	$31, %edx
	cmpl	-576(%ebp), %ecx
	setge	%al
	orb	%dl, %al
	jne	L624
	movl	_numero, %edx
	incl	%ebx
	movl	-576(%ebp), %eax
	imull	%edx, %eax
	leal	(%eax,%ecx), %edx
	movl	%edx, _numero
	movzbl	(%ebx), %eax
	testb	%al, %al
	je	L850
L643:
	cmpb	$57, %al
	jle	L851
	cmpb	$64, %al
	jle	L624
	movsbl	%al,%eax
	leal	-55(%eax), %ecx
	jmp	L639
L829:
	xorl	%eax, %eax
	leal	4(%edx), %ecx
	movl	%eax, _dato(%edx)
	movl	%ecx, _cntdato
	jmp	L413
L395:
	movl	%ebx, 4(%esp)
	movl	_cntdato, %esi
	addl	$_dato, %esi
	movl	%esi, (%esp)
	call	_strcpy
	movl	%ebx, (%esp)
	call	_strlen
	movl	_cntdato, %ecx
	addl	%ecx, %eax
	incl	%eax
L799:
	movl	%eax, _cntdato
	incl	%edi
	jmp	L830
L742:
	cmpl	$1, -544(%ebp)
	je	L499
	cmpl	$2, -544(%ebp)
	jne	L392
	movl	_numero, %edx
	cmpl	$5, %edx
	ja	L616
	jmp	*L622(,%edx,4)
	.section .rdata,"dr"
	.align 4
L622:
	.long	L530
	.long	L551
	.long	L558
	.long	L582
	.long	L602
	.long	L612
	.text
	.p2align 4,,7
L835:
	cmpl	$1, -572(%ebp)
	je	L852
L471:
	cmpl	$1, -544(%ebp)
	je	L473
	cmpl	$2, -544(%ebp)
	jne	L392
	movl	_numero, %eax
	movl	_cntprog, %edx
	cmpl	$142, %eax
	leal	_prog(%edx), %ecx
	jbe	L811
	movb	$1, _prog(%edx)
	movl	%eax, 1(%ecx)
	leal	5(%edx), %eax
	jmp	L797
L747:
	cmpl	$1, -544(%ebp)
	je	L682
	cmpl	$2, -544(%ebp)
	jne	L392
	movl	-592(%ebp), %edx
	testl	%edx, %edx
	jne	L690
	movl	_numero, %ecx
	leal	(%ecx,%ecx,2), %eax
	cmpl	$35, _indiceex+8(,%eax,4)
	je	L853
	movl	_cntprog, %eax
	leal	_prog(%eax), %ebx
	movb	$3, _prog(%eax)
	movl	%ebx, _lastcall
L793:
	leal	1(%eax), %edx
L699:
	leal	(%ecx,%ecx,2), %eax
	movl	_indiceex+4(,%eax,4), %eax
L794:
	movl	%eax, _prog(%edx)
	leal	4(%edx), %eax
	jmp	L797
L842:
	leal	1(%esi), %ebx
	jmp	L418
L459:
	movl	$16, %eax
	jmp	L817
L746:
	cmpl	$1, -544(%ebp)
	je	L652
	cmpl	$2, -544(%ebp)
	jne	L392
	movl	-592(%ebp), %ecx
	testl	%ecx, %ecx
	jne	L660
	movl	_numero, %ecx
	leal	(%ecx,%ecx,2), %ebx
	cmpl	$35, _indice+8(,%ebx,4)
	je	L854
	movl	_cntprog, %eax
	leal	_prog(%eax), %edx
	movb	$3, _prog(%eax)
	movl	%edx, _lastcall
L791:
	leal	1(%eax), %edx
L669:
	leal	(%ecx,%ecx,2), %ebx
	movl	_indice+4(,%ebx,4), %eax
	jmp	L794
L844:
	cmpl	$1, -564(%ebp)
	je	L855
L435:
	movb	$0, _error+12
	movl	$544174702, %ebx
	movl	$1635151465, %esi
	movl	%ebx, _error
	movl	$1868851564, %edi
	movl	%esi, _error+4
	movl	%edi, _error+8
	jmp	L405
L399:
	movb	$1, _prog(%edx)
	movl	%esi, 1(%eax)
	leal	5(%edx), %eax
	jmp	L797
L843:
	movl	$2, %eax
	jmp	L816
L632:
	movl	$16, %eax
L819:
	movl	%eax, -576(%ebp)
	incl	%ebx
	jmp	L631
L612:
	movl	_cntpila, %eax
	leal	-1(%eax), %edx
	cmpl	$4, _pila(,%edx,4)
	jne	L743
	subl	$2, %eax
	movl	_pila(,%eax,4), %edx
	movl	%eax, _cntpila
L809:
	movb	%dl, %al
	notb	%al
	addb	_cntprog, %al
L796:
	movb	%al, _prog(%edx)
	incl	%edi
	jmp	L830
L602:
	movl	_cntprog, %edx
	movl	$4, %ebx
	xorl	%eax, %eax
	movl	%eax, _lastcall
	incl	%edi
	leal	7(%edx), %ecx
	movb	$1, _prog(%edx)
	leal	_prog(%ecx), %esi
	movl	%esi, _prog+1(%edx)
	movl	_cntpila, %esi
	movb	$5, _prog+5(%edx)
	addl	$6, %edx
	movl	%edx, _pila(,%esi,4)
	movl	%ebx, _pila+4(,%esi,4)
	addl	$2, %esi
	movl	%esi, _cntpila
	movl	%ecx, _cntprog
	jmp	L830
L582:
	movl	_cntpila, %ebx
	leal	-1(%ebx), %esi
	movl	_pila(,%esi,4), %eax
	cmpl	$1, %eax
	je	L856
	cmpl	$2, %eax
	jne	L594
	cmpl	$1, -552(%ebp)
	leal	-2(%ebx), %edx
	movl	_pila(,%edx,4), %ecx
	jne	L596
	movl	_cntprog, %eax
	movl	%eax, _pila(,%edx,4)
	incl	%eax
	movl	%ecx, _pila(,%esi,4)
	leal	1(%ebx), %edx
	movl	$3, %ecx
	movl	%eax, _cntprog
	movl	%ecx, _pila(,%ebx,4)
	movl	%edx, _cntpila
L798:
	xorl	%eax, %eax
L820:
	movl	%eax, -552(%ebp)
	incl	%edi
	jmp	L830
L558:
	movl	_cntpila, %ebx
	leal	-1(%ebx), %edx
	movl	_pila(,%edx,4), %eax
	cmpl	$1, %eax
	je	L857
	cmpl	$2, %eax
	je	L858
	cmpl	$3, %eax
	jne	L573
	movl	-552(%ebp), %ecx
	leal	-2(%ebx), %eax
	movl	%eax, _cntpila
	movl	_pila(,%eax,4), %eax
	testl	%ecx, %ecx
	jne	L805
	movl	_cntprog, %edx
	xorl	%esi, %esi
	incl	%edi
	movl	%esi, _lastcall
	leal	-3(%ebx), %esi
	leal	1(%edx), %ecx
	movb	$5, _prog(%edx)
	subb	%cl, %al
	movl	_pila(,%esi,4), %ebx
	movl	%esi, _cntpila
	addl	$2, %edx
	decb	%al
	movb	%al, _prog(%ecx)
	movb	%dl, %cl
	subb	%bl, %cl
	movl	%edx, _cntprog
	decb	%cl
	movb	%cl, _prog(%ebx)
	jmp	L830
L551:
	cmpl	$1, -552(%ebp)
	je	L859
	movl	_cntpila, %eax
	movl	$2, %edx
	incl	%edi
	movl	_cntprog, %esi
	movl	%edx, _pila+4(,%eax,4)
	movl	%esi, _pila(,%eax,4)
	addl	$2, %eax
	movl	%eax, _cntpila
	jmp	L830
L530:
	movl	_cntpila, %ebx
	testl	%ebx, %ebx
	jle	L815
L537:
	movl	_cntprog, %eax
	xorl	%ebx, %ebx
	movl	%ebx, _lastcall
	movb	$0, _prog(%eax)
	incl	%eax
	jmp	L797
	.p2align 4,,7
L847:
	movl	$1, %edx
	leal	1(%esi), %ebx
	movl	%edx, -580(%ebp)
	jmp	L627
L473:
	movl	-548(%ebp), %ebx
	testl	%ebx, %ebx
	jne	L474
	movl	_numero, %eax
	movl	_cntdato, %ebx
	cmpl	%eax, -548(%ebp)
	leal	_dato(%ebx), %ecx
	jge	L726
	movl	%eax, %edx
L478:
	movb	$0, (%ecx)
	incl	%ecx
	decl	%edx
	jne	L478
L726:
	leal	(%ebx,%eax), %eax
	jmp	L799
L852:
	negl	%edx
	movl	%edx, _numero
	jmp	L471
L499:
	movl	_numero, %eax
	cmpl	$5, %eax
	ja	L526
	jmp	*L527(,%eax,4)
	.section .rdata,"dr"
	.align 4
L527:
	.long	L815
	.long	L517
	.long	L524
	.long	L521
	.long	L522
	.long	L524
	.text
L524:
	movl	_cntpila, %eax
	decl	%eax
	movl	%eax, _cntpila
	movl	_pila(,%eax,4), %eax
L821:
	movl	%eax, -548(%ebp)
	incl	%edi
	jmp	L830
L522:
	movl	_cntpila, %esi
	movl	$2, %eax
	movl	-548(%ebp), %ecx
	movl	%ecx, _pila(,%esi,4)
	incl	%esi
	movl	%esi, _cntpila
	jmp	L821
L521:
	xorl	%eax, %eax
	jmp	L821
L517:
	movl	_cntpila, %ebx
	movl	$1, %eax
	movl	-548(%ebp), %edx
	movl	%edx, _pila(,%ebx,4)
	incl	%ebx
	movl	%ebx, _cntpila
	jmp	L821
L815:
	movl	_cntindice, %esi
	leal	(%esi,%esi,2), %edx
	leal	_indice-12(,%edx,4), %ecx
	cmpl	$58, 8(%ecx)
	je	L860
	movl	_cntdato, %edx
	leal	_dato(%edx), %eax
	cmpl	4(%ecx), %eax
	jne	L392
	xorl	%esi, %esi
	leal	4(%edx), %eax
	movl	%esi, _dato(%edx)
	jmp	L799
	.p2align 4,,7
L682:
	movl	_numero, %ebx
	leal	(%ebx,%ebx,2), %esi
	movl	_indiceex+4(,%esi,4), %edx
L795:
	movl	_cntdato, %eax
	movl	%edx, _dato(%eax)
	addl	$4, %eax
	jmp	L799
L652:
	movl	_numero, %edx
	leal	(%edx,%edx,2), %esi
	movl	_indice+4(,%esi,4), %edx
	jmp	L795
L848:
	leal	1(%esi), %ebx
	jmp	L627
L855:
	negl	%edx
	movl	%edx, _numero
	jmp	L435
L850:
	cmpl	$1, -580(%ebp)
	je	L861
L644:
	movl	$544174702, %esi
	movl	$63, %edi
	movl	%esi, _error
	movw	%di, _error+4
	jmp	L405
L378:
	incl	-556(%ebp)
	movl	-540(%ebp), %eax
	jmp	L783
L474:
	cmpl	$2, -548(%ebp)
	movl	_numero, %edx
	movl	_cntdato, %eax
	je	L483
	jg	L485
	cmpl	$1, -548(%ebp)
	jne	L481
	movb	%dl, _dato(%eax)
L481:
	movl	-548(%ebp), %esi
	addl	%esi, %eax
	jmp	L799
L849:
	movl	$2, %eax
	jmp	L819
L690:
	movl	_cntprog, %ecx
	xorl	%edx, %edx
	movl	%edx, _lastcall
	leal	1(%ecx), %edx
	movb	$1, _prog(%ecx)
	movl	_numero, %ecx
	jmp	L699
L616:
	movl	_cntprog, %eax
	cmpl	$3, %edx
	leal	_prog(%eax), %ecx
	movb	%dl, _prog(%eax)
	je	L818
	xorl	%ecx, %ecx
L818:
	movl	%ecx, _lastcall
	leal	-6(%edx), %ebx
	incl	%eax
	movl	%eax, _cntprog
	cmpl	$9, %ebx
	setbe	%cl
	movzbl	%cl, %eax
	jmp	L820
L660:
	movl	_cntprog, %eax
	xorl	%ecx, %ecx
	movl	%ecx, _lastcall
	movl	_numero, %ecx
	leal	1(%eax), %edx
	movb	$1, _prog(%eax)
	jmp	L669
L736:
	movl	$1903127650, %ebx
	movl	$1830839669, %esi
	movl	$1663069281, %edi
	movl	%ebx, _error
	movl	$1634890341, %eax
	movl	$28516, %edx
	movl	%esi, _error+4
	movl	%edi, _error+8
	movl	%eax, _error+12
	movw	%dx, _error+16
L803:
	movb	$0, _error+18
	jmp	L405
L485:
	cmpl	$4, -548(%ebp)
	jne	L481
	movl	%edx, _dato(%eax)
	jmp	L481
L483:
	movw	%dx, _dato(%eax)
	jmp	L481
L861:
	negl	%edx
	movl	%edx, _numero
	jmp	L644
L853:
	movl	_cntprog, %eax
	xorl	%esi, %esi
	movl	%esi, _lastcall
	movb	$2, _prog(%eax)
	jmp	L793
L740:
	movl	-584(%ebp), %edx
	movl	%edx, 8(%esp)
	jmp	L801
L854:
	movl	_cntprog, %eax
	xorl	%esi, %esi
	movl	%esi, _lastcall
	movb	$2, _prog(%eax)
	jmp	L791
L860:
	movl	_lastcall, %eax
	testl	%eax, %eax
	je	L537
	movb	$4, (%eax)
	xorl	%ecx, %ecx
	incl	%edi
	movl	%ecx, _lastcall
	jmp	L830
L596:
	movl	%edx, _cntpila
	movl	$1713383465, %ecx
	movl	$1635019873, %edx
	movl	%ecx, _error
	movl	$1852793632, %ebx
	movl	$1768122724, %edi
	movl	%edx, _error+4
	movl	$28271, %esi
	movl	%ebx, _error+8
	movl	%edi, _error+12
	movw	%si, _error+16
	jmp	L803
L526:
	movl	%esi, 8(%esp)
	movl	$LC124, %edi
	movl	%edi, 4(%esp)
	jmp	L807
L859:
	movl	_cntpila, %ebx
	movl	$1, %ecx
	movl	_cntprog, %edx
	movl	%ecx, _pila+4(,%ebx,4)
	movl	%edx, _pila(,%ebx,4)
	addl	$2, %ebx
	movl	%ebx, _cntpila
L808:
	incl	%edx
	movl	%edx, _cntprog
	jmp	L798
L743:
	movl	%edx, _cntpila
	movl	$1830837595, %edi
	movl	%edi, _error
L802:
	movl	$1663069281, %ebx
	movl	$1634890341, %esi
	movl	%ebx, _error+4
	movl	%esi, _error+8
L804:
	movl	$28516, %ecx
	movw	%cx, _error+12
L806:
	movb	$0, _error+14
	jmp	L405
L594:
	movl	%esi, _cntpila
	movl	$1830823977, %eax
	movl	%eax, _error
	jmp	L802
L856:
	leal	-2(%ebx), %ecx
	movl	-552(%ebp), %eax
	movl	_pila(,%ecx,4), %edx
	movl	%ecx, _cntpila
	testl	%eax, %eax
	movl	%edx, -588(%ebp)
	jne	L586
	movl	%ebx, _cntpila
	movl	_cntprog, %edx
	xorl	%eax, %eax
	movl	%eax, _lastcall
	leal	1(%edx), %eax
	movb	$5, _prog(%edx)
	addl	$2, %edx
	movl	%eax, _pila(,%ecx,4)
	movb	%dl, %al
	movl	%edx, _cntprog
	movl	-588(%ebp), %edx
	movl	$1, %ecx
	subb	-588(%ebp), %al
	movl	%ecx, _pila(,%esi,4)
	decb	%al
	jmp	L796
L573:
	movl	%edx, _cntpila
L805:
	xorl	%ecx, %ecx
	movl	$1634541609, %edx
	movl	$1700995180, %ebx
	movl	%ecx, _lastcall
	movl	$1684107890, %eax
	movl	$111, %edi
	movl	%edx, _error
	movl	%ebx, _error+4
	movl	%eax, _error+8
	movw	%di, _error+12
	jmp	L405
L858:
	cmpl	$1, -552(%ebp)
	leal	-2(%ebx), %ecx
	movl	_pila(,%ecx,4), %ebx
	movl	%ecx, _cntpila
	je	L862
	movl	_cntprog, %eax
	movb	%bl, %dl
	xorl	%esi, %esi
	movl	%esi, _lastcall
	leal	1(%eax), %ecx
	subb	%cl, %dl
	movb	$5, _prog(%eax)
	decb	%dl
	addl	$2, %eax
	movb	%dl, _prog(%ecx)
	jmp	L797
L857:
	leal	-2(%ebx), %ecx
	movl	-552(%ebp), %ebx
	xorl	%eax, %eax
	movl	%eax, _lastcall
	movl	_pila(,%ecx,4), %edx
	testl	%ebx, %ebx
	movl	%ecx, _cntpila
	je	L809
	movl	$539566143, %ebx
	movl	$1981837166, %esi
	movl	$1684630625, %edx
	movl	%ebx, _error
	movl	$8303, %edi
	movl	%esi, _error+4
	movl	%edx, _error+8
	movw	%di, _error+12
	jmp	L806
L862:
	xorl	%edx, %edx
	movb	%bl, %al
	movl	%edx, _lastcall
	movl	_cntprog, %edx
	subb	%dl, %al
	decb	%al
	movb	%al, _prog(%edx)
	jmp	L808
L586:
	movl	$673783871, %ebx
	movl	$544173600, %edi
	movl	$1768710518, %esi
	movl	%ebx, _error
	movl	%edi, _error+4
	movl	%esi, _error+8
	jmp	L804
	.section .rdata,"dr"
LC126:
	.ascii "w+\0"
LC127:
	.ascii "debug.err\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z10grabalineav
	.def	__Z10grabalineav;	.scl	2;	.type	32;	.endef
__Z10grabalineav:
	pushl	%ebp
	movl	$LC126, %eax
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	%eax, 4(%esp)
	movl	$LC127, (%esp)
	call	_fopen
	testl	%eax, %eax
	movl	%eax, %ebx
	je	L863
	movl	%eax, 4(%esp)
	movl	$_error, (%esp)
	call	_fputs
	movl	%ebx, (%esp)
	call	_fclose
L863:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC128:
	.ascii "\12******* %s *******\12\0"
LC129:
	.ascii "pila compilador %d\12\0"
LC130:
	.ascii "boot: %d\12\0"
	.align 4
LC131:
	.ascii "** locales cnt:%d nom:%d bytes\12\0"
LC132:
	.ascii "%s \0"
	.align 4
LC133:
	.ascii "\12** export cnt:%d nom:%d bytes\12\0"
	.align 4
LC134:
	.ascii "\12includes:%d\12dato:%d bytes\12prog:%d bytes\0"
LC135:
	.ascii "\12====================\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z7dumpmemv
	.def	__Z7dumpmemv;	.scl	2;	.type	32;	.endef
__Z7dumpmemv:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	$_linea, %esi
	pushl	%ebx
	subl	$16, %esp
	movl	%esi, 4(%esp)
	xorl	%esi, %esi
	movl	$LC128, (%esp)
	call	_printf
	movl	$LC129, (%esp)
	movl	_cntpila, %ebx
	movl	%ebx, 4(%esp)
	call	_printf
	movl	$LC130, (%esp)
	movl	_bootaddr, %ecx
	movl	%ecx, 4(%esp)
	call	_printf
	movl	$LC131, (%esp)
	movl	_cntnombre, %edx
	movl	_cntindice, %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	call	_printf
	cmpl	_cntindice, %esi
	jge	L876
	movl	$_indice, %ebx
	.p2align 4,,15
L870:
	movl	(%ebx), %eax
	incl	%esi
	addl	$12, %ebx
	movl	$LC132, (%esp)
	movl	%eax, 4(%esp)
	call	_printf
	cmpl	_cntindice, %esi
	jl	L870
L876:
	movl	$LC133, (%esp)
	movl	_cntnombreex, %ecx
	xorl	%esi, %esi
	movl	_cntindiceex, %edx
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	call	_printf
	cmpl	_cntindiceex, %esi
	jge	L878
	movl	$_indiceex, %ebx
	.p2align 4,,15
L874:
	movl	(%ebx), %eax
	incl	%esi
	addl	$12, %ebx
	movl	$LC132, (%esp)
	movl	%eax, 4(%esp)
	call	_printf
	cmpl	_cntindiceex, %esi
	jl	L874
L878:
	movl	$LC134, (%esp)
	movl	_cntprog, %edx
	movl	_cntdato, %esi
	movl	_cntincludes, %ebx
	movl	%edx, 12(%esp)
	movl	%esi, 8(%esp)
	movl	%ebx, 4(%esp)
	call	_printf
	movl	$LC135, (%esp)
	call	_puts
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z7WndProcP6HWND__jjl@16
	.def	__Z7WndProcP6HWND__jjl@16;	.scl	2;	.type	32;	.endef
__Z7WndProcP6HWND__jjl@16:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	12(%ebp), %edx
	movl	8(%ebp), %ebx
	movl	16(%ebp), %eax
	cmpl	$513, %edx
	movl	20(%ebp), %ecx
	je	L890
	ja	L898
	cmpl	$256, %edx
	je	L892
	jbe	L903
	cmpl	$257, %edx
	je	L891
	cmpl	$512, %edx
	je	L904
	.p2align 4,,15
L897:
	movl	%ebx, 8(%ebp)
	movl	-4(%ebp), %ebx
	movl	%ecx, 20(%ebp)
	movl	%eax, 16(%ebp)
	movl	%edx, 12(%ebp)
	leave
	jmp	_DefWindowProcA@16
	.p2align 4,,7
L898:
	cmpl	$517, %edx
	je	L887
	ja	L900
	cmpl	$514, %edx
	je	L887
	cmpl	$516, %edx
	jne	L897
	.p2align 4,,15
L890:
	andl	$3, %eax
	movl	%eax, _SYSBM
	movl	_SYSMS, %eax
L902:
	movl	%eax, _SYSEVENT
L882:
	movl	-4(%ebp), %ebx
	xorl	%eax, %eax
	leave
	ret	$16
	.p2align 4,,7
L903:
	cmpl	$2, %edx
	je	L896
	cmpl	$28, %edx
	jne	L897
	andl	$255, %eax
	testl	%eax, %eax
	movl	%eax, _active
	jne	L894
	movl	$0, (%esp)
	xorl	%eax, %eax
	movl	%eax, 4(%esp)
	call	_ChangeDisplaySettingsA@8
	subl	$8, %esp
	movl	$6, %ecx
	movl	%ecx, 4(%esp)
	movl	%ebx, (%esp)
	call	_ShowWindow@8
	subl	$8, %esp
	jmp	L882
	.p2align 4,,7
L900:
	cmpl	$519, %edx
	je	L890
	cmpl	$520, %edx
	jne	L897
	.p2align 4,,15
L887:
	andl	$3, %eax
	movl	%eax, _SYSBM
	movl	_SYSME, %eax
	jmp	L902
	.p2align 4,,7
L892:
	movl	%ecx, %edx
	sarl	$16, %edx
	andl	$127, %edx
	movl	%edx, _SYSKEY
	movl	_SYSKEYM(,%edx,4), %eax
	jmp	L902
L891:
	movl	%ecx, %eax
	sarl	$16, %eax
	andl	$127, %eax
	movl	%eax, _SYSKEY
	movl	_SYSKEYM+512(,%eax,4), %eax
	jmp	L902
L904:
	cmpl	%ecx, _SYSXYM
	je	L882
	movl	%ecx, _SYSXYM
	movl	_SYSMM, %eax
	jmp	L902
L896:
	movl	$0, (%esp)
	call	_PostQuitMessage@4
	subl	$4, %esp
	jmp	L882
L894:
	movl	%ebx, (%esp)
	movl	$1, %edx
	movl	%edx, 4(%esp)
	call	_ShowWindow@8
	subl	$8, %esp
	movl	%ebx, (%esp)
	call	_UpdateWindow@4
	subl	$4, %esp
	jmp	L882
	.align 2
	.p2align 4,,15
.globl __Z11clearkeymapv
	.def	__Z11clearkeymapv;	.scl	2;	.type	32;	.endef
__Z11clearkeymapv:
	pushl	%ebp
	movl	$_SYSKEYM, %edx
	movl	%esp, %ebp
	movl	$254, %eax
	.p2align 4,,15
L909:
	movl	$0, (%edx)
	addl	$4, %edx
	decl	%eax
	jns	L909
	popl	%ebp
	ret
	.section .rdata,"dr"
LC136:
	.ascii "NO BOOT|0|%s\0"
	.text
	.align 2
	.p2align 4,,15
.globl _WinMain@16
	.def	_WinMain@16;	.scl	2;	.type	32;	.endef
_WinMain@16:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	pushl	%ebx
	movl	$48, %eax
	subl	$52, %esp
	movl	%ecx, _wc+4
	movl	_znam, %edx
	movl	$__Z7WndProcP6HWND__jjl@16, %ecx
	movl	%eax, _wc
	movl	8(%ebp), %ebx
	xorl	%eax, %eax
	movl	%edx, _wc+40
	xorl	%edx, %edx
	movl	%ecx, _wc+8
	movl	$32512, %ecx
	movl	%edx, _wc+24
	movl	%ecx, 4(%esp)
	movl	%ebx, _wc+20
	movl	%eax, _wc+44
	movl	$0, (%esp)
	call	_LoadCursorA@8
	movl	%eax, _wc+28
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	movl	%edx, _wc+32
	subl	$8, %esp
	xorl	%eax, %eax
	movl	%ecx, _wc+12
	xorl	%edx, %edx
	movl	%eax, _wc+36
	movl	%edx, _wc+16
	movl	$_wc, (%esp)
	call	_RegisterClassExA@4
	subl	$4, %esp
	xorl	%ecx, %ecx
	testw	%ax, %ax
	jne	L960
L914:
	movl	-4(%ebp), %ebx
	movl	%ecx, %eax
	leave
	ret	$16
L960:
	movl	%ebx, 40(%esp)
	movl	$1024, %ebx
	xorl	%eax, %eax
	movl	%ebx, 24(%esp)
	movl	_znam, %ebx
	xorl	%ecx, %ecx
	movl	%eax, 44(%esp)
	xorl	%edx, %edx
	movl	$768, %eax
	movl	%ecx, 36(%esp)
	xorl	%ecx, %ecx
	movl	%edx, 32(%esp)
	xorl	%edx, %edx
	movl	%eax, 28(%esp)
	movl	$-1879048192, %eax
	movl	%ecx, 20(%esp)
	movl	%edx, 16(%esp)
	movl	%eax, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	%ebx, 4(%esp)
	movl	$0, (%esp)
	call	_CreateWindowExA@48
	movl	%eax, _hWnd
	subl	$48, %esp
	xorl	%ecx, %ecx
	testl	%eax, %eax
	movl	%eax, %edx
	je	L914
	movl	%edx, (%esp)
	movl	20(%ebp), %eax
	movl	$32, %ebx
	movl	%eax, 4(%esp)
	call	_ShowWindow@8
	movl	_hWnd, %ecx
	subl	$8, %esp
	movl	%ecx, (%esp)
	call	_UpdateWindow@4
	subl	$4, %esp
	call	__Z6gr_iniv
	movl	%ebx, 4(%esp)
	xorl	%edx, %edx
	movl	%edx, 8(%esp)
	movl	$44100, (%esp)
	call	_FSOUND_Init@12
	subl	$12, %esp
	testb	%al, %al
	movl	$1, %ecx
	je	L914
	movl	$_pathdata, (%esp)
	xorl	%ebx, %ebx
	movl	$3092270, %edx
	movl	%ebx, _cntindex
	movl	$_mindice, %ebx
	movl	%edx, _pathdata
	call	_opendir
	movl	%eax, _dp
	testl	%eax, %eax
	je	L925
L952:
	movl	%eax, (%esp)
	call	_readdir
	movl	%eax, _ep
	testl	%eax, %eax
	je	L961
	movl	%ebx, (%esp)
	addl	$8, %eax
	movl	%eax, 4(%esp)
	call	_strcpy
	movl	_cntindex, %ecx
	movl	%ebx, _indexdir(,%ecx,4)
	incl	%ecx
	movl	%ecx, _cntindex
	jmp	L956
L962:
	incl	%ebx
L956:
	cmpb	$0, (%ebx)
	jne	L962
	movl	_dp, %eax
	incl	%ebx
	jmp	L952
L961:
	movl	_dp, %eax
	movl	%eax, (%esp)
	call	_closedir
L925:
	movb	$0, _linea+8
	movl	$1852399981, %edx
	movl	$1954051118, %ebx
	movl	%edx, _linea
	movl	%ebx, _linea+4
L926:
L959:
	movl	$_SYSKEYM, %edx
	movl	$254, %eax
	.p2align 4,,15
L930:
	movl	$0, (%edx)
	addl	$4, %edx
	decl	%eax
	jns	L930
	movl	$_linea, (%esp)
	xorl	%edx, %edx
	xorl	%ebx, %ebx
	movl	%edx, _cntincludes
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	movl	%ebx, _cntnombreex
	xorl	%edx, %edx
	xorl	%ebx, %ebx
	movl	%eax, _cntindiceex
	xorl	%eax, %eax
	movl	%ecx, _cntprog
	xorl	%ecx, %ecx
	movl	%edx, _cntdato
	movl	%ebx, _cntnombre
	movl	%eax, _cntindice
	movl	%ecx, _bootaddr
	call	__Z11compilafilePc
	testl	%eax, %eax
	jne	L963
	movl	_bootaddr, %eax
	testl	%eax, %eax
	jne	L937
	movl	$_error, (%esp)
	movl	$_linea, %edx
	movl	$LC136, %ebx
	movl	%edx, 8(%esp)
	movl	%ebx, 4(%esp)
	call	_sprintf
	movl	$LC127, (%esp)
	movl	$LC126, %eax
	movl	%eax, 4(%esp)
	call	_fopen
	testl	%eax, %eax
	movl	%eax, %ebx
	je	L939
	movl	%eax, 4(%esp)
	movl	$_error, (%esp)
	call	_fputs
	movl	%ebx, (%esp)
	call	_fclose
L939:
	movl	$_linea, (%esp)
	movl	_NDEBUG, %ebx
	movl	%ebx, 4(%esp)
	call	_strcmp
L958:
	testl	%eax, %eax
	je	L964
	movl	%ebx, 4(%esp)
	movl	$_linea, (%esp)
	call	_strcpy
	jmp	L959
L937:
	movl	%eax, (%esp)
	xorl	%ecx, %ecx
	movl	%ecx, _SYSEVENT
	call	__Z10interpretePh
	decl	%eax
	je	L959
	call	__Z6gr_finv
	movl	_wc+20, %ebx
	movl	_znam, %eax
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	_UnregisterClassA@8
	subl	$8, %esp
	call	_FSOUND_Close@0
	xorl	%ecx, %ecx
	jmp	L914
	.p2align 4,,7
L963:
	movl	$LC127, (%esp)
	movl	$LC126, %ecx
	movl	%ecx, 4(%esp)
	call	_fopen
	testl	%eax, %eax
	movl	%eax, %ebx
	je	L934
	movl	%eax, 4(%esp)
	movl	$_error, (%esp)
	call	_fputs
	movl	%ebx, (%esp)
	call	_fclose
L934:
	movl	$_linea, (%esp)
	movl	_NDEBUG, %ebx
	movl	%ebx, 4(%esp)
	call	_strcmp
	jmp	L958
L964:
	movl	$1, %ecx
	jmp	L914
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	__Z6gr_finv;	.scl	3;	.type	32;	.endef
	.def	__Z6gr_iniv;	.scl	3;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fputs;	.scl	2;	.type	32;	.endef
	.def	_toupper;	.scl	3;	.type	32;	.endef
	.def	_fgets;	.scl	3;	.type	32;	.endef
	.def	_tolower;	.scl	3;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	3;	.type	32;	.endef
	.def	_fread;	.scl	3;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	__Z11gr_drawPoliv;	.scl	3;	.type	32;	.endef
	.def	__Z10gr_psplineiiiiii;	.scl	3;	.type	32;	.endef
	.def	__Z12gr_psegmentoiiii;	.scl	3;	.type	32;	.endef
	.def	__Z9gr_splineiiiiii;	.scl	3;	.type	32;	.endef
	.def	__Z7gr_lineiiii;	.scl	3;	.type	32;	.endef
	.def	__Z8gr_alphav;	.scl	3;	.type	32;	.endef
	.def	__Z8gr_solidv;	.scl	3;	.type	32;	.endef
	.def	__Z10gr_restorev;	.scl	3;	.type	32;	.endef
	.def	__Z6redrawv;	.scl	3;	.type	32;	.endef
	.def	_localtime;	.scl	3;	.type	32;	.endef
	.def	_time;	.scl	3;	.type	32;	.endef
	.def	_closedir;	.scl	3;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_readdir;	.scl	3;	.type	32;	.endef
	.def	_opendir;	.scl	3;	.type	32;	.endef
	.def	_fopen;	.scl	3;	.type	32;	.endef
