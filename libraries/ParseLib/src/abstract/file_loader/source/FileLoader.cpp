// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../FileLoader.hpp"
#include <iostream>
#include <fstream>

using ::sdg::FileLoader;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::string;
using ::std::ifstream;



int FileLoader::load(string filepath)
{
    //open file
    ifstream file (filepath.c_str());
    if (file.is_open())
    {
        char ch;
        while (file.get(ch))
        {
            target_->send_char(ch);
        }

        file.close();
    }
    else
    {
        return -1;
    }

    //sends a new line to indicate the end of the file.
    target_->send_char('\r');
    target_->send_char('\n');

    return 0;
}