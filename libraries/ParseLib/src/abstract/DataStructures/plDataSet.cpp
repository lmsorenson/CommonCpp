// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "plDataSet.hpp"
#include <iostream>

using namespace std;




string plDataSet::id_lexer(
    string a_identifier, 
    function<void(int32_t key_i, int32_t index, string found_label)> callback_desc_found,
    function<void(string label_not_found)> callback_desc_not_found,
    function<void(string label_unrecognized)> callback_unrecognized_desc)
{
    string r_new_id;
    char * token = strtok((char*)a_identifier.c_str(),"-");

    vector<bool> v_b_found;

    //initialize a boolean for each expected descriptor,
    //that indicates if that descriptor was found
    for (int i=0; i<this->expected_descriptors.size();++i)
    {
        //before searching this is false.
        v_b_found.push_back(false);
    }

    //Check every descriptor in the original key.
    while (token != NULL)
    {
        char scanned_label[1];
        int32_t scanned_index;
        
        //a boolean that indicates whether the current token
        //was an expected token.
        bool b_token_recognized = false;

        //scan the token
        sscanf(token, "%1s%i", scanned_label, &scanned_index);

        
        //iterate over expected descriptors
        for(int i=0; i<this->expected_descriptors.size(); ++i)
        {
            //Check if the token's key matches the current descriptor's label.
            if (strcmp(this->expected_descriptors[i]->GetLabel().c_str(), scanned_label)==0)
            {
                //if the token was a match, it was expected
                b_token_recognized = true;

                //indicate that this expected descriptor was found.
                v_b_found[i]=true;

                if(!r_new_id.empty())
                    r_new_id.append("-");

                //only add recognized descriptors to the output.
                r_new_id.append(token);

                //run the callback
                if (this->expected_descriptors[i]->HasIndex())
                    callback_desc_found(i, scanned_index, this->expected_descriptors[i]->GetLabel());
                else
                    callback_desc_found(i, NO_INDEX, this->expected_descriptors[i]->GetLabel());
            }
        }

        if(!b_token_recognized && callback_unrecognized_desc)
        {
            callback_unrecognized_desc(scanned_label);
        }
        
        token = strtok(NULL, "-");
    }

        //by default no callback for descriptors not found,
        //execute the callback only if it exists.
        if(callback_desc_not_found)
        {
            for (int i=0; i<this->expected_descriptors.size();++i)
            {
                //pass the missing descriptor to the calling context
                //if the descriptor was not matched.
                if (!v_b_found[i] && this->expected_descriptors[i]->IsRequired())
                    callback_desc_not_found(this->expected_descriptors[i]->GetLabel());   
            }
        }  

    delete[] token;
    return r_new_id;
}

