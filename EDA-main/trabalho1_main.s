	.file	"trabalho1_main.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "r\0"
LC1:
	.ascii "informacoes_trabalho1.txt\0"
LC2:
	.ascii "ERRO NA ABERTURA DO ARQUIVO\0"
LC3:
	.ascii "Lista original:\0"
LC4:
	.ascii "\12Lista ordenada:\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB17:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$LC0, 4(%esp)
	movl	$LC1, (%esp)
	call	_fopen
	movl	%eax, 28(%esp)
	cmpl	$0, 28(%esp)
	jne	L2
	movl	$LC2, (%esp)
	call	_puts
	movl	$1, (%esp)
	call	_exit
L2:
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	_arq_lista
	movl	%eax, 24(%esp)
	movl	$LC3, (%esp)
	call	_puts
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	_fila_imprime
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	_ordena_fila
	movl	$LC4, (%esp)
	call	_puts
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	_fila_imprime
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	_fila_libera
	movl	$0, 24(%esp)
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_arq_lista;	.scl	2;	.type	32;	.endef
	.def	_fila_imprime;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_ordena_fila;	.scl	2;	.type	32;	.endef
	.def	_fila_libera;	.scl	2;	.type	32;	.endef
