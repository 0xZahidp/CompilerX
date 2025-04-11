#include "intermediate_code.h"
#include "code_generation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int temp_counter = 0;  // For creating unique temporary variables

// Create a new TAC instruction
TAC* create_tac(char *op, char *arg1, char *arg2, char *result) {
    TAC *tac = (TAC*)malloc(sizeof(TAC));
    tac->op = strdup(op);
    tac->arg1 = strdup(arg1);
    tac->arg2 = strdup(arg2);
    tac->result = strdup(result);
    tac->next = NULL;
    return tac;
}

// Generate TAC for an AST node
TAC* generate_tac(ASTNode* node) {
    if (node == NULL) return NULL;

    TAC *tac = NULL;

    switch (node->type) {
        case AST_NUMBER:
            {
                char temp[10];
                sprintf(temp, "%d", node->ival);
                tac = create_tac("MOV", temp, "", "t0");  // Example: Store number in t0
            }
            break;
        case AST_IDENTIFIER:
            {
                char temp[10];
                sprintf(temp, "%s", node->strval);
                tac = create_tac("MOV", temp, "", "t0");  // Example: Load identifier into t0
            }
            break;
        case AST_ADD:
            {
                TAC *left_tac = generate_tac(node->binop.left);
                TAC *right_tac = generate_tac(node->binop.right);
                char temp[10];
                sprintf(temp, "t%d", temp_counter++);
                tac = create_tac("ADD", "t0", "t1", temp);  // Example: t0 + t1 -> result
            }
            break;
        case AST_SUB:
            {
                TAC *left_tac = generate_tac(node->binop.left);
                TAC *right_tac = generate_tac(node->binop.right);
                char temp[10];
                sprintf(temp, "t%d", temp_counter++);
                tac = create_tac("SUB", "t0", "t1", temp);  // Example: t0 - t1 -> result
            }
            break;
        case AST_MUL:
            {
                TAC *left_tac = generate_tac(node->binop.left);
                TAC *right_tac = generate_tac(node->binop.right);
                char temp[10];
                sprintf(temp, "t%d", temp_counter++);
                tac = create_tac("MUL", "t0", "t1", temp);  // Example: t0 * t1 -> result
            }
            break;
        case AST_DIV:
            {
                TAC *left_tac = generate_tac(node->binop.left);
                TAC *right_tac = generate_tac(node->binop.right);
                char temp[10];
                sprintf(temp, "t%d", temp_counter++);
                tac = create_tac("DIV", "t0", "t1", temp);  // Example: t0 / t1 -> result
            }
            break;
        case AST_IF:
            {
                // Generate TAC for if statement
                TAC *condition_tac = generate_tac(node->binop.left);  // Condition
                char label_true[10], label_end[10];
                sprintf(label_true, "L%d", temp_counter++);
                sprintf(label_end, "L%d", temp_counter++);
                tac = create_tac("JZ", "t0", "", label_true);  // Jump if condition is false
                tac->next = create_tac("LABEL", label_true, "", "");  // Label for true block
            }
            break;
        case AST_WHILE:
            {
                // Generate TAC for while statement
                TAC *condition_tac = generate_tac(node->binop.left);  // Condition
                char label_start[10], label_end[10];
                sprintf(label_start, "L%d", temp_counter++);
                sprintf(label_end, "L%d", temp_counter++);
                tac = create_tac("LABEL", label_start, "", "");  // Loop start
                tac->next = create_tac("JZ", "t0", "", label_end);  // Jump if condition is false
                tac->next->next = create_tac("LABEL", label_end, "", "");  // End of loop
            }
            break;
    }

    return tac;
}

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
void print_tac(TAC* tac) {
    while (tac != NULL) {
        printf("%s %s, %s -> %s\n", tac->op, tac->arg1, tac->arg2, tac->result);
        tac = tac->next;
    }
}

// Free the memory allocated for TAC instructions
void free_tac(TAC* tac) {
    while (tac != NULL) {
        TAC *temp = tac;
        tac = tac->next;
        free(temp->op);
        free(temp->arg1);
        free(temp->arg2);
        free(temp->result);
        free(temp);
    }
}
