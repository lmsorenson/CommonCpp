// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "private/TokenSource.hpp"
#include "../../utils/patterns/observer/Observer.hpp"
#include "../Reads/Stream.hpp"
#include "../data/structures/node.hpp"


namespace sdg {


//takes in a stream of characters
//creates a stream of tokens
class Parser : public pattern::Observer
{
    std::shared_ptr<TokenSource> source_;

    int32_t record_index_, field_index_;
    std::shared_ptr<sdg::SyntaxNode> syntax_tree_;

    void parse();
    bool ready()
    {
        return true;
    }

public:
    Parser();
    ~Parser() = default;

    virtual void receive_event() override;


    template<class T>
    void set_source(sdg::pipeline::Stream<std::string> *queue_ptr)
    {
        this->set_subject(queue_ptr);
        source_=std::shared_ptr<T>( new T( queue_ptr ) );

        this->parse();
    }

    // template<class T>
    // void set_target(pipeline::Stream<std::string> *queue_ptr)
    // {
    //     target_=std::shared_ptr<T>( new T( queue_ptr ) );

    //     this->scan();
    // }
};


}// namespace sdg