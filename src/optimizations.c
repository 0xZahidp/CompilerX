#include "optimizations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Example: Constant Folding optimization (simplifying constant expressions)
TAC* optimize_tac(TAC* tac) {
    if (tac == NULL) return NULL;

    if (strcmp(tac->op, "ADD") == 0 || strcmp(tac->op, "SUB") == 0) {
        // Check if both arguments are constants
        if (isdigit(tac->arg1[0]) && isdigit(tac->arg2[0])) {
            int result = 0;
            int op1 = atoi(tac->arg1);
            int op2 = atoi(tac->arg2);

            if (strcmp(tac->op, "ADD") == 0) result = op1 + op2;
            if (strcmp(tac->op, "SUB") == 0) result = op1 - op2;

            // Replace the operation with the constant result
            sprintf(tac->result, "%d", result);
            tac->op = strdup("MOV");  // Change operation to MOV for the result
            tac->arg1 = strdup(tac->result);
            tac->arg2 = strdup("");
        }
    }

    // Return the potentially optimized TAC
    tac->next = optimize_tac(tac->next);
    return tac;
}
