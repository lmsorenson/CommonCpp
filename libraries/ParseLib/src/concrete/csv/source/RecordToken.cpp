// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../RecordToken.hpp"
#include <iostream>
#include <string>

using sdg::RecordToken;
using std::string;
using std::cout;
using std::endl;

void RecordToken::print() const
{
    cout << "record" << endl;
}

bool RecordToken::classify(std::string token) const
{
    cout << "classifing token expecting a record: " << token << endl;
    if(token.compare("R")==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}