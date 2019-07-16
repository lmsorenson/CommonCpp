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


int32_t hTable::compute_index(std::string value)
{
    int index = 1;

    for (string::iterator si = value.begin(); si!=value.end(); ++si)
    {
        index += (int)*si;
    }

    index %= hTableSize;

    return index;
}


int32_t hTable::insert(string key, string value)
{
    int32_t index = compute_index(key);
    shared_ptr<hElement> e (table[index]);

    if (e!=nullptr)
    {
        //Find the last element
        while(e->has_next())
        {
            e = e->next();
        }

        e->set_next(hElement(value));
    }
    else
    {
        table[index]=make_shared<hElement>(hElement(value));
    }
    

    return 0;
}

std::string hTable::get(std::string key)
{
    return table[compute_index(key)]->get_value();
}


hElement::hElement(std::string aValue) : value(aValue){}
hElement::~hElement(){}

std::shared_ptr<hElement> hElement::next()
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

string hElement::get_value()
{
    return value;
}