// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <memory>
#include "../../intermediate/node.hpp"

namespace sdg {

class SyntaxTreeSource
{
    std::shared_ptr<sdg::SyntaxNode> syntax_tree_;

public:
    SyntaxTreeSource(std::shared_ptr<sdg::SyntaxNode> syntax_tree_)
    : syntax_tree_(syntax_tree_) {}

    SyntaxNode get_syntax_tree();

};

}// namespace sdg