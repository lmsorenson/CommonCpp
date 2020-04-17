#include "../load_text.h"

#include <iostream>
#include <fstream>
#include "sys/types.h"
#include "unistd.h"
#include <fcntl.h>


using ::std::string;
using ::std::ifstream;



string sdg::utils::loadText(string filepath)
{
    //return file
    string output, line;
    
    //open file
    ifstream file (filepath.c_str());
    if (file.is_open())
    {
        while ( getline(file,line) )
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