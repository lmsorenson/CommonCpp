// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../ErrorQueue.hpp"



using ::std::string;
using ::sdg::ErrorQueue;
using ::sdg::Error;


void ErrorQueue::add_error( Error a_new_error )
{
    error_stream_->add( a_new_error );
}