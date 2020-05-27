# Parser Design

## Problem Space
The parser consumes ordered tokens produced by the lexer.  The parser needs to interpret the tokens and assign them to the abstract syntax tree.  The parser shall <u>classify tokens</u>.  The parser shall manage token <u>scope</u>.  If the token represents a dependent entity that scope might be another token of the <u>parent type</u>.  If the token represents an independent entity that scope will probably be the <u>global scope</u> (which might be assigned to the root of the tree).

## Citations
[Compiler Architecture - Layola Marymount University](https://cs.lmu.edu/~ray/notes/compilerarchitecture/)
