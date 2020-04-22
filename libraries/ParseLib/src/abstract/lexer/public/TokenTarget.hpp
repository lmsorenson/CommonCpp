// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <queue>

namespace sdg {

class TokenTarget
{
    std::queue<std::string> * token_stream_;

public:
    TokenTarget(std::queue<std::string> * token_stream_ptr) 
    : token_stream_(token_stream_ptr){}

    void add_token(std::string);
};

}// namespace sdg