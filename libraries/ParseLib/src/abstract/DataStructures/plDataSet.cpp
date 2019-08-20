// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "plDataSet.hpp"
#include <iostream>

using namespace std;




plDataSet::plDataSet()
: state(DATA_SET_EMPTY){}
plDataSet::plDataSet(State s)
: state(s){}
plDataSet::plDataSet(int32_t hash_table_size)
: hash_table(hash_table_size)
, state(DATA_SET_GOOD){}
plDataSet::~plDataSet(){}

plInstance plDataSet::get(std::string aKey)
{

    string key_buffer = aKey;
    string generated_key;

    //TOKENIZE THE KEY
    char * pch;
    pch = strtok((char*)key_buffer.c_str(),"-");

    //check every EntityKey in the passed in key
    while (pch != NULL)
    {
        char str[1];
        int32_t d;
        sscanf(pch, "%1s%i", str, &d);

        //Compare to each recognized key
        for(int i=0; i<recognized_key.size(); ++i)
        {
            //Check if the token's key matches a recognized key's label.
            if (strcmp(recognized_key[i]->GetLabel().c_str(), str)==0)
                recognized_key[i]->SetIndex(d);
        }

        pch = strtok(NULL, "-");
    }

    delete[] pch;

    //generate a key.
    for(int i=0; i<recognized_key.size(); ++i)
    {
        if (!generated_key.empty())
            generated_key.append("-");

        //push key to the format.
        generated_key.append(recognized_key[i]->GetLabel());
        if(recognized_key[i]->GetIndex()!=-1)
        {
            generated_key.append(to_string(recognized_key[i]->GetIndex()));
        }
    }


   return (state==DATA_SET_GOOD)
   ? plInstance(hash_table.get(generated_key))
   : plInstance(plInstance::NULL_INST);
}

int32_t plDataSet::set(std::string aKey, hValue aValue)
{
    switch (state)
    {
    case DATA_SET_EMPTY: state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: return hash_table.insert(aKey, hValue(aValue)); break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}


int32_t plDataSet::add_label(std::string new_label)
{
    recognized_key.push_back(make_shared<EntityKey>(EntityKey(new_label)));

    return 0;
}

plDataSet::EntityKey::EntityKey()
:label("")
,index(-1)
{
}
plDataSet::EntityKey::EntityKey(string a_label)
:label(a_label)
,index(-1)
{
}
plDataSet::EntityKey::~EntityKey()
{

}

string plDataSet::EntityKey::GetLabel(){return label;}

 int32_t plDataSet::EntityKey::SetIndex(int32_t a_index)
 {
     index = a_index;
     return 0;
 }

int32_t plDataSet::EntityKey::GetIndex(){return index;}