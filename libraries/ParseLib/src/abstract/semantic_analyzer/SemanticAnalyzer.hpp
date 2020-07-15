// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "private/queue/SyntaxTreeSource.hpp"
#include "private/queue/DataSetTarget.hpp"
#include "../intermediate/observer/Observer.hpp"
#include "../intermediate/node.hpp"
#include "../../utils/stopwatch.hpp"


namespace sdg {


//takes in a stream of characters
//creates a stream of tokens
class SemanticAnalyzer : public pattern::Observer
{
    std::shared_ptr<SyntaxTreeSource> source_;
    std::shared_ptr<DataSetTarget> target_;

    utils::Stopwatch stopwatch_;

    void analyze();
    bool ready()
    {
        return ( source_ && target_ );
    }

    void check_nodes(std::shared_ptr<SyntaxNode> node, std::shared_ptr<DataSetTarget> target);

public:
    SemanticAnalyzer() = default;
    virtual ~SemanticAnalyzer() = default;

    virtual void receive_event() override;

    double get_time() const;
    double get_target_time() const;

    template<class T>
    void set_source( std::shared_ptr<SyntaxNode> syntax_tree )
    {
        this->set_subject( syntax_tree.get() );
        source_ = std::shared_ptr<T>( new T( syntax_tree ) );
    }

    template<class T>
    void set_target(DataSet *data_set)
    {
        target_ = std::shared_ptr<T>( new T( data_set ) );
    }
};


}// namespace sdg