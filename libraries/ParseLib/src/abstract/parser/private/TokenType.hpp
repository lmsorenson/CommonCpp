// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>



namespace sdg {

class Parser;

class TokenType
{
    int32_t count_;

protected:
    const std::string type_id_;
    Parser *owner_;
    TokenType *parent_;

    virtual void update_count();

public:
    TokenType(Parser *parser, std::string new_type_id, TokenType *parent = nullptr) 
    : owner_(parser)
    , type_id_(new_type_id)
    , parent_(parent)
    , count_(0)
    {}
    ~TokenType()=default;

    virtual bool classify(std::string token) = 0;
    void handle_type(std::string token);
    
    void reset_count();
    int32_t get_count() const;
};

class CollectionToken : public TokenType
{
    std::vector<sdg::TokenType*> children_;

public:
    CollectionToken(Parser *parser, std::string new_type_id) 
    : TokenType(parser, new_type_id){}
    ~CollectionToken()=default;

    virtual bool classify(std::string token) override = 0;

    void update_count() override;
    void reset_child_counters();

    void add_child(TokenType *child);
};

}// namespace sdg