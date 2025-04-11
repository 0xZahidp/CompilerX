#include "code_emission.h"
#include <stdio.h>
#include <stdlib.h>

void emit_code_to_file(TAC* tac, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    while (tac != NULL) {
        if (strcmp(tac->op, "MOV") == 0) {
            fprintf(file, "    li $t0, %s\n", tac->arg1);
        }
        else if (strcmp(tac->op, "ADD") == 0) {
            fprintf(file, "    add $t0, $t1, $t2\n");
        }
        else if (strcmp(tac->op, "SUB") == 0) {
            fprintf(file, "    sub $t0, $t1, $t2\n");
        }
        else if (strcmp(tac->op, "MUL") == 0) {
            fprintf(file, "    mul $t0, $t1, $t2\n");
        }
        else if (strcmp(tac->op, "DIV") == 0) {
            fprintf(file, "    div $t0, $t1, $t2\n");
        }
        else if (strcmp(tac->op, "LABEL") == 0) {
            fprintf(file, "%s:\n", tac->result);
        }
        else if (strcmp(tac->op, "JUMP") == 0) {
            fprintf(file, "    j %s\n", tac->result);
        }
        else if (strcmp(tac->op, "JZ") == 0) {
            fprintf(file, "    beq $t0, $zero, %s\n", tac->result);
        }
        else {
            fprintf(file, "Unknown operation: %s\n", tac->op);
        }

        tac = tac->next;
    }

    fclose(file);
}
