#include "../include/loadText.h"

#include <iostream>
#include <fstream>

using namespace std;

const char * loadText(const char * filepath)
{
    //return file
    char * text = new char[1024];
    
    string line;
    
    //open file
    ifstream file (filepath);
    if (file.is_open())
    {
        while ( getline(file,line) )
        {
            strcat(text, line.c_str());
            strcat(text, "\n");
        }

        file.close();
    }
    else
    {
        return LOAD_ERROR_STR;
    }
    	return text;
}

