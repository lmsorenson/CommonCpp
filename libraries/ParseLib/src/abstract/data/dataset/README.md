# DataSet Requirements 
##### Version 1.

***

<ol>
    <li>A DataSet shall contain a set of key-value pairs.
    <ol>
        <li>Keys shall contain a possibly-empty set of descriptors.  No two values shall have the same set of descriptors.</li>
        <li>Entities with multiplicity should have one or more ORDINAL descriptors.  </li>
        <li>BOOLEAN descriptors are optional.  </li>
        <li>Key-values can be empty.  A key-value is empty if the key exists and the corresponding value is empty.  </li>
        <li>Key-values can be null.  A key-value is null if the key does not exist on the DataSet.</li>
    </ol>
    <li>The program shall be able to add key-value pairs to the DataSet.
    <ol>
        <li>Key-value pairs can be added to a specific position within a set.</li>
        <li>If a key-value pair exists at the specified position, the course of action will depend on the parameters of the entity being added.
        <ol>
            <li>If the entity has multiplicity, overwritten item will be repositioned within the set.
            <li>If the entity does not have multiplicity, the overwritten key will be lost.  </li>
            <li>The DataSet shall be configurable, such that additions can permanently overwrite keys. </li>
        </ol>
        <li>If a desired position is not specified the dataset shall add the key-value pair to the end of the set.  </li>
        <li>If the dataset is in a bad state, the key-value pair shall not be added to the dataset and an error will be thrown. </li>
        <li>If the dataset is in a unknown state, the key-value pair shall not be added to the dataset and an error will be thrown. </li>
    </ol>
    <li>The program shall be able to remove key-value pairs from the DataSet.  </li>
    <li>The program shall be able to reposition key-value pairs in the DataSet. </li>
</ol>
 
***