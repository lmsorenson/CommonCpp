// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "public/SemanticNet.hpp"
#include "private/queue/SyntaxTreeSource.hpp"
#include "private/queue/DataSetTarget.hpp"
#include "private/queue/ErrorQueue.hpp"
#include "../intermediate/Error.hpp"
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
    std::shared_ptr<SemanticNet> net_;
    std::shared_ptr<analyzer::ErrorQueue> error_queue_;

    utils::Stopwatch stopwatch_;

    void analyze();
    bool ready()
    {
        return ( source_ && target_ );
    }

    void check_nodes(const std::shared_ptr<const SyntaxNode> node, std::shared_ptr<DataSetTarget> target);

public:
    SemanticAnalyzer() = default;
    virtual ~SemanticAnalyzer() = default;

    virtual void receive_event() override;

    double get_time() const;
    double get_target_time() const;

    void handle_error(Error error);

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

    template<class T>
    void set_semantic_net()
    {
        net_ = std::shared_ptr<T>( new T() );
    }

    template<class T>
    void set_error_queue(pipeline::Stream<Error> *error_queue_ptr)
    {
        error_queue_=std::shared_ptr<T>( new T( error_queue_ptr ) );
    }
};


}// namespace sdg