// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../HeaderToken.hpp"
#include <iostream>
#include <string>

using sdg::HeaderToken;
using sdg::SyntaxNode;
using std::string;
using std::to_string;
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

SyntaxNode HeaderToken::create_node(string a_token)
{
    //updates the count for the new node
    new_node();

    return SyntaxNode(this->get_id(), nullptr);
}

string HeaderToken::get_id() const
{
    return string("H-R0");
}