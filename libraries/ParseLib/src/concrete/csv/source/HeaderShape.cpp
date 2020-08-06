// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../HeaderShape.hpp"
#include "../RecordShape.hpp"
#include "../../../abstract/lexer/Lexer.hpp"

using ::sdg::HeaderShape;

int32_t HeaderShape::transition() const
{
    context_->set_shape<RecordShape>();
    return 0;
}