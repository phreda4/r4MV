	.file	"graf.cpp"
.globl _ddsd
	.bss
	.align 32
_ddsd:
	.space 124
.globl _g_lpddsBack
	.align 4
_g_lpddsBack:
	.space 4
.globl _g_lpddsPrimary
	.align 4
_g_lpddsPrimary:
	.space 4
.globl _g_lpdd7
	.align 4
_g_lpdd7:
	.space 4
.globl _hWnd
	.align 4
_hWnd:
	.space 4
.globl _wc
	.align 32
_wc:
	.space 48
.globl _height
	.data
	.align 4
_height:
	.long	768
.globl _width
	.align 4
_width:
	.long	1024
.globl _gr_pixela
	.bss
	.align 4
_gr_pixela:
	.space 4
.globl _gr_pixel
	.align 4
_gr_pixel:
	.space 4
.globl _gr_alphav
_gr_alphav:
	.space 1
.globl _gr_buffer
	.align 32
_gr_buffer:
	.space 3145728
.globl _gr_seg
	.align 32
_gr_seg:
	.space 20480
.globl _gr_lines
	.align 32
_gr_lines:
	.space 4096
.globl _gr_linact
	.align 4
_gr_linact:
	.space 4
.globl _gr_limymax
	.align 4
_gr_limymax:
	.space 4
.globl _gr_limymin
	.align 4
_gr_limymin:
	.space 4
.globl _gr_color2
	.align 4
_gr_color2:
	.space 4
.globl _gr_color1
	.align 4
_gr_color1:
	.space 4
.globl _IID_IDirectDrawGammaControl
	.section .rdata,"dr"
	.align 4
_IID_IDirectDrawGammaControl:
	.long	1774263358
	.word	-19349
	.word	4561
	.byte	-83
	.byte	122
	.byte	0
	.byte	-64
	.byte	79
	.byte	-62
	.byte	-101
	.byte	78
.globl _IID_IDirectDrawColorControl
	.align 4
_IID_IDirectDrawColorControl:
	.long	1268715232
	.word	3454
	.word	4560
	.byte	-101
	.byte	6
	.byte	0
	.byte	-96
	.byte	-55
	.byte	3
	.byte	-93
	.byte	-72
.globl _IID_IDirectDrawClipper
	.align 4
_IID_IDirectDrawClipper:
	.long	1813306245
	.word	-22733
	.word	4558
	.byte	-91
	.byte	33
	.byte	0
	.byte	32
	.byte	-81
	.byte	11
	.byte	-27
	.byte	96
.globl _IID_IDirectDrawPalette
	.align 4
_IID_IDirectDrawPalette:
	.long	1813306244
	.word	-22733
	.word	4558
	.byte	-91
	.byte	33
	.byte	0
	.byte	32
	.byte	-81
	.byte	11
	.byte	-27
	.byte	96
.globl _IID_IDirectDrawSurface7
	.align 4
_IID_IDirectDrawSurface7:
	.long	107436672
	.word	15259
	.word	4562
	.byte	-71
	.byte	47
	.byte	0
	.byte	96
	.byte	-105
	.byte	-105
	.byte	-22
	.byte	91
.globl _IID_IDirectDrawSurface4
	.align 4
_IID_IDirectDrawSurface4:
	.long	187401776
	.word	-21195
	.word	4560
	.byte	-114
	.byte	-90
	.byte	0
	.byte	96
	.byte	-105
	.byte	-105
	.byte	-22
	.byte	91
.globl _IID_IDirectDrawSurface3
	.align 4
_IID_IDirectDrawSurface3:
	.long	-637252096
	.word	27058
	.word	4560
	.byte	-95
	.byte	-43
	.byte	0
	.byte	-86
	.byte	0
	.byte	-72
	.byte	-33
	.byte	-69
.globl _IID_IDirectDrawSurface2
	.align 4
_IID_IDirectDrawSurface2:
	.long	1468029061
	.word	28396
	.word	4559
	.byte	-108
	.byte	65
	.byte	-88
	.byte	35
	.byte	3
	.byte	-63
	.byte	14
	.byte	39
.globl _IID_IDirectDrawSurface
	.align 4
_IID_IDirectDrawSurface:
	.long	1813306241
	.word	-22733
	.word	4558
	.byte	-91
	.byte	33
	.byte	0
	.byte	32
	.byte	-81
	.byte	11
	.byte	-27
	.byte	96
.globl _IID_IDirectDraw7
	.align 4
_IID_IDirectDraw7:
	.long	367419072
	.word	15260
	.word	4562
	.byte	-71
	.byte	47
	.byte	0
	.byte	96
	.byte	-105
	.byte	-105
	.byte	-22
	.byte	91
.globl _IID_IDirectDraw4
	.align 4
_IID_IDirectDraw4:
	.long	-1671868262
	.word	14781
	.word	4561
	.byte	-116
	.byte	74
	.byte	0
	.byte	-64
	.byte	79
	.byte	-39
	.byte	48
	.byte	-59
.globl _IID_IDirectDraw2
	.align 4
_IID_IDirectDraw2:
	.long	-1280904224
	.word	11075
	.word	4559
	.byte	-94
	.byte	-34
	.byte	0
	.byte	-86
	.byte	0
	.byte	-71
	.byte	51
	.byte	86
.globl _IID_IDirectDraw
	.align 4
_IID_IDirectDraw:
	.long	1813306240
	.word	-22733
	.word	4558
	.byte	-91
	.byte	33
	.byte	0
	.byte	32
	.byte	-81
	.byte	11
	.byte	-27
	.byte	96
.globl _CLSID_DirectDrawClipper
	.align 4
_CLSID_DirectDrawClipper:
	.long	1496848288
	.word	32179
	.word	4559
	.byte	-94
	.byte	-34
	.byte	0
	.byte	-86
	.byte	0
	.byte	-71
	.byte	51
	.byte	86
.globl _CLSID_DirectDraw7
	.align 4
_CLSID_DirectDraw7:
	.long	1009799574
	.word	20699
	.word	4563
	.byte	-100
	.byte	-2
	.byte	0
	.byte	-64
	.byte	79
	.byte	-39
	.byte	48
	.byte	-59
.globl _CLSID_DirectDraw
	.align 4
_CLSID_DirectDraw:
	.long	-675868960
	.word	17216
	.word	4559
	.byte	-80
	.byte	99
	.byte	0
	.byte	32
	.byte	-81
	.byte	-62
	.byte	-51
	.byte	53
	.text
	.align 2
	.p2align 4,,15
.globl __Z10_gr_pixelsPm
	.def	__Z10_gr_pixelsPm;	.scl	2;	.type	32;	.endef
__Z10_gr_pixelsPm:
	pushl	%ebp
	movl	_gr_color1, %edx
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z10_gr_pixelaPmh
	.def	__Z10_gr_pixelaPmh;	.scl	2;	.type	32;	.endef
