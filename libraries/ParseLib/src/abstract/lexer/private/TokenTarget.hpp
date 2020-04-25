// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../Reads/Stream.hpp"

namespace sdg {

class TokenTarget
{
    pipeline::Stream<std::string> * token_stream_;

public:
    TokenTarget(pipeline::Stream<std::string> * token_stream_ptr) 
    : token_stream_(token_stream_ptr){}

    void send_token(std::string);
};

}// namespace sdg