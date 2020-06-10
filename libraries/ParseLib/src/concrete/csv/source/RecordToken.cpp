// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../RecordToken.hpp"
#include <iostream>
#include <string>

using sdg::RecordToken;
using sdg::SyntaxNode;
using std::string;
using std::to_string;
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

SyntaxNode RecordToken::create_node(string a_token) 
{
    //updates the count for the new node
    new_node();

    return SyntaxNode(this->get_id(), nullptr);
}

string RecordToken::get_id() const
{
    return string("R" + to_string(shape_occurances_-1));
}