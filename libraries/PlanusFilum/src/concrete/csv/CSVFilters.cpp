// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSVFilters.hpp"
#include <iostream>
#include <sstream>

    using namespace std;


    RecordFilter::RecordFilter(){}
    RecordFilter::~RecordFilter(){ cout <<"deconstructing record filter. "<< endl; }

    void RecordFilter::execute()
    {
        istringstream f("line1\nline2\nline3");
        string line;    
        while (std::getline(f, line)) {
            cout << line << endl;
        }
    }
    
    const char * RecordFilter::name()
    {
        return "record";
    }




    FieldFilter::FieldFilter(){}
    FieldFilter::~FieldFilter(){ cout <<"deconstructing field filter. "<< endl; }

    void FieldFilter::execute()
    {

    }
    
    const char * FieldFilter::name()
    {
        return "field";
    }