// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../Reads/Stream.hpp"

namespace sdg {

class TokenSource
{
    pipeline::Stream<std::string> * token_stream_;

public:
    TokenSource( pipeline::Stream<std::string> * shared_queue_ptr ) 
    : token_stream_( shared_queue_ptr ){}

    bool tokens_available() const;
    std::string pull_token();
};

}// namespace sdg