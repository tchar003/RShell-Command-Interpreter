

# RShell – Shell Interpreter

A custom shell implemented in C++ for CS100: Software Construction. RShell supports execution of Unix commands, logical operators (`&&`, `||`, `;`), built-in commands (`exit`, `test`, `[ ]`), and parentheses for grouping. Input is parsed into an abstract syntax tree (AST) and evaluated recursively.

## Features

- Command execution via `fork()` and `execvp()`
- Logical operator support: `&&`, `||`, `;`
- Built-in test evaluation: `test`, `[ -f file ]`, `[ -d dir ]`, `[ file ]`
- Recursive AST construction using design patterns
- Parenthesis grouping: `(... && ...) || (...)`

## Technical Highlights

- **C++11/14**: Smart pointers (`std::shared_ptr`), STL containers, RAII
- **Design patterns**: Interpreter, Composite, Command
- **System-level programming**: POSIX calls (`fork`, `execvp`, `stat`)
- **Manual memory management**: Safely handled raw `char*` for argument passing
- **Regex-based parsing**: Custom logic for command, operator, and grouping detection

## Project Structure

- `Base.h`: Abstract interface for all command tree nodes
- `Cmd.h/cpp`: Executes leaf shell commands and built-in logic
- `And/Or/Semi/Paren.h`: Logical/composite operator nodes
- `Executor.h/cpp`: Parses input, builds AST, triggers recursive execution
- `main.cpp`: Entry point, input loop, and user interaction

## Why This Project

This project demonstrates core skills in:

- C++ programming with attention to memory safety and system interaction
- Object-oriented design and software architecture
- Building tools that reflect real-world shell behavior and control flow

## Author

Tyler Chargualaf  
B.S. Computer Engineering, University of California, Riverside  
https://www.linkedin.com/in/tyler-chargualaf/