// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <iostream>
#include "shape/Shape.hpp"
#include "queue/CharacterSource.hpp"
#include "queue/TokenTarget.hpp"
#include "queue/ErrorQueue.hpp"
#include "../intermediate/Error.hpp"
#include "../intermediate/observer/Observer.hpp"
#include "../intermediate/Stream.hpp"
#include "../../utils/stopwatch.hpp"

namespace sdg {

class CharacterSource;
class TokenTarget;

//takes in a stream of characters
//creates a stream of tokens
class Lexer : public pattern::Observer
{
    std::shared_ptr<CharacterSource> source_;
    std::shared_ptr<TokenTarget> target_;
    std::shared_ptr<ErrorQueue> error_queue_;

    std::string buffer_;

    std::shared_ptr<Shape> shape_;
    std::map<std::string, std::shared_ptr<Shape>> shapes_;

    utils::Stopwatch stopwatch_;

    void scan();
    bool ready()
    {
        return (shape_ && source_ && target_ && error_queue_);
    }

public:
    Lexer()=default;
    ~Lexer()=default;

    virtual void receive_event() override;

    double get_time() const;

    void produce_token();
    void produce_token(std::string);
    void produce_tagged_token(std::pair<std::string, std::string>);

    void handle_error(Error error);
    bool is_buffer_empty();

    template<class T>
    void set_shape(char ch = '\0');

    template<class T>
    void add_shape();

    template<class T>
    void set_source(sdg::pipeline::Stream<char> *queue_ptr);

    template<class T>
    void set_target(pipeline::Stream<std::string> *queue_ptr);

    template<class T>
    void set_error_queue(pipeline::Stream<Error> *error_queue_ptr);
};


template<class T>
void Lexer::set_shape(char ch)
{
    std::string key = typeid(T).name();
    shape_ = shapes_.at(key);
}

template<class T>
void Lexer::add_shape()
{
    std::string key = typeid(T).name();
    shapes_[key] = std::shared_ptr<T>(new T(this));

    if(!shape_)
        shape_ = shapes_.at(key);
}

template<class T>
void Lexer::set_source(sdg::pipeline::Stream<char> *queue_ptr)
{
    this->set_subject(queue_ptr);
    source_=std::shared_ptr<T>( new T( queue_ptr ) );

    this->scan();
}

template<class T>
void Lexer::set_target(pipeline::Stream<std::string> *queue_ptr)
{
    target_=std::shared_ptr<T>( new T( queue_ptr ) );

    this->scan();
}

template<class T>
void Lexer::set_error_queue(pipeline::Stream<Error> *error_queue_ptr)
{
    error_queue_=std::shared_ptr<T>( new T( error_queue_ptr ) );

    this->scan();
}


}// namespace sdg