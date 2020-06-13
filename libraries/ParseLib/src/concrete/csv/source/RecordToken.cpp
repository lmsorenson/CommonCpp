// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../RecordToken.hpp"
#include <iostream>
#include <string>

using sdg::RecordToken;
using sdg::SyntaxNode;
using std::string;
using std::pair;
using std::to_string;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;

bool RecordToken::classify(string token) const
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

pair<string, string> RecordToken::create_node(string a_token) 
{
    //updates the count for the new node
    new_node();

    return pair<string, string>(this->get_id(), a_token);
}

string RecordToken::get_id() const
{
    return string("R" + to_string(shape_occurances_-1));
}