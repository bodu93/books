	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_tmult_ok2              ## -- Begin function tmult_ok2
	.p2align	4, 0x90
_tmult_ok2:                             ## @tmult_ok2
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
	pushq	%rbx
Lcfi3:
	.cfi_offset %rbx, -24
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
	## InlineAsm Start
	setae	%bl
	movzbl	%bl, %eax
	## InlineAsm End
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
