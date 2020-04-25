// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "private/TokenSource.hpp"
#include "private/SyntaxTreeTarget.hpp"
#include "../../utils/patterns/observer/Observer.hpp"
#include "../Reads/Stream.hpp"

#include "../data/structures/node.hpp"


namespace sdg {


//takes in a stream of characters
//creates a stream of tokens
class Parser : public pattern::Observer
{
    std::shared_ptr<TokenSource> source_;
    std::shared_ptr<SyntaxTreeTarget> target_;

    int32_t record_index_, field_index_;

    void parse();
    bool ready()
    {
        return (source_ && target_);
    }

public:
    Parser();
    ~Parser() = default;

    virtual void receive_event() override;


    template<class T>
    void set_source(sdg::pipeline::Stream<std::string> *queue_ptr)
    {
        this->set_subject( queue_ptr );
        source_ = std::shared_ptr<T>( new T( queue_ptr ) );

        this->parse();
    }

    template<class T>
    void set_target(std::shared_ptr<SyntaxNode> syntax_tree)
    {
        target_ = std::shared_ptr<T>( new T( syntax_tree ) );
        target_->add_to_root("R0", std::string());

        this->parse();
    }
};


}// namespace sdg