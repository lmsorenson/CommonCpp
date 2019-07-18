#  ParseLib Requirements - v1

## Functional Requirements
1. read file.  
>1.1. Read entire file.  
>1.2. Read by line.  
>1.3. Read by data structure.  
  
  
2. No two  parse filters can have the same ID stem.
3. A 10,000 line read should take less than 1/60th of a second.
4. If an invalid path is used the system shall indicate the error.
5. If the supplied File path begins with a slash, read the path as an absolute path.
6. If the supplied file path begins with a letter or a period treat the path as a relative path.

7. When accessing the data structure if a key does not exist then return an error.

2. write file.  
>2.1. write entire file.  
>2.2. write line.  
>2.2.1. overwrite line.  
>2.2.2. insert line.  
>2.3. Write data structure element.  

3. Cross platform
4. simple to add more formats.
