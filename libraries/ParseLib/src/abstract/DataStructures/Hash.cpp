#include "Hash.hpp"
#include <iostream>


using namespace std;

plHashTable::plHashTable(int32_t table_size_arg)
{
    hTableSize = table_size_arg;
    table.resize(hTableSize);
}

plHashTable::~plHashTable()
{

}


int32_t plHashTable::compute_index(string value) const
{
    int index = 1;

    for (string::iterator si = value.begin(); si!=value.end(); ++si)
    {
        index += (int)*si;
    }

    index %= hTableSize;

    return index;
}


int32_t plHashTable::insert(string key, plHashValue value)
{
    int32_t index = compute_index(key);
    shared_ptr<plHashElement> e (table[index]);

    //if the bucket is NOT null
    if (e!=nullptr)
    {
        //Find the last element
        while(e->has_next())
        {
            e = e->next();
        }

        e->set_next(plHashElement(key, value));
        this->hash_key_list.push_back(key);
    }
    //if the bucket is null
    else
    {
        table[index]=make_shared<plHashElement>(plHashElement(key, value));
        hash_key_list.push_back(key);
    }
    

    return 0;
}

string plHashTable::get(string key) const
{
    string ret = "";

    shared_ptr<plHashElement> e = table[compute_index(key)];

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

vector<string> plHashTable::GetMatchingKeys(string descriptor_list_str) const
{
    vector<string> return_list;

    char * token=strtok((char*)descriptor_list_str.c_str(), "-");
    vector<string> 
        local_hash_keys = hash_key_list,
        local_hash_key_buffer;

    while(token!=NULL)
    {
        //iterate through all valid keys.
        for(int i=0; i<local_hash_keys.size(); ++i)
        {
            //check if the key matches the passed in key.
            if((local_hash_keys[i].find(token))!=string::npos)
            {
                local_hash_key_buffer.push_back(local_hash_keys[i]);
            }
        }

        local_hash_keys.clear();
        local_hash_keys=local_hash_key_buffer;
        local_hash_key_buffer.clear();

        token=strtok(NULL, "-");
    }

    return_list = local_hash_keys;

    delete[] token;
    return return_list;
}

plHashElement::plHashElement(string aKey, plHashValue aValue) 
: key(aKey)
, value( plHashValue(aValue) )
{}
plHashElement::~plHashElement(){}

shared_ptr<plHashElement> plHashElement::next() const
{
    return next_element;
}

bool plHashElement::has_next() const
{
    return (this->next() != nullptr);
}

void plHashElement::set_next(plHashElement e)
{
    next_element = make_shared<plHashElement>(e);
}

string plHashElement::get_key() const
{
    return key;
}

string plHashElement::get_value() const
{
    return value.get_value();
}



plHashValue::plHashValue(string aValue, string aParentString)
: value(aValue)
, parent_key(aParentString)
{}
plHashValue::~plHashValue()
{}

string plHashValue::get_value() const
{
    return value;
}