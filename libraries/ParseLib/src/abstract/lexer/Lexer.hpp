// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <iostream>
#include "private/shape/Shape.hpp"
#include "private/queue/CharacterSource.hpp"
#include "private/queue/TokenTarget.hpp"
#include "private/queue/ErrorQueue.hpp"
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
protected:
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
    virtual ~Lexer()=default;

    virtual void receive_event() override;

    double get_time() const;

    void produce_token();
    void produce_token(std::string);
    int32_t produce_tagged_token(std::pair<std::string, std::string>);

    void handle_error(Error error);
    bool is_buffer_empty();

    template<class T>
    void set_shape(char ch = '\0');

    template<class T>
    void add_shape(std::string entity_id, Shape::Cardinality cardinality = Shape::Cardinality::Many);

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
    std::string key = std::string(typeid(T).name());
    shape_ = shapes_.at(key);
}

template<class T>
void Lexer::add_shape(std::string entity_id, Shape::Cardinality cardinality)
{
    std::string key = std::string(typeid(T).name());
    shapes_[key] = std::shared_ptr<T>(new T(this, entity_id, cardinality));

    if(!shape_)
        shape_ = shapes_.at(key);
}

template<class T>
void Lexer::set_source(sdg::pipeline::Stream<char> *queue_ptr)
{
    this->set_subject(queue_ptr);
    source_=std::shared_ptr<T>( new T( queue_ptr ) );
}

template<class T>
void Lexer::set_target(pipeline::Stream<std::string> *queue_ptr)
{
    target_=std::shared_ptr<T>( new T( queue_ptr ) );
}

template<class T>
void Lexer::set_error_queue(pipeline::Stream<Error> *error_queue_ptr)
{
    error_queue_=std::shared_ptr<T>( new T( error_queue_ptr ) );
}


}// namespace sdg