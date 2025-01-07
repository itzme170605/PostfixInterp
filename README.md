

# Postfix Expression Interpreter

## Overview
This project implements a simple interpreter that evaluates postfix expressions. The interpreter reads expressions from the user or a file, parses them, and evaluates them using a symbol table for variable management. The implementation supports operations like addition (`+`), subtraction (`-`), multiplication (`*`), and division (`/`), along with basic symbol table operations.

## Features
- Parses and evaluates postfix expressions.
- Supports building a symbol table from an optional file.
- Provides interactive input with a REPL (Read-Eval-Print Loop).
- Allows adding comments in expressions using `#`.
- Includes unit tests for the symbol table module.

---

## File Structure
- **`interp.c`**: Main program implementing the REPL loop.
- **`parser.c`**: Handles parsing and evaluation of postfix expressions.
- **`symtab.c`**: Implements the symbol table for storing variables.
- **`stack.c`**: Stack implementation for expression evaluation.
- **`tree_node.c`**: Binary tree node implementation for intermediate representations.
- **`Makefile`**: Automates compilation and cleanup tasks.

---

## Getting Started

### Prerequisites
- **C Compiler**: GCC or any compiler supporting C99 standard.
- **Make**: For building the project.

### Build Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/postfix-interpreter.git
   cd postfix-interpreter
   ```

2. Build the project using the `Makefile`:
   ```bash
   make
   ```

   This will create the following executables:
   - `interp`: The main interpreter.
   - `symtab_test`: A test program for the symbol table.

---

## Usage

### Running the Interpreter
```bash
./interp [symbol-table-file]
```
- **`symbol-table-file`** (optional): A file containing initial variable definitions for the symbol table.

#### Example Session:
```bash
$ ./interp
Enter postfix expressions (CTRL-D to exit):
> 5 3 + =
8
> a 2 * =
a = 16
> # This is a comment
> a b + =
```

### Testing the Symbol Table
Run the symbol table tests:
```bash
./symtab_test
```

---

## Code Documentation
Each file is documented with function descriptions and usage details:
- **`interp.h`**: Declares functions for the main interpreter.
- **`parser.h`**: Functions for parsing and evaluating postfix expressions.
- **`stack.h` / `stack_node.h`**: Stack data structure for expression evaluation.
- **`symtab.h`**: Symbol table management functions.
- **`tree_node.h`**: Binary tree node implementation.

---

## Makefile Targets
- **`make`**: Builds all executables (`interp`, `symtab_test`).
- **`make clean`**: Removes object files.
- **`make realclean`**: Removes object files and executables.
- **`make archive`**: Creates a `archive.tgz` containing source files and `Makefile`.

---

## Contributing
Contributions are welcome! Please:
1. Fork the repository.
2. Create a feature branch.
3. Submit a pull request.



## Author
**Jatin Jain**  
Contact: jj7485@rit.edu
