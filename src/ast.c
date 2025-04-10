#include "ast.h"

// Create a node for a number (AST_NUMBER)
ASTNode* create_number_node(int value) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = AST_NUMBER;
    node->ival = value;
    node->next = NULL;
    return node;
}

// Create a node for an identifier (AST_IDENTIFIER)
ASTNode* create_identifier_node(char *name) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = AST_IDENTIFIER;
    node->strval = strdup(name);
    node->next = NULL;
    return node;
}

// Create a node for a binary operation (e.g., AST_ADD, AST_SUB, etc.)
ASTNode* create_binop_node(ASTNodeType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->binop.left = left;
    node->binop.right = right;
    node->next = NULL;
    return node;
}

// Create a node for an if statement
ASTNode* create_if_node(ASTNode *condition, ASTNode *true_block, ASTNode *false_block) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = AST_IF;
    node->binop.left = condition;
    node->binop.right = true_block;  // We assume false block is optional for simplicity
    node->next = false_block;
    return node;
}

// Create a node for a while loop
ASTNode* create_while_node(ASTNode *condition, ASTNode *block) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = AST_WHILE;
    node->binop.left = condition;
    node->binop.right = block;
    node->next = NULL;
    return node;
}

// Free the memory allocated for the AST
void free_ast(ASTNode *node) {
    if (node == NULL) return;
    if (node->type == AST_IDENTIFIER) {
        free(node->strval);
    } else if (node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV) {
        free_ast(node->binop.left);
        free_ast(node->binop.right);
    } else if (node->type == AST_IF || node->type == AST_WHILE) {
        free_ast(node->binop.left);
        free_ast(node->binop.right);
    }
    free(node);
}

// Print the AST for debugging purposes
void print_ast(ASTNode *node) {
    if (node == NULL) return;
    
    switch (node->type) {
        case AST_NUMBER:
            printf("Number: %d\n", node->ival);
            break;
        case AST_IDENTIFIER:
            printf("Identifier: %s\n", node->strval);
            break;
        case AST_ADD:
            printf("Add: \n");
            print_ast(node->binop.left);
            print_ast(node->binop.right);
            break;
        case AST_SUB:
            printf("Subtract: \n");
            print_ast(node->binop.left);
            print_ast(node->binop.right);
            break;
        case AST_MUL:
            printf("Multiply: \n");
            print_ast(node->binop.left);
            print_ast(node->binop.right);
            break;
        case AST_DIV:
            printf("Divide: \n");
            print_ast(node->binop.left);
            print_ast(node->binop.right);
            break;
        case AST_IF:
            printf("If: \n");
            print_ast(node->binop.left);  // Condition
            print_ast(node->binop.right); // True block
            if (node->next != NULL) {
                printf("Else: \n");
                print_ast(node->next);
            }
            break;
        case AST_WHILE:
            printf("While: \n");
            print_ast(node->binop.left);  // Condition
            print_ast(node->binop.right); // Block
            break;
    }
}
