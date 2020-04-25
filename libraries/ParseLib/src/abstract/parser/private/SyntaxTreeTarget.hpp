// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <memory>
#include "../../data/structures/node.hpp"

namespace sdg {

class SyntaxTreeTarget
{
    std::shared_ptr<sdg::SyntaxNode> syntax_tree_;

public:
    SyntaxTreeTarget(std::shared_ptr<sdg::SyntaxNode> syntax_tree_)
    : syntax_tree_(syntax_tree_) {}

    void add_to_root(std::string id, std::string value);
    void add_to_node(std::vector<int> path, std::string id, std::string value);
};

}// namespace sdg