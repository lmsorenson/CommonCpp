// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../CharacterStream.hpp"
#include <iostream>
#include <utility>

using ::sdg::CSVSource;
using ::std::string;


bool CSVSource::characters_available() const
{
    return !character_stream_->is_empty();
}

char CSVSource::pull_char()
{
    return character_stream_->get_element();
}