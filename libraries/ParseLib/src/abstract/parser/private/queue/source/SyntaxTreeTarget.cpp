// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SyntaxTreeTarget.hpp"
#include <iostream>
#include <vector>

using ::std::string;
using ::std::vector;
using ::sdg::SyntaxTreeTarget;
using ::sdg::SyntaxNode;
using ::std::cout;
using ::std::endl;



void SyntaxTreeTarget::add_to_root(string id, string value)
{
    SyntaxNode n = SyntaxNode(value, syntax_tree_);
    n.append_key(id);

    syntax_tree_->AddChild(n);
}

int32_t SyntaxTreeTarget::add_to_node(vector<int> path, string id, string value)
{
    auto node_buffer = syntax_tree_;

    for(int i=0; i<path.size(); ++i)
    {
        node_buffer = node_buffer->get_child(path[i]);
    }

    if(node_buffer)
    {
        SyntaxNode n = SyntaxNode( value, node_buffer );
        n.append_key(id);
        node_buffer->AddChild(n);
        
        return 0;
    }
    
    return 1;
}

bool SyntaxTreeTarget::is_empty()
{
    return !syntax_tree_->has_children();
}