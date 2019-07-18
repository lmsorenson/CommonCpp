// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../include/ParseLib.h"
#include "abstract/DataStructures/AbstractDataStructure.hpp"

#include <iostream>
#include <string>

#include "concrete/csv/CSVData.hpp"
#include "concrete/csv/CSV_Factory.hpp"

using namespace std;

int32_t ParseLib::read_file(AbstractDataStructure& data_store, const char * filepath)
{
    cout << "DEBUG: reading file. . . " << '\r' << flush;

    //-----------------------|   Parse file path   |-----------------------//




    //-----------------------|   Generate strategies & Data   |-----------------------//
    CSV_Factory factory;                    //TODO-->make factory producer
    auto data = factory.make_data();         //use the factory to initialize the data variable.
    auto strategy = factory.make_read();     //initialize appropriate read strategy

    //-----------------------|   Execute read   |-----------------------//
    if(strategy->execute_read(filepath, *data))
    {
        //return 1 on execution failure.
        cout << "ERROR: read execution failed." << '\r' << flush;    
        return 1;
    }

    //-----------------------|   Clean up   |-----------------------//
    cout << "DEBUG: done reading file." << '\r' << flush;

    //-----------------------|   Return   |-----------------------//
    data_store = *data;
    return 0;
}

int32_t ParseLib::write_file()
{
    cout << "DEBUG: starting a write. . ."
    //STEP 1 -- FACTORY.
    
    //STEP 2 -- READ the file.
    // this->read_file();

    //STEP 3 -- MODIFY the data.

    //STEP 4 -- WRITE the file.

    "DEBUG: done writing file." << '\r' << flush;
    return 0;
}

