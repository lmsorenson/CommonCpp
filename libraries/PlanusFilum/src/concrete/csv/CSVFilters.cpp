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

    std::vector<std::string> RecordFilter::execute(const char * text)
    {
        vector<string> output;

        istringstream file(text);
        string line;

        while (std::getline(file, line)) {
            cout << line << endl;
            output.push_back(line);
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

    std::vector<std::string> FieldFilter::execute(const char * text)
    {
        vector<string> output;

        char * pch;

        printf ("Splitting string \"%s\" into tokens:\n", text);
        pch = strtok((char *)text,",");

        while (pch != NULL)
        {
            cout << pch << endl;
            output.push_back(string(pch));
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