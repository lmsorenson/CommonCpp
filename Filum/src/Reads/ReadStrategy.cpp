#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include "../../include/loadText.h"

using namespace std;

AbstractDataStructure * ReadStrategy::run(const char * path)
{
    cout << "Running read strategy." << endl; 

    string str = loadText(path);

    // parse();
    // select();

    return new AbstractDataStructure();
}