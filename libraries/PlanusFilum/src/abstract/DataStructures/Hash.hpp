#pragma once
#include <vector>
#include <string>


class hTable;
class hElement;

 
class hTable
{
public:
    int32_t hTableSize;                         //size of the table.
    std::vector<std::shared_ptr<hElement>> table;                //storage for the table.
    int32_t ComputeIndex(std::string value);    //hash function.


    hTable(int32_t aHTableSize);
    ~hTable();

    int32_t Insert(std::string key, std::string value);  //insert into the table
    std::string Get(std::string key);   //get value
};


class hElement
{
    std::string value;  //
    std::shared_ptr<hElement> next;    //

public:
    hElement() = default;           //
    hElement(std::string aValue);   //
    ~hElement();                    //

    std::shared_ptr<hElement> Next();
    bool HasNext();
    void SetNext(hElement e);
    std::string GetValue();
};

