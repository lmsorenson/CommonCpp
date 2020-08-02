// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../hash_table.hpp"


using std::string;
using std::make_shared;
using std::shared_ptr;
using sdg::plHashElementIterator;
using sdg::plHashValue;

plHashElementIterator::plHashElementIterator(const string &aKey, plHashValue aValue)
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
    return 0;
}

plHashValue plHashElementIterator::assign_value_to_existing_key(const string &a_key, plHashValue a_value)
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

plHashValue plHashElementIterator::find_hash_value(const string &a_key) const
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

void plHashElementIterator::remove_value(const string &a_key)
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