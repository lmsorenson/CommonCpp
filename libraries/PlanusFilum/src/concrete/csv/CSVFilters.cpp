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
    void CSVOutput::execute()
    {
        cout << "CSV Output" << endl;
        // (*n)[0].Print();
    }