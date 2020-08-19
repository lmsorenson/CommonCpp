// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>
#include <string.h>
#include <stdio.h>

#include "../types/types.hpp"



using std::string;
using std::vector;
using std::function;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::cout;
using std::endl;


//id lexer matches descriptors against expected descriptors
//todo-- also adjust this algorithm to more closely adhere to concepts of lexical analysis, and assess time complexity.
sdg::hash::KeyInstance sdg::DataSet::id_lexer(
    hash::KeyInstance a_key, // the identifier to be broken down into descriptors.
    function<void(int32_t key_i, int32_t index, string found_label)> callback_desc_found,
    function<void(string label_not_found)> callback_desc_not_found,
    function<void(string label_unrecognized)> callback_unrecognized_desc) const
{

    string r_new_id;
    string key_as_string(a_key.as_string());
    char * token = strtok((char*)key_as_string.c_str(),"-");

    vector<bool> v_b_found;

    vector<shared_ptr<Descriptor>> identifying_descriptors = this->logical_data_structure.get_identifier_of_granular_entity();

    //initialize a boolean for each expected descriptor,
    //that indicates if that descriptor was found
    for (int i=0; i<identifying_descriptors.size();++i)
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
        for(int i=0; i<identifying_descriptors.size(); ++i)
        {
            auto descriptor = identifying_descriptors[i];
            //Check if the token's key matches the current descriptor's label.
            if (descriptor && descriptor->get_id().compare(scanned_label)==0)
            {
                //if the token was a match, it was expected
                b_token_recognized = true;

                //indicate that this expected descriptor was found.
                v_b_found[i]=true;

                if(!r_new_id.empty())
                    r_new_id.append("-");

                //only add recognized descriptors to the output.
                r_new_id.append(token);

                std::shared_ptr<const Attribute> attr_descriptor = dynamic_pointer_cast<const Attribute>(identifying_descriptors[i]);

                //run the callback
                if (attr_descriptor && (attr_descriptor->get_scale() == Attribute::Scale::Ordinal ))
                {
                    callback_desc_found(i, scanned_index, attr_descriptor->get_id());
                }
                    
                else if(attr_descriptor && (attr_descriptor->get_scale() == Attribute::Scale::Boolean ))
                {
                    callback_desc_found(i, NO_INDEX, identifying_descriptors[i]->get_id());
                }
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
            for (int i=0; i<identifying_descriptors.size();++i)
            {
                std::shared_ptr<const Attribute> attr_descriptor = dynamic_pointer_cast<const Attribute>(identifying_descriptors[i]);

                //pass the missing descriptor to the calling context
                //if the descriptor was not matched.
                if (!v_b_found[i] && attr_descriptor && attr_descriptor->get_scale() != Attribute::Scale::Boolean )
                    callback_desc_not_found(identifying_descriptors[i]->get_id());   
            }
        }  

    delete[] token;
    return hash::KeyInstance(r_new_id);
}

vector<std::string> sdg::DataSet::get_missing_descriptors(hash::KeyInstance a_key_subset) const
{
    vector<std::string> r_missing_descriptors;

    this->id_lexer(
        a_key_subset,
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

//searches the key for an instance of a_descriptor
sdg::hash::KeyInstance sdg::DataSet::increment_descriptor_in_key(hash::DescriptorInstance a_descriptor, hash::KeyInstance a_hash_key, int32_t a_position)
{
    std::string hash_key_as_string = a_hash_key.as_string();
    std::vector<hash::DescriptorInstance> descriptor_list;

    auto function = [&](const std::string callback_token)
    {
        //if the descriptor matches increment 
        //the value on the descriptor
        if(a_descriptor==callback_token)
        {  
            //increments the descriptor's value
            a_descriptor++;

            descriptor_list.push_back(a_descriptor);
        }
        else
        {
            std::string token_as_string(callback_token);
            hash::DescriptorInstance local_descriptor(token_as_string.substr(0,1), Attribute::Scale::Ordinal);
            local_descriptor.set_value(std::stoi(token_as_string.substr(1,1)));

            descriptor_list.push_back(local_descriptor);
        }
    };

    a_hash_key.for_each_descriptor(function);

    return hash::KeyInstance(descriptor_list);
}



//recursively replaces elements that are over written.
void sdg::DataSet::displace_overwritten_keys( plHashValue replaced_value, hash::DescriptorInstance a_descriptor, hash::KeyInstance new_key)
{
    plHashValue replaced = replaced_value;
    while(replaced.is_valid())
    {
        //increment the value on the descriptor
        a_descriptor++;

        //takes a descriptor increments it and applys it to the provided key
        new_key=increment_descriptor_in_key(a_descriptor, new_key, 1);

        //apply the previously replaced value and assign the newly replaced value(if one exists) 
        replaced=this->hash_table_.insert(new_key, replaced);

        //update the count of descriptors.
        this->update_descriptor_counts(new_key);
    }
}

sdg::hash::KeyInstance sdg::DataSet::compile_hash_key(const std::vector<hash::DescriptorInstance> &expected_descriptors) const
{

    std::string compiled_key;
    bool data_missing;

    /*-----------------------------------*
    *             Compiler               *
    * ----------------------------------*/
    for(int i=0; i<expected_descriptors.size(); ++i)
    {

        //-- if the descriptor value is not a null value. --
        if(expected_descriptors[i].get_descriptor_value()!=-1)
        {
            //add the delimiter
            if (!compiled_key.empty())
                compiled_key.append("-");

            //push key to the format.
            compiled_key.append(expected_descriptors[i].get_descriptor_id());
            
            if( expected_descriptors[i].get_scale() == Attribute::Scale::Ordinal)
                compiled_key.append(std::to_string(expected_descriptors[i].get_descriptor_value()));
        }

        //-- if the descriptor value is not required. --
        else if (expected_descriptors[i].get_scale() == Attribute::Scale::Boolean)
        {
            //add the delimiter
            if (!compiled_key.empty())
                compiled_key.append("-");

            if (expected_descriptors[i].is_found())
                compiled_key.append(expected_descriptors[i].get_descriptor_id());
        }

        //-- note missing data. --
        else
        {
            //if any token returns missing record it.
            data_missing = true;
        }
    }

    return sdg::hash::KeyInstance(compiled_key, data_missing);
}


//applies key values to expected descriptors
std::vector<sdg::hash::DescriptorInstance> sdg::DataSet::get_descriptors_from_descriptor_id_set(hash::KeyInstance key_buffer, std::vector<std::shared_ptr<Descriptor>> expected_descriptor_buffer) const
{
    using sdg::hash::DescriptorInstance;
    std::vector<DescriptorInstance> buffer;


    for(auto descriptor : expected_descriptor_buffer)
    {
        std::shared_ptr<Attribute> attribute;
        //if the current descriptor is an attribute
        if( (attribute=dynamic_pointer_cast<Attribute>(descriptor)) )
        {
            buffer.push_back( DescriptorInstance(descriptor->get_id(), attribute->get_scale()) );
        }
        else
        {
            return buffer;
        }
    }


    /*-----------------------------------*
    *              Lexer                 *
    * ----------------------------------*/
    key_buffer = this->id_lexer(
        key_buffer, 
        [&](int32_t key_i,int32_t index, string found_label)
        {
            if (buffer[key_i].get_scale() == Attribute::Scale::Ordinal)
            {
                buffer[key_i].set_value(index);
            }
            else
            {
                buffer[key_i].set_found();
            }
        }
        );

    return buffer;

}