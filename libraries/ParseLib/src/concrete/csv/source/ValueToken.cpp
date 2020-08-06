// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../ValueToken.hpp"
#include <iostream>
#include <string>


using sdg::ValueToken;
using sdg::SyntaxNode;
using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::string;
using std::pair;
using std::to_string;
using std::cout;
using std::endl;


ValueToken::ValueToken()
: TokenType("F", Cardinality::Many)
, parse::DependentEntity()
{}

bool ValueToken::classify(const std::string &token) const
{
    if(token[0] == 'F')
        return true;

    else
        return false;
}

std::pair<std::string, std::string> ValueToken::create_node(const string &a_token)
{
    //updates the count for the new node
    new_node();

    shared_ptr<Shape> shape = dynamic_pointer_cast<Shape>(owner_);
    if( shape )
    {
        cout << "Parser generating a node at " << shape->get_id(); 
    }
    else
        return pair<string, string>(string(), string());
    
    cout << "-" << this->get_id();
    cout << " owned by ";
    owner_->print();

    return pair<string, string>(shape->get_id() + "-" + this->get_id(), a_token);
}

string ValueToken::get_id() const
{
    return string("F" + to_string(shape_occurances_-1));
}