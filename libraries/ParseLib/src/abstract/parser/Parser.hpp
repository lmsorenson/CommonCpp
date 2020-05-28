// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "private/queue/ErrorQueue.hpp"
#include "private/queue/SyntaxTreeTarget.hpp"
#include "private/queue/TokenSource.hpp"
#include "private/queue/ErrorQueue.hpp"
#include "private/sequence/Sequence.hpp"
#include "public/TokenType.hpp"
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

    std::shared_ptr<parse::Sequence> expected_token_sequence_;


    utils::Stopwatch stopwatch_;

    void parse();
    bool ready()
    {
        return (source_ && target_ && error_queue_);
    }

public:
    Parser() = default;
    ~Parser() = default;

    std::string scope_ = "";
    int record_count_ = 0;
    int field_count_=0;

    virtual void receive_event() override;

    double get_time() const;

    void produce_node(std::string, std::string);
    int32_t produce_child_node(std::vector<int>, std::string, std::string);
    
    void handle_error(Error error);

    template<class T> void set_source(sdg::pipeline::Stream<std::string> *queue_ptr);
    template<class T> void add_expected_token();
    template<class ... Types> void add_subsequence(int32_t &err);
    template<class T> void set_target(std::shared_ptr<SyntaxNode> syntax_tree);
    template<class T> void set_error_queue(pipeline::Stream<Error> *error_queue_ptr);
};

template<class T>
void Parser::set_source(sdg::pipeline::Stream<std::string> *queue_ptr)
{
    this->set_subject( queue_ptr );
    source_ = std::shared_ptr<T>( new T( queue_ptr ) );

    this->parse();
}

//adds a token to the sequence of expected tokens.
template<class T>
void Parser::add_expected_token()
{
    if(!expected_token_sequence_)
        expected_token_sequence_ = std::make_shared<parse::Sequence>(this);

    expected_token_sequence_->add_type( std::make_shared<T>() );
}

//adds a token to the sequence of expected tokens.
template<class ... Types>
void Parser::add_subsequence(int32_t &err)
{
    if(!expected_token_sequence_)
        expected_token_sequence_ = std::make_shared<parse::Sequence>(this);
    
    if(expected_token_sequence_->add_subsequence( std::make_shared<Types>()... ) == 0)
        err = 0;//return 0 code (success) if subsequence was added successfully.

    else
        err = 1;//return 1 code (failure) if subsequence was not added successfully
}

template<class T>
void Parser::set_target(std::shared_ptr<SyntaxNode> syntax_tree)
{
    target_ = std::shared_ptr<T>( new T( syntax_tree ) );

    //starts a parse process in case content exists before the target is assigned.
    this->parse();
}

template<class T>
void Parser::set_error_queue(pipeline::Stream<Error> *error_queue_ptr)
{
    error_queue_=std::shared_ptr<T>( new T( error_queue_ptr ) );

    this->parse();
}


}// namespace sdg