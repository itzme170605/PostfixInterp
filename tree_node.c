/**
* @author       Jatin Jain
* @file         tree_node.c
* @desc         implementation for tree_node adt as defioned in the project requirements, and the .h file
*/

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include "tree_node.h"
#include <string.h>


// Construct an interior node dynamically on the heap.
// @param op  the operation (add, subtract, etc.)
// @param token  the token that derives this node
// @param left  pointer to the left child of this node
// @param right pointer to the right child of this node
// @return the new TreeNode, or NULL if error
tree_node_t * make_interior(op_type_t op, char *token, tree_node_t *left, tree_node_t *right){
    tree_node_t *new_node = (tree_node_t*)malloc(sizeof(tree_node_t));
    if(new_node == NULL){
        return NULL;
    }
    new_node->type = INTERIOR;
    new_node->token = strdup(token);
    new_node->node = (interior_node_t*)malloc(sizeof(interior_node_t));
    if(new_node->node == NULL){
        free(new_node->token);
        free(new_node);
        perror("Memory allocation Failed");
        return NULL;
    }

    interior_node_t *interior = (interior_node_t*)new_node->node;

    interior->op = op;
    interior->left = left;
    interior->right = right;

    return new_node;
}

// Construct a leaf node dynamically on the heap.
// @param expType  the operation token type (INTEGER or SYMBOL)
// @param token  the token that derives this node
// @return the new TreeNode, or NULL if error
tree_node_t *make_leaf(exp_type_t exp_type, char *token){
    tree_node_t *new_node = (tree_node_t*)malloc(sizeof(tree_node_t));
    if(new_node == NULL){
        perror("Memory allocation failed");
        return NULL;
    }
    new_node->type = LEAF;
    new_node->token = strdup(token);
    new_node->node = (leaf_node_t*)malloc(sizeof(leaf_node_t));
    if(new_node->node == NULL){
        free(new_node->token);
        free(new_node);
        perror("Memory allocation failed");
        return NULL;
    }
    leaf_node_t *leaf = (leaf_node_t*)new_node->node;
    leaf->exp_type = exp_type;

    return new_node;
}

