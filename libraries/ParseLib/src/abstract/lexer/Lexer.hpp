// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "private/CharacterSource.hpp"
#include "private/TokenFilter.hpp"
#include "private/TokenTarget.hpp"
#include "private/LexerError.hpp"
#include "../intermediate/observer/Observer.hpp"
#include "../intermediate/Stream.hpp"
#include "../../utils/stopwatch.hpp"

namespace sdg {

class CharacterSource;
class TokenFilter;
class ChildTokenFilter;
class TokenTarget;

//takes in a stream of characters
//creates a stream of tokens
class Lexer : public pattern::Observer
{
    std::shared_ptr<CharacterSource> source_;
    std::vector<std::shared_ptr<TokenFilter>> filters_;
    std::shared_ptr<TokenTarget> target_;

    std::string buffer_;
    char previous_delimiter_;
    std::string previous_token_;

    bool bAllowDuplicates_;
    utils::Stopwatch stopwatch_;

    void scan();
    bool ready()
    {
        return (source_ && !filters_.empty() && target_);
    }

public:
    Lexer() : bAllowDuplicates_(false){}

    virtual void receive_event() override;

    double get_time() const;

    void produce_token();
    void produce_token(std::string);
    void produce_tagged_token(std::pair<std::string, std::string>);

    void handle_error(LexerError error);
    bool is_buffer_empty();
    char last_delimiter();

    template<class T>
    void set_source(sdg::pipeline::Stream<char> *queue_ptr);

    template<class T>
    int32_t add_filter(std::string a_filter_id);

    template<class T>
    int32_t add_filter(std::string a_filter_id, int32_t parent_index);

    template<class T>
    void set_target(pipeline::Stream<std::string> *queue_ptr);
};




template<class T>
void Lexer::set_source(sdg::pipeline::Stream<char> *queue_ptr)
{
    this->set_subject(queue_ptr);
    source_=std::shared_ptr<T>( new T( queue_ptr ) );

    this->scan();
}

template<class T>
int32_t Lexer::add_filter(std::string a_filter_id)
{
    filters_.push_back( std::shared_ptr<T>( new T(this, a_filter_id) ) );
    
    //return the index of the last pushed element.
    return (filters_.size()-1);
}

template<class T>
int32_t Lexer::add_filter(std::string a_filter_id, int32_t parent_index)
{
    filters_.push_back( std::shared_ptr<T>( new T(this, a_filter_id, filters_[parent_index].get()) ) );

    //return the index of the last pushed element.
    return (filters_.size()-1);
}

template<class T>
void Lexer::set_target(pipeline::Stream<std::string> *queue_ptr)
{
    target_=std::shared_ptr<T>( new T( queue_ptr ) );

    this->scan();
}


}// namespace sdg