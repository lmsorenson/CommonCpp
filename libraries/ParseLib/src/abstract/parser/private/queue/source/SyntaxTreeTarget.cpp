// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SyntaxTreeTarget.hpp"
#include <iostream>
#include <vector>

using ::std::string;
using ::std::vector;
using ::sdg::SyntaxTreeTarget;
using ::sdg::SyntaxNode;
using ::std::shared_ptr;
using ::std::cout;
using ::std::endl;



std::shared_ptr<SyntaxNode> SyntaxTreeTarget::add_to_root(string id, string value)
{
    SyntaxNode n = SyntaxNode(value, syntax_tree_);
    n.append_key(id);

    return syntax_tree_->AddChild(n);
}

std::shared_ptr<SyntaxNode> SyntaxTreeTarget::add_to_node(shared_ptr<SyntaxNode> node, string id, string value)
{
    if(node)
    {
        SyntaxNode n = SyntaxNode( value, node );
        n.append_key(id);
        
        return node->AddChild(n);
    }
    
    return nullptr;
}

bool SyntaxTreeTarget::is_empty()
{
    return !syntax_tree_->has_children();
}