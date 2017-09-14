.text
.globl _push_test
_push_test:
    movq    %rsp, %rax
    pushq   %rsp
    popq    %rdx
    subq    %rdx, %rax
    ret
