// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <typeinfo>
#include <memory>
#include <string>
#include <iostream>
#include <map>
#include "LexerState.hpp"
#include "../../../intermediate/Error.hpp"

namespace sdg {

class Lexer;

class Shape
{    
    int32_t executions_;

public:
    enum Cardinality : int32_t
    {
        One,
        Many
    } cardinality_;

protected:
    Lexer * const context_;

    std::shared_ptr<LexerState> current_state_;
    std::map<std::string, std::shared_ptr<LexerState>> states_;

    bool is_initialized_;

    bool ready()
    {
        return (bool)(current_state_);
    }

public:
    Shape(Lexer *context, Cardinality cardinality = Cardinality::Many) 
    : is_initialized_(false)
    , executions_(0)
    , cardinality_(cardinality)
    , context_(context) {}
    virtual ~Shape() = default;

    void init();
    void run(bool &should_buffer, char ch='\0');

    void generate_token(std::string token) const;
    void generate_token(std::pair<std::string, std::string> bracket);

    void handle_error(Error error);

    virtual bool is_complete() const = 0;
    virtual int32_t transition() const = 0;

    template<class T>
    void set_state(char ch = '\0');

    template<class T>
    bool state_equals();

    template<class T>
    void add_state();
};

template<class T>
void Shape::set_state(char ch)
{
    std::string key = typeid(T).name();
    auto candidate = states_.at(key);
    ++(*candidate);

    current_state_ = candidate;

    current_state_->initialize(ch);
}

template<class T>
bool Shape::state_equals()
{
    std::string current_state_key = typeid(current_state_).name();
    std::string comparator_key = typeid(T).name();

    return (current_state_key.compare(comparator_key) == 0);
}

template<class T>
void Shape::add_state()
{
    std::string key = typeid(T).name();
    states_[key] = std::shared_ptr<T>(new T(this));

    if(!current_state_)
        current_state_ = states_.at(key);
}

}// namespace sdg