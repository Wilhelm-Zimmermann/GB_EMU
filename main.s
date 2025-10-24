	.file	"main.c"
	.text
	.globl	PIXEL_SCALE
	.section	.rodata
	.align 4
	.type	PIXEL_SCALE, @object
	.size	PIXEL_SCALE, 4
PIXEL_SCALE:
	.long	2
.LC0:
	.string	"%s: %s\n"
	.text
	.globl	printSdlError
	.type	printSdlError, @function
printSdlError:
.LFB4209:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	SDL_GetError@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4209:
	.size	printSdlError, .-printSdlError
	.section	.rodata
.LC1:
	.string	"Usage: %s <ROM file>\n"
	.align 8
.LC2:
	.string	"SDL was not able to initialize"
.LC3:
	.string	"Window could not be created"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4210:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movl	%edi, -132(%rbp)
	movq	%rsi, -144(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -132(%rbp)
	jg	.L3
	movq	-144(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %eax
	jmp	.L14
.L3:
	movl	$32, %edi
	call	SDL_Init@PLT
	testl	%eax, %eax
	jns	.L5
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printSdlError
	movl	$1, %eax
	jmp	.L14
.L5:
	movl	$2, %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %ecx
	movl	$2, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$5, %eax
	movl	%eax, %edx
	movq	-144(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$4, %r9d
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movl	$805240832, %edx
	movl	$805240832, %esi
	movq	%rax, %rdi
	call	SDL_CreateWindow@PLT
	movq	%rax, -120(%rbp)
	movl	$120, %edi
	call	malloc@PLT
	movq	%rax, -112(%rbp)
	movl	$0, %edi
	call	malloc@PLT
	movq	%rax, -104(%rbp)
	movl	$12, %edi
	call	malloc@PLT
	movq	%rax, -96(%rbp)
	movl	$16, %edi
	call	malloc@PLT
	movq	%rax, -88(%rbp)
	cmpq	$0, -120(%rbp)
	jne	.L6
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printSdlError
	movl	$1, %eax
	jmp	.L14
.L6:
	movq	-120(%rbp), %rax
	movl	$2, %edx
	movl	$-1, %esi
	movq	%rax, %rdi
	call	SDL_CreateRenderer@PLT
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movl	$144, %r8d
	movl	$160, %ecx
	movl	$1, %edx
	movl	$373694468, %esi
	movq	%rax, %rdi
	call	SDL_CreateTexture@PLT
	movq	%rax, -72(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	initMemory@PLT
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	initRegisters@PLT
	movq	-144(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rdx
	movq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	loadRom@PLT
	movl	$0, -128(%rbp)
	jmp	.L7
.L10:
	movl	-64(%rbp), %eax
	cmpl	$256, %eax
	jne	.L9
	movl	$1, -128(%rbp)
.L9:
	movl	-64(%rbp), %eax
	cmpl	$768, %eax
	jne	.L8
	movl	-44(%rbp), %eax
	cmpl	$27, %eax
	jne	.L8
	movl	$1, -128(%rbp)
.L8:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_PollEvent@PLT
	testl	%eax, %eax
	jne	.L10
	movq	-112(%rbp), %rdx
	movq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	cpu_cycle@PLT
	movzbl	%al, %eax
	movl	%eax, -124(%rbp)
	movl	-124(%rbp), %edx
	movq	-112(%rbp), %rcx
	movq	-88(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ppuStep@PLT
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_RenderClear@PLT
	movq	-72(%rbp), %rsi
	movq	-80(%rbp), %rax
	movl	$0, %ecx
	movl	$0, %edx
	movq	%rax, %rdi
	call	SDL_RenderCopy@PLT
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_RenderPresent@PLT
.L7:
	cmpl	$0, -128(%rbp)
	je	.L8
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_DestroyTexture@PLT
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_DestroyRenderer@PLT
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_DestroyWindow@PLT
	call	SDL_Quit@PLT
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	freeMemory@PLT
	cmpq	$0, -104(%rbp)
	je	.L12
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L12:
	cmpq	$0, -96(%rbp)
	je	.L13
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L13:
	movl	$0, %eax
.L14:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L15
	call	__stack_chk_fail@PLT
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4210:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.2) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
