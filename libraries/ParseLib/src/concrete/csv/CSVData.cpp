// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSVData.hpp"
#include <iostream>
#include "../../colortext.hpp"


using namespace std;

void CSVData::csv_model()
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
}

CSVData::CSVData()
: plDataSet()
{
    this->add_optional_flag("H");
    this->add_label("R");
    this->add_label("F");
    this->csv_model();//generate the meta data
}

CSVData::CSVData(int32_t hash_table_size)
: plDataSet(hash_table_size)
{
    this->add_optional_flag("H");
    this->add_label("R");
    this->add_label("F");
    this->csv_model();//generate the meta data
}

CSVData::~CSVData()
{
}

void CSVData::assign()
{
}

void CSVData::add_instance(std::string entity_name, std::vector<std::string> entity_values, int32_t position)
{
    //adding a record
    if(entity_name.compare("R")==0)
    {
        //get the number of fields in the dataset.
        int32_t 
            field_count = this->logical_data_structure.get_entity_count("F"),
            record_count = this->logical_data_structure.get_entity_count("R");

        this->increment_counter("R");//todo--> maybe implement the counter within the plDataSet::set function

        //cell values 
        if(entity_values.size()<=field_count)
        {
            std::string str = "R";

            //called if the position parameter is left empty,
            //by default add new records to the end of the document.
            if(position==END_OF_ENTITY_LIST)
                str.append(std::to_string(record_count));

            //if a position is given insert the record at the position given.
            else 
                str.append(std::to_string(position));

            //todo->after creating the new line push everything else down a record.


            for(int32_t i=0;i<field_count;++i)
            {
                std::string key_buffer = str;
                key_buffer.append("-");
                key_buffer.append("F");
                key_buffer.append(std::to_string(i));


                if(i<entity_values.size())
                {
                    this->set(key_buffer, plHashValue(entity_values[i], str));
                    this->increment_counter("F");
                }
                else
                {
                    this->set(key_buffer, plHashValue("", str));
                }
                
            }
        }
        else
        {
            // pad_entity_count("F", (entity_values.size() - field_count) );

            std::string str = "R";
            str.append(std::to_string(record_count));

            for(int32_t i=0;i<entity_values.size();++i)
            {
                std::string key_buffer = str;
                key_buffer.append("-");
                key_buffer.append("F");
                key_buffer.append(std::to_string(i));


                if(i<entity_values.size())
                {
                    this->set(key_buffer, plHashValue(entity_values[i], str));
                    this->increment_counter("F");
                }
                else
                {
                    this->set(key_buffer, plHashValue("", str));
                }
            }
        }
        
    }

    //adding a field
    else if(entity_name.compare("F")==0)
    {
        //todo --> populate this function.
    }
    
    //error
    else
    {
        //todo --> populate this function.
    }
}

void CSVData::remove_instance(std::string entity_id)
{
    //todo-->define

    for (auto key : hash_table.GetMatchingKeys(entity_id))
    {
        hash_table.delete_value(key);
    }
}

void CSVData::increment_instance_id(std::string entity_id, int32_t position)
{
    //todo-->define

    for (auto key : hash_table.GetMatchingKeys(entity_id))
    {
        std::string copy = key;

        char * token = strtok((char*)copy.c_str(),"-");
        std::string new_key;

        

        while(token!=NULL)
        {
            if(entity_id.compare(token)==0)
            {
                char scanned_label[1];
                int32_t scanned_index;

                //scan the token
                sscanf(token, "%1s%i", scanned_label, &scanned_index);

                scanned_index++;

                new_key.append(scanned_label);
                new_key.append(std::to_string(scanned_index));
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
        
        hash_table.move(key, new_key);
    }
}

int32_t CSVData::pad_entity_count(std::string entity_name, int32_t a_num_blanks)
{
    //get the current number of fields.
    int32_t 
        record_count = this->logical_data_structure.get_entity_count("R"),
        field_count = this->logical_data_structure.get_entity_count("F");

    std::string r_buffer, f_buffer, c_buffer;

    if(entity_name.compare("F")==0)
    {
        for(int i=0; i<record_count; ++i)
        {
            r_buffer.clear();
            r_buffer
                .append("R")
                .append(std::to_string(i))
                .append("-");

            for(int k=field_count; k<field_count+a_num_blanks; ++k)
            {
                f_buffer.clear();
                f_buffer
                    .append("F")
                    .append(std::to_string(k)); 


                c_buffer.clear();
                c_buffer.append(r_buffer).append(f_buffer);

                this->set(c_buffer, plHashValue("", ""));
            }
        }

        return 0;
    }
    else if(entity_name.compare("R")==0)
    {
        for(int i=record_count; i<record_count+a_num_blanks; ++i)
        {
            r_buffer.clear();
            r_buffer
                .append("R")
                .append(std::to_string(i))
                .append("-");

            for(int k=0; k<field_count; ++k)
            {
                f_buffer.clear();
                f_buffer
                    .append("F")
                    .append(std::to_string(k));

                c_buffer.clear();
                c_buffer.append(r_buffer).append(f_buffer);

                this->set(c_buffer, plHashValue("", ""));
            }
        }

        return 0;
    }

    else
        return -1;
}