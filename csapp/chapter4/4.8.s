.text
.globl _poptest
_poptest:
    movq    %rsp, %rdi
    pushq   $0xabcd
    popq    %rsp
    movq    %rsp, %rax
    movq    %rdi, %rsp
    ret
