#include "../include/loadText.h"

#include <iostream>
#include <fstream>
#include "sys/types.h"
#include "unistd.h"
#include <fcntl.h>

using namespace std;

string loadText(string filepath)
{
    //return file
    string output;
    
    string line;
    
    //open file
    ifstream file (filepath.c_str());
    if (file.is_open())
    {
        while ( getline(file,line), file.good() )
        {
            output
            .append(line)
            .append("\r\n");
        }

        file.close();
    }
    else
    {
        return string(LOAD_ERROR_STR);
    }
    	return output;
}