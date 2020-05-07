// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <memory>
#include "../../intermediate/Error.hpp"




namespace sdg {

class Lexer;

/* Each element/entity output by the filter is identified using the format:
    label + index
     */
class TokenFilter
{
    Lexer * owner_;
    const std::string filter_id_;

protected:

    bool is_cache_empty();
    char last_delimiter();
    void notify_error(Error error);
    
    void stream_token();
    void stream_tagged_token();
    

public:
    TokenFilter(Lexer * owner, std::string new_filter_id);
    ~TokenFilter()=default;

    virtual bool execute(char ch) = 0;
    virtual bool is_a_delimiter(char ch)=0;

    enum : int32_t
    {
        SUCCESS=0,
        FORMAT_ERROR,
        UNKNOWN_ERROR
    };
};



class ChildTokenFilter : public TokenFilter
{
protected:
    TokenFilter * parent_;

public:
    ChildTokenFilter(Lexer * owner, std::string new_filter_id, TokenFilter * parent_filter);
    ~ChildTokenFilter()=default;

};

}// namespace sdg