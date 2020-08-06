<a href="https://app.codacy.com/manual/lmsorenson/CommonCpp?utm_source=github.com&utm_medium=referral&utm_content=lmsorenson/CommonCpp&utm_campaign=Badge_Grade_Dashboard">
  <img alt="Codacy badge"
       src="https://api.codacy.com/project/badge/Grade/c2d0837a40894b0b8965167d325bc722"/>
</a>

<a href="https://scan.coverity.com/projects/lmsorenson-commoncpp">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/21163/badge.svg"/>
</a>

<a href="https://travis-ci.org/github/lmsorenson/CommonCpp">
  <img alt="Travis CI Build Status" src="https://travis-ci.org/lmsorenson/CommonCpp.svg"/>
</a>

# CommonCpp

## ParseLib
ParseLib is an extensible data serialization & ETL tool.  A set of abstract read/write procedures that separates <i>what</i> from <i>how</i>.  That is <i>what</i> data we want to remember, and <i>how</i> the data is stored or implemented.  ParseLib provides methods to read and parse data into a format-neutral dataset which can be modified and written to any supported format.  ParseLib is also built to be extensible so that support for more formats can be included when needed.

### Getting Started
#### Reading a file
~~~cpp
auto file = CSV("/path/to/file.csv");
~~~
#### Traversing a dataset
~~~cpp
auto file = CSV("/path/to/file.csv");

auto column = file.column("name");

column.begin();
~~~
#### Modifying a dataset
~~~cpp
auto file = CSV("/path/to/file.csv");

file["Name"][5] = "John";
~~~
#### Writing a file
~~~cpp
auto file = CSV("/path/to/file.csv");

file["Name"][5] = "John";

file.Write();
~~~
#### ETL
~~~cpp
auto file = CSV("/path/to/file.csv");

OBJ(file).Write();
~~~

<img align="center" src="libraries/ParseLib/docs/images/ParseLibUseCaseDiagram1.png" width="500"/>
