#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { 
    AST_NUMBER, 
    AST_IDENTIFIER, 
    AST_ASSIGN, 
    AST_ADD, 
    AST_SUB, 
    AST_MUL, 
    AST_DIV, 
    AST_IF, 
    AST_WHILE 
} ASTNodeType;

// Structure to represent a single node in the AST
typedef struct ASTNode {
    ASTNodeType type;  // Type of node (e.g., number, identifier, operator)
    union {
        int ival;          // For AST_NUMBER
        char *strval;      // For AST_IDENTIFIER
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
        } binop;            // For binary operators
    };
    struct ASTNode *next;  // For linked list of statements (in case of program, if, while, etc.)
} ASTNode;

// Functions to create AST nodes
ASTNode* create_number_node(int value);
ASTNode* create_identifier_node(char *name);
ASTNode* create_binop_node(ASTNodeType type, ASTNode *left, ASTNode *right);
ASTNode* create_if_node(ASTNode *condition, ASTNode *true_block, ASTNode *false_block);
ASTNode* create_while_node(ASTNode *condition, ASTNode *block);

void free_ast(ASTNode *node);  // Free the AST memory
void print_ast(ASTNode *node); // Print the AST for debugging

#endif
