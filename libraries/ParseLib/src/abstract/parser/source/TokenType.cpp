// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/TokenType.hpp"
#include <iostream>

using sdg::TokenType;
using sdg::CollectionToken;
using std::cout;
using std::endl;

void TokenType::handle_type(std::string token)
{
    bool matches_type = this->classify(token);

    if(matches_type)
        this->update_count();

}

void TokenType::update_count()
{
    count_++;
}

int32_t TokenType::get_count() const
{
    return count_;
}

void TokenType::reset_count()
{
    count_=0;
}

void CollectionToken::update_count()
{
    TokenType::update_count();
    this->reset_child_counters();
}

void CollectionToken::reset_child_counters()
{
    for( auto child : children_ )
        child->reset_count();
}

void CollectionToken::add_child(TokenType *child)
{
    children_.push_back(child);
}