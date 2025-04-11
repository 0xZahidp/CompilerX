.data
newline: .asciiz "\n"

.text
main:
    li $t0, 5        # a = 5
    li $t1, 3        # b = 3
    add $t2, $t0, $t1  # result1 = a + b
    sub $t3, $t0, $t1  # result2 = a - b
    mul $t4, $t0, $t1  # result3 = a * b
    div $t5, $t0, $t1  # result4 = a / b

    li $v0, 10        # Exit system call
    syscall
