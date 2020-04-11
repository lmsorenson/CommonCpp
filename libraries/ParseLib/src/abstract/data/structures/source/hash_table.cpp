// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../hash_table.hpp"
#include <iostream>

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::endl;
using std::cout;
using sdg::plHashTable;
using sdg::plHashValue;

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

bool plHashTable::key_value_exists(std::string a_key)
{
    int32_t index = compute_index(a_key);

    std::string value = table[index]->find(a_key);

    return !(value=="NULL");
}

plHashValue plHashTable::insert(string key, plHashValue value)
{
    int32_t index = compute_index(key);
    shared_ptr<plHashElementIterator> e (table[index]);

    plHashValue replaced_key_value;

    //if the bucket is NOT null
    if (e!=nullptr)
    {
        if(this->key_value_exists(key))
        {
            replaced_key_value = e->assign_value_to_existing_key(key, value);
        }
        else
        {
            e->set_last(plHashElementIterator(key, value));
            this->hash_key_list.push_back(key);
        }
    }
    //if the bucket is null
    else
    {
        table[index]=make_shared<plHashElementIterator>(plHashElementIterator(key, value));
        hash_key_list.push_back(key);
    }
    

    return replaced_key_value;
}

plHashValue plHashTable::move(string old_key, string new_key)
{
    plHashValue replaced_value;

    //create a new instance of the old hash value at a new loxation.
    replaced_value = this->insert( new_key, this->get_hash_value(old_key) );

    //delete the value at the old location.
    this->delete_value(old_key);

    //todo-->finish defining this function.

    return replaced_value;
}

void plHashTable::delete_value(string a_key)
{
    //todo-->define this function
    table[compute_index(a_key)]->remove_value(a_key);
}

string plHashTable::get(string key) const
{
    return table[compute_index(key)]->find(key);
}

plHashValue plHashTable::get_hash_value(string key) const
{
    return table[compute_index(key)]->find_hash_value(key);
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




