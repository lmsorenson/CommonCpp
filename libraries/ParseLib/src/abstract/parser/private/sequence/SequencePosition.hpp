// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SequenceElement.hpp"


namespace sdg {
namespace parse {

class Sequence;

class SequencePosition
{
    Sequence *sequence_;
    std::shared_ptr<SequenceElement> element_;
    bool is_completed;

public:
    explicit SequencePosition(Sequence *context, std::shared_ptr<SequenceElement> a_element);
    ~SequencePosition() = default;
    
    std::shared_ptr<SequenceElement> next_item() const;
    std::shared_ptr<SequenceElement> item() const;
    std::shared_ptr<Sequence> get_sequence();
    std::shared_ptr<TokenType> get_token();
    void notify_completion();
    void go_to_next_element();
    bool complete();
};

}// namespace parser
}// namespace sdg