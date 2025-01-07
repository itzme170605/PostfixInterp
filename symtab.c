/**
* author    Jatin Jain
* filename  symtab.c
* this is the implemetation for symbol table and its functions as define in the symtab.h file
*/


#define _DEFAULT_SOURCE
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//static field symbol_table, cannot be accessed outside this scope
static symbol_t* symbol_table = NULL;

//char *strdup(const char *str) {
//    size_t len = strlen(str) + 1;  // Include null terminator
//    char *copy = malloc(len);
//    if (copy == NULL) {
//        return NULL;  // Memory allocation failed
//    }
//    memcpy(copy, str, len);
//    return copy;
//}

symbol_t *create_symbol(char *name, int val){
    symbol_t *new_symbol = (symbol_t*)malloc(sizeof(symbol_t));
    if(!new_symbol){
        perror("Memory allocation failed create_symbol");
        exit(EXIT_FAILURE);
    }
    new_symbol->var_name = strdup(name);
    if(!new_symbol->var_name){
        perror("Memory allocation failed");
        free(new_symbol);
        exit(EXIT_FAILURE);
    }
    new_symbol->val = val;
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
    return new_symbol;
}

void build_table(char *filename){
    FILE *file = NULL;
    if(filename){
        file = fopen(filename,"r");
        if(!file){
            perror("Error in loading file");
            exit(EXIT_FAILURE);
        }
    }

    if(!file){
        symbol_table = NULL;
        return;
    }

    char line[BUFLEN];
    char name[BUFLEN];
    int value;

    while(fgets(line, sizeof(line), file)){
        if(line[0] == '#' || line[0] == '\n'){
            continue;
        }

        char *start = line;
        while(*start == ' ') start++;
        char *end = start + strlen(start) - 1;
        while(end > start && *end == 32) end--;
        *(end + 1) = '\0';

        int scanned = sscanf(start,"%s %d", name, &value);
        if(scanned == 2){
            create_symbol(name, value);
            //new_symbol->next = symbol_table;
            //symbol_table = new_symbol;
        }
    }

    if(file){
        fclose(file);
    }
}


void dump_table(void){
    if(symbol_table == NULL){
        return;
    }

    printf("SYMBOL TABLE:\n");
    symbol_t *current = symbol_table;
    while(current){
        printf("\tName: %s, Value: %d\n", current->var_name, current->val);
        current = current->next;
    }

}

symbol_t *lookup_table(char *variable){
    symbol_t *current = symbol_table;
    while(current){
        if(strcmp(current->var_name,variable) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}


void free_table(){
    symbol_t *current = symbol_table;
    while (current){
        symbol_t *next = current->next;
        free(current->var_name);
        free(current);
        current = next;
    }
    symbol_table = NULL;
}

