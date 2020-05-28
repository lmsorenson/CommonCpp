// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>



namespace sdg {
namespace parse {

class SequencePosition;

class SequenceElement
{
    std::vector<SequencePosition*> position_;
    
public:
    enum Cardinality : int32_t
    {
        One,
        Many
    };

private:
    Cardinality cardinality_;

public:
    explicit SequenceElement(Cardinality cardinality = Cardinality::One) : cardinality_(cardinality){}
    ~SequenceElement() = default;

    void assign_position(SequencePosition *position);
    virtual void print() const;
};


}// namespace parser
}// namespace sdg