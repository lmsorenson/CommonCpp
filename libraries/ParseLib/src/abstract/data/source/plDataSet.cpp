// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../plDataSet.hpp"
#include <iostream>

using namespace std;




/* helpers */
void increment_descriptor_value(std::string a_descriptor_id, std::string &a_out_descriptor_id, std::string &a_out_meta_descriptor_id);
std::string get_matching_descriptor(std::string a_descriptor_list, std::string a_meta_entity_id);

string plDataSet::id_lexer(
    string a_identifier, 
    function<void(int32_t key_i, int32_t index, string found_label)> callback_desc_found,
    function<void(string label_not_found)> callback_desc_not_found,
    function<void(string label_unrecognized)> callback_unrecognized_desc) const
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

vector<std::string> plDataSet::get_missing_descriptors(std::string a_descriptor_labels) const
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
: state(DATA_SET_EMPTY)
{
}
plDataSet::plDataSet(State s)
: state(s)
{
}
plDataSet::plDataSet(int32_t hash_table_size)
: hash_table(hash_table_size)
, state(DATA_SET_GOOD)
{
}

//deconstructors
plDataSet::~plDataSet(){}

plInstance plDataSet::get(std::string a_descriptor) const
{
    if (state == DATA_SET_BAD)
        return plInstance(this, plInstance::NO_FILE);

    plInstance return_var;
   
    string 
        key_buffer = a_descriptor,
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
    return_var.SetKey(a_descriptor);//assign the key which was passed into this function.

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

plInstance plDataSet::where(std::string descriptor, std::string value) const
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

int32_t plDataSet::set(std::string a_descriptor_list, plHashValue a_value)
{
    switch (state)
    {
    case DATA_SET_EMPTY: 
        state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: 
        hash_table.insert(a_descriptor_list, plHashValue(a_value));
        this->update_descriptor_counts(a_descriptor_list);
        return 0; 
        break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}

int32_t plDataSet::set(std::string a_descriptor_list, plHashValue a_value, std::string a_entity_id)
{
    plHashValue replaced_value;
    std::string new_entity_id, new_key, copy_entity_id = a_entity_id;

    switch (state)
    {
    case DATA_SET_EMPTY: 
        state = DATA_SET_GOOD; //Empty data sets should also implement DATA_SET_GOOD protecol
    case DATA_SET_GOOD: 


        replaced_value = hash_table.insert(a_descriptor_list, plHashValue(a_value));
        this->update_descriptor_counts(a_descriptor_list);

        if(replaced_value.is_valid())
        {
            new_entity_id = get_matching_descriptor(a_descriptor_list, copy_entity_id);
            
            new_key = increment_descriptor_in_key(new_entity_id, a_descriptor_list, 0);

            replaced_value = hash_table.insert(new_key, plHashValue(replaced_value));
            
            this->update_descriptor_counts(new_key);
            
            displace_overwritten_keys(replaced_value, new_entity_id, new_key);
        }
        
        return 0; 
        break;
    case DATA_SET_BAD: return DATA_SET_BAD; break;
    default:
    case UNKNOWN: return UNKNOWN; break;
    }
}


int32_t plDataSet::register_descriptor(std::string a_new_descriptor)
{
    expected_descriptors.push_back(make_shared<EntityKey>(EntityKey(a_new_descriptor)));

    return 0;
}

int32_t plDataSet::add_optional_flag(std::string a_new_descriptor)
{
    expected_descriptors.push_back(make_shared<EntityKey>(EntityKey(a_new_descriptor, false, false)));

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

bool plDataSet::EntityKey::IsRequired() const
{
    return this->required;
}
bool plDataSet::EntityKey::HasIndex() const
{
    return this->has_index;
}

string plDataSet::EntityKey::GetLabel() const {return label;}

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

  bool plDataSet::EntityKey::IsFound() const
 {
     return b_found;
 }

int32_t plDataSet::EntityKey::GetIndex() const {return index;}


Model plDataSet::get_data_model() const
{
    return logical_data_structure;
}

int32_t plDataSet::IsDescriptorRequired(string a_descriptor) const
{
    int32_t r=-1;

    bool b_descriptor_found = false;

    for(auto descriptor : this->expected_descriptors)
    {
        if(descriptor->GetLabel() == a_descriptor)//if this is never called return an error.
        {       
            if (b_descriptor_found)//if this is ever called return an error.
                r=-1;

            r=descriptor->IsRequired();
        }
    }

    return r;
}

int32_t plDataSet::number_of_entity_instances(std::string a_entity_id)
{
    return this->logical_data_structure.get_entity_count(a_entity_id);
}

int32_t plDataSet::increment_counter(std::string a_entity_id)
{
    // logical_data_structure.increment_entity_counter(a_entity_id);
    return 0;
}





void plDataSet::add_instance(std::string entity_id, std::vector<std::string> entity_values, int32_t position)
{
    //todo-->handle definition of this function
}

void plDataSet::remove_instance(std::string entity_id)
{
    //todo-->handle definition of this function
}

void plDataSet::increment_instance_id(std::string entity_id, int32_t position)
{
    //todo-->handle definition of this function
}

int32_t plDataSet::pad_entity_count(std::string entity_id, int32_t a_num_blanks)
{
    //todo-->handle definition of this function
    return 0;
}




std::string plDataSet::increment_descriptor_in_key(std::string a_entity_id, std::string a_hash_key, int32_t a_position)
{
    std::string 
            copy = a_hash_key,
            new_key,
            descriptor_id;

    char * token = strtok((char*)copy.c_str(),"-");

    //iterates through all tokens(descriptors)
    while(token!=NULL)
    {
        //if the descriptor mat
        if(a_entity_id.compare(token)==0)
        {   
            std::string copy_new_key = new_key;
            increment_descriptor_value(token, copy_new_key, descriptor_id);
            new_key.append(copy_new_key);
        
            for(int i=0; i<a_position; ++i)
            {
                // this->increment_counter(descriptor_id);
            }
        }
        else
        {
            new_key.append(token);
        }
        
        token = strtok(NULL,"-");

        if(token!=NULL)
            new_key.append("-");
    }
    delete[] token;

    return new_key;
}


//increments the id for each 
void plDataSet::displace_overwritten_keys( plHashValue replaced_value, std::string new_entity_id, std::string new_key)
{
    plHashValue replaced = replaced_value;
    while(replaced.is_valid())
    {
        std::string scanned_meta_descriptor_id;
        increment_descriptor_value(new_entity_id, new_entity_id, scanned_meta_descriptor_id);
        new_key = increment_descriptor_in_key(new_entity_id, new_key, 1);
        replaced = this->hash_table.insert(new_key, replaced);
        this->update_descriptor_counts(new_key);
    }
}




/* helpers */
void increment_descriptor_value(std::string a_descriptor_id, std::string &a_out_descriptor_id, std::string &a_out_meta_descriptor_id)
{
    char* descriptor_id = (char*)a_descriptor_id.c_str();
    char scanned_descriptor_id[1];
    int32_t scanned_descriptor_value;

    //scan the token
    sscanf(descriptor_id, "%1s%i", scanned_descriptor_id, &scanned_descriptor_value);

    //increment the numeric descriptor value
    scanned_descriptor_value++;

    //assign the value of the descriptor_id to the reference parameter
    a_out_meta_descriptor_id=scanned_descriptor_id;

    a_out_descriptor_id.clear();
    a_out_descriptor_id.append(scanned_descriptor_id).append(std::to_string(scanned_descriptor_value));
}




std::string get_matching_descriptor(std::string a_descriptor_list, std::string a_meta_entity_id)
{
    std::string copy = a_descriptor_list;
    char * token = strtok((char*)copy.c_str(),"-");

    while(token!=NULL)
    {
        if(std::string(token).substr(0,1).compare(a_meta_entity_id)==0)
        {
            return token;
        }

        token = strtok(NULL,"-");
    }

    return "NULL";
}

void plDataSet::update_descriptor_counts(std::string a_descriptor_list)
{
    std::string copy = a_descriptor_list;
    char * token = strtok((char*)copy.c_str(),"-");

    while(token!=NULL)
    {
        logical_data_structure.found_descriptor(token);

        token = strtok(NULL,"-");
    }
}