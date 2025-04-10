#include "intermediate_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int temp_counter = 0;  // To generate unique temporary variables

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
        // Add more cases for other operations (e.g., AST_SUB, AST_MUL, AST_DIV, etc.)
    }

    return tac;
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
