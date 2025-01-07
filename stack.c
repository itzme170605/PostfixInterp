/**
* @author       Jatin Jain
* @file         stack.c 
* @description   
* Implementation for stack_ADT defined in stack.h and project 
* requirements. 
*/

#include "stack.h"
#include <stdlib.h>
#include <stdio.h>


stack_t *make_stack(){
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if(!stack){
        perror("Memory allocation Failed:9::make_stack::stack.c");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

void push(stack_t *stack, void *data){
    if(!stack){
        fprintf(stderr,"Value of NULL type passed, expected stack_t");
        exit(EXIT_FAILURE);
    }

    stack_node_t *new_node = (stack_node_t*)malloc(sizeof(stack_node_t));
    if(!new_node){
        perror("Memory allocation failed 24:push::stack.c");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

void *top(stack_t *stack){
    if(!stack){
        fprintf(stderr, "unintialized stack passed");
        exit(EXIT_FAILURE);
    }
    
    if(stack->top == NULL){
        fprintf(stderr,"StackUnderflow");
        exit(EXIT_FAILURE);
    }
    //return stack->top; //returning the popinter to stack_node_t 
    return stack->top->data;
}

void pop(stack_t *stack){
    if(!stack){
        fprintf(stderr, "Invalid args");
        exit(EXIT_FAILURE);
    }
    if(stack->top == NULL){
        exit(EXIT_FAILURE);
    }

    stack_node_t *temp = stack->top;
    stack->top = temp->next;
    free(temp);
}

int empty_stack(stack_t *stack){
    return stack->top == NULL;
}

void free_stack(stack_t *stack){
    if(!stack){
        return;
    }
    while(!empty_stack(stack)){
        pop(stack);
    }

    free(stack);
}

