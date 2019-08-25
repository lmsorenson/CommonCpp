// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSVFilters.hpp"
#include <iostream>
#include <sstream>
#include <vector>

    using namespace std;


    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    HeaderFilter::HeaderFilter(std::string new_filter_id) 
    : ParserFilter(new_filter_id)
    {}

    int32_t HeaderFilter::execute(string text, vector<node>& output)
    {

    }

    string HeaderFilter::name()
    {
        return "header line";
    }
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    RecordFilter::RecordFilter(std::string new_filter_id) 
    : ParserFilter(new_filter_id)
    {}

    int32_t RecordFilter::execute(string text, vector<node>& output)
    {
        istringstream file(text);
        string line, rBuffer;
        
        int32_t number_of_quotes = 0;

        while (std::getline(file, line)) 
        {
            number_of_quotes %= 2;
            string record_value;

            //iterate through every character in the line
            for ( std::string::iterator it=line.begin(); it!=line.end(); ++it)
            {
                bool bIsQuote;

                if ((bIsQuote= (*it=='"')))
                    number_of_quotes++;

                if( (*it!='\r') && (*it!='\n') )
                {
                    rBuffer.push_back(*it);
                }

                //if there is a set of quotes open by the end of the line
                //add any new lines or carriage returns to the record.
                else if ((number_of_quotes%2)!=0)
                {
                    rBuffer.push_back(*it);
                }

                //if there is not a set of quotes open at the line break, 
                //append the buffer to the record value.
                else 
                {
                    record_value.append(rBuffer);
                    rBuffer.clear();
                }
            }//last character in line

            //add the new node to the filter output.
            if(!record_value.empty())
                output.push_back(node(record_value.c_str(), nullptr));
        }//last line
        
        if(output.size()==0)
            return FILTER_FORMAT_ERROR;
        
        return FILTER_SUCCESS;
    }
    
    string RecordFilter::name()
    {
        return "record";
    }


    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    FieldFilter::FieldFilter(std::string new_filter_id) 
    : ParserFilter(new_filter_id), 
    field_count(-1)
    {}

    int32_t FieldFilter::execute(string text, vector<node>& output)
    {
        if (text.back()==',')
            return FILTER_FORMAT_ERROR;

        string buffer;
        int32_t number_of_quotes=0;
        char * pch;

        pch = strtok((char*)text.c_str(),",");

        while (pch != NULL)
        {
            char last_char;//this character describes only characters found in the token

            string param = pch;
            for(std::string::iterator it=param.begin(); it!=param.end(); ++it)
            {
                bool bIsQuote = (*it=='"');

                if (bIsQuote)
                    number_of_quotes++;

                if (!bIsQuote)
                    buffer.push_back(*it);

                else if((number_of_quotes%2!=0) && (last_char=='"'))
                    buffer.push_back(*it);

                last_char = *it;
            }

            //if there is not an open quotation, push the node to the buffer
            if ((number_of_quotes%2==0))
            {
                output.push_back(node(buffer, nullptr));
                buffer.clear();
            }
            //if there is a quotation open put the comma back, and do NOT clear the buffer
            else
                buffer.push_back(',');


            last_char = '0';//this character describes only characters found in the token
            pch = strtok(NULL, ",");            
        }//end tokenization

        delete[] pch;

        //all records must have the same size.
        if (!IsFieldCountValid(output.size()))
            return FILTER_FORMAT_ERROR;

        return FILTER_SUCCESS;
    }
    
    string FieldFilter::name()
    {
        return "field";
    }

    bool FieldFilter::IsFieldCountValid(int32_t field_count_param)
    {
        if( (field_count!=0)
            && (field_count==field_count_param
            || field_count==-1) )
        {
            return true;
        }
        else
        {
            field_count=field_count_param;
            return false;
        }
    }


    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    void CSVOutput::execute(std::shared_ptr<node>& text, plDataSet& data_store)
    {
        //set of nodes to check
        vector<shared_ptr<node>> in;
        vector<shared_ptr<node>> out;
        out.push_back(text);

        //run the following loop while there are still nodes to parse.
        while(out.size() > 0)
        {
            in.clear();     //clear i
            in = out;       //set i equal to the previous o
            out.clear();    //clear o for new nodes.

            //loop through a node set
            for (int i=0; i<in.size(); ++i)
            { 
                //if the node has children:
                if (in[i]->HasChildren())
                {
                    //loop through all children
                    for(int j=0; j<in[i]->GetNumberOfChildren(); ++j)
                    {
                        //add them to a new set of nodes to parse.
                        out.push_back(in[i]->GetChild(j));
                    }//j
                }
                //if not:
                else
                {
                    //add the node value to the hash table.
                    data_store.set( in[i]->GetID(), hValue(in[i]->GetValue(), in[i]->GetPath()) );
                }
            }//i
        }
    }