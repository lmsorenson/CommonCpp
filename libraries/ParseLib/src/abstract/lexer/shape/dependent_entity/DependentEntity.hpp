// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <map>
#include <memory>
#include "../LexerState.hpp"
#include "../Shape.hpp"

namespace sdg {
    
class DependentEntity : public Shape
{
public: 
    DependentEntity(Lexer *context);
    ~DependentEntity() = default;
};

}// namespace sdg