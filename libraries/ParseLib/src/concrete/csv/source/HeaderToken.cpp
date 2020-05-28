// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../HeaderToken.hpp"
#include <iostream>
#include <string>

using sdg::HeaderToken;
using std::string;
using std::cout;
using std::endl;

void HeaderToken::print() const
{
}

bool HeaderToken::classify(std::string token) const
{
    cout << "classifing token expecting a header: " << token << endl;

    if(token.compare("H")==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}