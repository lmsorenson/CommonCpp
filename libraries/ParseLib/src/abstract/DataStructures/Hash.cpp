#include "Hash.hpp"
#include <iostream>


using namespace std;

hTable::hTable(int32_t table_size_arg)
{
    hTableSize = table_size_arg;
    table.resize(hTableSize);
}

hTable::~hTable()
{

}


int32_t hTable::compute_index(string value)
{
    int index = 1;

    for (string::iterator si = value.begin(); si!=value.end(); ++si)
    {
        index += (int)*si;
    }

    index %= hTableSize;

    return index;
}


int32_t hTable::insert(string key, hValue value)
{
    int32_t index = compute_index(key);
    shared_ptr<hElement> e (table[index]);

    //if the bucket is NOT null
    if (e!=nullptr)
    {
        //Find the last element
        while(e->has_next())
        {
            e = e->next();
        }

        e->set_next(hElement(key, value));
        key_list.push_back(key);
    }
    //if the bucket is null
    else
    {
        table[index]=make_shared<hElement>(hElement(key, value));
        key_list.push_back(key);
    }
    

    return 0;
}

string hTable::get(string key)
{
    string ret = "";

    shared_ptr<hElement> e = table[compute_index(key)];

    //if a value at the key exists.
    while((e!=nullptr) && (ret == ""))
    {
        //check if the key of the element is the same as
        //the key passed in.
       if (e->get_key() == key)
       {
           //returns the correct value
           return e->get_value();
       }

       e = e->next();
    }
    //should return an error if the correct value is not found.
    return "NULL";
}

vector<string> hTable::GetMatchingKeys(string str)
{
    vector<string> return_list;

    //iterate through all valid keys.
    for(int i=0; i<key_list.size(); ++i)
    {
        //check if the key matches the passed in key.
        if((key_list[i].find(str))!=string::npos)
            return_list.push_back(key_list[i]);
    }

    return return_list;
}

hElement::hElement(string aKey, hValue aValue) 
: key(aKey)
, value( hValue(aValue) )
{}
hElement::~hElement(){}

shared_ptr<hElement> hElement::next()
{
    return next_element;
}

bool hElement::has_next()
{
    return (this->next() != nullptr);
}

void hElement::set_next(hElement e)
{
    next_element = make_shared<hElement>(e);
}

string hElement::get_key()
{
    return key;
}

string hElement::get_value()
{
    return value.get_value();
}



hValue::hValue(string aValue, string aParentString)
: value(aValue)
, parent_key(aParentString)
{}
hValue::~hValue()
{}

string hValue::get_value()
{
    return value;
}