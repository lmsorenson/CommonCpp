// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../TokenType.hpp"
#include <iostream>
#include "../../../intermediate/Error.hpp"

using sdg::parse::TokenType;
using std::function;
using std::cout;
using std::endl;
using std::string;

void TokenType::print() const
{
    cout << "token type found . . ." << endl;
}

bool TokenType::evaluate(string a_token, function<void()> next_element, function<void(int32_t type, std::string message)> handle_error)
{
    bool 
        token_valid = classify(a_token),
        token_repeating = HasMultiplicity();

    if ( token_valid )
    {
        create_node(a_token);

        if(!token_repeating)
            next_element();
    }
    //if the inverse is true, check the next token
    else if( !token_valid && token_repeating )
    {
        return false;
    }
    //if the token does not match
    else
    {
        handle_error(UNKNOWN_ERROR, "Error: Sequence position has unexpected type.");
    }

    return true;
}