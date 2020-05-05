// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../Parser.hpp"
#include <iostream>
#include <time.h>

using ::sdg::Parser;
using ::sdg::TokenType;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::make_shared;
using ::std::string;

using ::sdg::SyntaxNode;




void Parser::receive_event()
{
    this->parse();
}


Parser::Parser()
: record_index_(0)
, field_index_(0)
{
    // syntax_tree_->AddChild( SyntaxNode("R0", syntax_tree_ ) );
}


//This function is called every time there is a change made to the token stream.
void Parser::parse()
{
    clock_t t = clock();

    //this while is executed for each token in the token stream,
    //only when the parser is sufficiently configured.
    while ( this->ready() && this->source_->tokens_available() )
    {   
        //removes a token from the token stream.
        string token=source_->pull_token();

            //todo -- this should be applied on the first write to the syntax tree
        if(target_->is_empty())
            target_->add_to_root("R0", std::string());

        for ( shared_ptr<TokenType> type : this->token_types_ )
            type->handle_type( token );

    }

    t = clock() - t; 
    time_taken_ += ((double)t)/CLOCKS_PER_SEC; // in seconds
}

double Parser::get_time() const
{
    return time_taken_;
}

void Parser::produce_node(string key, string value)
{
    target_->add_to_root(key, value);
}

void Parser::produce_child_node(std::vector<int> path, std::string key, std::string value)
{
    target_->add_to_node(path, key, value);
}