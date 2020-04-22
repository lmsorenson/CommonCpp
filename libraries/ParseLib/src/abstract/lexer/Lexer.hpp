// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "public/TokenFilter.hpp"
#include "public/TokenTarget.hpp"




namespace sdg {

class TokenFilter;
class ChildTokenFilter;
class TokenTarget;

//takes in a stream of characters
//creates a stream of tokens
class Lexer
{
    std::vector<std::shared_ptr<TokenFilter>> filters_;
    std::shared_ptr<TokenTarget> target_;

    std::string buffer_;
    std::string previous_token_;

    bool bAllowDuplicates_;

public:
    Lexer(): bAllowDuplicates_(false){}

    void add_char(char ch);

    void produce_token();
    void produce_token(std::string);
    void produce_tagged_token(std::pair<std::string, std::string>);


    template<class T>
    int32_t add_filter(std::string a_filter_id)
    {
        filters_.push_back( std::shared_ptr<T>( new T(this, a_filter_id) ) );
        
        //return the index of the last pushed element.
        return (filters_.size()-1);
    }

    template<class T>
    int32_t add_filter(std::string a_filter_id, int32_t parent_index)
    {
        filters_.push_back( std::shared_ptr<T>( new T(this, a_filter_id, filters_[parent_index].get()) ) );

        //return the index of the last pushed element.
        return (filters_.size()-1);
    }

    template<class T>
    void set_target(std::queue<std::string> *queue_ptr)
    {
        target_=std::shared_ptr<T>( new T( queue_ptr ) );
    }
};


}// namespace sdg