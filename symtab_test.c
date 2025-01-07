#include "symtab.h"
#include <stdio.h>

int main() {
    printf("Building symbol table from file...\n");
    build_table("sym.1");  // Ensure you have the sym.1 file

    printf("Dumping symbol table:\n");
    dump_table();

    free_table();  // Free the symbol table memory
    printf("\nSymbol table memory freed.\n");

    return 0;
}

