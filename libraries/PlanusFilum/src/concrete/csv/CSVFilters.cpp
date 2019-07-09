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

    std::vector<node> RecordFilter::execute(const char * text)
    {
        vector<node> output;

        istringstream file(text);
        string line;

        while (std::getline(file, line)) {
            cout << line << endl;
            node n = node(line.c_str());
            output.push_back(n);
        }

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

    std::vector<node> FieldFilter::execute(const char * text)
    {
        vector<node> output;

        char * pch;

        printf ("Splitting string \"%s\" into tokens:\n", text);
        pch = strtok((char *)text,",");

        while (pch != NULL)
        {
            cout << pch << endl;
            node n = node(pch);
            output.push_back(n);
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
        cout << "Pipeline finished." << endl;
    }