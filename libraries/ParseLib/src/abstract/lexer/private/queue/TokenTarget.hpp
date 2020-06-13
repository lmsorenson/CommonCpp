// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../../intermediate/Stream.hpp"

namespace sdg {

class TokenTarget
{
    pipeline::Stream<std::string> * token_stream_;

public:
    TokenTarget(pipeline::Stream<std::string> * stream)
    : token_stream_(stream){}
    
    virtual ~TokenTarget() = default;

    virtual void send_token(std::string);
};

}// namespace sdg