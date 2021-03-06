#include "../write_text.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include "sys/types.h"
#include "unistd.h"
#include <fcntl.h>


using ::std::string;
using ::std::ofstream;



string sdg::utils::writeText(string filepath, string contents)
{   
    //open file
    ofstream file (filepath.c_str());
    if (file.is_open())
    {
        file.write(contents.c_str(), contents.size());

        file.close();
    }
    else
    {
        return string(WRITE_ERROR_STR);
    }
    	return "";
}