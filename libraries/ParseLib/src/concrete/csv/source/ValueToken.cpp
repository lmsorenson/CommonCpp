// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../ValueToken.hpp"
#include <iostream>
#include <string>


using sdg::ValueToken;
using sdg::SyntaxNode;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::string;
using std::to_string;
using std::cout;
using std::endl;

void ValueToken::print() const
{
    cout << "value" << endl;
}

bool ValueToken::classify(std::string token) const
{
    if(token[0] == 'F')
        return true;

    else
        return false;
}

SyntaxNode ValueToken::create_node(string a_token) 
{
    //updates the count for the new node
    new_node();

    shared_ptr<Shape> shape = dynamic_pointer_cast<Shape>(owner_);
    if( shape )
        cout << "CREATE_NODE " << shape->get_id();
    else
        return SyntaxNode("null", nullptr);
    
    cout << "-" << this->get_id() << endl;

    return SyntaxNode(shape->get_id() + "-" + this->get_id(), nullptr);
}

string ValueToken::get_id() const
{
    return string("F" + to_string(shape_occurances_-1));
}