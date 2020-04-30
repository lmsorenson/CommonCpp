// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SemanticAnalyzer.hpp"
#include <iostream>

using ::sdg::SemanticAnalyzer;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::make_shared;
using ::std::string;
using ::sdg::SyntaxNode;
using ::sdg::DataSetTarget;
using ::sdg::hash::KeyInstance;




void SemanticAnalyzer::receive_event()
{
    this->analyze();
}



void check_nodes(SyntaxNode node, std::shared_ptr<DataSetTarget> target)
{
    if (node.has_children())
    {
        for(int i=0; i<node.get_number_of_children();++i)
        {
            check_nodes(*node.get_child(i), target);
        }
    }
    else
    {
        target->add( node.get_item_key(), node.get_item_value(), node.get_path() );
    }
}



//This function is called every time there is a change made to the source.
void SemanticAnalyzer::analyze()
{
    SyntaxNode syntax_tree_ = source_->get_syntax_tree();

    if ( this->ready() && syntax_tree_.has_children() )
    {   
        check_nodes(syntax_tree_, target_);
    }
}