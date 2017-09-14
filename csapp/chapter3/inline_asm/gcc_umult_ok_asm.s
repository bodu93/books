# Hand-generated code for umult_ok
.global umult_ok_asm
# int umult_ok_asm(unsigned long x, unsigned long y, unsigned long *dest);
# x in %rdi, y in %rsi, dest in %rdx
umult_ok_asm:
    movq    %rdx, %rcx      # save copy of dest
    movq    %rsi, %rax      # copy y to %rax
    mulq    %rdi            # unsigned multiply by x
    movq    %rax, (%rcx)    # store product at dest
    setae   %al
    movzbl  %al, %eax
    ret
