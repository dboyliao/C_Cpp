# Chapter 2

Basic procedure for a compiler

- Lexical Analysis: parse the source code into to **tokens**.(lexer, scanner)
- Parsing: construct **parse tree**. Normally, it is called **syntax tree** or **abstract syntax tree (AST)**.
- Syntax Analysisy: In this stage, the compiler will analyse if there is any syntax or logical error in the AST, such as type-error.
- Code generation: generate machine code (or byte code) according to the sytax tree.


