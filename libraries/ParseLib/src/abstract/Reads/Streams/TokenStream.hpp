// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../lexer/Lexer.hpp"
#include "../../parser/Parser.hpp"
#include "Stream.hpp"



namespace sdg {

class CSVTarget : public TokenTarget
{
    pipeline::Stream<std::string> * token_stream_;

public:
    CSVTarget( pipeline::Stream<std::string> * token_stream_ptr ) 
    : token_stream_( token_stream_ptr ){}

    virtual void send_token(std::string) override;
};

class CSVTokenSource : public TokenSource
{
    pipeline::Stream<std::string> * token_stream_;

public:
    CSVTokenSource( pipeline::Stream<std::string> * token_stream_ptr ) 
    : token_stream_( token_stream_ptr ){}

    virtual bool tokens_available() const override;
    virtual std::string pull_token() override ;
};

}// namespace sdg