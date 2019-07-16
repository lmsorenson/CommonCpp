// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSVFilters.hpp"
#include <iostream>
#include <sstream>
#include <vector>

    using namespace std;


    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    RecordFilter::RecordFilter(std::string new_filter_id) : ParserFilter(new_filter_id){}
    RecordFilter::~RecordFilter(){ cout <<"deconstructing record filter. "<< endl; }

    vector<node> RecordFilter::execute(const char * text)
    {
        cout << "record: start" << endl;
        vector<node> output;

        istringstream file(text);
        string line;

        while (std::getline(file, line)) {
            cout << "record: new line" << endl;
            output.push_back(node(line.c_str()));
            cout << "record: end of loop" << endl;
        }
        
        cout << "record: nearly done" << endl;
        return output;
    }
    
    const char * RecordFilter::name()
    {
        return "record";
    }


    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    FieldFilter::FieldFilter(std::string new_filter_id) : ParserFilter(new_filter_id){}
    FieldFilter::~FieldFilter(){ cout <<"deconstructing field filter. "<< endl; }

    vector<node> FieldFilter::execute(const char * text)
    {
        vector<node> output;

        char * pch;

        printf ("Splitting string \"%s\" into tokens:\n", text);
        pch = strtok((char *)text,",");

        while (pch != NULL)
        {
            output.push_back(node(pch));
            pch = strtok(NULL, ", ");
        }

        return output;
    }
    
    const char * FieldFilter::name()
    {
        return "field";
    }


    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    void CSVOutput::execute(std::shared_ptr<node>& text, AbstractDataStructure& data_store)
    {
        cout << "CSV Output" << endl;

        //set of nodes to check
        vector<shared_ptr<node>> in;
        vector<shared_ptr<node>> out;
        out.push_back(text);

        //run the following loop while there are nodes still nodes to parse.
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
                    data_store.set(in[i]->GetID(), in[i]->GetValue());
                }
            }//i
        }

        // text->Print();
    }