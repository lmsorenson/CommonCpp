// Copyright 2020 Lucas Sorenson, All rights reserved.
#pragma once
#include <string>

namespace sdg {
namespace parse {

class Shape
{
protected:
    int32_t shape_occurances_;

public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual std::string get_id() const = 0;
    virtual void new_node() = 0;
    int32_t number() const;
    void count_up();
    void reset();

};

}// namespace parse
}// namespace sdg