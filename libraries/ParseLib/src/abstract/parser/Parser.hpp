// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "private/TokenSource.hpp"
#include "../../utils/patterns/observer/Observer.hpp"
#include "../Reads/Stream.hpp"


namespace sdg {


//takes in a stream of characters
//creates a stream of tokens
class Parser : public pattern::Observer
{
    std::shared_ptr<TokenSource> source_;


    void parse();
    bool ready()
    {
        return true;
    }

public:
    Parser() = default;

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