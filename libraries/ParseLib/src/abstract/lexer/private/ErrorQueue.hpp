// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../intermediate/Stream.hpp"
#include "../../intermediate/Error.hpp"

namespace sdg {

class ErrorQueue
{
    pipeline::Stream<Error> * error_stream_;

public:
    ErrorQueue(pipeline::Stream<Error> * stream)
    : error_stream_(stream){}
    
    ~ErrorQueue() = default;

    virtual void add_error(Error);
};

}// namespace sdg