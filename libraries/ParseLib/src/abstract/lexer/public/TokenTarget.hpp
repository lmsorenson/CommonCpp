// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <queue>

namespace sdg {

class TokenTarget
{
    std::deque<std::string> * token_stream_;

public:
    TokenTarget(std::deque<std::string> * token_stream_ptr) 
    : token_stream_(token_stream_ptr){}

    void send_token(std::string);
};

}// namespace sdg