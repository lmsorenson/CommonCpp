// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../hash_table.hpp"
#include <iostream>

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::endl;
using std::cout;
using std::fixed;
using std::flush;
using sdg::plHashTable;
using sdg::plHashValue;
using sdg::hash::KeyInstance;

plHashTable::plHashTable()
: hash_table_size(100)
, table(100)
{
}

plHashTable::plHashTable(int32_t table_size_arg)
: hash_table_size(table_size_arg)
, table(hash_table_size)
{
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

    index %= hash_table_size;

    return index;
}

bool plHashTable::key_value_exists(KeyInstance a_key)
{
    int32_t index = compute_index(a_key.as_string());

    std::string value = table[index]->find(a_key.as_string());

    return !(value=="NULL");
}

plHashValue plHashTable::insert(KeyInstance key, plHashValue value)
{
    int32_t index = compute_index(key.as_string());

    shared_ptr<plHashElementIterator> e (table[index]);

    plHashValue replaced_key_value;

    //if the bucket is NOT null
    if (e!=nullptr)
    {
        stopwatch_.start();
        bool keyExists = this->key_value_exists(key);
        stopwatch_.stop();
        cout << fixed << "\rCheck key value exists: " << stopwatch_.read_seconds() << flush;

        if(keyExists)
        {
            replaced_key_value = e->assign_value_to_existing_key(key.as_string(), value);
        }
        else
        {
            e->set_last(plHashElementIterator(key.as_string(), value));
            this->hash_key_list.push_back(key);
        }
    }
    //if the bucket is null
    else
    {
        table[index]=make_shared<plHashElementIterator>(plHashElementIterator(key.as_string(), value));
        hash_key_list.push_back(key);
    }
    

    return replaced_key_value;
}

plHashValue plHashTable::move(KeyInstance old_key, KeyInstance new_key)
{
    plHashValue replaced_value;

    //create a new instance of the old hash value at a new loxation.
    replaced_value = this->insert( new_key, this->get_hash_value(old_key) );

    //delete the value at the old location.
    this->delete_value(old_key);

    return replaced_value;
}

void plHashTable::delete_value(KeyInstance a_key)
{
    table[compute_index(a_key.as_string())]->remove_value(a_key.as_string());
}

//returns the string value of a key in the hash table.
string plHashTable::get(KeyInstance a_key) const
{
    return table[compute_index(a_key.as_string())]->find(a_key.as_string());
}

//returns a plHashValue value from by a key from the hash_table.
plHashValue plHashTable::get_hash_value(KeyInstance a_key) const
{
    return table[compute_index(a_key.as_string())]->find_hash_value(a_key.as_string());
}

//returns a list of keys that matches the passed in descriptors.(hyphen delimited)
std::vector<KeyInstance> plHashTable::GetMatchingKeys(KeyInstance a_key_subset) const
{
    vector<KeyInstance> return_list;
    vector<KeyInstance> local_hash_keys = hash_key_list;
    vector<KeyInstance> local_hash_key_buffer;


    std::string local_key_subset = a_key_subset.as_string();

    auto function = [&](const std::string callback_token)
    {
        //iterate through all valid keys.
        for(int i=0; i<local_hash_keys.size(); ++i)
        {
            //check if the key matches the passed in key.
            if((local_hash_keys[i].as_string().find(callback_token))!=string::npos)
            {
                local_hash_key_buffer.push_back(local_hash_keys[i]);
            }
        }

        local_hash_keys.clear();
        local_hash_keys=local_hash_key_buffer;
        local_hash_key_buffer.clear();
    };

    a_key_subset.for_each_descriptor(function);

    return_list=local_hash_keys;

    return return_list;
}