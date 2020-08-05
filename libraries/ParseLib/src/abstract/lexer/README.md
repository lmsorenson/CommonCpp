# Lexer Design
The Lexical Analyzer(lexer) scans a character stream for tokens.  The order of tokens matters, therefor the meaning or interpretation of a token depends on its context (or which types of tokens came before and after).  This design uses a series of state systems to track the context of characters.

## Specifications
<ol>
<li>The Lexer shall continuously process a stream of characters.</li>
<ol>
    <li>When a target exists and new characters are added to the input stream, the Lexer should begin filtering the stream into tokens. </li> 
    <li>The Lexer should stop processing when it's owner or another external party issues a stop signal to the Lexer.</li> 
</ol>
<li> The Lexer shall produce a stream of tokens.</li>
<ol>
    <li>If a Target is provided. </li>
</ol>
</ol>

## References
[Compiler Architecture - Layola Marymount University](https://cs.lmu.edu/~ray/notes/compilerarchitecture/)  <br/>
[State Pattern](https://www.tutorialspoint.com/design_pattern/state_pattern.htm)  <br/>
[Reducers & Transducers](https://medium.com/async-la/a-short-and-sour-guide-to-reducers-b5b54d3bb018)