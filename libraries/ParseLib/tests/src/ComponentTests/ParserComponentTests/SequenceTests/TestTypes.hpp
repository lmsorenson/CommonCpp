#pragma once
#include "../../../../../src/abstract/parser/public/IndependentEntity.hpp"



class TestTokenA : public sdg::parse::TokenType, public sdg::parse::IndependentEntity
{
public:
    TestTokenA() 
    : TokenType("A", Cardinality::One)
    , sdg::parse::IndependentEntity()
    {}
    virtual ~TestTokenA() = default;
    
    virtual bool classify(std::string a_token) const override
    {
        if (a_token.compare("A") == 0)
            return true;
        else
            return false;
    }

    virtual std::pair<std::string, std::string> create_node(std::string a_token) override
    {
        return std::pair<std::string, std::string>("A", "A");
    }

    virtual std::string get_id() const override
    {
        return string("A" + std::to_string(shape_occurances_-1));
    }
};

class TestTokenB : public sdg::parse::TokenType, public sdg::parse::IndependentEntity
{
public:
    TestTokenB() 
    : TokenType("B", Cardinality::One)
    , sdg::parse::IndependentEntity()
    {}
    virtual ~TestTokenB() = default;
    
    virtual bool classify(std::string a_token) const override
    {
        if (a_token.compare("B") == 0)
            return true;
        else
            return false;
    }

    virtual std::pair<std::string, std::string> create_node(std::string a_token) override
    {
        return std::pair<std::string, std::string>("A", "A");
    }

    virtual std::string get_id() const override
    {
        return string("B" + std::to_string(shape_occurances_-1));
    }
};