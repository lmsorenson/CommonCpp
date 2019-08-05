#  ParseLib Requirements - v1

## Functional Requirements
1. The library shall read and parse files of different formats and structures.</br>
1.1. The library shall read and parse RAW text files.</br>
1.2. The library shall read and parse CSV data files.</br>
1.3. The library shall read and parse OBJ data files.</br>
2. The library shall validate the format of the file as enumerated in the format specifications.</br>
2.1 If the library detects an invalid format no data will be returned.</br>
3. The library shall provide client code with a means to access each element within the file directly as enumerated in each file format's requirements.</br>
4. The read data structure should provide references to an instance's relationships (or related entities) as enumerated in each file format's requirements and data models.</br>
5. Elements within the read data structure should be uniquely identified.</br>
5.1 No two parse filters can have the same ID stem.</br>
6. The library shall write new data model instances to existing files.</br>
7. The library shall modify existing data model instances of existing files.</br>
8. The library shall write new files for data if no file exists.</br>

## Performance Requirements
1. A 10,000 line read should take less than 1/60th of a second.</br>
2. The file read shall indicate  noticably slow requirements.</br>
3. Concurrency.</br>

## Security Requirements
1. The library shall allow the client code to encrypt large data files.</br>
2. The library should be able to build using an encrypted hash function.</br>
3. Encrypted files will shall keep unathorized viewers from accessing data.</br>

## unsorted
3. If an invalid path is used the system shall indicate the error.</br>
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

