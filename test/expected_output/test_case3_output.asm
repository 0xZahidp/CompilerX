.data
newline: .asciiz "\n"

.text
main:
    li $t0, 5        # a = 5
    li $t1, 10       # b = 10
    slt $t2, $t0, $t1  # Check if a < b
    beq $t2, $zero, else_block  # Jump to else_block if a >= b
    add $t0, $t0, 1  # a = a + 1
    j end_if

else_block:
    sub $t1, $t1, 1  # b = b - 1

end_if:
    li $v0, 10       # Exit system call
    syscall
