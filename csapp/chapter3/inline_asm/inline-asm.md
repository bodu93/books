### GCC/Clang之内联汇编(inline asm)

#### 语法形式:

```att-asm
asm(code-strings[:output-list[:input-list[:overwrite-list]]]);
```

#### 参数解释

- `code-strings` : 汇编代码, 其中寄存器使用格式化字符串表示，其命名方式为`%[name]` ,如果需要引用某个寄存器, 如`%eax`, 需要进行转义:`%%eax` .
- `output-list `  : 格式化字符串中的目标寄存器列表, 参数之间以逗号分隔.
- `input-list`  : 格式化字符串中的源寄存器列表, 参数之间以逗号分隔.
- `overwrite-list`  : 被覆盖的寄存器列表, 参数之间以逗号分隔. 

#### 格式解释

​	`output-list`和`input-list`的格式如下:  `[name] tag (expr)`  其中，name表示汇编代码中格式化寄存器名。tag表示使用该寄存器的使用限制，expr为C可赋值的C表达式(即所谓的左值lvalue)。对于tag的解释如下:

| Output-list Constraint | Meanings                                 |
| :--------------------- | :--------------------------------------- |
| "=r"                   | Update value stored in a register        |
| "+r"                   | Read and update value stored in a register |
| "=m"                   | Update value stored in memory            |
| "+m"                   | Read and update value stored in memory   |
| "=rm"                  | Update value stored in a register or in memory |
| "+rm"                  | Read and update value stored in a register or memory |

| Input-list Constraint | Meanings                     |
| :-------------------- | :--------------------------- |
| r                     | read from register           |
| m                     | read from memory             |
| rm                    | read from register or memory |



#### Examples

```C
int tmult_ok2(long x, long y, long *dest) {
    int result;
  
  	*dest = x * y;
  	asm("setae			%%bl			# Set low-order byte\n\t"
        "movzbl			%%bl, %[val]	 # Zero extend to be result"
        : [val] "=r" (result) /* output-list */
        :					/* no input-list */
        : "%bl"				/* overwrite-list */
        );
  
  	return result;
}
```

```C
int tmult_ok3(long x, long y, long *dest) {
    unsigned char bresult;
  	*dest = x * y;
  
  	asm("setae		%[b]			# Set result"
        : [b] "=r" (bresult)		 /* output-list */
        );
  
  	return (int)bresult;
}
```

```C
int umult_ok(unsigned long x, unsigned long y, unsigned long *dest) {
    unsigned char bresult;
  
  	asm("movq	%[x], %%rax			# Get x\n\t"
        "mulq	%[y]				# Unsigned long multiply by y\n\t"
        "movq	%%rax, %[p]			# Store low-order 8 bytes at dest\n\t"
        "setae	%[b]				# Set result"
        : [p] "=m" (*dest), [b] "=r" (bresult) /* output-list */
        : [x] "r" (x), [y] "r" (y)			  /* input-list */
        : "%rax", "%rax"					 /* overwrites */
        );
  	return (int)bresult;
}
```

