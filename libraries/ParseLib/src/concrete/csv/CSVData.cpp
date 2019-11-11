// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSVData.hpp"
#include <iostream>
#include "../../colortext.hpp"


using namespace std;


CSVData::CSVData()
: plDataSet()
{

}

CSVData::CSVData(int32_t hash_table_size)
: plDataSet(hash_table_size)
{
}

CSVData::~CSVData()
{
}

void CSVData::assign()
{
}

void CSVData::add_instance(std::string entity_name, std::vector<std::string> entity_values)
{
    //adding a record
    if(entity_name.compare("R")==0)
    {
        //get the number of fields in the dataset.
        int32_t 
        field_count = this->logical_data_structure.get_entity_count("F"),
        record_count = this->logical_data_structure.get_entity_count("R");

        this->increment_counter("R");
        this->state = DATA_SET_GOOD;

        //cell values 
        if(entity_values.size()<=field_count)
        {
            std::string str = "R";
            str.append(std::to_string(record_count));
            for(int32_t i=0;i<field_count;++i)
            {
                std::string key_buffer = str;
                key_buffer.append("-");
                key_buffer.append("F");
                key_buffer.append(std::to_string(i));


                if(i<entity_values.size())
                {
                    this->set(key_buffer, plHashValue(entity_values[i], str));
                    cout << key_buffer << endl;
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
            pad_entity_count("F", (entity_values.size() - field_count) );

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
                    cout << key_buffer << endl;
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

    }
    
    //error
    else
    {

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