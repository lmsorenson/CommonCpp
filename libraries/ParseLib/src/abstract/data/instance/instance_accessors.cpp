// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/instance.hpp>

#include <objects/data_set.hpp>


using ::std::vector;
using ::std::string;
using ::std::to_string;
using ::std::cout;
using ::std::endl;
using ::sdg::Instance;


//todo -- check if this this returns a modifiable iterator. (consider const key words)
const std::vector<std::string>::iterator Instance::begin()
{
    return value_.begin();
}

//todo -- check if this this returns a modifiable iterator. (consider const key words)
const std::vector<std::string>::iterator Instance::end()
{
    return value_.end();
}


string Instance::get() const
{
    if (state_ == VALID_INST && value_.size()!= 0)
    {
        if (value_.size()==1)
        {
            return value_[0];
        }
        else if(value_.size()>0)
        {
            return "SPECIFY_AN_INDEX";
        }
        else
        {
            return "ERROR";
        }
    }

    else if (state_ == NO_FILE)
        return "NO_FILE";

    //if the value of the instance is of size 0
    else
        return "NULL";
}




std::vector<std::string> Instance::get_vector()
{
    return value_;
}




string Instance::at(int8_t index) const
{
    if(state_ == VALID_INST && value_.size()!= 0)
    {
        if(value_.size()>=(index+1))
            return value_[index];

        else
            return "NULL";
    }
    else
    {
       return "NULL";
    }
}




Instance Instance::GetRelatedInstance(string a_entity_id) const
{ 
    //get the descriptor-index value off the entity identified
    //by 'a_label'
    string attr_buffer;
    
    
    if( GetDescriptorByDescriptorID(a_entity_id) != "NO_VALUE" )
        attr_buffer.append( GetDescriptorByDescriptorID(a_entity_id) );

    else if( !kOwner_->IsDescriptorRequired(a_entity_id) )
        attr_buffer.append(a_entity_id);

    //get any other descriptors that might be necessary
    vector<string> identifier = kOwner_->get_data_model().get_entity_identifier(a_entity_id);

    for(int i=0; i<identifier.size();++i)
    {
        if(GetDescriptorByDescriptorID(identifier[i])!="NO_VALUE")
        {
            if(!attr_buffer.empty())
                attr_buffer.append("-");

            attr_buffer.append(GetDescriptorByDescriptorID(identifier[i]));
        }
            

        else if( !kOwner_->IsDescriptorRequired(identifier[i]) )
        {
            if(!attr_buffer.empty())
                attr_buffer.append("-");

            attr_buffer.append(identifier[i]);
        }
    }

    //get the value from the associated DataSet
    return kOwner_->get(attr_buffer);
}




//Get next instance in 'a_label'
Instance Instance::GetNextInstance(string a_label) const
{
    // get next instance with respect to entity identified by a_label
    Instance owner;

    //1. get owning entity instance
    //2. check if the instance is valid before continuing
    if(!(owner = this->GetRelatedInstance(a_label)).is_valid())
        return Instance(kOwner_, NULL_INST);

    //------------------------------------------
    //      step through value iterator
    //------------------------------------------
    //start at the first value in the set
    auto itr = owner.value_.cbegin();
    int32_t pos=0;

    //find the current instance if it exists.
    while(((*itr)!=this->get()) && (itr!=owner.value_.cend()))
    {
        itr++;
        pos++;
    }

    //check that this and the next item both exist before continuing
    if((itr!=owner.value_.cend()) && (++itr!=owner.value_.cend()))
    {
        vector<string> 
        missing_desc = kOwner_->get_missing_descriptors(a_label);
        
        pos++;

        if(missing_desc.size()==1)
        {
            string generated_identifier;
            generated_identifier.append(key_);
            generated_identifier.append("-");
            generated_identifier.append(missing_desc[0]);
            generated_identifier.append(to_string(pos));

            return kOwner_->get(generated_identifier);
        }
        //todo-->so far this should never happen
        else if(missing_desc.size()>1)
            return Instance(kOwner_, NULL_INST);
        else
            return Instance(kOwner_, NULL_INST);
    }

    //if the next item doesn't exist then end here.
    else
        return Instance(kOwner_, NULL_INST);
}




Instance Instance::GetPreviousInstance(string a_label) const
{
    //todo->GetPreviousInstance undefined.
    return Instance();
}


bool Instance::is_valid() const
{
    return (state_ == VALID_INST);
}    



int32_t Instance::FindIndexOfValue(std::string a_value_to_search_for, int32_t offset) const
{
    //------------------------------------------
    //      step through value iterator
    //------------------------------------------
    //start at the first value in the set
    auto itr = this->value_.cbegin();
    int32_t pos=offset;

    //find the current instance if it exists.
    while(( (itr!=this->value_.cend()) && (*itr) != a_value_to_search_for ))
    {
        itr++;
        pos++;
    }

    return pos;
}


string Instance::GetDescriptorByDescriptorID(string a_descriptor_id) const
{
    //create a buffer to act as a return value and construct it in steps.
    string desc_buffer = a_descriptor_id;

    //the index buffer is an a place to store matching indices from the lexer.
    //the index buffer is null or not found when the value is -1.
    int32_t index_buffer = -1;

    //find the matching descriptor.
    kOwner_->id_lexer(
        this->key_, //passes in the partial key used to create this instance.
                    //in the lexer this is broken down into descriptors and compared with the argument.
        [&](int32_t key_i, int32_t index, string found_label) mutable
        {
            // where found_label is the label being processed in a loop.
            // and the argument is equal to the found label.
            if(found_label==desc_buffer)
                index_buffer = index;
        }
        );

    //if an index is found, append it to the output string.
    if (index_buffer!=-1)
        desc_buffer.append(to_string(index_buffer));

    //if the index buffer is null return a NO VALUE message.
    else
        return "NO_VALUE";

    //if there is no error, return the descriptor buffer.
    return desc_buffer;
}