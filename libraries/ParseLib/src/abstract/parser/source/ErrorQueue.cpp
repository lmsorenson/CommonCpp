// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/ErrorQueue.hpp"



using ::std::string;
using ::sdg::parser::ErrorQueue;
using ::sdg::Error;


void ErrorQueue::add_error( Error a_new_error )
{
    error_stream_->add( a_new_error );
}