# Hand-generated code for tmult_ok
.global tmult_ok_asm
# int tmult_ok_asm(long x, int y, long *dest);
# x in %rdi, y in %rsi, dest in %rdx
tmult_ok_asm:
    imulq   %rdi, %rsi
    movq    %rsi, (%rdi)
# Deleted code
#   testq   %rsi, %rsi
#   setg    %al
#   Inserted code
    setae   %al
# End of inserted code
    movzbl  %al, %eax
    ret
