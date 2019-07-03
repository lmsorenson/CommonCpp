#include "../include/file_inst.h"

#include <iostream>
#include <string>

#include "DataStructures/CSVData.hpp"
#include "Factories/CSV_Factory.hpp"

using namespace std;

int32_t Filum::read_file(const char * filepath)
{
    cout << "DEBUG: reading file. . . " << endl;

    string file_extension;

    //STEP 1 -- FACTORY
    CSV_Factory factory; //TODO-->make factory producer

    cout << "Construct" << endl;
    auto data = factory.MakeData();
    
    cout << "Run" << endl;
    data = factory.MakeRead()->run(filepath);//TODO --> substitute real path

    cout << "DEBUG: done reading file." << endl;
    return 0;
}

int32_t Filum::write_file()
{
    cout << "DEBUG: starting a write. . ."
    //STEP 1 -- FACTORY.
    
    //STEP 2 -- READ the file.
    // this->read_file();

    //STEP 3 -- MODIFY the data.

    //STEP 4 -- WRITE the file.

    "DEBUG: done writing file." << endl;
    return 0;
}

