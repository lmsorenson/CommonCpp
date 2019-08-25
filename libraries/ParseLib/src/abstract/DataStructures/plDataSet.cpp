// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "plDataSet.hpp"
#include <iostream>

using namespace std;




void plDataSet::id_lexer(
    string a_partial_identifier, 
    function<void(int32_t key_i, int32_t index, string label)> lambda_expr,
    function<void(std::string label_not_found)> lambda_expr2)
{
    char * pch = strtok((char*)a_partial_identifier.c_str(),"-");

    //check every EntityKey in the passed in key
    while (pch != NULL)
    {
        char str[1];
        int32_t d;
        sscanf(pch, "%1s%i", str, &d);
        vector<bool> v_b_found;

        //initialize a boolean for each expected descriptor,
        //that indicates if that descriptor was found
        for (int i=0; i<this->expected_descriptors.size();++i)
        {
            //before searching this is false.
            v_b_found.push_back(false);
        }

        //Compare to each expected descriptor
        for(int i=0; i<this->expected_descriptors.size(); ++i)
        {
            //Check if the token's key matches an expected descriptor's label.
            if (strcmp(this->expected_descriptors[i]->GetLabel().c_str(), str)==0)
            {
                //call the passed expression
                lambda_expr(i, d, this->expected_descriptors[i]->GetLabel());
                
                //indicate that this key was found
                v_b_found[i]=true;
            }
        }
        
        if(lambda_expr2)
        {
            for (int i=0; i<this->expected_descriptors.size();++i)
            {
                //pass the missing descriptor to the calling context
                //if the descriptor was not matched.
                if (!v_b_found[i])
                    lambda_expr2(this->expected_descriptors[i]->GetLabel());   
            }
        }  

        pch = strtok(NULL, "-");
    }

    delete[] pch;
}

vector<std::string> plDataSet::get_missing_descriptors(std::string a_descriptor_labels)
{
    vector<std::string> r_missing_descriptors;

    this->id_lexer(
        a_descriptor_labels,
        [=](int32_t key_i,int32_t index, string label)
        {
            //if there is a match
        },
        [&](std::string label_not_found)
        {
            //if there is not a match
            r_missing_descriptors.push_back(label_not_found);
        }
        );

    return r_missing_descriptors;
}

plDataSet::plDataSet()
: state(DATA_SET_EMPTY){}
plDataSet::plDataSet(State s)
: state(s){}
plDataSet::plDataSet(int32_t hash_table_size)
: hash_table(hash_table_size)
, state(DATA_SET_GOOD){}
plDataSet::~plDataSet(){}

plInstance plDataSet::get(std::string a_key)
{
    if (state == DATA_SET_BAD)
        return plInstance(this, plInstance::NO_FILE);

    plInstance return_var;
    string 
        key_buffer = a_key,
        generated_key,
        result;
    bool data_missing = false;

    //buffer the expected_descriptors to avoid modifying the data set.
    std::vector<plDataSet::EntityKey> expected_descriptor_buffer;
    for(int32_t i=0; i<expected_descriptors.size(); ++i)
    {
        expected_descriptor_buffer.push_back(*(expected_descriptors[i]));
    }

    return_var = plInstance(this, plInstance::VALID_INST);
    return_var.SetKey(a_key);//assign the key which was passed into this function.

    /*-----------------------------------*
    *              Lexer                 *
    * ----------------------------------*/
    this->id_lexer(
        key_buffer, 
        [&](int32_t key_i,int32_t index, string label)
        {
            expected_descriptor_buffer[key_i].SetIndex(index);
        }
        );
    
    /*-----------------------------------*
    *             Compiler               *
    * ----------------------------------*/
    for(int i=0; i<expected_descriptor_buffer.size(); ++i)
    {
        //add the delimiter
        if (!generated_key.empty())
            generated_key.append("-");

        if(expected_descriptor_buffer[i].GetIndex()!=-1)
        {
            //push key to the format.
            generated_key.append(expected_descriptor_buffer[i].GetLabel());
            generated_key.append(to_string(expected_descriptor_buffer[i].GetIndex()));
        }
        else
        {
            data_missing = true;
        }
    }

    //Ask the storage for all valid keys with matching descriptors.
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

    return (state==DATA_SET_GOOD)
    ? return_var
    : plInstance(this, plInstance::NULL_INST);
}

int32_t plDataSet::set(std::string a_key, hValue a_value)
{
    switch (state)
    {
    case DATA_SET_EMPTY: state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: return hash_table.insert(a_key, hValue(a_value)); break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}


int32_t plDataSet::add_label(std::string new_label)
{
    expected_descriptors.push_back(make_shared<EntityKey>(EntityKey(new_label)));

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