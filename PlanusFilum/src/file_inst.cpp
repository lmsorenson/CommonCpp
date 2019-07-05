#include "../include/file_inst.h"

#include <iostream>
#include <string>

#include "concrete/csv/CSVData.hpp"
#include "concrete/csv/CSV_Factory.hpp"

using namespace std;

int32_t Filum::read_file(const char * filepath)
{
    cout << "DEBUG: reading file. . . " << endl;

    string file_extension;


    CSV_Factory factory;                    //TODO-->make factory producer
    auto data = factory.MakeData();         //use the factory to initialize the data variable.
    auto strategy = factory.MakeRead();     //initialize appropriate read strategy
    cout << "data type: " << typeid(data).name() << endl;

    //Execute read
    if(strategy->execute_read(filepath, *data))
    {
        //return 1 on execution failure.
        cout << "ERROR: read execution failed." << endl;    
        return 1;
    }

    cout << "DEBUG: done reading file." << endl;

    //free pointers
    delete(data);
    delete(strategy);

    //return 0 on success
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

