# ParseLib

## Context
### Goals of the system:
1. Read and write files of many types.
2. Simplify file parsing so that a new system doesn't have to be learned for each filetype.

### External Entities:
1. CodexLib
    Provides an interfaces for encrypting and decrypting data.
2. Client code
    This is the code that uses the library.  The client code is dependent on interfaces offered by ParseLib.  One interface for reading files and one for writing files.

## Functional View

## Information View

## Development View

### Scenarios

1. <strong>Modifiability Scenario</strong></br>
<strong>Source of Stimulus:</strong></br>
A developer discovers the need for the library to support a new file format.</br>
<strong>Stimulus:</strong></br>
The developer adds a few new child components to the abstract classes in the system.  Writes a few extra unit tests then runs the test and moves on.</br>
<strong>Artifact:</strong></br>
The developer adds a new Read Strategy, Write Strategy, new pipeline filters, a pipeline target and a factory for the file format.</br>
<strong>Environment</strong>:</br>
The developer makes this change at design time.</br>
<strong>Response:</strong></br>
No new defects are introduced in reading and writing of other file formats, security of other file formats is not affected, performance is not affected.  The change takes a few hours at the most.</br>

## Performance Perspective

### Scenarios
1. <strong>Performance Scenario</strong></br>
<strong>Source of Stimulus:</strong></br>
The stimulus is source code of a client program or application a synchronous function call.</br>
<strong>Stimulus:</strong></br>
The requests come in a stochastic or sporadic manor only as defined in the client program.</br>
<strong>Artifact:</strong></br>
The client software is the artifact.</br>
<strong>Environment</strong></br>
The client program or system is at peak load.  The file is 10,000 lines.</br>
<strong>Response:</strong></br>
The library reads the file in half a second 90% of the time.</br>

## Security Perspective
