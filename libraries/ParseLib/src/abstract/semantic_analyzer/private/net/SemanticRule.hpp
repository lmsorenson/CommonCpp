// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once

namespace sdg {

template<class T>
class SemanticRule
{
public:
    enum class Type: int16_t
    {
        Equal
    };

    SemanticRule(Type type)
    : type_( type )
    {}
    ~SemanticRule() = default;

    bool succeeded(const std::shared_ptr<const T> A, const std::shared_ptr<const T> B) const
    {

    }
private:

    Type type_;
};

}// namespace sdg