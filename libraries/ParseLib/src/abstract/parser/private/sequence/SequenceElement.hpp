// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>



namespace sdg {
namespace parse {

class SequencePosition;
class TokenType;

enum MatchStatus : int32_t
    {
        PositiveMatch,
        NegativeMatch,
        NextElementViable,
        Unknown
    };
class SequenceElement
{
protected:
    SequencePosition *element_position_;
    
public:
    enum Cardinality : int32_t
    {
        One,
        Many
    };

private:
    Cardinality cardinality_;

public:
    explicit SequenceElement(Cardinality cardinality = Cardinality::One);
    ~SequenceElement() = default;

    void assign_position(SequencePosition *position);
    virtual void print() const;
    virtual std::shared_ptr<TokenType> evaluate(std::string token, std::function<void()> next_element, MatchStatus &status) = 0;

    bool HasMultiplicity() const;
};


}// namespace parser
}// namespace sdg