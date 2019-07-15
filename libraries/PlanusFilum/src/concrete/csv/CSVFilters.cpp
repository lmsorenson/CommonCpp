// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSVFilters.hpp"
#include <iostream>
#include <sstream>
#include <vector>

    using namespace std;


    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    //---------------------------------------------------------------------------//
    RecordFilter::RecordFilter(){}
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
    FieldFilter::FieldFilter(){}
    FieldFilter::~FieldFilter(){ cout <<"deconstructing field filter. "<< endl; }

    vector<node> FieldFilter::execute(const char * text)
    {
        vector<node> output;

        char * pch;

        printf ("Splitting string \"%s\" into tokens:\n", text);
        pch = strtok((char *)text,",");

        while (pch != NULL)
        {
            // cout << pch << endl;
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
        vector<node> n;
        n.push_back(*text);

        //loop through a node set
        for (int i=0; i<n.size(); ++i)
        { 
            //if the node has children:
            if (n[i]->HasChildren())
            {
                //loop through all children
                for(int j=0; j<n[i]->GetNumberOfChildren(); ++j)
                {
                    //add them to a new vector.
                    vector<node> n2;
                    n2.push_back(n[i].GetChild(j));
                }
            }
            //if not:
            else
            {
                //add the node value to the hash table.
                // data_store.Set("Hello", "World!");
            }
        }
        // text->Print();
    }