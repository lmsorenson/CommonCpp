#include "ReadStrategy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../../../include/loadText.h"

using namespace std;

int32_t ReadStrategy::Execute(const char * filepath, AbstractDataStructure &ds)
{
    cout << "Running read strategy." << endl; 

    //load text
    string file_contents = loadText(filepath);

    //parse text
    vector<vector<string>> arr = parse(file_contents.c_str());

    //select fields
    string sel = select();
    
    //assign fields
    ds.assign();

    return 0;
}