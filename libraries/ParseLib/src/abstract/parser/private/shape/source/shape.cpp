// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../shape.hpp"

using ::sdg::parse::Shape;

int32_t Shape::number() const
{
    return shape_occurances_;
}

void Shape::count_up()
{
    shape_occurances_++;
}

void Shape::reset()
{
    shape_occurances_ = 0;
}