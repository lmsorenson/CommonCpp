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
    shared_ptr<plHashElementIterator> e (table[index]);

    //if the bucket is NOT null
    if (e!=nullptr)
    {
        e->set_last(plHashElementIterator(key, value));
        this->hash_key_list.push_back(key);
    }
    //if the bucket is null
    else
    {
        table[index]=make_shared<plHashElementIterator>(plHashElementIterator(key, value));
        hash_key_list.push_back(key);
    }
    

    return 0;
}

string plHashTable::get(string key) const
{
    return table[compute_index(key)]->find(key);
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

plHashElementIterator::plHashElementIterator(string aKey, plHashValue aValue) 
: key(aKey)
, value( plHashValue(aValue) )
{}
plHashElementIterator::~plHashElementIterator(){}

shared_ptr<const plHashElementIterator> plHashElementIterator::next() const
{
    return next_element;
}

bool plHashElementIterator::has_next() const
{
    return (this->next() != nullptr);
}

void plHashElementIterator::set_last(plHashElementIterator e)
{
    const plHashElementIterator * x = this;

    //Find the last element
    while(x->has_next())
    {
        x = x->next().get();
    }

    next_element = make_shared<plHashElementIterator>(e);
}

string plHashElementIterator::find(string a_key) const
{
    string ret = "";
    const plHashElementIterator * e = this;

    //if a value at the key exists.
    while((e!=nullptr) && (ret == ""))
    {
        //check if the key of the element is the same as
        //the key passed in.
       if (e->get_key() == a_key)
       {
           //returns the correct value
           return e->get_value();
       }

       e = e->next().get();
    }

    return "NULL";
}

string plHashElementIterator::get_key() const
{
    return key;
}

string plHashElementIterator::get_value() const
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