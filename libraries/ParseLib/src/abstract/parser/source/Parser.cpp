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
: syntax_tree_(make_shared<SyntaxNode>("root", nullptr))
, record_index_(0)
, field_index_(0)
{
    syntax_tree_->AddChild( SyntaxNode("R0", syntax_tree_ ) );
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

            auto n = SyntaxNode(string(), syntax_tree_);

            //determine which parent the record should be assigned to.
            syntax_tree_->AddChild( n );

            this->field_index_ = 0;
        }

        if( token.substr(0,1).compare("F") == 0 )
        {
            char buffer[10];
            sprintf(buffer, "R%d-F%d", record_index_, field_index_);

            auto n = SyntaxNode(token.substr( token.find("(")+1, token.length()-(token.find("(")+2) ), syntax_tree_);
            n.append_key(buffer);
            syntax_tree_->get_child(record_index_)->AddChild( n );

            auto read_node = syntax_tree_->get_child(record_index_)->get_child(field_index_);
            cout << read_node->get_item_key() << " " << read_node->get_item_value() << endl;

            this->field_index_++;
        }
    }
}