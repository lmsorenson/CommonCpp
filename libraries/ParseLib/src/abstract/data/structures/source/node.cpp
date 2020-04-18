// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../node.hpp"
#include <iostream>

using std::string;
using std::shared_ptr;
using std::make_shared;
using sdg::SyntaxNode;

SyntaxNode::SyntaxNode(string a_value, std::shared_ptr<SyntaxNode> a_parent)
: value_(a_value)
, parent_(a_parent)
{
}

SyntaxNode::SyntaxNode(const SyntaxNode &a_syntax_node)
{
    id_ = a_syntax_node.id_;
    value_ = a_syntax_node.value_;
    children_ = a_syntax_node.children_;
    parent_ = a_syntax_node.parent_;
}

SyntaxNode::~SyntaxNode(){}

string SyntaxNode::get_item_value(){return value_;}
void SyntaxNode::set_value(const char * text){value_ = text;}
string SyntaxNode::get_item_key(){return id_;}

SyntaxNode SyntaxNode::append_key(string a_new_id){id_.append(a_new_id); return *this;}
bool SyntaxNode::is_empty_key(){return (id_.empty());};

string SyntaxNode::get_path()
{
    string path;

    shared_ptr<SyntaxNode> current_node;
    
    if (!current_node && this->has_parent())
    {
        current_node = this->parent_;
    }

    if (current_node)
    {
        while(current_node->has_parent())
        {
            path.insert(0, current_node->get_item_key());
            current_node = current_node->parent_;
        }
    }

    return path;
}

void SyntaxNode::AddChild(SyntaxNode n)
{
    children_.push_back(make_shared<SyntaxNode>(n));
}

shared_ptr<SyntaxNode> SyntaxNode::get_child(int32_t index){return this->children_[index];}
int32_t SyntaxNode::get_number_of_children(){return children_.size();}
bool SyntaxNode::has_children(){return (children_.size()>0);}
bool SyntaxNode::has_parent(){return ((bool)parent_);}

void SyntaxNode::Print()
{
    for (int i=0; i < children_.size(); ++i)
    {
        children_[i]->Print();
    }
}