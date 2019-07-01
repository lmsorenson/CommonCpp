#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../include/loadText.h"

using namespace std;

AbstractDataStructure * ReadStrategy::run(const char * path)
{
    cout << "Running read strategy." << endl; 

    AbstractDataStructure ds;

    //load text
    string str = loadText(path);

    //parse text
    vector<string> arr = parse();

    //select fields
    string sel = select();
    
    //assign fields
    ds.assign();

    return new AbstractDataStructure();
}