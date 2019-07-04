#include "CSV_Factory.hpp"
#include "ReadCSV.hpp"
#include "CSVData.hpp"
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
    cout << "Make csv data" << endl;
    return new CSVData();
}