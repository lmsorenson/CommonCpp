// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include "../../../intermediate/Stream.hpp"
#include "../../../intermediate/Error.hpp"

namespace sdg {

class ErrorQueue
{
    pipeline::Stream<Error> * error_stream_;

public:
    explicit ErrorQueue(pipeline::Stream<Error> * stream);
    virtual ~ErrorQueue() = default;

    virtual void add_error(Error);
};

}// namespace sdg