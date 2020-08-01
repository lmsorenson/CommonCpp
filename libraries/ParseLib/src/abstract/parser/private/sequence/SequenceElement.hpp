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
public:
    enum Cardinality : int32_t
    {
        One,
        Many
    };

    explicit SequenceElement(Cardinality cardinality = Cardinality::One);
    virtual ~SequenceElement() = default;

    virtual void print() const;

    void assign_position(SequencePosition *position);

    //evaluate a passed in token.  when the token matches the current type return a status
    virtual std::shared_ptr<TokenType> evaluate(const std::string &token, MatchStatus &status) = 0;

    bool HasMultiplicity() const;

protected:
    SequencePosition *element_position_;

private:
    
    Cardinality cardinality_;
};


}// namespace parser
}// namespace sdg