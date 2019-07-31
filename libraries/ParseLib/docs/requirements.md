#  ParseLib Requirements - v1

## Functional Requirements
1. The library shall read and parse files of different formats and structures.  
1.1. The library shall read and parse RAW text files.  
1.2. The library shall read and parse CSV data files.  
1.3. The library shall read and parse OBJ data files.  
2. The library shall provide client code access to data instances within the file as enumerated in each file format's requirements.
3. The read data structure should provide references to an instance's relationships (or related entities) as enumerated in each file format's requirements and data models.
4. Elements within the read data structure should be uniquely identifiable.
4.1 No two parse filters can have the same ID stem.
5. The library shall write new data model instances to existing files.
6. The library shall modify existing data model instances of existing files.
7. The library shall write new files for data if no file exists.

## Performance Requirements
1. A 10,000 line read should take less than 1/60th of a second.
2. The file read shall indicate  noticably slow requirements.

## Security Requirements
1. The library shall allow the client code to encrypt large data files.  
2. The library should be able to build using an encrypted hash function.

## unsorted
3. If an invalid path is used the system shall indicate the error.
4. If the supplied File path begins with a slash, read the path as an absolute path.
5. If the supplied file path begins with a letter or a period treat the path as a relative path.
6. When accessing the data structure if a key does not exist then return an error.

## Interoperability Requirements
1. Cross platform  
1.1. MacOSX  
1.2. Fedora  
1.3. Windows  
2. Cross language  
1.1. C++  
1.2. C  
1.3. C#  
1.4. Java  
1.5. Python  

## Scalability Requirements
1. simple to add more formats.
