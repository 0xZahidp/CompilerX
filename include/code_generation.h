#ifndef CODE_GENERATION_H
#define CODE_GENERATION_H

#include "intermediate_code.h"

// Function to generate assembly-like code from TAC
void generate_code(TAC* tac);

// Print the generated assembly code for debugging
void print_assembly(TAC* tac);

#endif
