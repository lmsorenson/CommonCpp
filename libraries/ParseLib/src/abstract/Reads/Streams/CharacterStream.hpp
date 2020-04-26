// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../lexer/Lexer.hpp"
#include "Stream.hpp"



namespace sdg {

class CSVSource : public CharacterSource
{
    pipeline::Stream<char> * character_stream_;

public:
    CSVSource( pipeline::Stream<char> * character_source_ptr )
    : character_stream_( character_source_ptr ){}

        virtual bool characters_available() const override;
        virtual char pull_char() override;
};

}// namespace sdg