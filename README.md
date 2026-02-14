# Lexical-Analyzer

A C-based implementation of a lexical analyzer that tokenizes source code into meaningful components such as keywords, identifiers, operators, literals, and special symbols.

## Overview

A lexical analyzer (also known as a scanner) is the first phase of a compiler.  
It reads source code as input and converts it into a sequence of tokens that can be processed by later stages such as parsing.

This project demonstrates the basic principles of lexical analysis using C.

## Features

- Identifies keywords
- Detects identifiers
- Recognizes operators
- Identifies special symbols
- Handles numeric constants
- Processes input from a source file

## How It Works

1. The program reads an input source file.
2. Characters are grouped into lexemes.
3. Each lexeme is compared against predefined patterns.
4. The corresponding token type is printed as output.

## Project Structure

All files are located in the root directory:

Lexical-Analyzer/
│
├── main.c        # Program entry point  
├── function.c    # Tokenization and classification logic  
├── header.h      # Token definitions and function declarations  
├── README.md  
└── .gitignore  

## Compilation

To compile using gcc:

```bash
gcc *.c -o lexer

## Usage

Run the program with an input file:

./lexer input.c
