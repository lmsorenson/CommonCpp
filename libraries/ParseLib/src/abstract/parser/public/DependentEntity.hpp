// Copyright 2020 Lucas Sorenson, All rights reserved.
#pragma once
#include <memory>
#include "../private/shape/shape.hpp"
#include "TokenType.hpp"

namespace sdg {
namespace parse {

class DependentEntity : public Shape
{
protected:
    std::shared_ptr<TokenType> owner_;
    int32_t scope_; 
    
public:
    DependentEntity() : owner_(nullptr), scope_(0) {}
    virtual ~DependentEntity() = default;

    void dependent_on(std::shared_ptr<TokenType> token);

    virtual std::string get_id() const override;
    void new_node() override;
    std::string dependent_on_typeid() const;
};

}// namespace parse
}// namespace sdg