// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../Parser.hpp"
#include <iostream>

using ::sdg::Parser;
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
    //this while is executed for each token in the token stream,
    //only when the parser is sufficiently configured.
    while ( this->ready() && this->source_->tokens_available() )
    {   
        //removes a token from the token stream.
        string token=source_->pull_token();

        if( token.compare("R")==0 )
        {
            char rec_buffer[10];
            sprintf(rec_buffer, "R%d", record_index_);
            this->record_index_++;

            target_->add_to_root(rec_buffer, string());

            this->field_index_ = 0;
        }

        if( token.substr(0,1).compare("F") == 0 )
        {
            char buffer[10];
            sprintf(buffer, "R%d-F%d", record_index_, field_index_);

            target_->add_to_node({record_index_}, buffer, token.substr( token.find("(")+1, token.length()-(token.find("(")+2) ));

            this->field_index_++;
        }
    }
}