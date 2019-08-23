// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "plDataSet.hpp"
#include <iostream>

using namespace std;




void plDataSet::TokenizeKeys(std::string a_key, std::function<void(int32_t key_i, int32_t index, string label)> lambda_expr)
{
    char * pch;
    pch = strtok((char*)a_key.c_str(),"-");

    //check every EntityKey in the passed in key
    while (pch != NULL)
    {
        char str[1];
        int32_t d;
        sscanf(pch, "%1s%i", str, &d);

        //Compare to each recognized key
        for(int i=0; i<this->recognized_key.size(); ++i)
        {
            //Check if the token's key matches a recognized key's label.
            if (strcmp(this->recognized_key[i]->GetLabel().c_str(), str)==0)
                lambda_expr(i, d, this->recognized_key[i]->GetLabel());
        }

        pch = strtok(NULL, "-");
    }

    delete[] pch;
}

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
    plInstance return_var;
    string key_buffer = aKey;

    string generated_key;

    bool data_missing = false;

    this->TokenizeKeys(
        key_buffer, 
        [=](int32_t key_i,int32_t index, string label){this->recognized_key[key_i]->SetIndex(index);}
        );
    

    string result;

    //generate a key.
    for(int i=0; i<this->recognized_key.size(); ++i)
    {
        //add the delimiter
        if (!generated_key.empty())
            generated_key.append("-");

        if(this->recognized_key[i]->GetIndex()!=-1)
        {
            //push key to the format.
            generated_key.append(this->recognized_key[i]->GetLabel());
            generated_key.append(to_string(this->recognized_key[i]->GetIndex()));
        }
        else
        {
            data_missing = true;
        }
    }

    return_var = plInstance(this, plInstance::VALID_INST);
    return_var.SetKey(aKey);//assign the key which was passed into this function.

    if (data_missing)
    {
        vector<string> matching_keys = hash_table.GetMatchingKeys(generated_key);
        for(int i=0; i<matching_keys.size(); ++i)
        {
            return_var.add(hash_table.get(matching_keys[i]));
        }
    }
    else
    {
        //return the value at the generated key
        return_var.add(hash_table.get(generated_key));
    }

    for(int i=0; i< this->recognized_key.size(); ++i)
    {
        this->recognized_key[i]->ClearIndex();
    }

    return (state==DATA_SET_GOOD)
    ? return_var
    : plInstance(this, plInstance::NULL_INST);
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

 int32_t plDataSet::EntityKey::ClearIndex()
 {
     index = -1;
 }

int32_t plDataSet::EntityKey::GetIndex(){return index;}