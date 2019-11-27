#include "../plHash.hpp"
#include <iostream>

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::endl;
using std::cout;

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

plHashElementIterator::plHashElementIterator(string aKey, plHashValue aValue) 
: key(aKey)
, value( plHashValue(aValue) )
{}
plHashElementIterator::~plHashElementIterator(){}

shared_ptr<const plHashElementIterator> plHashElementIterator::next() const
{
    return next_element;
}

shared_ptr<plHashElementIterator> plHashElementIterator::next()
{
    return next_element;
}

shared_ptr<plHashElementIterator> plHashElementIterator::previous()
{
    //todo-->define this function
}

plHashValue plHashElementIterator::assign_value_to_existing_key(std::string a_key, plHashValue a_value)
{
    plHashElementIterator * e = this;

    //if a value at the key exists.
    while(e!=nullptr)
    {
        //check if the key of the element is the same as
        //the key passed in.
       if (e->get_key() == a_key)
       {
            //record the value that is being replaced.
            plHashValue replaced_value = e->value;

            //assign the new value to the key.
            e->value = a_value;

            //return the replaced_value
            return replaced_value;
       }

       e = e->next().get();
    }

    return plHashValue();
}

bool plHashElementIterator::has_next() const
{
    return (this->next() != nullptr);
}

void plHashElementIterator::set_last(plHashElementIterator e)
{
    plHashElementIterator * x = this;

    //Find the last element
    while(x->has_next())
    {
        x = x->next().get();
    }

    x->next_element = make_shared<plHashElementIterator>(e);
}

string plHashElementIterator::find(string a_key) const
{
    const plHashElementIterator * e = this;

    //if a value at the key exists.
    while(e!=nullptr)
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

plHashValue plHashElementIterator::find_hash_value(string a_key) const
{
    const plHashElementIterator * e = this;

    //if a value at the key exists.
    while(e!=nullptr)
    {
        //check if the key of the element is the same as
        //the key passed in.
       if (e->get_key() == a_key)
       {
           //returns the correct value
           return e->value;
       }

       e = e->next().get();
    }

    return plHashValue("", "");
}

string plHashElementIterator::get_key() const
{
    return key;
}

string plHashElementIterator::get_value() const
{
    return value.get_value();
}

void plHashElementIterator::remove_value(string a_key)
{
    plHashElementIterator * e = this;

    //if a value at the key exists.
    while(e!=nullptr)
    {
        //check if the key of the element is the same as
        //the key passed in.
       if (e->get_key() == a_key)
       {
           //clears the key and value
           e->key.clear();
           e->value.clear_hash_value();
           return;
       }

       e = e->next().get();
    }
    //todo->close the gap between the two linked list elements before and after this one.
}


plHashValue::plHashValue()
: value("")
, parent_key("")
{}
plHashValue::plHashValue(string aValue, string aParentString)
: value(aValue)
, parent_key(aParentString)
{}
plHashValue::~plHashValue()
{}

bool plHashValue::is_valid()
{
    return !(value.empty() && parent_key.empty());
}

string plHashValue::get_value() const
{
    return value;
}

void plHashValue::clear_hash_value()
{
    value.clear();
    parent_key.clear();
}