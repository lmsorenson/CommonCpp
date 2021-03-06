// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../csv_filters.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>
#include <stdio.h>

using std::string;
using std::vector;
using std::istringstream;
using std::shared_ptr;
using sdg::SyntaxNode;
using sdg::plHashValue;
using sdg::ParserFilter;



//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
sdg::csv::HeaderFilter::HeaderFilter(const string &new_filter_id)
: ParserFilter(new_filter_id)
{}

int32_t sdg::csv::HeaderFilter::execute(const string &text, vector<SyntaxNode>& output)
{
    istringstream file(text);
    string line, r_buffer;
    bool b_first_line = true;

    while (std::getline(file, line)) 
    {
        if(b_first_line)
        {
            //push line 1 as a new SyntaxNode.
            output.push_back(SyntaxNode(line, nullptr));

            //once the first line has been separated.
            //indicate this is no longer the first line.
            b_first_line = false;
        }
        else
        {
            r_buffer.append(line);
            r_buffer.append("\r\n");//add the carriage return back
        }
    }

    output.push_back(SyntaxNode(r_buffer, nullptr));


    return FILTER_SUCCESS;
}

int32_t sdg::csv::HeaderFilter::inverse(std::vector<std::string> string_set, std::string &compiled_string)
{
    return 0;
}

string sdg::csv::HeaderFilter::name()
{
    return "header";
}
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
sdg::csv::RecordFilter::RecordFilter(const string &new_filter_id)
: ParserFilter(new_filter_id)
{}

int32_t sdg::csv::RecordFilter::execute(const string &text, vector<SyntaxNode>& output)
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

        //add the new SyntaxNode to the filter output.
        if(!record_value.empty())
            output.push_back(SyntaxNode(record_value.c_str(), nullptr));
    }//last line
    
    if(output.size()==0)
        return FILTER_FORMAT_ERROR;
    
    return FILTER_SUCCESS;
}

int32_t sdg::csv::RecordFilter::inverse(std::vector<std::string> string_set, std::string &compiled_string)
{
    for(int32_t i=0; i<string_set.size(); ++i)
    {
        compiled_string.append(string_set[i]);

        if(i+1 == string_set.size())
            continue;
        else
            compiled_string.append(",");

    }

    return FILTER_SUCCESS;
}

string sdg::csv::RecordFilter::name()
{
    return "record";
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
sdg::csv::FieldFilter::FieldFilter(const string &new_filter_id)
: ParserFilter(new_filter_id)
, field_count(-1)
{}

int32_t sdg::csv::FieldFilter::execute(const string &text, vector<SyntaxNode>& output)
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

        //if there is not an open quotation, push the SyntaxNode to the buffer
        if ((number_of_quotes%2==0))
        {
            output.push_back(SyntaxNode(buffer, nullptr));
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

int32_t sdg::csv::FieldFilter::inverse(std::vector<std::string> string_set, std::string &compiled_string)
{
    for(int32_t i=0; i<string_set.size(); ++i)
    {
        compiled_string.append(string_set[i]);

        if(i+1 == string_set.size())
            continue;
        else
            compiled_string.append("\r\n");

    }

    return FILTER_SUCCESS;
}

string sdg::csv::FieldFilter::name()
{
    return "field";
}

bool sdg::csv::FieldFilter::IsFieldCountValid(int32_t field_count_param)
{
    //if the field_count is null '-1' set the field count to the first entry.
    if (field_count==-1)
        field_count=field_count_param;
    
    //field count 0 and inconsistent field sizes are format violations.
    if( (field_count!=0) && (field_count==field_count_param) )
    {
        return true;
    }
    else
    {
        return false;
    }
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
void sdg::csv::CSVOutput::execute(std::shared_ptr<SyntaxNode>& text, sdg::DataSet& data_store)
{
    std::cout << "------------------" << std::endl;
    text->Print();

    //set of nodes to check
    vector<shared_ptr<SyntaxNode>> in;
    vector<shared_ptr<SyntaxNode>> out;
    out.push_back(text);

    //run the following loop while there are still nodes to parse.
    while(out.size() > 0)
    {
        in.clear();     //clear i
        in = out;       //set i equal to the previous o
        out.clear();    //clear o for new nodes.

        //loop through a SyntaxNode set
        for (int i=0; i<in.size(); ++i)
        { 
            //if the SyntaxNode has children:
            if (in[i]->has_children())
            {
                //loop through all children
                for(int j=0; j<in[i]->get_number_of_children(); ++j)
                {
                    //add them to a new set of nodes to parse.
                    out.push_back(in[i]->get_child(j));
                }//j
            }
            //if not:
            else
            {
                //add the SyntaxNode value to the hash table.
                data_store.set( hash::KeyInstance(in[i]->get_item_key()), plHashValue( in[i]->get_item_value(), in[i]->get_path() ) );
            }
        }//i
    }
}