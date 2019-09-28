#pragma once
#include <vector>
#include <string>


class plHashTable;
class plHashElement;

class plHashValue
{
    std::string parent_key;
    std::string value;

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
    std::vector<std::shared_ptr<plHashElement>> table;

    std::vector<std::string> hash_key_list;
    
public:
    plHashTable() = default;
    plHashTable(int32_t table_size_arg);
    ~plHashTable();

    int32_t insert(std::string key, plHashValue aValue);  //insert into the table
    std::string get(std::string key) const;   //get value
    std::vector<std::string> GetMatchingKeys(std::string descriptor_list_str) const;
};


class plHashElement
{
private:
    std::string key;
    plHashValue value;  //
    std::shared_ptr<plHashElement> next_element;    //

public:
    plHashElement() = default;           //
    plHashElement(std::string key, plHashValue aValue);   //
    ~plHashElement();                    //

    std::shared_ptr<plHashElement> next() const;
    bool has_next() const;
    void set_next(plHashElement e);
    std::string get_key() const;
    std::string get_value() const;
};



