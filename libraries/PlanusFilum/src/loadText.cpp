#include "../include/loadText.h"

#include <iostream>
#include <fstream>

using namespace std;

const char * loadText(const char * filepath)
{
    //return file
    char * output = new char[1024];
    
    string line;
    
    //open file
    ifstream file (filepath);
    if (file.is_open())
    {
        while ( getline(file,line) )
        {
            strcat(output, line.c_str());
            strcat(output, "\n");
        }

        file.close();
    }
    else
    {
        return LOAD_ERROR_STR;
    }
    	return output;
}