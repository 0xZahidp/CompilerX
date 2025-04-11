#include "code_generation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int label_counter = 0;  // For creating unique labels

// Generate assembly-like code from TAC
void generate_code(TAC* tac) {
    printf(".data\n");
    printf("newline: .asciiz \"\\n\"\n");
    printf(".text\n");
    printf("main:\n");

    while (tac != NULL) {
        if (strcmp(tac->op, "MOV") == 0) {
            // Example: MOV t0, 5 -> t0 = 5
            printf("    li $t0, %s\n", tac->arg1);
        }
        else if (strcmp(tac->op, "ADD") == 0) {
            // Example: ADD t0, t1, t2 -> t0 = t1 + t2
            printf("    add $t0, $t1, $t2\n");
        }
        else if (strcmp(tac->op, "SUB") == 0) {
            // Example: SUB t0, t1, t2 -> t0 = t1 - t2
            printf("    sub $t0, $t1, $t2\n");
        }
        else if (strcmp(tac->op, "MUL") == 0) {
            // Example: MUL t0, t1, t2 -> t0 = t1 * t2
            printf("    mul $t0, $t1, $t2\n");
        }
        else if (strcmp(tac->op, "DIV") == 0) {
            // Example: DIV t0, t1, t2 -> t0 = t1 / t2
            printf("    div $t0, $t1, $t2\n");
        }
        else if (strcmp(tac->op, "LABEL") == 0) {
            // Example: LABEL loop_start -> loop_start:
            printf("%s:\n", tac->result);
        }
        else if (strcmp(tac->op, "JUMP") == 0) {
            // Example: JUMP loop_start -> jump to loop_start
            printf("    j %s\n", tac->result);
        }
        else if (strcmp(tac->op, "JZ") == 0) {
            // Example: JZ t0, loop_start -> if t0 == 0, jump to loop_start
            printf("    beq $t0, $zero, %s\n", tac->result);
        }
        else {
            printf("Unknown operation: %s\n", tac->op);
        }

        tac = tac->next;  // Move to the next TAC instruction
    }

    printf("    li $v0, 10\n");  // Exit system call
    printf("    syscall\n");
}

// Print TAC for debugging purposes
void print_assembly(TAC* tac) {
    while (tac != NULL) {
        printf("%s %s, %s -> %s\n", tac->op, tac->arg1, tac->arg2, tac->result);
        tac = tac->next;
    }
}
