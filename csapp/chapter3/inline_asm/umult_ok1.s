	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_umult_ok               ## -- Begin function umult_ok
	.p2align	4, 0x90
_umult_ok:                              ## @umult_ok
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	movq	%rdx, %rcx
	## InlineAsm Start
	movq	%rdi, %rax	## Get x
	mulq	%rsi	## Unsigned long multiply by y
	movq	%rax, (%rcx)	## Store low-order 8 bytes at dest
	setae	%cl	## Set result
	## InlineAsm End
	movzbl	%cl, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
