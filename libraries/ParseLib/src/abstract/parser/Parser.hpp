// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "private/TokenSource.hpp"
#include "private/SyntaxTreeTarget.hpp"
#include "../intermediate/observer/Observer.hpp"

#include "../intermediate/node.hpp"
#include "private/TokenType.hpp"

namespace sdg {


//takes in a stream of characters
//creates a stream of tokens
class Parser : public pattern::Observer
{
    std::shared_ptr<TokenSource> source_;
    std::shared_ptr<SyntaxTreeTarget> target_;

    int32_t record_index_, field_index_;
    std::vector<std::shared_ptr<TokenType>> token_types_;

    void parse();
    bool ready()
    {
        return (source_ && target_);
    }

public:
    Parser();
    ~Parser() = default;

    virtual void receive_event() override;

    void produce_node(std::string, std::string);
    void produce_child_node(std::vector<int>, std::string, std::string);

    template<class T>
    void set_source(sdg::pipeline::Stream<std::string> *queue_ptr)
    {
        this->set_subject( queue_ptr );
        source_ = std::shared_ptr<T>( new T( queue_ptr ) );

        this->parse();
    }

    template<class T>
    int32_t add_token_type(std::string a_type_id)
    {
        token_types_.push_back( std::shared_ptr<T>( new T(this, a_type_id) ) );
        
        //return the index of the last pushed element.
        return (token_types_.size()-1);
    }

    template<class T>
    int32_t add_token_type(std::string a_type_id, int32_t parent_index)
    {
        std::shared_ptr<CollectionToken> parent_ptr;
        
        if ( (parent_ptr = std::dynamic_pointer_cast<CollectionToken>(token_types_[parent_index])) )
        {
            auto child_ptr = std::shared_ptr<T>( new T(this, a_type_id, parent_ptr.get()) );

            token_types_.push_back( child_ptr );
            parent_ptr->add_child( child_ptr.get() );


            //return the index of the last pushed element.
            return (token_types_.size()-1);
        }
        else
        {
            //failed to add token type with parent.
            return -1;
        }
    }

    template<class T>
    void set_target(std::shared_ptr<SyntaxNode> syntax_tree)
    {
        target_ = std::shared_ptr<T>( new T( syntax_tree ) );

        //starts a parse process in case content exists before the target is assigned.
        this->parse();
    }
};


}// namespace sdg