// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../Parser.hpp"
#include <iostream>
#include <time.h>

using ::sdg::Parser;
using ::sdg::parse::Shape;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::dynamic_pointer_cast;
using ::std::make_shared;
using ::std::string;

using ::sdg::SyntaxNode;




void Parser::receive_event()
{
    this->parse();
}


//This function is called every time there is a change made to the token stream.
void Parser::parse()
{
    stopwatch_.start();

    //this while is executed for each token in the token stream,
    //only when the parser is sufficiently configured.
    while ( this->ready() && this->source_->tokens_available() )
    {   
        //removes a token from the token stream.
        string token = source_->pull_token();

        //gets the expected token type
        auto token_type = expected_token_sequence_->match_token(token);

        if (token_type)
        {
            auto node = token_type->create_node(token);
            cout << "parser generating node of type: " << token_type->get_typeid() << endl;
            auto key = token_type->get_typeid();

            shared_ptr<parse::DependentEntity> dependent;
            if((dependent = dynamic_pointer_cast<parse::DependentEntity>(token_type)))
            {
                scope_[key] = produce_child_node(scope_[dependent->dependent_on_typeid()], node.first, node.second);
            }
            else
            {
                scope_[key] = produce_node(node.first, node.second);
            }
        }
        else
        {
            cout << "Error: The token ( " << token << " ) was not expected in this scope. " << endl;
            handle_error({UNKNOWN_ERROR});
        }
    }

    stopwatch_.stop();
}

double Parser::get_time() const
{
    return stopwatch_.read_seconds();
}

shared_ptr<SyntaxNode> Parser::produce_node(string key, string value)
{
    stopwatch_.stop();
    auto node = target_->add_to_root(key, value);
    stopwatch_.start();

    return node;
}

shared_ptr<SyntaxNode> Parser::produce_child_node(shared_ptr<SyntaxNode> node, string key, string value)
{
    stopwatch_.stop();
    
    auto new_node = target_->add_to_node(node, key, value);
    if (!new_node)
    {
        cout << "ERROR FOUND: could not assign token to node." << endl;
        handle_error({UNKNOWN_ERROR});
    }
    
    return new_node;

    stopwatch_.start();
}

void Parser::handle_error(Error error)
{
    error_queue_->add_error(error);
}