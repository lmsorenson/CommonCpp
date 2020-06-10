// Copyright 2020 Lucas Sorenson, All rights reserved.
#pragma once
#include "../private/shape/shape.hpp"

namespace sdg {
namespace parse {

class IndependentEntity : public Shape
{
public:
    IndependentEntity() = default;
    ~IndependentEntity() = default;

    virtual std::string get_id() const override;
    void new_node() override;
};

}// namespace parse
}// namespace sdg