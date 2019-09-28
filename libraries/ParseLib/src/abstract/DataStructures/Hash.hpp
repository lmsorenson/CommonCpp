#pragma once
#include <vector>
#include <string>


class plHashTable;
class plHashElement;

class plHashValue
{
    const std::string parent_key;
    const std::string value;

public:
    plHashValue()=default;
    plHashValue(std::string aValue, std::string aParentKey);
    ~plHashValue();

    std::string get_value() const;
};

 
class plHashTable
{
private:
    virtual int32_t compute_index(std::string aValue) const;    //hash function.
    
    int32_t hTableSize; //size of the table.
    std::vector<std::shared_ptr<plHashElement>> table;  //the table of data.
    std::vector<std::string> hash_key_list;             //a list of keys entered into this table.
    
public:
    //Constructors
    plHashTable() = default;
    plHashTable(int32_t table_size_arg);
    ~plHashTable();

    //Mutators
    int32_t insert(std::string key, plHashValue aValue);  //insert into the table

    //Accessors
    std::string get(std::string key) const;   //get value
    std::vector<std::string> GetMatchingKeys(std::string descriptor_list_str) const;
};


class plHashElement
{
private:
    const std::string key;                                //the key for the key-value pair.
    const plHashValue value;                              //the value of the element.
    std::shared_ptr<plHashElement> next_element;          //a pointer to the next element in the bucket(or with the same key)

public:
    plHashElement() = default;                            //
    plHashElement(std::string key, plHashValue aValue);   //
    ~plHashElement();                                     //

    std::shared_ptr<const plHashElement> next() const;
    bool has_next() const;
    void set_last(plHashElement e);
    std::string find(std::string a_key) const;
    std::string get_key() const;
    std::string get_value() const;
};



