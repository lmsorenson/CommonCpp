#  ParseLib Requirements - v1

## Functional Requirements
1. The library shall create transactions to read and parse files of different sevaral formats.</br>
1.1. The library shall be capable of reading and parsing RAW text files.</br>
1.2. The library shall be capable of reading and parsing CSV data files.</br>
1.3. The library shall be capable of reading and parsing OBJ data files.</br>
2. The library shall validate the file at the given path as enumerated in the format specifications.</br>
2.1. By default when a transaction fails because of a format violation and the system attempts to query the resulting instance set, the system shall respond with a string that will indicate the invalid format.</br>
2.2. By default when a transaction fails because of an invalid file path and the system attempts to query the resulting instance set, the system shall respond with a string that will indicate the invalid file.</br>
3. The library shall provide client code a means to access each element within the file directly as enumerated in each file format's requirements.(With valid permission)</br>
3.1. If the library attempts to query a data element that does not exist the data set will return an error.</br>
4. The library shall query and filter the resulting data set by the entities within the data structure associated with the file.</br>
4.1. The library shall query the resulting data set for a single instance of an entity and its relations.</br><!--i.e. Get the field at some record-->
4.2. The library shall query the resulting data set for a list of related instances of a particular entity and its relations.  As enumerated in each file format's specification.</br><!--i.e. get all fields in a record/get all records of one field.-->
5. The read data structure should provide references to an instance's relationships (or related entities) as enumerated in each file format's requirements and data models.</br>
6. Elements within the read data structure should be uniquely identified.</br>
6.1 No two parse filters can have the same ID stem.</br>
7. The library shall write new data model instances to existing files.</br>
8. The library shall modify existing data model instances of existing files.</br>
9. The library shall write new files for data if no file exists.</br>


## Performance Requirements
1. A 10,000 line read should take less than 1/60th of a second.</br>
2. The file read shall indicate  noticably slow requirements.</br>
3. Concurrency.</br>

## Security Requirements
1. The library shall allow the client code to encrypt large data files.</br>
2. The library should be able to build using an encrypted hash function.</br>
3. Encrypted files will shall keep unathorized viewers from accessing data.</br>

## unsorted
4. If the supplied File path begins with a slash, read the path as an absolute path.</br>
5. If the supplied file path begins with a letter or a period treat the path as a relative path.</br>
6. When accessing the data structure if a key does not exist then return an error.</br>

## Interoperability Requirements
1. Cross platform</br>
1.1. MacOSX</br>
1.2. Fedora</br>
1.3. Windows</br>
2. Cross language</br>  
1.1. C++</br>
1.2. C</br>
1.3. C#</br>
1.4. Java</br>
1.5. Python</br>

## Scalability Requirements
1. simple to add more formats.</br>

