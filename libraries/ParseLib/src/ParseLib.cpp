// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../include/ParseLib.h"
#include "abstract/DataStructures/InstanceSet.hpp"

#include <iostream>
#include <string>

#include "concrete/csv/CSVData.hpp"
#include "concrete/csv/CSV_Factory.hpp"

using namespace std;

int32_t ParseLib::read_file(InstanceSet& data_store, const char * filepath)
{
    cout << "DEBUG: reading file. . . " << '\r' << flush;

    //-----------------------|   Parse file path   |-----------------------//




    //-----------------------|   Generate strategies & Data   |-----------------------//
    CSV_Factory factory;                    //TODO-->make factory producer
    auto data = factory.make_data();         //use the factory to initialize the data variable.
    auto strategy = factory.make_read();     //initialize appropriate read strategy

    //-----------------------|   Execute read   |-----------------------//
    int32_t return_code;
    if((return_code=strategy->execute_read(filepath, *data)))
    {
        switch (return_code)
        {
            case ReadStrategy::FILE_NOT_FOUND: return READ_FILE_NOT_FOUND; break;
            case ReadStrategy::FILE_FORMAT_INVALID: return READ_FORMAT_INVALID; break;
            default: return UNKNOWN_ERROR; break;
        }
    }

    //-----------------------|   Clean up   |-----------------------//

    //-----------------------|   Return   |-----------------------//
    data_store = *data;
    return READ_SUCCESSFUL;
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

