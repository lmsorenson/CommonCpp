// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "private/TokenSource.hpp"
#include "private/SyntaxTreeTarget.hpp"
#include "private/TokenType.hpp"
#include "private/ErrorQueue.hpp"
#include "../intermediate/Error.hpp"
#include "../intermediate/observer/Observer.hpp"
#include "../intermediate/node.hpp"
#include "../../utils/stopwatch.hpp"


namespace sdg {


//takes in a stream of characters
//creates a stream of tokens
class Parser : public pattern::Observer
{
    std::shared_ptr<TokenSource> source_;
    std::shared_ptr<SyntaxTreeTarget> target_;
    std::shared_ptr<parser::ErrorQueue> error_queue_;

    std::vector<std::shared_ptr<TokenType>> token_types_;

    utils::Stopwatch stopwatch_;

    void parse();
    bool ready()
    {
        return (source_ && target_ && error_queue_);
    }

public:
    Parser() = default;
    ~Parser() = default;

    virtual void receive_event() override;

    double get_time() const;

    void produce_node(std::string, std::string);
    int32_t produce_child_node(std::vector<int>, std::string, std::string);
    
    void handle_error(Error error);

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


    template<class T>
    void set_error_queue(pipeline::Stream<Error> *error_queue_ptr);
};

template<class T>
void Parser::set_error_queue(pipeline::Stream<Error> *error_queue_ptr)
{
    error_queue_=std::shared_ptr<T>( new T( error_queue_ptr ) );

    this->parse();
}


}// namespace sdg