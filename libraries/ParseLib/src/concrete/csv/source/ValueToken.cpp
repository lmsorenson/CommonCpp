// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../ValueToken.hpp"
#include <iostream>
#include <string>

using sdg::ValueToken;
using std::string;
using std::cout;
using std::endl;

void ValueToken::print() const
{
    cout << "value" << endl;
}

bool ValueToken::classify(std::string token) const
{
    cout << "classifing token expecting a value: " << token << endl;

    if(token[0] == 'F')
        return true;

    else
        return false;
}