#pragma once
#include <vector>
#include <string>






namespace sdg
{

/* 
* Hash Value
* -- Value in a hash bucket.  Includes metadata about the value.
*
*/
class plHashValue
{
    //@param parent_key = todo-> I forgot what this is used for.  
    //I think this is the key that owns this value.
    std::string parent_key;

    //@param value = the main value stored in the object.
    std::string value;

public:
    plHashValue();
    plHashValue(std::string aValue, std::string aParentKey);
    ~plHashValue();

    bool is_valid();

    //get_value()
    std::string get_value() const;

    //nullifys this object.
    //this method clears all of the values on this object.
    void clear_hash_value();
};




/* 
* Hash Element Iterator
* -- a hash value on a linked list.
* -- more or less a linked list of elements that will be stored at 
* -- the same index on the hash table.
*/
class plHashElementIterator
{
private:
    //the hash key
    std::string key;

    //the value
    plHashValue value;

    //a pointer to the next element in the linked list.
    std::shared_ptr<plHashElementIterator> next_element;

    //** Notice ** this method should be kept private.
    //a form of the next() function to be used internally.
    //this method is meant to allow access to clear the 
    //element during a delete procedure.
    std::shared_ptr<plHashElementIterator> next();
    std::shared_ptr<plHashElementIterator> previous();


public:
    plHashElementIterator() = default;                            
    plHashElementIterator(std::string key, plHashValue aValue);   
    ~plHashElementIterator();                                     

    //returns a const pointer to the next element in the linked list.
    std::shared_ptr<const plHashElementIterator> next() const;

    //returns a boolean value that is true if the element 
    //is not the last in the list, and false if it is
    //the last element in the list.
    bool has_next() const;

    //this method adds another element 'e' to the end of this linked list.
    void set_last(plHashElementIterator e);

    //this method finds a specific element in the linked list by its key.
    std::string find(std::string a_key) const;

    //this method finds a specific element in the linked list by its key and returns 
    //the whole hash value along with it's metadata.
    plHashValue find_hash_value(std::string a_key) const;

    plHashValue assign_value_to_existing_key(std::string a_key, plHashValue a_value);

    //returns the value of the key.
    std::string get_key() const;
    
    //returns the value of the value.
    std::string get_value() const;

    //deletes the value.
    void remove_value(std::string a_key);
};
 


 
/* 
* Hash Table
* -- 
* -- more or less a linked list of elements that will be stored at 
* -- the same index on the hash table.
*/
class plHashTable
{
private:
    //takes in a hash key as a parameter by value and returns the apropriate array index.
    virtual int32_t compute_index(std::string a_hash_key) const;
    
    //the number of elements in the hash table array.
    int32_t hash_table_size;

    //the hash table.
    std::vector<std::shared_ptr<plHashElementIterator>> table;  

    //a list of keys entered into this table.
    std::vector<std::string> hash_key_list;             


    bool key_value_exists(std::string a_key);
    
public:
    //Constructors
    plHashTable();
    plHashTable(int32_t table_size_arg);
    ~plHashTable();



    /*      Mutators        */

    //inserts a key and value into the hash table.
    plHashValue insert(std::string key, plHashValue aValue);

    //moves a hash value from one key to another.
    plHashValue move(std::string old_key, std::string new_key);

    //deletes a hash key and hash value from the hash table.
    void delete_value(std::string a_key);



    /*      Accessors     */

    //returns the string value of a key in the hash table.
    std::string get(std::string key) const;

    //returns a plHashValue value from by a key from the hash_table.
    plHashValue get_hash_value(std::string key) const;

    //returns a list of keys that matches the passed in descriptors.(hyphen delimited)
    std::vector<std::string> GetMatchingKeys(std::string descriptor_list_str) const;
};


}// namespace sdg