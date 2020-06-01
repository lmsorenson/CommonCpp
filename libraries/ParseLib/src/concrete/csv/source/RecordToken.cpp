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
    if(token.compare("R")==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void RecordToken::create_node(string a_token) const 
{
    cout << "token classified:" << a_token << " ";
    print();
}