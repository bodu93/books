	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_tmult_ok               ## -- Begin function tmult_ok
	.p2align	4, 0x90
_tmult_ok:                              ## @tmult_ok
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
	## InlineAsm Start
	imulq	%rdi, %rsi
	movq	%rsi, (%rdx)
	setae	%al
	## InlineAsm End
	movzbl	%al, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
