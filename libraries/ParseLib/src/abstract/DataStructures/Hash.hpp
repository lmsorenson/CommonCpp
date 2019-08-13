#pragma once
#include <vector>
#include <string>


class hTable;
class hElement;

class hValue
{
    std::string parent_key;
    std::string value;

public:
    hValue()=default;
    hValue(std::string aValue, std::string aParentKey);
    ~hValue();

    std::string get_value();
};

 
class hTable
{
private:
    virtual int32_t compute_index(std::string aValue);    //hash function.
    int32_t hTableSize; //size of the table.
    std::vector<std::shared_ptr<hElement>> table;
    
public:
    hTable() = default;
    hTable(int32_t table_size_arg);
    ~hTable();

    int32_t insert(std::string key, hValue aValue);  //insert into the table
    std::string get(std::string key);   //get value
};


class hElement
{
private:
    std::string key;
    hValue value;  //
    std::shared_ptr<hElement> next_element;    //

public:
    hElement() = default;           //
    hElement(std::string key, hValue aValue);   //
    ~hElement();                    //

    std::shared_ptr<hElement> next();
    bool has_next();
    void set_next(hElement e);
    std::string get_key();
    std::string get_value();
};



