# ToyLanguage Compiler & Tree-Walk Interpreter

A standalone, lightweight C++ compiler and tree-walk interpreter built entirely from scratch without external libraries or frameworks. This project demonstrates core concepts in compiler construction, programming language implementation, and modern C++ system design.

---

## Technical Overview

The goal of this project is to implement a complete front-end and execution environment for a custom procedural programming language, featuring manual memory management via modern C++ smart pointers and clean OOP abstractions.

### Core Stack & Architecture
* **Language:** Modern C++ (C++17)
* **Build Tooling:** `g++` / MinGW GCC toolchain
* **Memory Management:** RAII pattern with explicit ownership transfer via `std::unique_ptr` and `std::move`
* **Design Patterns:** Polymorphic AST traversal, Recursive Descent Parsing, Encapsulated Symbol Tables

---

## Pipeline & Components

Source Code  ->  Lexer  ->  Tokens  ->  Parser  ->  AST  ->  Interpreter / Environment

## Building and Running

### Prerequisites 
  GCC C++ Compiler (g++) with C++17 support.

### Compilation
  g++ -Wall -Wextra -Iinclude src/*.cpp -o main.exe

### Execution
  .\main.exe
