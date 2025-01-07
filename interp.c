/**
* @author   Jatin Jain
* @file     interp.c
* @desc     this is the implemetation for the main loop for the interpreter, the main dunction takes in an optional 
*           parameter [filename] whichb is used to build the symbol table , this then alls the rep() function from 
*           parse.c which perfoms the parsing and evaluation for each postfix expression
*/

#include "interp.h"
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"


int main(int argc, char* argv[]){
    if(argc > 2){
        fprintf(stderr, "Usage: interp [sym-table]\n");
        return EXIT_FAILURE;
    }

    //symbol_t* symbol_table = NULL; 

    if(argc == 2){
        build_table(argv[1]);
    } else{
        build_table(NULL);
    }
    

    dump_table();
   
    printf("Enter postfix expressions (CTRL-D to exit):\n");

    char line[MAX_LINE + 1];
    while(1){
        printf("> ");
        if((fgets(line, sizeof(line), stdin) == NULL))break;
        
        char *comment_start = strchr(line,'#');
        if(comment_start != NULL){
                *comment_start = '\0';
        }
        
        line[strcspn(line,"\n")] = '\0';

        if(strlen(line) == 0 || line[0] == '\n') continue;

        //printf("%s\n", line);
        rep(line);
    }
    printf("\n");    
    dump_table();
    //printf("\n");
    free_table();

    return EXIT_SUCCESS;
}

