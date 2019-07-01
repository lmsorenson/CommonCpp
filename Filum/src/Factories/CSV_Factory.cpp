#include "CSV_Factory.hpp"
#include "../Reads/ReadCSV.hpp"
#include "../DataStructures/CSVData.hpp"
#include <iostream>


using namespace std;

ReadStrategy * CSV_Factory::MakeRead()
{
    cout << "Make csv read strategy" << endl;
    return new ReadCSV();
}

WriteStrategy * CSV_Factory::MakeWrite()
{
    cout << "Make csv write strategy" << endl;
    return new WriteStrategy();
}

AbstractDataStructure * CSV_Factory::MakeData()
{
    return new CSVData();
}