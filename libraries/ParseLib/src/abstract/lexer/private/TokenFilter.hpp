// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <memory>





namespace sdg {

class Lexer;

/* Each element/entity output by the filter is identified using the format:
    label + index
     */
class TokenFilter
{
protected:
    const std::string filter_id_;
    Lexer * owner_;

public:
    TokenFilter(Lexer * owner, std::string new_filter_id);
    ~TokenFilter()=default;

    virtual bool execute(char ch) = 0;

    virtual bool is_a_delimeter(char ch)=0;

    enum : int32_t
    {
        FILTER_SUCCESS=0,
        FILTER_FORMAT_ERROR,
        FILTER_UNKNOWN_ERROR
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