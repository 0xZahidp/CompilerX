#include "semantic_analysis.h"

Symbol* symbol_table = NULL;  // Global symbol table

// Create a new symbol and return its pointer
Symbol* create_symbol(char* name, int type) {
    Symbol* new_symbol = (Symbol*)malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->next = NULL;
    return new_symbol;
}

// Insert a symbol into the symbol table
void insert_symbol(char* name, int type) {
    Symbol* new_symbol = create_symbol(name, type);
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
}

// Look up a symbol in the symbol table
Symbol* lookup_symbol(char* name) {
    Symbol* current = symbol_table;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Symbol not found
}

// Print the symbol table (for debugging)
void print_symbol_table() {
    Symbol* current = symbol_table;
    while (current != NULL) {
        printf("Symbol: %s, Type: %d\n", current->name, current->type);
        current = current->next;
    }
}

// Free the symbol table memory
void free_symbol_table() {
    Symbol* current = symbol_table;
    while (current != NULL) {
        Symbol* temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
    symbol_table = NULL;
}
