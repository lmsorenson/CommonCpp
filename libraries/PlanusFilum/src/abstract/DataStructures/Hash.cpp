#include "Hash.hpp"
#include <iostream>


using namespace std;

hTable::hTable(int32_t aHTableSize)
{
    hTableSize = aHTableSize;
    table.resize(hTableSize);
}

hTable::~hTable()
{

}


int32_t hTable::ComputeIndex(std::string value)
{
    int index = 1;

    for (string::iterator si = value.begin(); si!=value.end(); ++si)
    {
        index += (int)*si;
    }

    index %= hTableSize;

    return index;
}


int32_t hTable::Insert(string key, string value)
{
    int32_t index = ComputeIndex(key);
    shared_ptr<hElement> e (table[index]);

    if (e!=nullptr)
    {
        //Find the last element
        while(e->HasNext())
        {
            e = e->Next();
        }

        e->SetNext(hElement(value));
    }
    else
    {
        table[index]=make_shared<hElement>(hElement(value));
    }
    

    return 0;
}

std::string hTable::Get(std::string key)
{
    if (table[ComputeIndex(key)]->HasNext())
    {
        cout << "HAS NEXT" << endl;
    }
    return table[ComputeIndex(key)]->GetValue();
}


hElement::hElement(std::string aValue) : value(aValue){}
hElement::~hElement(){}

std::shared_ptr<hElement> hElement::Next()
{
    return next;
}

bool hElement::HasNext()
{
    return (this->Next() != nullptr);
}

void hElement::SetNext(hElement e)
{
    next = make_shared<hElement>(e);
}

string hElement::GetValue()
{
    return value;
}