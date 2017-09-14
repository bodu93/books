	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_tmult_ok_asm           ## -- Begin function tmult_ok_asm
	.p2align	4, 0x90
_tmult_ok_asm:                          ## @tmult_ok_asm
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
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
	#xorl	%eax, %eax
	#testq	%rdi, %rdi
	#setg	%al
# following line is hand-generated
    setae   %al
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
