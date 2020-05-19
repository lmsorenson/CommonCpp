<a href="https://scan.coverity.com/projects/lmsorenson-commoncpp">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/21163/badge.svg?branch=create-parser-components"/>
</a>
<a href="https://travis-ci.org/github/lmsorenson/CommonCpp">
  <img alt="Travis CI Build Status" src="https://travis-ci.org/lmsorenson/CommonCpp.svg?branch=create-parser-components"/>
</a>


# CommonCpp
This repository is a set of common utility libraries.  Including:

1. ParseLib

## ParseLib
A primitive document access library.  A set of abstract read/write procedures that separates <i>what</i> from <i>how</i>.  That is <i>what</i> data we want to remember, and <i>how</i> the data is stored or implemented. <br></br>

Parse Lib reads and parses data into a format-neutral dataset which can be modified and written to multiple file formats.

### Architectural Description:
1. [Requirements](https://github.com/lmsorenson/CommonCpp/blob/master/libraries/ParseLib/docs/requirements.md#parselib-requirements---v1)</br>
2. [Context View](https://github.com/lmsorenson/CommonCpp/blob/master/libraries/ParseLib/README.md#context)</br>
3. [Functional View](https://github.com/lmsorenson/CommonCpp/blob/master/libraries/ParseLib/README.md#functional-view)</br>
4. [Information View](https://github.com/lmsorenson/CommonCpp/tree/master/libraries/ParseLib#information-view)</br>

<img align="center" src="libraries/ParseLib/docs/images/ParseLibUseCaseDiagram1.png" width="500"/>
