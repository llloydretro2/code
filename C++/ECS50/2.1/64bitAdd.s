.data
num1:
    .long 1
    .long 1

num2:
    .long 1
    .long 1

.text
.global _start

_start:
    movl num1, %edx
    movl num1+4, %eax
    addl num2, %edx
    addl num2+4, %eax
    jnc done
    addl $1, %edx
done:
    nop
