# Semantic Analyzer Design

## Problem Space
Given an abstract syntax tree a dataset needs to be constructed in a way that is overrideable by the developer.  Relationships need to be drawn between items produced by the parser.  In order to illustrate an example of these relationships I will use the example of a CSV dataset, in the semantic analysis stage of deserialization the parser has provided a set of records in the form of an abstract syntax tree.  At this point relationships between records have not been established, and the only relationships that are known are between a record and its set of values.  CSV format is tabular and a value in the table is what's known as an intersection entity, meaning that a value in the table is dependent on two or more entities.  A value is identified by its row and its column.  A requirement in the CSV format states that all columns shall have the same number of rows.  In order to validate semantic rules such as this it will be necessary to establish relationships and draw comparisons between the records in the document.

## Solution
A blackboard architecture could potentially do well to solve this problem.  A Semantic Net can be created incrementally by strategically placing lexical items from the abstract syntax tree onto a graph and noting conceptual dependencies as they are placed.

<ol>
<li>Lexical Item
<ol>
    <li>Entity</li>
    <li>Concept</li>
    <li>Relation</li>
    <li>Predicate</li>
</ol>
</ol>

<ol>
<li>Lexical Semantics
<ol>
    <li>Classification</li>
    <li>Concept</li>
    <li>Decomposition</li>
    <li>Compare and Contrast.</li>
</ol>
</ol>

First order predicate logic (FOPL)  
Semantic Nets  
Frames  
Conceptual dependency (CD)  
Rule-based architecture  
Case Grammar  
Conceptual Graphs  

## Citations
[Compiler Architecture - Layola Marymount University](https://cs.lmu.edu/~ray/notes/compilerarchitecture/)<br/>
[Semantic Analysis](https://www.tutorialspoint.com/natural_language_processing/natural_language_processing_semantic_analysis.htm)<br/>
[Time Complexity - Carnegie Melon University](https://www.cs.cmu.edu/~adamchik/15-121/lectures/Algorithmic%20Complexity/complexity.html)