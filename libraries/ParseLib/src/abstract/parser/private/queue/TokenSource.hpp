// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../../intermediate/Stream.hpp"

namespace sdg {

class TokenSource
{
    pipeline::Stream<std::string> * token_stream_;

public:
    TokenSource(pipeline::Stream<std::string> * stream)
    : token_stream_(stream){}
    
    virtual ~TokenSource() = default;

    virtual bool tokens_available() const;
    virtual std::string pull_token();
};

}// namespace sdg