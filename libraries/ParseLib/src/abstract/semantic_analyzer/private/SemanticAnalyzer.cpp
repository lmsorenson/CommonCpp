// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SemanticAnalyzer.hpp"
#include <iostream>
#include <time.h>

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


double SemanticAnalyzer::get_time() const
{
    return stopwatch_.read_seconds();
}

double SemanticAnalyzer::get_target_time() const
{
    return target_->get_time();
}


void SemanticAnalyzer::check_nodes(shared_ptr<SyntaxNode> node, std::shared_ptr<DataSetTarget> target)
{
    net_->add_item("token", Properties());

    if (node->has_children())
    {
        for(int i=0; i < node->get_number_of_children(); ++i)
        {
            check_nodes(node->get_child(i), target);
        }
    }
    else
    {
        stopwatch_.stop();

        target->add( node->get_item_key(), node->get_item_value(), node->get_path() );

        stopwatch_.start();
    }
}



//This function is called every time there is a change made to the source.
void SemanticAnalyzer::analyze()
{
    stopwatch_.start();

    shared_ptr<SyntaxNode> syntax_tree_ = source_->get_syntax_tree();

    if ( this->ready() && syntax_tree_->has_children() )
    {   
        check_nodes(syntax_tree_, target_);
    }

    stopwatch_.stop();
}