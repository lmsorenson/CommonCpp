// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <data_set.hpp>



using std::string;
using std::vector;
using std::function;



/* helpers */
void increment_descriptor_value(std::string a_descriptor_id, std::string &a_out_descriptor_id, std::string &a_out_meta_descriptor_id);


//todo -- increase the clarity and readability of the inner workings of the lexer.
//-- also adjust this algorithm to more closely adhere to concepts of lexical analysis, and assess time complexity.
string sdg::DataSet::id_lexer(
    string a_identifier, // the identifier to be broken down into descriptors.
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

vector<std::string> sdg::DataSet::get_missing_descriptors(std::string a_descriptor_labels) const
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


std::string sdg::DataSet::increment_descriptor_in_key(std::string a_entity_id, std::string a_hash_key, int32_t a_position)
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
void sdg::DataSet::displace_overwritten_keys( plHashValue replaced_value, std::string new_entity_id, std::string new_key)
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




