#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol Table Entry
typedef struct Symbol {
    char* name;         // Name of the variable
    int type;           // Type of the variable (INT, FLOAT)
    struct Symbol* next;
} Symbol;

// Symbol Table Functions
Symbol* create_symbol(char* name, int type);
void insert_symbol(char* name, int type);
Symbol* lookup_symbol(char* name);
void print_symbol_table();
void free_symbol_table();

#endif
