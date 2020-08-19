# Metadata Requirements 
##### Version 1.

***

## Functional Requirements
<ol>
    <li>Add things.
    <ol>
        <li>No two things can have the same type and identifier.
        <ol>
            <li>If a second item with the same identifier is added to the model, it will not be added and will return an error status code.</li>
        </ol>
    </ol>
    <li>Get a list of identifying descriptors of an entity or granular entity.
    <ol>
        <li>If the specified entity has identifying attributes they will be included in the returned list.  </li>
        <li>If the specified entity has identifying links the idenfitying attributes of the identifying link's entity will be included in the returned list.  </li>
    </ol>
</ol>
 
***

## Glossary

<ul>
    <li>Descriptor
    <ul>
        <li>Descriptor ID</li>
        <li>Descriptor Instance</li>
    </ul>
    <li>Attribute
    <ul>
        <li>Attribute ID</li>
        <li>Attribute Instance</li>
    </ul>
    <li>Link
        <ul>
            <li>Link ID</li>
            <li>Link Instance</li>
        </ul>
    <li>Entity
    <ul>
        <li>Entity ID</li>
        <li>Entity Instance</li>
    </ul>
</ul>

***