vector<std::string> plDataSet::get_missing_descriptors(std::string a_descriptor_labels)
{
    vector<std::string> r_missing_descriptors;

    this->id_lexer(
        a_descriptor_labels,
        [=](int32_t key_i,int32_t index, string found_label)
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
    key_buffer = this->id_lexer(
        key_buffer, 
        [&](int32_t key_i,int32_t index, string found_label)
        {
            if (expected_descriptor_buffer[key_i].HasIndex())
                expected_descriptor_buffer[key_i].SetIndex(index);
            else
                expected_descriptor_buffer[key_i].SetFound();
        }
        );
    
    /*-----------------------------------*
    *             Compiler               *
    * ----------------------------------*/
    for(int i=0; i<expected_descriptor_buffer.size(); ++i)
    {
        

        if(expected_descriptor_buffer[i].GetIndex()!=-1)
        {
            //add the delimiter
            if (!generated_key.empty())
                generated_key.append("-");

            //push key to the format.
            generated_key.append(expected_descriptor_buffer[i].GetLabel());
            
            if(expected_descriptor_buffer[i].HasIndex())
                generated_key.append(to_string(expected_descriptor_buffer[i].GetIndex()));
        }
        else if (!expected_descriptor_buffer[i].IsRequired())
        {
            //add the delimiter
            if (!generated_key.empty())
                generated_key.append("-");

            if (expected_descriptor_buffer[i].IsFound())
                generated_key.append(expected_descriptor_buffer[i].GetLabel());
        }
        else
        {
            //if any token returns missing record it.
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

plInstance plDataSet::where(std::string descriptor, std::string value)
{
    plInstance ret;

    //1. get owning entity instance
    //2. check if the instance is valid before continuing
    if(!(ret = this->get(descriptor)).is_valid())
        return plInstance(this, plInstance::NULL_INST);

    int32_t pos = ret.find(value);

    vector<string> missing_desc = this->get_missing_descriptors(descriptor);        

    if(missing_desc.size()==1)
    {
        string generated_identifier;
        generated_identifier.append(missing_desc[0]);
        generated_identifier.append(to_string(pos));

        return this->get(generated_identifier);
    }
    //todo-->so far this should never happen
    else if(missing_desc.size()>1)
    {
        return plInstance(this, plInstance::NULL_INST);
    }
    else
    {
        return plInstance(this, plInstance::NULL_INST);
    }
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


int32_t plDataSet::add_label(std::string a_new_label)
{
    expected_descriptors.push_back(make_shared<EntityKey>(EntityKey(a_new_label)));

    return 0;
}

int32_t plDataSet::add_optional_flag(std::string a_new_label)
{
    expected_descriptors.push_back(make_shared<EntityKey>(EntityKey(a_new_label, false, false)));

    return 0;
}

plDataSet::EntityKey::EntityKey()
:label("")
,index(-1)
,b_found(false)
{
}
plDataSet::EntityKey::EntityKey(string a_label, bool a_required, bool a_has_index)
:label(a_label)
,index(-1)
,required(a_required)
,has_index(a_has_index)
,b_found(false)
{
}
plDataSet::EntityKey::~EntityKey()
{

}

bool plDataSet::EntityKey::IsRequired()
{
    return this->required;
}
bool plDataSet::EntityKey::HasIndex()
{
    return this->has_index;
}

string plDataSet::EntityKey::GetLabel(){return label;}

 int32_t plDataSet::EntityKey::SetIndex(int32_t a_index)
 {
     index = a_index;
     return 0;
 }

 int32_t plDataSet::EntityKey::SetFound()
 {
     b_found = true;
     return 0;
 }

  bool plDataSet::EntityKey::IsFound()
 {
     return b_found;
 }

int32_t plDataSet::EntityKey::GetIndex(){return index;}



int32_t plDataSet::generate_data_model()
{
    shared_ptr<Entity>
        eRecord = make_shared<Entity>("R", "record"),
        eCell = make_shared<Entity>("C", "cell"),
        eField = make_shared<Entity>("F", "field"),
        eField_name = make_shared<Entity>("H", "field_name");

    shared_ptr<Attribute>
        eRecord_line_id,
        eCell_value,
        eField_field_id,
        eField_name_value;

    eRecord->add_descriptor(eRecord_line_id=make_shared<Attribute>(Attribute("record_id", "R")), true);
    eCell->add_descriptor(eCell_value=make_shared<Attribute>(Attribute("value", "V")));
    eField->add_descriptor(eField_field_id=make_shared<Attribute>(Attribute("field_id", "F")), true);
    eField_name->add_descriptor(eField_name_value=make_shared<Attribute>(Attribute("name", "N")));

    shared_ptr<Relationship>
        cell_to_record = make_shared<Relationship>("cell_to_record", eCell, eRecord,  false, Relationship::IDENTIFY_BY::LINK_1),
        cell_to_field = make_shared<Relationship>("cell_to_field", eCell, eField, false, Relationship::IDENTIFY_BY::LINK_1),
        
        //be-be relationship 
        cell_to_field_name = make_shared<Relationship>(
            "cell_to_field_name", //relationship name
            eCell, //entity 1
            eField_name, //entity 2
            true, //true indicates that this relationship is a be relationship.
            Relationship::IDENTIFY_BY::LINK_2);//the link to entity 1 will be an identifying descriptor for entity_2

    logical_data_structure.add_thing(eRecord);
    logical_data_structure.add_thing(eCell); 
    logical_data_structure.add_thing(eField);
    logical_data_structure.add_thing(eField_name);

    logical_data_structure.add_thing(cell_to_record);
    logical_data_structure.add_thing(cell_to_field); 
    logical_data_structure.add_thing(cell_to_field_name);

};


Model plDataSet::get_data_model()
{
    return logical_data_structure;
}

int32_t plDataSet::IsLabelRequired(string a_label)
{
    int32_t r=-1;

    bool b_descriptor_found = false;

    for(auto descriptor : this->expected_descriptors)
    {
        if(descriptor->GetLabel() == a_label)//if this is never called return an error.
        {       
            if (b_descriptor_found)//if this is ever called return an error.
                r=-1;

            r=descriptor->IsRequired();
        }
    }

    return r;
}