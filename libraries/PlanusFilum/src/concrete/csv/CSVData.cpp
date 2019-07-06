#include "CSVData.hpp"
#include <iostream>


using namespace std;


CSVData::CSVData()
{
    cout << "constructing csv data . . . " << endl;
}

CSVData::~CSVData()
{
    cout << "destructing csv data . . . " << endl;
}

void CSVData::assign()
{
    cout << "assign csv data" << endl;
}