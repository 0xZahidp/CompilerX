#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type identifiers for variables
#define INT_TYPE 1
#define FLOAT_TYPE 2

// Enum for AST node types
typedef enum {
    AST_NUMBER,      // Integer literal
    AST_IDENTIFIER,  // Variable name
    AST_ASSIGN,      // Assignment (var = expr)
    AST_ADD,         // Addition
    AST_SUB,         // Subtraction
    AST_MUL,         // Multiplication
    AST_DIV,         // Division
    AST_IF,          // If statement
    AST_WHILE,       // While loop
    AST_RETURN,      // Return statement
    AST_PRINT,       // Print statement
    AST_DECL,        // Variable declaration
    AST_BLOCK        // Block of statements
} ASTNodeType;

// Structure to represent a single node in the AST
typedef struct ASTNode {
    ASTNodeType type;  // Type of node
    union {
        int ival;          // For AST_NUMBER
        char* strval;      // For AST_IDENTIFIER
        struct {
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;           // For AST_ADD, AST_SUB, AST_MUL, AST_DIV, AST_ASSIGN, AST_BLOCK
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_branch;
            struct ASTNode* else_branch;
        } if_node;         // For AST_IF
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } while_node;      // For AST_WHILE
        struct {
            struct ASTNode* expr;
        } return_node;     // For AST_RETURN
        struct {
            struct ASTNode* expr;
        } print_node;      // For AST_PRINT
        struct {
            char* name;
            int type;      // INT_TYPE or FLOAT_TYPE
        } decl_node;       // For AST_DECL
    } value;
} ASTNode;

// Functions to create AST nodes
ASTNode* create_number_node(int value);
ASTNode* create_identifier_node(char* name);
ASTNode* create_binop_node(ASTNodeType type, ASTNode* left, ASTNode* right);
ASTNode* create_assign_node(char* name, ASTNode* expr);
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
ASTNode* create_while_node(ASTNode* condition, ASTNode* body);
ASTNode* create_return_node(ASTNode* expr);
ASTNode* create_print_node(ASTNode* expr);
ASTNode* create_decl_node(char* name, int type);
ASTNode* create_block_node(ASTNode* left, ASTNode* right);

void free_ast(ASTNode* node);  // Free the AST memory
void print_ast(ASTNode* node); // Print the AST for debugging

#endif