__Z10_gr_pixelaPmh:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	%edi, 8(%esp)
	movl	8(%ebp), %edi
	movl	_gr_color1, %eax
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	movl	(%edi), %ecx
	movl	%eax, %edx
	movzbl	12(%ebp), %esi
	andl	$16711935, %edx
	andl	$65280, %eax
	movl	%ecx, %ebx
	andl	$16711935, %ebx
	andl	$65280, %ecx
	subl	%ebx, %edx
	subl	%ecx, %eax
	imull	%esi, %edx
	imull	%esi, %eax
	shrl	$8, %edx
	shrl	$8, %eax
	addl	%ebx, %edx
	addl	%ecx, %eax
	andl	$16711935, %edx
	andl	$65280, %eax
	orl	%edx, %eax
	movl	%eax, (%edi)
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	8(%esp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11_gr_pixelsaPm
	.def	__Z11_gr_pixelsaPm;	.scl	2;	.type	32;	.endef
__Z11_gr_pixelsaPm:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	%edi, 8(%esp)
	movl	8(%ebp), %edi
	movl	_gr_color1, %eax
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	movl	(%edi), %ecx
	movl	%eax, %edx
	movzbl	_gr_alphav, %esi
	andl	$16711935, %edx
	andl	$65280, %eax
	movl	%ecx, %ebx
	andl	$16711935, %ebx
	andl	$65280, %ecx
	subl	%ebx, %edx
	subl	%ecx, %eax
	imull	%esi, %edx
	imull	%esi, %eax
	shrl	$8, %edx
	shrl	$8, %eax
	addl	%ebx, %edx
	addl	%ecx, %eax
	andl	$16711935, %edx
	andl	$65280, %eax
	orl	%edx, %eax
	movl	%eax, (%edi)
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	8(%esp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11_gr_pixelaaPmh
	.def	__Z11_gr_pixelaaPmh;	.scl	2;	.type	32;	.endef
__Z11_gr_pixelaaPmh:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movzbl	12(%ebp), %eax
	movzbl	_gr_alphav, %edx
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %esi
	movl	%ebx, -12(%ebp)
	imull	%edx, %eax
	movl	%edi, -4(%ebp)
	movl	(%esi), %edi
	movl	%eax, %ecx
	movl	_gr_color1, %eax
	movl	%edi, %ebx
	shrl	$8, %ecx
	andl	$65280, %edi
	andl	$16711935, %ebx
	movzbl	%cl, %esi
	movl	%edi, -16(%ebp)
	movl	%eax, %edx
	andl	$16711935, %edx
	andl	$65280, %eax
	subl	%ebx, %edx
	subl	%edi, %eax
	imull	%esi, %edx
	imull	%esi, %eax
	shrl	$8, %edx
	shrl	$8, %eax
	addl	%ebx, %edx
	addl	%edi, %eax
	andl	$16711935, %edx
	andl	$65280, %eax
	orl	%edx, %eax
	movl	8(%ebp), %edx
	movl	%eax, (%edx)
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_solidv
	.def	__Z8gr_solidv;	.scl	2;	.type	32;	.endef
__Z8gr_solidv:
	pushl	%ebp
	movl	$__Z10_gr_pixelsPm, %edx
	movl	%esp, %ebp
	popl	%ebp
	movl	$__Z10_gr_pixelaPmh, %eax
	movl	%edx, _gr_pixel
	movl	%eax, _gr_pixela
	movb	$-1, _gr_alphav
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_alphav
	.def	__Z8gr_alphav;	.scl	2;	.type	32;	.endef
__Z8gr_alphav:
	pushl	%ebp
	movl	$__Z11_gr_pixelsaPm, %eax
	movl	%esp, %ebp
	popl	%ebp
	movl	$__Z11_gr_pixelaaPmh, %ecx
	movl	%eax, _gr_pixel
	movl	%ecx, _gr_pixela
	ret
	.align 2
	.p2align 4,,15
.globl __Z9gr_hlinediiihh
	.def	__Z9gr_hlinediiihh;	.scl	2;	.type	32;	.endef
__Z9gr_hlinediiihh:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	16(%ebp), %edi
	movzbl	20(%ebp), %ebx
	movl	8(%ebp), %ecx
	movl	%edi, %edx
	movzbl	24(%ebp), %eax
	subl	%ecx, %edx
	movl	%ebx, %esi
	sall	$8, %esi
	subl	%ebx, %eax
	sall	$8, %eax
	movl	%eax, -20(%ebp)
	movl	%edx, %ebx
	cltd
	idivl	%ebx
	testl	%ecx, %ecx
	movl	%eax, -16(%ebp)
	js	L20
L11:
	cmpl	$1023, %edi
	jle	L12
	cmpl	$1023, %ecx
	movl	$1023, %edi
	jg	L10
L12:
	sall	$10, 12(%ebp)
	movl	12(%ebp), %edx
	addl	%ecx, %edx
	leal	_gr_buffer(,%edx,4), %ebx
	leal	(%ebx,%edi,4), %eax
	leal	0(,%ecx,4), %edi
	subl	%edi, %eax
	leal	4(%eax), %edi
	.p2align 4,,15
L14:
	movl	%ebx, (%esp)
	movl	%esi, %edx
	movzbl	%dh, %eax
	movl	%eax, 4(%esp)
	addl	$4, %ebx
	call	*_gr_pixela
	movl	-16(%ebp), %ecx
	addl	%ecx, %esi
	cmpl	%edi, %ebx
	jb	L14
L10:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L20:
	imull	%eax, %ecx
	subl	%ecx, %esi
	xorl	%ecx, %ecx
	jmp	L11
	.align 2
	.p2align 4,,15
.globl __Z9gr_vlinediiihh
	.def	__Z9gr_vlinediiihh;	.scl	2;	.type	32;	.endef
__Z9gr_vlinediiihh:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	16(%ebp), %ecx
	movzbl	20(%ebp), %edx
	movl	12(%ebp), %edi
	movl	%ecx, %eax
	movzbl	24(%ebp), %ebx
	subl	%edi, %eax
	movl	%edx, %esi
	movl	%eax, -20(%ebp)
	sall	$8, %esi
	subl	%edx, %ebx
	sall	$8, %ebx
	movl	%ebx, %eax
	cltd
	idivl	-20(%ebp)
	testl	%edi, %edi
	movl	%eax, -16(%ebp)
	js	L30
L22:
	cmpl	$767, %ecx
	jle	L23
	cmpl	$767, %edi
	movl	$767, %ecx
	jg	L21
L23:
	movl	8(%ebp), %ebx
	movl	%edi, %eax
	subl	%edi, %ecx
	sall	$10, %eax
	sall	$12, %ecx
	addl	%ebx, %eax
	leal	_gr_buffer(,%eax,4), %ebx
	leal	4096(%ecx,%ebx), %edi
	.p2align 4,,15
L25:
	movl	%ebx, (%esp)
	movl	%esi, %edx
	movzbl	%dh, %eax
	movl	%eax, 4(%esp)
	addl	$4096, %ebx
	call	*_gr_pixela
	movl	-16(%ebp), %ecx
	addl	%ecx, %esi
	cmpl	%edi, %ebx
	jb	L25
L21:
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L30:
	imull	%eax, %edi
	subl	%edi, %esi
	xorl	%edi, %edi
	jmp	L22
	.align 2
	.p2align 4,,15
.globl __Z8gr_hlineiii
	.def	__Z8gr_hlineiii;	.scl	2;	.type	32;	.endef
__Z8gr_hlineiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %edx
	movl	16(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	%edx, %eax
	notl	%eax
	movl	%eax, %ecx
	sarl	$31, %ecx
	andl	%edx, %ecx
	cmpl	$1023, %esi
	jle	L33
	cmpl	$1023, %ecx
	movl	$1023, %esi
	jg	L31
L33:
	sall	$10, %ebx
	leal	(%ebx,%ecx), %edx
	leal	_gr_buffer(,%edx,4), %ebx
	leal	(%ebx,%esi,4), %eax
	leal	0(,%ecx,4), %esi
	subl	%esi, %eax
	leal	4(%eax), %esi
	.p2align 4,,15
L35:
	movl	%ebx, (%esp)
	addl	$4, %ebx
	call	*_gr_pixel
	cmpl	%esi, %ebx
	jb	L35
L31:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_vlineiii
	.def	__Z8gr_vlineiii;	.scl	2;	.type	32;	.endef
__Z8gr_vlineiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	12(%ebp), %edx
	movl	16(%ebp), %ecx
	movl	%edx, %eax
	notl	%eax
	movl	%eax, %esi
	sarl	$31, %esi
	andl	%edx, %esi
	cmpl	$767, %ecx
	jle	L41
	cmpl	$767, %esi
	movl	$767, %ecx
	jg	L39
L41:
	movl	8(%ebp), %ebx
	movl	%esi, %edx
	subl	%esi, %ecx
	sall	$10, %edx
	sall	$12, %ecx
	addl	%ebx, %edx
	leal	_gr_buffer(,%edx,4), %ebx
	leal	4096(%ecx,%ebx), %esi
	.p2align 4,,15
L43:
	movl	%ebx, (%esp)
	addl	$4096, %ebx
	call	*_gr_pixel
	cmpl	%esi, %ebx
	jb	L43
L39:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11gr_cliplinePiS_S_S_
	.def	__Z11gr_cliplinePiS_S_S_;	.scl	2;	.type	32;	.endef
__Z11gr_cliplinePiS_S_S_:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	8(%ebp), %edx
	movl	(%edx), %eax
	movl	%eax, %esi
	shrl	$31, %esi
	movl	%eax, -36(%ebp)
	cmpl	$1023, %eax
	jle	L50
	orl	$2, %esi
L50:
	movl	12(%ebp), %ecx
	movl	(%ecx), %edx
	testl	%edx, %edx
	js	L78
L51:
	cmpl	$766, %edx
	jle	L52
	orl	$8, %esi
L52:
	movl	16(%ebp), %edi
	movl	(%edi), %ebx
	movl	%ebx, %edi
	shrl	$31, %edi
	cmpl	$1023, %ebx
	jle	L55
	orl	$2, %edi
L55:
	movl	20(%ebp), %eax
	movl	(%eax), %ecx
	testl	%ecx, %ecx
	js	L79
L56:
	cmpl	$766, %ecx
	jle	L57
	orl	$8, %edi
L57:
	testl	%edi, %esi
	jne	L58
	movl	%esi, %eax
	orl	%edi, %eax
	je	L58
	testl	$12, %esi
	jne	L80
L59:
	testl	$12, %edi
	je	L65
	movl	20(%ebp), %ebx
	xorl	%eax, %eax
	cmpl	$7, %edi
	movl	16(%ebp), %ecx
	setle	%al
	decl	%eax
	movl	(%ebx), %edi
	andl	$766, %eax
	movl	(%ecx), %ebx
	movl	%eax, -40(%ebp)
	movl	-40(%ebp), %eax
	movl	%ebx, %ecx
	subl	-36(%ebp), %ecx
	subl	%edi, %eax
	subl	%edx, %edi
	imull	%ecx, %eax
	movl	20(%ebp), %ecx
	cltd
	idivl	%edi
	movl	16(%ebp), %edi
	movl	-40(%ebp), %edx
	addl	%eax, %ebx
	movl	%ebx, (%edi)
	movl	%edx, (%ecx)
	movl	(%edi), %ebx
	movl	%ebx, %edi
	shrl	$31, %edi
	cmpl	$1023, %ebx
	jle	L65
	orl	$2, %edi
	.p2align 4,,15
L65:
	testl	%edi, %esi
	jne	L58
	movl	%esi, %edx
	orl	%edi, %edx
	je	L58
	testl	%esi, %esi
	jne	L81
L72:
	testl	%edi, %edi
	je	L58
	movl	16(%ebp), %ebx
	xorl	%eax, %eax
	cmpl	$1, %edi
	movl	20(%ebp), %ecx
	sete	%al
	movl	12(%ebp), %edx
	movl	(%ebx), %edi
	decl	%eax
	movl	(%ecx), %ebx
	andl	$1023, %eax
	movl	%eax, -44(%ebp)
	movl	%ebx, %ecx
	subl	%edi, %eax
	subl	(%edx), %ecx
	imull	%ecx, %eax
	movl	8(%ebp), %ecx
	movl	(%ecx), %edx
	movl	20(%ebp), %ecx
	subl	%edx, %edi
	cltd
	idivl	%edi
	movl	16(%ebp), %edi
	addl	%eax, %ebx
	movl	%ebx, (%ecx)
	movl	-44(%ebp), %ebx
	movl	%ebx, (%edi)
	xorl	%edi, %edi
	.p2align 4,,15
L58:
	orl	%edi, %esi
	sete	%al
	addl	$40, %esp
	popl	%ebx
	movzbl	%al, %eax
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L79:
	orl	$4, %edi
	jmp	L56
	.p2align 4,,7
L78:
	orl	$4, %esi
	jmp	L51
	.p2align 4,,7
L80:
	xorl	%eax, %eax
	cmpl	$7, %esi
	setle	%al
	subl	-36(%ebp), %ebx
	leal	-1(%eax), %esi
	andl	$766, %esi
	movl	%esi, %eax
	subl	%edx, %ecx
	subl	%edx, %eax
	imull	%ebx, %eax
	cltd
	idivl	%ecx
	movl	-36(%ebp), %edx
	movl	8(%ebp), %ecx
	addl	%edx, %eax
	movl	%esi, %edx
	movl	12(%ebp), %esi
	movl	%eax, (%ecx)
	movl	%edx, (%esi)
	movl	(%ecx), %ebx
	movl	%ebx, %esi
	movl	%ebx, -36(%ebp)
	shrl	$31, %esi
	cmpl	$1023, %ebx
	jle	L59
	orl	$2, %esi
	jmp	L59
L81:
	movl	8(%ebp), %eax
	xorl	%ebx, %ebx
	cmpl	$1, %esi
	sete	%bl
	movl	20(%ebp), %ecx
	decl	%ebx
	movl	(%eax), %edx
	andl	$1023, %ebx
	movl	12(%ebp), %eax
	movl	%ebx, %esi
	subl	%edx, %esi
	movl	%esi, -24(%ebp)
	movl	(%ecx), %esi
	movl	(%eax), %ecx
	movl	%edx, -48(%ebp)
	movl	-24(%ebp), %edx
	movl	16(%ebp), %eax
	subl	%ecx, %esi
	imull	%edx, %esi
	movl	-48(%ebp), %edx
	movl	%esi, -24(%ebp)
	movl	(%eax), %esi
	movl	-24(%ebp), %eax
	subl	%edx, %esi
	cltd
	movl	%esi, -52(%ebp)
	movl	8(%ebp), %esi
	idivl	-52(%ebp)
	addl	%eax, %ecx
	movl	12(%ebp), %eax
	movl	%ecx, (%eax)
	movl	%ebx, (%esi)
	xorl	%esi, %esi
	jmp	L72
	.align 2
	.p2align 4,,15
.globl __Z7gr_lineiiii
	.def	__Z7gr_lineiiii;	.scl	2;	.type	32;	.endef
__Z7gr_lineiiii:
	pushl	%ebp
	movl	%esp, %ebp
	leal	16(%ebp), %ecx
	pushl	%edi
	leal	12(%ebp), %edx
	leal	8(%ebp), %eax
	pushl	%esi
	pushl	%ebx
	subl	$92, %esp
	leal	20(%ebp), %ebx
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__Z11gr_cliplinePiS_S_S_
	testb	%al, %al
	je	L82
	movl	8(%ebp), %esi
	movl	16(%ebp), %ecx
	movl	%esi, -60(%ebp)
	cmpl	%ecx, %esi
	je	L135
	movl	12(%ebp), %ebx
	movl	20(%ebp), %edx
	cmpl	%edx, %ebx
	je	L136
	jg	L137
L104:
	movl	$1, -28(%ebp)
	movl	%ecx, %esi
	movl	-60(%ebp), %ecx
	movl	%edx, %edi
	subl	%ebx, %edi
	subl	%ecx, %esi
	testl	%esi, %esi
	jle	L138
L108:
	movl	$0, -32(%ebp)
	movl	-60(%ebp), %edx
	sall	$10, %ebx
	leal	(%ebx,%edx), %eax
	leal	_gr_buffer(,%eax,4), %ebx
	movl	%ebx, (%esp)
	call	*_gr_pixel
	cmpl	%esi, %edi
	jle	L109
	sall	$16, %esi
	movl	%esi, %eax
	cltd
	idivl	%edi
	movzwl	%ax, %esi
	jmp	L132
	.p2align 4,,7
L139:
	movl	8(%ebp), %edx
	movl	-28(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, 8(%ebp)
L112:
	movl	12(%ebp), %ebx
	movl	-32(%ebp), %edx
	incl	%ebx
	movl	%ebx, 12(%ebp)
	shrl	$8, %edx
	movb	%dl, %cl
	movb	%dl, -56(%ebp)
	sall	$10, %ebx
	notb	%cl
	addl	%eax, %ebx
	movzbl	%cl, %edx
	leal	_gr_buffer(,%ebx,4), %ebx
	movl	%ebx, (%esp)
	movl	%edx, 4(%esp)
	call	*_gr_pixela
	movl	-28(%ebp), %eax
	leal	(%ebx,%eax,4), %ecx
	movzbl	-56(%ebp), %ebx
	movl	%ecx, (%esp)
	movl	%ebx, 4(%esp)
	call	*_gr_pixela
L132:
	testl	%edi, %edi
	jle	L82
	movl	-32(%ebp), %ebx
	decl	%edi
	leal	(%ebx,%esi), %eax
	movzwl	%ax, %ecx
	cmpl	%ebx, %ecx
	movl	%ecx, -32(%ebp)
	jle	L139
	movl	8(%ebp), %eax
	jmp	L112
	.p2align 4,,7
L136:
	cmpl	%ecx, -60(%ebp)
	jle	L95
	movl	-60(%ebp), %edx
	xorl	%ecx, %edx
	xorl	%edx, %ecx
	movl	%ecx, 16(%ebp)
	xorl	%ecx, %edx
	movl	%edx, -60(%ebp)
	movl	%edx, 8(%ebp)
L95:
	movl	-60(%ebp), %eax
	movl	-60(%ebp), %esi
	notl	%eax
	cltd
	andl	%esi, %edx
	cmpl	$1023, %ecx
	jle	L98
	cmpl	$1023, %edx
	movl	$1023, %ecx
	jle	L98
	.p2align 4,,15
L82:
	addl	$92, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L135:
	movl	12(%ebp), %ecx
	movl	20(%ebp), %edx
	cmpl	%edx, %ecx
	jle	L85
	movl	%ecx, %edi
	xorl	%edx, %edi
	xorl	%edi, %edx
	movl	%edx, 20(%ebp)
	movl	%edi, %ecx
	xorl	%edx, %ecx
	movl	%ecx, 12(%ebp)
L85:
	movl	%ecx, %eax
	notl	%eax
	movl	%eax, %esi
	sarl	$31, %esi
	andl	%ecx, %esi
	cmpl	$767, %edx
	jle	L88
	cmpl	$767, %esi
	movl	$767, %edx
	jg	L82
L88:
	movl	-60(%ebp), %ecx
	movl	%esi, %edi
	subl	%esi, %edx
	sall	$10, %edi
	sall	$12, %edx
	addl	%ecx, %edi
	leal	_gr_buffer(,%edi,4), %ebx
	leal	4096(%edx,%ebx), %esi
	.p2align 4,,15
L91:
	movl	%ebx, (%esp)
	addl	$4096, %ebx
	call	*_gr_pixel
	cmpl	%esi, %ebx
	jb	L91
	addl	$92, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L137:
	movl	-60(%ebp), %edi
	movl	%ebx, %eax
	xorl	%edx, %eax
	xorl	%eax, %edx
	movl	%eax, %ebx
	xorl	%ecx, %edi
	movl	%edx, 20(%ebp)
	xorl	%edi, %ecx
	xorl	%edx, %ebx
	movl	%ecx, 16(%ebp)
	xorl	%ecx, %edi
	movl	%edi, -60(%ebp)
	movl	%edi, 8(%ebp)
	movl	%ebx, 12(%ebp)
	jmp	L104
	.p2align 4,,7
L109:
	sall	$16, %edi
	movl	%edi, %eax
	cltd
	idivl	%esi
	movzwl	%ax, %edi
	jmp	L133
	.p2align 4,,7
L140:
	movl	12(%ebp), %eax
	incl	%eax
	movl	%eax, 12(%ebp)
L117:
	movl	8(%ebp), %edx
	sall	$10, %eax
	movl	-28(%ebp), %ecx
	addl	%edx, %ecx
	movl	-32(%ebp), %edx
	leal	(%eax,%ecx), %ebx
	movl	%ecx, 8(%ebp)
	leal	_gr_buffer(,%ebx,4), %ebx
	shrl	$8, %edx
	movb	%dl, -88(%ebp)
	movb	%dl, %al
	notb	%al
	movl	%ebx, (%esp)
	movzbl	%al, %ecx
	addl	$4096, %ebx
	movl	%ecx, 4(%esp)
	call	*_gr_pixela
	movzbl	-88(%ebp), %edx
	movl	%ebx, (%esp)
	movl	%edx, 4(%esp)
	call	*_gr_pixela
L133:
	testl	%esi, %esi
	jle	L82
	movl	-32(%ebp), %ebx
	decl	%esi
	leal	(%ebx,%edi), %eax
	movzwl	%ax, %ecx
	cmpl	%ebx, %ecx
	movl	%ecx, -32(%ebp)
	jle	L140
	movl	12(%ebp), %eax
	jmp	L117
L98:
	sall	$10, %ebx
	leal	(%ebx,%edx), %esi
	leal	_gr_buffer(,%esi,4), %ebx
	leal	(%ebx,%ecx,4), %edi
	sall	$2, %edx
	subl	%edx, %edi
	leal	4(%edi), %esi
	.p2align 4,,15
L101:
	movl	%ebx, (%esp)
	addl	$4, %ebx
	call	*_gr_pixel
	cmpl	%esi, %ebx
	jb	L101
	jmp	L82
L138:
	movl	$-1, -28(%ebp)
	negl	%esi
	jmp	L108
	.align 2
	.p2align 4,,15
.globl __Z8gr_plineiiiit
	.def	__Z8gr_plineiiiit;	.scl	2;	.type	32;	.endef
__Z8gr_plineiiiit:
	pushl	%ebp
	movl	%esp, %ebp
	leal	16(%ebp), %ecx
	pushl	%edi
	leal	12(%ebp), %edx
	leal	8(%ebp), %eax
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	leal	20(%ebp), %ebx
	movzwl	24(%ebp), %esi
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%esi, -16(%ebp)
	movl	%eax, (%esp)
	call	__Z11gr_cliplinePiS_S_S_
	testb	%al, %al
	je	L141
	movl	$2, -36(%ebp)
	movl	8(%ebp), %ebx
	xorl	%eax, %eax
	movl	16(%ebp), %ecx
	movl	%ebx, -32(%ebp)
	cmpl	%ecx, %ebx
	setl	%al
	leal	-1(%eax,%eax), %esi
	movl	%ebx, %eax
	subl	%ecx, %eax
	movl	%esi, -48(%ebp)
	cltd
	movl	12(%ebp), %ecx
	movl	20(%ebp), %esi
	xorl	%edx, %eax
	subl	%edx, %eax
	movl	%eax, -40(%ebp)
	xorl	%edx, %edx
	movl	%ecx, %eax
	cmpl	%esi, %ecx
	setl	%dl
	subl	%esi, %eax
	leal	-1(%edx,%edx), %edi
	cltd
	movl	%edx, %esi
	movl	%edi, -44(%ebp)
	xorl	%eax, %esi
	movl	-40(%ebp), %eax
	subl	%edx, %esi
	leal	(%esi,%esi), %edi
	addl	%eax, %eax
	testb	$1, -16(%ebp)
	movl	%edi, -24(%ebp)
	movl	%ecx, %edi
	movl	%eax, -20(%ebp)
	jne	L177
L147:
	cmpl	%esi, -40(%ebp)
	jle	L148
	movl	-40(%ebp), %ecx
	movl	-24(%ebp), %ebx
	movl	-40(%ebp), %edx
	movl	-24(%ebp), %esi
	incl	%ecx
	movl	-20(%ebp), %eax
	subl	%edx, %ebx
	subl	%eax, %esi
	decl	%ecx
	movl	%esi, -28(%ebp)
	jle	L141
	movl	-40(%ebp), %esi
	jmp	L157
	.p2align 4,,7
L154:
	cmpw	$-32768, -36(%ebp)
	je	L178
L155:
	movl	-36(%ebp), %eax
	addl	%eax, %eax
	movzwl	%ax, %ecx
	movl	%ecx, -36(%ebp)
	decl	%esi
	je	L141
L157:
	testl	%ebx, %ebx
	js	L152
	movl	-44(%ebp), %ecx
	movl	-28(%ebp), %eax
	addl	%ecx, %edi
L175:
	addl	%eax, %ebx
	movl	-48(%ebp), %edx
	movl	-36(%ebp), %eax
	addl	%edx, -32(%ebp)
	testl	%eax, -16(%ebp)
	je	L154
	movl	-32(%ebp), %edx
	movl	%edi, %eax
	sall	$10, %eax
	addl	%edx, %eax
	leal	_gr_buffer(,%eax,4), %ecx
	movl	%ecx, (%esp)
	call	*_gr_pixel
	cmpw	$-32768, -36(%ebp)
	jne	L155
	.p2align 4,,15
L178:
	movl	$1, -36(%ebp)
	decl	%esi
	jne	L157
	.p2align 4,,15
L141:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L148:
	movl	-20(%ebp), %ebx
	leal	1(%esi), %edx
	movl	-20(%ebp), %ecx
	movl	-24(%ebp), %eax
	subl	%esi, %ebx
	subl	%eax, %ecx
	movl	%ecx, -52(%ebp)
	decl	%edx
	jle	L141
	testl	%ebx, %ebx
	jns	L179
	.p2align 4,,15
L162:
	movl	-20(%ebp), %eax
	movl	-36(%ebp), %ecx
	addl	%eax, %ebx
	movl	-44(%ebp), %eax
	addl	%eax, %edi
	testl	%ecx, -16(%ebp)
	jne	L180
	.p2align 4,,15
L164:
	cmpw	$-32768, -36(%ebp)
	je	L181
L165:
	movl	-36(%ebp), %ecx
	addl	%ecx, %ecx
	movzwl	%cx, %edx
	movl	%edx, -36(%ebp)
L161:
	decl	%esi
	je	L141
	testl	%ebx, %ebx
	js	L162
L179:
	movl	-52(%ebp), %eax
	movl	-48(%ebp), %edx
	movl	-36(%ebp), %ecx
	addl	%edx, -32(%ebp)
	addl	%eax, %ebx
	movl	-44(%ebp), %eax
	addl	%eax, %edi
	testl	%ecx, -16(%ebp)
	je	L164
L180:
	movl	-32(%ebp), %eax
	movl	%edi, %ecx
	sall	$10, %ecx
	addl	%eax, %ecx
	leal	_gr_buffer(,%ecx,4), %edx
	movl	%edx, (%esp)
	call	*_gr_pixel
	cmpw	$-32768, -36(%ebp)
	jne	L165
	.p2align 4,,15
L181:
	movl	$1, -36(%ebp)
	jmp	L161
	.p2align 4,,7
L177:
	movl	%ecx, %edx
	sall	$10, %edx
	addl	%ebx, %edx
	leal	_gr_buffer(,%edx,4), %ebx
	movl	%ebx, (%esp)
	call	*_gr_pixel
	jmp	L147
	.p2align 4,,7
L152:
	movl	-24(%ebp), %eax
	jmp	L175
	.align 2
	.p2align 4,,15
.globl __Z13gr_splineiteriiiiii
	.def	__Z13gr_splineiteriiiiii;	.scl	2;	.type	32;	.endef
__Z13gr_splineiteriiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %edx
	movl	24(%ebp), %eax
	movl	28(%ebp), %ecx
	movl	%ebx, -16(%ebp)
	movl	16(%ebp), %esi
	movl	20(%ebp), %edi
	movl	%edx, -20(%ebp)
	movl	%eax, -24(%ebp)
	movl	%ecx, -28(%ebp)
	jmp	L185
	.p2align 4,,7
L183:
	movl	-24(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	-28(%ebp), %ebx
	movl	-20(%ebp), %eax
	addl	%esi, %edx
	addl	%ecx, %esi
	movl	%esi, -32(%ebp)
	addl	%edi, %eax
	addl	%ebx, %edi
	sarl	-32(%ebp)
	sarl	%edx
	sarl	%eax
	movl	-32(%ebp), %ecx
	sarl	%edi
	leal	(%eax,%edi), %ebx
	movl	%eax, 12(%esp)
	sarl	%ebx
	leal	(%edx,%ecx), %esi
	movl	%ebx, 20(%esp)
	sarl	%esi
	movl	%esi, 16(%esp)
	movl	%edx, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %edx
	movl	%edx, (%esp)
	call	__Z13gr_splineiteriiiiii
	movl	%esi, -16(%ebp)
	movl	-32(%ebp), %esi
	movl	%ebx, -20(%ebp)
L185:
	movl	-16(%ebp), %ebx
	movl	%esi, %eax
	movl	-20(%ebp), %edx
	movl	-16(%ebp), %ecx
	subl	%ebx, %eax
	movl	%edi, %ebx
	subl	%edx, %ebx
	movl	-24(%ebp), %edx
	subl	%ecx, %edx
	movl	-28(%ebp), %ecx
	imull	%ebx, %edx
	subl	-20(%ebp), %ecx
	imull	%ecx, %eax
	subl	%edx, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cmpl	$999, %eax
	jg	L183
	sarl	$4, -28(%ebp)
	sarl	$4, -24(%ebp)
	sarl	$4, -20(%ebp)
	movl	-28(%ebp), %ecx
	movl	-24(%ebp), %eax
	sarl	$4, -16(%ebp)
	movl	-20(%ebp), %edi
	movl	%ecx, 20(%ebp)
	movl	-16(%ebp), %esi
	movl	%eax, 16(%ebp)
	movl	%edi, 12(%ebp)
	movl	%esi, 8(%ebp)
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	__Z7gr_lineiiii
	.align 2
	.p2align 4,,15
.globl __Z9gr_splineiiiiii
	.def	__Z9gr_splineiiiiii;	.scl	2;	.type	32;	.endef
__Z9gr_splineiiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	%esi, -8(%ebp)
	movl	16(%ebp), %esi
	movl	20(%ebp), %eax
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	24(%ebp), %ecx
	movl	%esi, -20(%ebp)
	sall	$4, %eax
	movl	28(%ebp), %esi
	movl	%edi, -16(%ebp)
	sall	$4, %ecx
	movl	12(%ebp), %edi
	sall	$4, -16(%ebp)
	sall	$4, %esi
	sall	$4, %edi
	sall	$4, -20(%ebp)
	movl	-16(%ebp), %edx
	movl	%eax, -24(%ebp)
	movl	-20(%ebp), %eax
	movl	%ecx, -28(%ebp)
	movl	%ebx, -12(%ebp)
	subl	%edx, %eax
	movl	%ecx, %edx
	movl	-16(%ebp), %ecx
	movl	-24(%ebp), %ebx
	subl	%ecx, %edx
	movl	%esi, %ecx
	subl	%edi, %ebx
	subl	%edi, %ecx
	imull	%ebx, %edx
	imull	%ecx, %eax
	subl	%edx, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cmpl	$999, %eax
	jg	L187
	sarl	$4, -28(%ebp)
	sarl	$4, %esi
	sarl	$4, %edi
	sarl	$4, -16(%ebp)
	movl	-28(%ebp), %ecx
	movl	%esi, 20(%ebp)
	movl	-16(%ebp), %ebx
	movl	%edi, 12(%ebp)
	movl	-8(%ebp), %esi
	movl	%ecx, 16(%ebp)
	movl	-4(%ebp), %edi
	movl	%ebx, 8(%ebp)
	movl	-12(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	jmp	__Z7gr_lineiiii
	.p2align 4,,7
L187:
	movl	-20(%ebp), %eax
	movl	-24(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	-28(%ebp), %ebx
	addl	%eax, %edx
	leal	(%edi,%ecx), %eax
	movl	-20(%ebp), %ecx
	sarl	%edx
	sarl	%eax
	addl	%ebx, %ecx
	sarl	%ecx
	movl	%ecx, -32(%ebp)
	movl	-24(%ebp), %ecx
	movl	-32(%ebp), %ebx
	addl	%esi, %ecx
	sarl	%ecx
	addl	%edx, %ebx
	movl	%ecx, -36(%ebp)
	sarl	%ebx
	movl	-36(%ebp), %ecx
	movl	%ebx, -40(%ebp)
	leal	(%eax,%ecx), %ebx
	sarl	%ebx
	movl	%ebx, 20(%esp)
	movl	-40(%ebp), %ecx
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%edi, 4(%esp)
	movl	%ecx, 16(%esp)
	movl	-16(%ebp), %ecx
	movl	%ecx, (%esp)
	call	__Z13gr_splineiteriiiiii
	movl	%esi, 28(%ebp)
	movl	-28(%ebp), %edi
	movl	-36(%ebp), %esi
	movl	%ebx, 12(%ebp)
	movl	-32(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edi, 24(%ebp)
	movl	-12(%ebp), %ebx
	movl	-4(%ebp), %edi
	movl	%esi, 20(%ebp)
	movl	-8(%ebp), %esi
	movl	%eax, 16(%ebp)
	movl	%edx, 8(%ebp)
	movl	%ebp, %esp
	popl	%ebp
	jmp	__Z13gr_splineiteriiiiii
	.align 2
	.p2align 4,,15
.globl __Z10gr_splineciiiiii
	.def	__Z10gr_splineciiiiii;	.scl	2;	.type	32;	.endef
__Z10gr_splineciiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	24(%ebp), %esi
	movl	28(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	12(%ebp), %edi
	movl	16(%ebp), %edx
	movl	20(%ebp), %ebx
	addl	%esi, %eax
	addl	%ecx, %edi
	sarl	%eax
	sarl	%edi
	subl	%eax, %edx
	subl	%edi, %ebx
	leal	(%edi,%ebx,2), %esi
	movl	%esi, -20(%ebp)
	leal	(%eax,%edx,2), %ecx
	movl	24(%ebp), %eax
	sall	$4, -20(%ebp)
	sall	$4, %ecx
	movl	8(%ebp), %esi
	movl	%ecx, -16(%ebp)
	sall	$4, %eax
	movl	12(%ebp), %edi
	movl	%eax, -24(%ebp)
	movl	28(%ebp), %ecx
	movl	-16(%ebp), %eax
	movl	-20(%ebp), %ebx
	sall	$4, %esi
	movl	-24(%ebp), %edx
	sall	$4, %edi
	subl	%esi, %eax
	sall	$4, %ecx
	movl	%ecx, -28(%ebp)
	subl	%edi, %ebx
	subl	%esi, %edx
	subl	%edi, %ecx
	imull	%ebx, %edx
	imull	%ecx, %eax
	subl	%edx, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cmpl	$999, %eax
	jg	L191
	sarl	$4, -28(%ebp)
	sarl	$4, %edi
	sarl	$4, %esi
	sarl	$4, -24(%ebp)
	movl	-28(%ebp), %edx
	movl	%edi, 12(%ebp)
	movl	-24(%ebp), %ebx
	movl	%edx, 20(%ebp)
	movl	%esi, 8(%ebp)
	movl	%ebx, 16(%ebp)
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	__Z7gr_lineiiii
	.p2align 4,,7
L191:
	movl	-16(%ebp), %eax
	movl	-20(%ebp), %ecx
	movl	-24(%ebp), %ebx
	leal	(%esi,%eax), %edx
	leal	(%edi,%ecx), %eax
	movl	-16(%ebp), %ecx
	sarl	%edx
	sarl	%eax
	addl	%ebx, %ecx
	sarl	%ecx
	movl	-28(%ebp), %ebx
	movl	%ecx, -32(%ebp)
	movl	-20(%ebp), %ecx
	addl	%ebx, %ecx
	sarl	%ecx
	movl	-32(%ebp), %ebx
	movl	%ecx, -36(%ebp)
	movl	-36(%ebp), %ecx
	addl	%edx, %ebx
	sarl	%ebx
	movl	%ebx, -40(%ebp)
	leal	(%eax,%ecx), %ebx
	sarl	%ebx
	movl	%ebx, 20(%esp)
	movl	-40(%ebp), %ecx
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, 16(%esp)
	movl	%edi, 4(%esp)
	movl	%esi, (%esp)
	call	__Z13gr_splineiteriiiiii
	movl	%ebx, 12(%ebp)
	movl	-24(%ebp), %esi
	movl	-40(%ebp), %edi
	movl	-28(%ebp), %edx
	movl	-36(%ebp), %ecx
	movl	%esi, 24(%ebp)
	movl	-32(%ebp), %eax
	movl	%edx, 28(%ebp)
	movl	%ecx, 20(%ebp)
	movl	%eax, 16(%ebp)
	movl	%edi, 8(%ebp)
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	__Z13gr_splineiteriiiiii
	.align 2
	.p2align 4,,15
.globl __Z12gr_psegmentoiiii
	.def	__Z12gr_psegmentoiiii;	.scl	2;	.type	32;	.endef
__Z12gr_psegmentoiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ebx, -12(%ebp)
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	movl	%esi, -8(%ebp)
	movl	8(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	%edi, -4(%ebp)
	cmpl	%eax, %edx
	je	L194
	jl	L219
	xchgl	%ecx, %ebx
	movl	%eax, %edi
	movl	%edx, %esi
L197:
	testl	%esi, %esi
	setle	%dl
	cmpl	$767, %edi
	setg	%al
	orb	%al, %dl
	jne	L194
	subl	%ebx, %ecx
	movl	%ebx, %eax
	sall	$8, %eax
	movl	%eax, -16(%ebp)
	sall	$8, %ecx
	movl	%esi, %edx
	subl	%edi, %edx
	movl	%ecx, %eax
	movl	%edx, %ebx
	cltd
	idivl	%ebx
	testl	%edi, %edi
	movl	%eax, -20(%ebp)
	js	L220
L200:
	cmpl	$768, %esi
	jg	L221
L201:
	movl	_gr_linact, %ebx
	movl	%ebx, %edx
	subl	$_gr_seg, %edx
	sarl	$2, %edx
	imull	$-858993459, %edx, %ecx
	cmpl	$1023, %ecx
	jg	L194
	cmpl	_gr_limymin, %edi
	leal	20(%ebx), %edx
	movl	%esi, (%ebx)
	movl	-16(%ebp), %ecx
	movl	%edx, _gr_linact
	movl	-20(%ebp), %eax
	movl	$0, 16(%ebx)
	movl	$0, 12(%ebx)
	movl	%ecx, 4(%ebx)
	movl	%eax, 8(%ebx)
	jge	L203
	movl	%edi, _gr_limymin
L203:
	cmpl	_gr_limymax, %esi
	jle	L204
	movl	%esi, _gr_limymax
L204:
	movl	_gr_lines(,%edi,4), %esi
	testl	%esi, %esi
	movl	%esi, -24(%ebp)
	jne	L205
	movl	%ebx, _gr_lines(,%edi,4)
	.p2align 4,,15
L194:
	movl	-12(%ebp), %ebx
	movl	-8(%ebp), %esi
	movl	-4(%ebp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.p2align 4,,7
L219:
	movl	%edx, %edi
	movl	%eax, %esi
	jmp	L197
	.p2align 4,,7
L221:
	movl	$768, %esi
	jmp	L201
L205:
	movl	-16(%ebp), %edx
	xorl	%esi, %esi
	movl	-20(%ebp), %eax
	movl	-24(%ebp), %ecx
	addl	%eax, %edx
	.p2align 4,,15
L213:
	movl	8(%ecx), %eax
	addl	4(%ecx), %eax
	cmpl	%edx, %eax
	jg	L222
	movl	%ecx, %esi
	movl	12(%ecx), %ecx
	testl	%ecx, %ecx
	jne	L213
L217:
	movl	%ebx, 12(%esi)
	movl	$0, 12(%ebx)
	jmp	L194
L220:
	imull	%eax, %edi
	subl	%edi, -16(%ebp)
	xorl	%edi, %edi
	jmp	L200
L222:
	testl	%esi, %esi
	je	L223
	movl	%ebx, 12(%esi)
	movl	%ecx, 12(%ebx)
L208:
	testl	%ecx, %ecx
	jne	L194
	jmp	L217
L223:
	movl	-24(%ebp), %edx
	movl	%edx, 12(%ebx)
	movl	%ebx, _gr_lines(,%edi,4)
	jmp	L208
	.align 2
	.p2align 4,,15
.globl __Z14gr_iteracionSPllllll
	.def	__Z14gr_iteracionSPllllll;	.scl	2;	.type	32;	.endef
__Z14gr_iteracionSPllllll:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %edx
	movl	24(%ebp), %eax
	movl	28(%ebp), %ecx
	movl	%ebx, -16(%ebp)
	movl	16(%ebp), %esi
	movl	20(%ebp), %edi
	movl	%edx, -20(%ebp)
	movl	%eax, -24(%ebp)
	movl	%ecx, -28(%ebp)
	jmp	L227
	.p2align 4,,7
L225:
	movl	-24(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	-28(%ebp), %ebx
	movl	-20(%ebp), %eax
	addl	%esi, %edx
	addl	%ecx, %esi
	movl	%esi, -32(%ebp)
	addl	%edi, %eax
	addl	%ebx, %edi
	sarl	-32(%ebp)
	sarl	%edx
	sarl	%eax
	movl	-32(%ebp), %ecx
	sarl	%edi
	leal	(%eax,%edi), %ebx
	movl	%eax, 12(%esp)
	sarl	%ebx
	leal	(%edx,%ecx), %esi
	movl	%ebx, 20(%esp)
	sarl	%esi
	movl	%esi, 16(%esp)
	movl	%edx, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %edx
	movl	%edx, (%esp)
	call	__Z14gr_iteracionSPllllll
	movl	%esi, -16(%ebp)
	movl	-32(%ebp), %esi
	movl	%ebx, -20(%ebp)
L227:
	movl	-16(%ebp), %ebx
	movl	%esi, %eax
	movl	-20(%ebp), %edx
	movl	-16(%ebp), %ecx
	subl	%ebx, %eax
	movl	%edi, %ebx
	subl	%edx, %ebx
	movl	-24(%ebp), %edx
	subl	%ecx, %edx
	movl	-28(%ebp), %ecx
	imull	%ebx, %edx
	subl	-20(%ebp), %ecx
	imull	%ecx, %eax
	subl	%edx, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cmpl	$999, %eax
	jg	L225
	sarl	$4, -28(%ebp)
	sarl	$4, -24(%ebp)
	sarl	$4, -20(%ebp)
	movl	-28(%ebp), %ecx
	movl	-24(%ebp), %eax
	sarl	$4, -16(%ebp)
	movl	-20(%ebp), %edi
	movl	%ecx, 20(%ebp)
	movl	-16(%ebp), %esi
	movl	%eax, 16(%ebp)
	movl	%edi, 12(%ebp)
	movl	%esi, 8(%ebp)
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	__Z12gr_psegmentoiiii
	.align 2
	.p2align 4,,15
.globl __Z10gr_psplineiiiiii
	.def	__Z10gr_psplineiiiiii;	.scl	2;	.type	32;	.endef
__Z10gr_psplineiiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$64, %esp
	movl	%esi, -8(%ebp)
	movl	16(%ebp), %esi
	movl	20(%ebp), %eax
	movl	%edi, -4(%ebp)
	movl	8(%ebp), %edi
	movl	24(%ebp), %ecx
	movl	%esi, -20(%ebp)
	sall	$4, %eax
	movl	28(%ebp), %esi
	movl	%edi, -16(%ebp)
	sall	$4, %ecx
	movl	12(%ebp), %edi
	sall	$4, -16(%ebp)
	sall	$4, %esi
	sall	$4, %edi
	sall	$4, -20(%ebp)
	movl	-16(%ebp), %edx
	movl	%eax, -24(%ebp)
	movl	-20(%ebp), %eax
	movl	%ecx, -28(%ebp)
	movl	%ebx, -12(%ebp)
	subl	%edx, %eax
	movl	%ecx, %edx
	movl	-16(%ebp), %ecx
	movl	-24(%ebp), %ebx
	subl	%ecx, %edx
	movl	%esi, %ecx
	subl	%edi, %ebx
	subl	%edi, %ecx
	imull	%ebx, %edx
	imull	%ecx, %eax
	subl	%edx, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cmpl	$999, %eax
	jg	L229
	sarl	$4, -28(%ebp)
	sarl	$4, %esi
	sarl	$4, %edi
	sarl	$4, -16(%ebp)
	movl	-28(%ebp), %ecx
	movl	%esi, 20(%ebp)
	movl	-16(%ebp), %ebx
	movl	%edi, 12(%ebp)
	movl	-8(%ebp), %esi
	movl	%ecx, 16(%ebp)
	movl	-4(%ebp), %edi
	movl	%ebx, 8(%ebp)
	movl	-12(%ebp), %ebx
	movl	%ebp, %esp
	popl	%ebp
	jmp	__Z12gr_psegmentoiiii
	.p2align 4,,7
L229:
	movl	-20(%ebp), %eax
	movl	-24(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	-28(%ebp), %ebx
	addl	%eax, %edx
	leal	(%edi,%ecx), %eax
	movl	-20(%ebp), %ecx
	sarl	%edx
	sarl	%eax
	addl	%ebx, %ecx
	sarl	%ecx
	movl	%ecx, -32(%ebp)
	movl	-24(%ebp), %ecx
	movl	-32(%ebp), %ebx
	addl	%esi, %ecx
	sarl	%ecx
	addl	%edx, %ebx
	movl	%ecx, -36(%ebp)
	sarl	%ebx
	movl	-36(%ebp), %ecx
	movl	%ebx, -40(%ebp)
	leal	(%eax,%ecx), %ebx
	sarl	%ebx
	movl	%ebx, 20(%esp)
	movl	-40(%ebp), %ecx
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%edi, 4(%esp)
	movl	%ecx, 16(%esp)
	movl	-16(%ebp), %ecx
	movl	%ecx, (%esp)
	call	__Z14gr_iteracionSPllllll
	movl	%esi, 28(%ebp)
	movl	-28(%ebp), %edi
	movl	-36(%ebp), %esi
	movl	%ebx, 12(%ebp)
	movl	-32(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edi, 24(%ebp)
	movl	-12(%ebp), %ebx
	movl	-4(%ebp), %edi
	movl	%esi, 20(%ebp)
	movl	-8(%ebp), %esi
	movl	%eax, 16(%ebp)
	movl	%edx, 8(%ebp)
	movl	%ebp, %esp
	popl	%ebp
	jmp	__Z14gr_iteracionSPllllll
	.align 2
	.p2align 4,,15
.globl __Z11gr_psplineciiiiii
	.def	__Z11gr_psplineciiiiii;	.scl	2;	.type	32;	.endef
__Z11gr_psplineciiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$52, %esp
	movl	24(%ebp), %esi
	movl	28(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	12(%ebp), %edi
	movl	16(%ebp), %edx
	movl	20(%ebp), %ebx
	addl	%esi, %eax
	addl	%ecx, %edi
	sarl	%eax
	sarl	%edi
	subl	%eax, %edx
	subl	%edi, %ebx
	leal	(%edi,%ebx,2), %esi
	movl	%esi, -20(%ebp)
	leal	(%eax,%edx,2), %ecx
	movl	24(%ebp), %eax
	sall	$4, -20(%ebp)
	sall	$4, %ecx
	movl	8(%ebp), %esi
	movl	%ecx, -16(%ebp)
	sall	$4, %eax
	movl	12(%ebp), %edi
	movl	%eax, -24(%ebp)
	movl	28(%ebp), %ecx
	movl	-16(%ebp), %eax
	movl	-20(%ebp), %ebx
	sall	$4, %esi
	movl	-24(%ebp), %edx
	sall	$4, %edi
	subl	%esi, %eax
	sall	$4, %ecx
	movl	%ecx, -28(%ebp)
	subl	%edi, %ebx
	subl	%esi, %edx
	subl	%edi, %ecx
	imull	%ebx, %edx
	imull	%ecx, %eax
	subl	%edx, %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cmpl	$999, %eax
	jg	L233
	sarl	$4, -28(%ebp)
	sarl	$4, %edi
	sarl	$4, %esi
	sarl	$4, -24(%ebp)
	movl	-28(%ebp), %edx
	movl	%edi, 12(%ebp)
	movl	-24(%ebp), %ebx
	movl	%edx, 20(%ebp)
	movl	%esi, 8(%ebp)
	movl	%ebx, 16(%ebp)
	addl	$52, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	__Z12gr_psegmentoiiii
	.p2align 4,,7
L233:
	movl	-16(%ebp), %eax
	movl	-20(%ebp), %ecx
	movl	-24(%ebp), %ebx
	leal	(%esi,%eax), %edx
	leal	(%edi,%ecx), %eax
	movl	-16(%ebp), %ecx
	sarl	%edx
	sarl	%eax
	addl	%ebx, %ecx
	sarl	%ecx
	movl	-28(%ebp), %ebx
	movl	%ecx, -32(%ebp)
	movl	-20(%ebp), %ecx
	addl	%ebx, %ecx
	sarl	%ecx
	movl	-32(%ebp), %ebx
	movl	%ecx, -36(%ebp)
	movl	-36(%ebp), %ecx
	addl	%edx, %ebx
	sarl	%ebx
	movl	%ebx, -40(%ebp)
	leal	(%eax,%ecx), %ebx
	sarl	%ebx
	movl	%ebx, 20(%esp)
	movl	-40(%ebp), %ecx
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, 16(%esp)
	movl	%edi, 4(%esp)
	movl	%esi, (%esp)
	call	__Z14gr_iteracionSPllllll
	movl	%ebx, 12(%ebp)
	movl	-24(%ebp), %esi
	movl	-40(%ebp), %edi
	movl	-28(%ebp), %edx
	movl	-36(%ebp), %ecx
	movl	%esi, 24(%ebp)
	movl	-32(%ebp), %eax
	movl	%edx, 28(%ebp)
	movl	%ecx, 20(%ebp)
	movl	%eax, 16(%ebp)
	movl	%edi, 8(%ebp)
	addl	$52, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	__Z14gr_iteracionSPllllll
	.align 2
	.p2align 4,,15
.globl __Z7avanzaSP10gr_segpolii
	.def	__Z7avanzaSP10gr_segpolii;	.scl	2;	.type	32;	.endef
__Z7avanzaSP10gr_segpolii:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	pushl	%edi
	movl	12(%ebp), %edi
	pushl	%esi
	xorl	%esi, %esi
	pushl	%ebx
	movl	8(%ebp), %ebx
	testl	%ebx, %ebx
	movl	%ebx, %edx
	je	L249
	.p2align 4,,15
L253:
	cmpl	%edi, (%edx)
	jg	L239
	testl	%ecx, %ecx
	je	L240
	movl	16(%edx), %eax
	movl	%eax, 16(%ecx)
	movl	16(%edx), %eax
	movl	%eax, %edx
L237:
	testl	%edx, %edx
L255:
	jne	L253
L249:
	movl	%ebx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L239:
	movl	8(%edx), %eax
	addl	4(%edx), %eax
	testl	%ecx, %ecx
	movl	%eax, 4(%edx)
	je	L243
	cmpl	4(%ecx), %eax
	jge	L243
	testl	%esi, %esi
	je	L254
	movl	%edx, 16(%esi)
L245:
	movl	16(%edx), %esi
	movl	%esi, 16(%ecx)
	movl	%edx, %esi
	movl	%ecx, 16(%edx)
	movl	16(%ecx), %edx
	testl	%edx, %edx
	jmp	L255
	.p2align 4,,7
L243:
	movl	%ecx, %esi
	movl	%edx, %ecx
	movl	16(%edx), %edx
	testl	%edx, %edx
	jmp	L255
L240:
	movl	16(%edx), %ebx
	movl	%ebx, %eax
	movl	%eax, %edx
	jmp	L237
L254:
	movl	%edx, %ebx
	jmp	L245
	.align 2
	.p2align 4,,15
.globl __Z6nuevoSP10gr_segpoliS0_
	.def	__Z6nuevoSP10gr_segpoliS0_;	.scl	2;	.type	32;	.endef
__Z6nuevoSP10gr_segpoliS0_:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	pushl	%esi
	movl	8(%ebp), %esi
	pushl	%ebx
	xorl	%ebx, %ebx
	testl	%eax, %eax
	movl	%esi, %edx
	je	L272
	.p2align 4,,15
L283:
	testl	%esi, %esi
	je	L281
	testl	%edx, %edx
	je	L275
	movl	4(%eax), %ecx
	.p2align 4,,15
L268:
	cmpl	%ecx, 4(%edx)
	jg	L282
	movl	%edx, %ebx
	movl	16(%edx), %edx
	testl	%edx, %edx
	jne	L268
L275:
	movl	%eax, 16(%ebx)
	movl	%eax, %edx
	movl	$0, 16(%eax)
	movl	12(%eax), %eax
L285:
	testl	%eax, %eax
	jne	L283
L272:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret
L282:
	testl	%ebx, %ebx
	je	L284
	movl	%edx, 16(%eax)
	movl	%eax, 16(%ebx)
L263:
	testl	%edx, %edx
	je	L275
	movl	%eax, %edx
	movl	12(%eax), %eax
	jmp	L285
L281:
	movl	$0, 16(%eax)
	movl	%eax, %esi
	movl	%eax, %edx
	movl	12(%eax), %eax
	jmp	L285
L284:
	movl	%esi, 16(%eax)
	movl	%eax, %esi
	jmp	L263
	.align 2
	.p2align 4,,15
.globl __Z11gr_drawPoliv
	.def	__Z11gr_drawPoliv;	.scl	2;	.type	32;	.endef
__Z11gr_drawPoliv:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	_gr_limymax, %edx
	cmpl	$-1, %edx
	je	L286
	movl	$0, -28(%ebp)
	movl	_gr_limymin, %eax
	leal	_gr_lines(,%eax,4), %ecx
	movl	%ecx, -32(%ebp)
	cmpl	%edx, %eax
	movl	%eax, -20(%ebp)
	jge	L360
L395:
	movl	-28(%ebp), %ebx
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	testl	%ebx, %ebx
	movl	%ebx, %edx
	je	L362
	.p2align 4,,15
L387:
	movl	-20(%ebp), %edi
	cmpl	%edi, (%edx)
	jg	L293
	testl	%ecx, %ecx
	je	L294
	movl	16(%edx), %eax
	movl	%eax, 16(%ecx)
	movl	16(%edx), %eax
	movl	%eax, %edx
L291:
	testl	%edx, %edx
L397:
	jne	L387
L362:
	movl	-32(%ebp), %edx
	movl	%ebx, %esi
	movl	%ebx, %eax
	xorl	%ebx, %ebx
	movl	(%edx), %ecx
	testl	%ecx, %ecx
	je	L364
	.p2align 4,,15
L390:
	testl	%esi, %esi
	je	L388
	testl	%eax, %eax
	je	L369
	movl	4(%ecx), %edx
	.p2align 4,,15
L314:
	cmpl	%edx, 4(%eax)
	jg	L389
	movl	%eax, %ebx
	movl	16(%eax), %eax
	testl	%eax, %eax
	jne	L314
L369:
	movl	%ecx, 16(%ebx)
	movl	%ecx, %eax
	movl	$0, 16(%ecx)
	movl	12(%ecx), %ecx
L399:
	testl	%ecx, %ecx
	jne	L390
L364:
	movl	%esi, -28(%ebp)
	testl	%esi, %esi
	movl	%esi, %eax
	je	L322
	movl	16(%esi), %edx
	testl	%edx, %edx
	je	L319
	movl	4(%edx), %ebx
	testl	%ebx, %ebx
	js	L373
L319:
	testl	%eax, %eax
	je	L322
	movl	16(%eax), %edi
	testl	%edi, %edi
	movl	%edi, -60(%ebp)
	je	L322
	movl	4(%eax), %edx
	cmpl	$262144, %edx
	jge	L322
	movl	-20(%ebp), %esi
	sall	$10, %esi
	movl	%esi, -52(%ebp)
L357:
	movl	8(%eax), %eax
	movl	%edx, %esi
	testl	%eax, %eax
	leal	(%edx,%eax), %ecx
	js	L391
	movl	-60(%ebp), %ebx
	movl	-60(%ebp), %edx
	movl	4(%ebx), %eax
	movl	8(%edx), %edi
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %ebx
	addl	%edi, %ebx
	movl	%ebx, -24(%ebp)
	testl	%edi, %edi
	js	L392
L325:
	movl	-24(%ebp), %edx
	movl	%esi, %ebx
	movl	-16(%ebp), %eax
	sarl	$8, %ebx
	sarl	$8, %edx
	sarl	$8, %eax
	movl	%edx, -44(%ebp)
	movl	%ecx, %edx
	sarl	$8, %edx
	movl	%eax, -40(%ebp)
	movl	%edx, -36(%ebp)
	js	L327
	cmpl	%edx, %ebx
	jge	L328
	movl	%edx, -64(%ebp)
	movl	$65280, %eax
	subl	%ebx, %edx
	movl	%edx, %esi
	cltd
	xorl	%edi, %edi
	idivl	%esi
	testl	%ebx, %ebx
	movl	%ebx, %ecx
	movl	%eax, -48(%ebp)
	js	L393
L329:
	cmpl	$1023, -36(%ebp)
	jle	L330
	movl	$1023, -64(%ebp)
	cmpl	$1023, %ecx
	jg	L327
L330:
	movl	-52(%ebp), %eax
	leal	0(,%ecx,4), %edx
	movl	-64(%ebp), %esi
	addl	%ecx, %eax
	leal	_gr_buffer(,%eax,4), %ebx
	leal	(%ebx,%esi,4), %eax
	subl	%edx, %eax
	leal	4(%eax), %esi
	.p2align 4,,15
L333:
	movl	%ebx, (%esp)
	movl	%edi, %eax
	movzbl	%ah, %edx
	movl	%edx, 4(%esp)
	addl	$4, %ebx
	call	*_gr_pixela
	movl	-48(%ebp), %ecx
	addl	%ecx, %edi
	cmpl	%esi, %ebx
	jb	L333
L327:
	movl	-36(%ebp), %edx
	incl	%edx
	cmpl	-40(%ebp), %edx
	jge	L339
	movl	-40(%ebp), %esi
	movl	%edx, %ebx
	notl	%ebx
	movl	%ebx, %ecx
	sarl	$31, %ecx
	decl	%esi
	andl	%edx, %ecx
	cmpl	$1023, %esi
	jle	L341
	cmpl	$1023, %ecx
	movl	$1023, %esi
	jg	L339
L341:
	movl	-52(%ebp), %eax
	addl	%ecx, %eax
	leal	_gr_buffer(,%eax,4), %ebx
	leal	(%ebx,%esi,4), %edi
	leal	0(,%ecx,4), %esi
	subl	%esi, %edi
	leal	4(%edi), %esi
	.p2align 4,,15
L344:
	movl	%ebx, (%esp)
	addl	$4, %ebx
	call	*_gr_pixel
	cmpl	%esi, %ebx
	jb	L344
L339:
	cmpl	$1023, -40(%ebp)
	jg	L338
	movl	-44(%ebp), %ecx
	cmpl	%ecx, -40(%ebp)
	jge	L348
	movl	-44(%ebp), %ecx
	movl	$-65280, %eax
	movl	$65280, %edi
	movl	-40(%ebp), %esi
	movl	%ecx, %edx
	subl	%esi, %edx
	movl	%edx, %ebx
	cltd
	idivl	%ebx
	testl	%esi, %esi
	movl	%eax, -56(%ebp)
	js	L394
L349:
	cmpl	$1023, %ecx
	jle	L350
	cmpl	$1023, %esi
	movl	$1023, %ecx
	jg	L338
L350:
	movl	-52(%ebp), %edx
	addl	%esi, %edx
	leal	_gr_buffer(,%edx,4), %ebx
	leal	(%ebx,%ecx,4), %eax
	leal	0(,%esi,4), %ecx
	subl	%ecx, %eax
	leal	4(%eax), %esi
	.p2align 4,,15
L353:
	movl	%ebx, (%esp)
	movl	%edi, %edx
	movzbl	%dh, %ecx
	movl	%ecx, 4(%esp)
	addl	$4, %ebx
	call	*_gr_pixela
	movl	-56(%ebp), %eax
	addl	%eax, %edi
	cmpl	%esi, %ebx
	jb	L353
L338:
	movl	-60(%ebp), %edi
	movl	16(%edi), %eax
	testl	%eax, %eax
	je	L322
	movl	16(%eax), %ebx
	testl	%ebx, %ebx
	movl	%ebx, -60(%ebp)
	je	L322
	movl	4(%eax), %edx
	cmpl	$262144, %edx
	jl	L357
L322:
	incl	-20(%ebp)
	movl	-32(%ebp), %esi
	movl	-20(%ebp), %eax
	movl	$0, (%esi)
	addl	$4, %esi
	movl	%esi, -32(%ebp)
	cmpl	_gr_limymax, %eax
	jl	L395
L360:
	movl	$-1, %edi
	movl	$769, %edx
	movl	$_gr_seg, %ecx
	movl	%edi, _gr_limymax
	movl	%edx, _gr_limymin
	movl	%ecx, _gr_linact
L286:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L293:
	movl	4(%edx), %edi
	movl	8(%edx), %eax
	addl	%edi, %eax
	movl	%eax, 4(%edx)
	testl	%ecx, %ecx
	je	L297
	cmpl	4(%ecx), %eax
	jge	L297
	testl	%esi, %esi
	je	L396
	movl	%edx, 16(%esi)
L299:
	movl	16(%edx), %esi
	movl	%esi, 16(%ecx)
	movl	%edx, %esi
	movl	%ecx, 16(%edx)
	movl	16(%ecx), %edx
	testl	%edx, %edx
	jmp	L397
L297:
	movl	%ecx, %esi
	movl	%edx, %ecx
	movl	16(%edx), %edx
	testl	%edx, %edx
	jmp	L397
L294:
	movl	16(%edx), %ebx
	movl	%ebx, %eax
	movl	%eax, %edx
	jmp	L291
L396:
	movl	%edx, %ebx
	jmp	L299
L389:
	testl	%ebx, %ebx
	je	L398
	movl	%eax, 16(%ecx)
	movl	%ecx, 16(%ebx)
L309:
	testl	%eax, %eax
	je	L369
	movl	%ecx, %eax
	movl	12(%ecx), %ecx
	jmp	L399
L388:
	movl	$0, 16(%ecx)
	movl	%ecx, %esi
	movl	%ecx, %eax
	movl	12(%ecx), %ecx
	jmp	L399
L400:
	movl	16(%eax), %edx
	testl	%edx, %edx
	je	L319
	movl	4(%edx), %ecx
	testl	%ecx, %ecx
	jns	L319
L373:
	movl	16(%edx), %eax
	testl	%eax, %eax
	jne	L400
	jmp	L322
	.p2align 4,,7
L328:
	movl	-52(%ebp), %edx
	leal	(%esi,%ecx), %eax
	sarl	%eax
	notb	%al
	addl	%ebx, %edx
	movzbl	%al, %esi
	movl	%esi, 4(%esp)
	leal	_gr_buffer(,%edx,4), %edi
	movl	%edi, (%esp)
	call	*_gr_pixela
	movl	-44(%ebp), %ebx
	cmpl	%ebx, -36(%ebp)
	jne	L327
	jmp	L338
L391:
	movl	%edx, %ebx
	xorl	%ecx, %ebx
	movl	-60(%ebp), %edx
	xorl	%ebx, %ecx
	movl	%ebx, %esi
	movl	-60(%ebp), %ebx
	movl	8(%edx), %edi
	xorl	%ecx, %esi
	movl	4(%ebx), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %ebx
	addl	%edi, %ebx
	movl	%ebx, -24(%ebp)
	testl	%edi, %edi
	jns	L325
L392:
	movl	-16(%ebp), %edi
	xchgl	%ebx, %edi
	movl	%ebx, -24(%ebp)
	movl	%edi, -16(%ebp)
	jmp	L325
L398:
	movl	%esi, 16(%ecx)
	movl	%ecx, %esi
	jmp	L309
L348:
	movl	-16(%ebp), %eax
	movl	-24(%ebp), %esi
	movl	-52(%ebp), %ecx
	movl	-40(%ebp), %edx
	addl	%esi, %eax
	sarl	%eax
	addl	%edx, %ecx
	movzbl	%al, %ebx
	leal	_gr_buffer(,%ecx,4), %edi
	movl	%ebx, 4(%esp)
	movl	%edi, (%esp)
	call	*_gr_pixela
	jmp	L338
L393:
	movl	%ebx, %edi
	xorl	%ecx, %ecx
	negl	%edi
	imull	%eax, %edi
	jmp	L329
L394:
	negl	-40(%ebp)
	movl	-40(%ebp), %esi
	imull	%eax, %esi
	leal	65280(%esi), %edi
	xorl	%esi, %esi
	jmp	L349
	.align 2
	.p2align 4,,15
.globl __Z6gr_iniv
	.def	__Z6gr_iniv;	.scl	2;	.type	32;	.endef
__Z6gr_iniv:
	pushl	%ebp
	movl	$_IID_IDirectDraw7, %edx
	movl	%esp, %ebp
	movl	$_g_lpdd7, %ecx
	subl	$56, %esp
	xorl	%eax, %eax
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, 12(%esp)
	movl	$0, (%esp)
	call	_DirectDrawCreateEx@16
	movl	_g_lpdd7, %edx
	subl	$16, %esp
	movl	$17, %eax
	movl	(%edx), %ecx
	movl	%eax, 8(%esp)
	movl	_hWnd, %eax
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	call	*80(%ecx)
	movl	_g_lpdd7, %eax
	xorl	%ecx, %ecx
	subl	$12, %esp
	movl	(%eax), %edx
	movl	%ecx, 20(%esp)
	xorl	%ecx, %ecx
	movl	%ecx, 16(%esp)
	movl	$32, %ecx
	movl	%ecx, 12(%esp)
	movl	$768, %ecx
	movl	%ecx, 8(%esp)
	movl	$1024, %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	*84(%edx)
	xorl	%edx, %edx
	movl	$124, %eax
	subl	$24, %esp
	movl	%edx, 4(%esp)
	movl	%eax, 8(%esp)
	movl	$_ddsd, (%esp)
	call	_memset
	movl	$33, %eax
	movl	$124, %ecx
	movl	$536, %edx
	movl	%eax, _ddsd+4
	movl	$1024, %eax
	movl	%eax, _ddsd+12
	movl	_g_lpdd7, %eax
	movl	%ecx, _ddsd
	movl	$1, %ecx
	movl	%edx, _ddsd+104
	movl	$768, %edx
	movl	%ecx, _ddsd+20
	xorl	%ecx, %ecx
	movl	%edx, _ddsd+8
	movl	(%eax), %edx
	movl	%ecx, 12(%esp)
	movl	$_g_lpddsPrimary, %ecx
	movl	%ecx, 8(%esp)
	movl	$_ddsd, %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	*24(%edx)
	movl	$4, -24(%ebp)
	movl	_g_lpddsPrimary, %edx
	movl	$_g_lpddsBack, %eax
	movl	$0, -20(%ebp)
	movl	$0, -16(%ebp)
	movl	(%edx), %ecx
	subl	$16, %esp
	movl	%eax, 8(%esp)
	leal	-24(%ebp), %eax
	movl	%edx, (%esp)
	movl	$0, -12(%ebp)
	movl	%eax, 4(%esp)
	call	*48(%ecx)
	movl	$_gr_seg, %eax
	movl	$_gr_lines, %edx
	movl	%eax, _gr_linact
	movl	$768, %eax
	subl	$12, %esp
	.p2align 4,,15
L405:
	movl	$0, (%edx)
	addl	$4, %edx
	decl	%eax
	jns	L405
	movl	$_ddsd, (%esp)
	movl	$769, %edx
	movl	$-1, %ecx
	movl	%edx, _gr_limymin
	movl	$16777215, %eax
	xorl	%edx, %edx
	movl	%ecx, _gr_limymax
	movl	$__Z10_gr_pixelsPm, %ecx
	movl	%eax, _gr_color1
	movl	$__Z10_gr_pixelaPmh, %eax
	movl	%edx, _gr_color2
	movl	$124, %edx
	movl	%ecx, _gr_pixel
	xorl	%ecx, %ecx
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, _gr_pixela
	movb	$-1, _gr_alphav
	call	_memset
	leave
	ret
	.align 2
	.p2align 4,,15
.globl __Z6redrawv
	.def	__Z6redrawv;	.scl	2;	.type	32;	.endef
__Z6redrawv:
	pushl	%ebp
	movl	$124, %edx
	movl	%esp, %ebp
	pushl	%edi
	xorl	%ecx, %ecx
	xorl	%edi, %edi
	pushl	%esi
	xorl	%esi, %esi
	pushl	%ebx
	subl	$28, %esp
	movl	%edx, _ddsd
	movl	_g_lpddsBack, %eax
	movl	$_ddsd, %ebx
	movl	(%eax), %edx
	movl	%edi, 16(%esp)
	movl	$_gr_buffer, %edi
	movl	%esi, 12(%esp)
	movl	$767, %esi
	movl	%ebx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	*100(%edx)
	movl	_ddsd+16, %eax
	movl	_ddsd+36, %ebx
	subl	$20, %esp
	movl	%eax, -16(%ebp)
	.p2align 4,,15
L415:
	movl	%edi, 4(%esp)
	movl	$4096, %ecx
	addl	$4096, %edi
	movl	%ebx, (%esp)
	movl	%ecx, 8(%esp)
	call	_memcpy
	movl	-16(%ebp), %eax
	addl	%eax, %ebx
	decl	%esi
	jns	L415
	movl	_g_lpddsBack, %eax
	xorl	%ecx, %ecx
	movl	(%eax), %ebx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	*128(%ebx)
	movl	_g_lpddsPrimary, %esi
	movl	$1, %edx
	movl	_g_lpddsBack, %edi
	movl	(%esi), %ebx
	subl	$8, %esp
	movl	%edi, 4(%esp)
	movl	%esi, (%esp)
	movl	%edx, 8(%esp)
	call	*44(%ebx)
	subl	$12, %esp
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z10gr_restorev
	.def	__Z10gr_restorev;	.scl	2;	.type	32;	.endef
__Z10gr_restorev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	_g_lpddsPrimary, %eax
	movl	(%eax), %edx
	movl	%eax, (%esp)
	call	*108(%edx)
	subl	$4, %esp
	leave
	ret
	.align 2
	.p2align 4,,15
.globl __Z6gr_finv
	.def	__Z6gr_finv;	.scl	2;	.type	32;	.endef
__Z6gr_finv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	_g_lpddsPrimary, %eax
	testl	%eax, %eax
	jne	L424
L422:
	movl	_g_lpdd7, %eax
	testl	%eax, %eax
	jne	L425
	leave
	ret
	.p2align 4,,7
L425:
	movl	%eax, (%esp)
	call	__ZdlPv
	xorl	%edx, %edx
	movl	%edx, _g_lpdd7
	leave
	ret
	.p2align 4,,7
L424:
	movl	%eax, (%esp)
	call	__ZdlPv
	xorl	%eax, %eax
	movl	%eax, _g_lpddsPrimary
	jmp	L422
	.def	_memcpy;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	__ZdlPv;	.scl	3;	.type	32;	.endef
	.def	__Z12gr_psegmentoiiii;	.scl	3;	.type	32;	.endef
