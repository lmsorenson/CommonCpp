// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "CSV_Write.hpp"







int32_t CSV_Write::set_read_options(std::vector<option> read_options)
{
    for (auto option : read_options)
    {
        if((option.name == "header_line") && (option.value>0))
            this->b_use_header_line = true;
    }

    return 0;
}