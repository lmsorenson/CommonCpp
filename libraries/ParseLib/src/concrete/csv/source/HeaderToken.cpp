// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../HeaderToken.hpp"
#include <iostream>
#include <string>

using sdg::HeaderToken;
using sdg::SyntaxNode;
using std::string;
using std::pair;
using std::shared_ptr;
using std::make_shared;
using std::to_string;
using std::cout;
using std::endl;

bool HeaderToken::classify(const std::string &token) const
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

std::pair<std::string, std::string> HeaderToken::create_node(const string &a_token)
{
    //updates the count for the new node
    new_node();

    return pair<string, string>(this->get_id(), a_token);
}

string HeaderToken::get_id() const
{
    return string("H-R0");
}