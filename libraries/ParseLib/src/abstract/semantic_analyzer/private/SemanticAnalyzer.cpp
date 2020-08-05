// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SemanticAnalyzer.hpp"
#include <iostream>
#include <time.h>
#include <vector>

using ::sdg::SemanticAnalyzer;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::make_shared;
using ::std::string;
using ::std::vector;
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


void SemanticAnalyzer::check_nodes(const shared_ptr<const SyntaxNode> node, std::shared_ptr<DataSetTarget> target)
{
    if (node->has_children())
    {
        for(int i=0; i < node->get_number_of_children(); ++i)
        {
            vector<string> err;
            const auto child = node->get_child(i);
            auto props = NodeProperties( child->get_item_value(), node->get_item_value(), child->get_number_of_children());

            auto item = net_->add_item(props, err);

            if (item && item->has_payload())
            {
                item->print_line();
                auto payload = item->get_payload();

                target->add( child->get_item_key(), payload.value(), child->get_path() );
            }
            else
            {
                cout << "Token cannot produce valid item. " << endl;

                if(err.size() > 0)
                {
                    this->handle_error(Error(FILE_FORMAT_INVALID));
                }
            }

            check_nodes(child, target);
        }
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

void SemanticAnalyzer::handle_error(Error error)
{
    error_queue_->add_error(error);
}