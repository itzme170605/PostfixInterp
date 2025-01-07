/**
* author    Jatin Jain
* filename  parser.c
* desc      this is the implementation for the parser as defined in the project and the .h files
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include <ctype.h>


static parse_error_t parse_error = PARSE_NONE;
static eval_error_t eval_error = EVAL_NONE;

int isOperator(char ch) {
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case '?':
            return 1; // True
        default:
            return 0; // False
    }
}


void rep(char* exp){
    parse_error = PARSE_NONE;
    eval_error = EVAL_NONE;
    //printf("test_input: %s\n",exp);
    tree_node_t* root = make_parse_tree(exp);
    
    //print_infix(root);
    //printf(" = ");
    if(parse_error != PARSE_NONE){
        return;
    }

    int result = eval_tree(root);

    if(eval_error != EVAL_NONE){
        return;
    }

    print_infix(root);
    printf(" = %d\n", result);
    
    cleanup_tree(root);
    return;

}

tree_node_t *parse(stack_t *stack){
    tree_node_t* right = NULL;
    tree_node_t* left = NULL;
    tree_node_t* node = NULL;
    tree_node_t* alt1 = NULL;
    tree_node_t* alt2 = NULL;
    tree_node_t* leaf = NULL;

    if(!stack || empty_stack(stack)){
        return NULL;
    }
    
    char* token = (char*) top(stack);
    pop(stack);

    if(isOperator(*token)){
        op_type_t op = NO_OP;
        if(strcmp(token, ADD_OP_STR) == 0) op = ADD_OP;
        if(strcmp(token, SUB_OP_STR) == 0) op = SUB_OP;
        if(strcmp(token, MUL_OP_STR) == 0) op = MUL_OP;
        if(strcmp(token, DIV_OP_STR) == 0) op = DIV_OP;
        if(strcmp(token, MOD_OP_STR) == 0) op = MOD_OP;
        if(strcmp(token, Q_OP_STR) == 0) op = Q_OP;
        if(strcmp(token, ASSIGN_OP_STR) == 0) op = ASSIGN_OP;
        
        if( op != Q_OP){
            right = parse(stack);
            left = parse(stack);
            node = make_interior(op, token, left, right);
            
            if(!left || !right || !node){
                cleanup_tree(node);
                if(leaf) cleanup_tree(leaf);
                right = NULL;
                left = NULL;
                node = NULL;
                fprintf(stderr, "Invalid operation\n");
                parse_error = TOO_FEW_TOKENS;
                return NULL;
            }
            //node = make_interior(op, token, left, right);
            return node;
        } else{
            alt2 = parse(stack);
            alt1 = parse(stack);
            
            right = make_interior(ALT_OP, ":", alt1, alt2);
            left = parse(stack);
            //tree_node_t* node = make_interior(op, token, condition, interior);
            node = make_interior(op, token, left, right);
            if(!alt2 || !alt1 || !right || !left){
                cleanup_tree(node);
                if(leaf) cleanup_tree(leaf);
                return NULL;
            }
            return node;
        }
        } else {
        exp_type_t exp_type;
        if(isdigit(token[0])){
            exp_type = INTEGER;
        } else if(isalpha(token[0])){
            exp_type = SYMBOL;
        } else {
            parse_error = ILLEGAL_TOKEN;
            fprintf(stderr, "Invalid token passed");
            return NULL;
        }

        leaf = make_leaf(exp_type, token);
        //free(token);
        //token = NULL;
        
        return leaf;

    }
}

tree_node_t *make_parse_tree(char *expr){
    if(!expr){
        fprintf(stderr, "Not enough token in expression");
        parse_error = TOO_FEW_TOKENS;
        return NULL;
    }

    stack_t* stack = make_stack();
    if(!stack){
        fprintf(stderr, "Memory allocation failed");
        return NULL;
    }

    char* token = strtok(expr, " \n");
    while(token){
        push(stack, token);
        token = strtok(NULL, " \n");
    }
    free(token);

    tree_node_t *root = parse(stack);
    
    if(!root && !empty_stack(stack)){
        fprintf(stderr, "Invalid expressions, not enough tokens\n");
        parse_error = TOO_FEW_TOKENS;
        free_stack(stack);
        //cleanup_tree(root);
        return NULL;
    }

    if(!empty_stack(stack)){
        fprintf(stderr, "invalid expression, too many tokens\n");
        parse_error = TOO_MANY_TOKENS;
        free_stack(stack);
        cleanup_tree(root);
        return NULL;
    }

    free_stack(stack);
    return root;
}

int eval_tree(tree_node_t* node){
    if(!node){
        fprintf(stderr,"Invalid expression\n");
        eval_error = UNKNOWN_OPERATION; 
        return EXIT_FAILURE;
    }
    if(node->type == LEAF){
        leaf_node_t* leaf = (leaf_node_t*)node->node;
        if(leaf->exp_type == INTEGER){
            return strtol(node->token, NULL, 10);
        } else {
            symbol_t* sym = lookup_table(node->token);
            if(sym == NULL){
                eval_error = UNDEFINED_SYMBOL;
                fprintf(stderr, "Undefined symbol %s\n",node->token);
                return EXIT_FAILURE;
            }
            return sym->val;
        }
    }else{
        interior_node_t* interior_node = (interior_node_t*)node->node;
        op_type_t op = interior_node->op;
        tree_node_t * left = interior_node->left;
        tree_node_t * right = interior_node->right;
        if(op != ASSIGN_OP){
            if(op == Q_OP){
                
                int leftVal = eval_tree(left);
                interior_node_t* alt = (interior_node_t*)right->node;
                if(leftVal == 0) return eval_tree(alt->right);
                return eval_tree(alt->left);
            }

            //normal stuff
            int leftVal = eval_tree(left);
            int rightVal = eval_tree(right);
            if(parse_error != PARSE_NONE && eval_error != EVAL_NONE){
                fprintf(stderr, "error");
                return EXIT_FAILURE;
            }
            if(op == ADD_OP) return (leftVal + rightVal);
            if(op == SUB_OP) return (leftVal - rightVal);
            if(op == MUL_OP) return (leftVal * rightVal);
            if(op == DIV_OP) {
                if(rightVal == 0){
                    fprintf(stderr, "Division by zero\n");
                    eval_error = DIVISION_BY_ZERO;
                    return EXIT_FAILURE;
                }
                return (leftVal / rightVal);
            }
            if(op == MOD_OP){
                if(rightVal == 0){
                    fprintf(stderr, "Division by zero\n");
                    eval_error = DIVISION_BY_ZERO;
                    return EXIT_FAILURE;
                }
                return (leftVal % rightVal);
            }
        }else{
            if(!left){
                fprintf(stderr, "Invalid LValue");
                eval_error = INVALID_LVALUE;
            }
            leaf_node_t* leaf = (leaf_node_t*)left->node;
            if(left->type != LEAF && leaf->exp_type != SYMBOL){
                fprintf(stderr, "invalid syntax");
                eval_error = INVALID_LVALUE;
                return EXIT_FAILURE;
            }
            char* sym = left->token;
            int val = eval_tree(right);
            symbol_t* symbol = lookup_table(sym);
            if(!symbol){ 

                create_symbol(sym, val);
            }else{
                symbol->val = val;
            }
            //newSymbol->next = symbol_table;
            //symbol_table = newSymbol;
            return val;
        }
    }
    return 0;
}


void print_infix(tree_node_t* node){
    if(node == NULL){
        return;
    }
    if(parse_error != PARSE_NONE){
        return;
    }
    if(node->type == LEAF){
        printf("%s", node->token);
        return;
    }

    printf("(");
    interior_node_t* interior = (interior_node_t*)node->node;

    print_infix(interior->left);
    
    printf("%s",node->token);

    print_infix(interior->right);

    printf(")");
}

void cleanup_tree(tree_node_t* node){
    if(node == NULL){
        return;
    }
    if(node->type == INTERIOR){
        interior_node_t* interior = (interior_node_t*)node->node;
        
        cleanup_tree(interior->left);
        cleanup_tree(interior->right);
        
        free(node->node);
        node->node = NULL;
    } else if(node->type == LEAF){
        //leaf_node_t* leaf = (leaf_node_t*)node->node;
        free(node->node);
        node->node = NULL;
    }
    if(node->token != NULL){
        free(node->token);
        node->token = NULL;
    }
    free(node);
}

