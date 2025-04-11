.data
newline: .asciiz "\n"

.text
main:
    li $t0, 10       # x = 10
    li $t1, 20       # y = 20
    add $t2, $t0, $t1  # z = x + y

    li $v0, 10        # Exit system call
    syscall
