#ifndef SEMANTIC_ANALYSIS_H
#define SEMANTIC_ANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type identifiers for variables
#define INT_TYPE    1
#define FLOAT_TYPE  2

// Symbol Table Entry
typedef struct Symbol {
    char* name;         // Name of the variable (dynamically allocated)
    int type;           // Type of the variable (INT_TYPE or FLOAT_TYPE)
    struct Symbol* next; // Pointer to the next symbol in the table (for collision handling or list)
} Symbol;

// Symbol Table Functions
// Creates a new symbol with the given name and type
Symbol* create_symbol(const char* name, int type);

// Inserts a symbol into the table; assumes name is not already present
void insert_symbol(const char* name, int type);

// Looks up a symbol by name; returns NULL if not found
Symbol* lookup_symbol(const char* name);

// Prints the symbol table for debugging
void print_symbol_table();

// Frees all memory allocated for the symbol table
void free_symbol_table();

#endif