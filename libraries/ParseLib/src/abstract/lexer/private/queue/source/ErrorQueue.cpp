// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../ErrorQueue.hpp"



using ::std::string;
using ::sdg::ErrorQueue;
using ::sdg::pipeline::Stream;
using ::sdg::Error;

ErrorQueue::ErrorQueue(Stream<Error> * stream)
: error_stream_(stream)
{}


void ErrorQueue::add_error( Error a_new_error )
{
    error_stream_->add( a_new_error );
}