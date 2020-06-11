// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <memory>
#include "../../../intermediate/node.hpp"

namespace sdg {

class SyntaxTreeTarget
{
    std::shared_ptr<sdg::SyntaxNode> syntax_tree_;

public:
    SyntaxTreeTarget(std::shared_ptr<sdg::SyntaxNode> syntax_tree_)
    : syntax_tree_(syntax_tree_) {}

    std::shared_ptr<SyntaxNode> add_to_root(std::string id, std::string value);
    std::shared_ptr<SyntaxNode> add_to_node(std::shared_ptr<SyntaxNode> node, std::string id, std::string value);

    bool is_empty();
};

}// namespace sdg