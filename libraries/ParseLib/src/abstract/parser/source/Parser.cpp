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


//This function is called every time there is a change made to the token stream.
void Parser::parse()
{
    stopwatch_.start();

    //this while is executed for each token in the token stream,
    //only when the parser is sufficiently configured.
    while ( this->ready() && this->source_->tokens_available() )
    {   
        //removes a token from the token stream.
        string token=source_->pull_token();

        if (token.compare(string("R")) == 0)
        {
            char rec_buffer[10];
            sprintf(rec_buffer, "R%d", record_count_); // important to increment before
            cout << "<<< " << rec_buffer << " >>>" << endl;

            produce_node(rec_buffer, string());

            scope_ = rec_buffer;
            record_count_++;
            field_count_ = 0;
        }

        if (token.compare(string("H")) == 0)
        {
            char rec_buffer[10];
            sprintf(rec_buffer, "H-R0"); // important to increment before
            cout << "<<< " << rec_buffer << " >>>" << endl;

            produce_node(rec_buffer, string());

            scope_ = rec_buffer;
            field_count_ = 0;
        }

        if (token.substr(0, 1).compare(string("F")) == 0 )
        {
            
            char buffer[10];
            sprintf(buffer, "%s-F%d", scope_.c_str(), field_count_);
            cout << "<<< " << buffer << " >>>" << endl;

            produce_child_node({record_count_-1}, buffer, token.substr(token.find("(") + 1, token.length() - (token.find("(") + 2)));

            field_count_++;
        }

        // for ( shared_ptr<TokenType> type : this->token_types_ )
        //     type->handle_type( token );
    }

    stopwatch_.stop();
}

double Parser::get_time() const
{
    return stopwatch_.read_seconds();
}

void Parser::produce_node(string key, string value)
{
    stopwatch_.stop();
    target_->add_to_root(key, value);
    stopwatch_.start();
}

int32_t Parser::produce_child_node(std::vector<int> path, std::string key, std::string value)
{
    stopwatch_.stop();
    
    if(target_->add_to_node(path, key, value)==0)
    {
        return 0;
    }
    else
    {
        cout << "ERROR FOUND: could not assign token to node." << endl;
        handle_error({UNKNOWN_ERROR});
        return 1;
    }
    
    stopwatch_.start();
}

void Parser::handle_error(Error error)
{
    error_queue_->add_error(error);
}