// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../TokenType.hpp"
#include <iostream>
#include "../../../intermediate/Error.hpp"

using sdg::parse::TokenType;
using sdg::parse::MatchStatus;
using std::shared_ptr;
using std::function;
using std::cout;
using std::endl;
using std::string;

void TokenType::print() const
{
    cout << "token type found . . ." << endl;
}

shared_ptr<TokenType> TokenType::evaluate(string a_token, function<void()> next_element, MatchStatus &status)
{
    bool 
        token_valid = classify(a_token),
        token_repeating = HasMultiplicity();

    if ( token_valid )
    {
        status = MatchStatus::PositiveMatch;

        if(!token_repeating)
            next_element();
    }
    //if the inverse is true, check the next token
    else if( !token_valid && token_repeating )
    {
        status = MatchStatus::NextElementViable;
    }
    //if the token does not match
    else
    {
        status = MatchStatus::NegativeMatch;
    }

    //whatever called this function already has a pointer to this.
    return nullptr;
}

string TokenType::get_typeid() const
{
    return id_;
}