#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#include "ast.h"

typedef struct TAC {
    char *op;      // Operation (e.g., "ADD", "MUL")
    char *arg1;    // First argument
    char *arg2;    // Second argument
    char *result;  // Result variable
    struct TAC *next;
} TAC;

TAC* generate_tac(ASTNode* node);  // Generate TAC from AST
void print_tac(TAC* tac);          // Print TAC for debugging
void free_tac(TAC* tac);          // Free TAC memory

#endif
