// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "private/SyntaxTreeSource.hpp"
#include "private/DataSetTarget.hpp"
#include "../../utils/patterns/observer/Observer.hpp"
#include "../Reads/Stream.hpp"

#include "../data/structures/node.hpp"


namespace sdg {


//takes in a stream of characters
//creates a stream of tokens
class SemanticAnalyzer : public pattern::Observer
{
    std::shared_ptr<SyntaxTreeSource> source_;
    std::shared_ptr<DataSetTarget> target_;

    void analyze();
    bool ready()
    {
        return (source_ && target_);
    }

public:
    SemanticAnalyzer() = default;
    ~SemanticAnalyzer() = default;

    virtual void receive_event() override;

    template<class T>
    void set_source(std::shared_ptr<SyntaxNode> syntax_tree)
    {
        this->set_subject( syntax_tree.get() );
        source_ = std::shared_ptr<T>( new T( syntax_tree ) );

        this->analyze();
    }

    template<class T>
    void set_target(std::shared_ptr<DataSet> data_set)
    {
        target_ = std::shared_ptr<T>( new T( data_set ) );

        this->analyze();
    }
};


}// namespace sdg