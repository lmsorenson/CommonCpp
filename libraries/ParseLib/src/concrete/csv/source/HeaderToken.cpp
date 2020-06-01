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
    cout << "header" << endl;
}

bool HeaderToken::classify(std::string token) const
{
    if(token.compare("H")==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void HeaderToken::create_node(string a_token) const
{
    cout << "token classified:" << a_token << " ";
    print();
}