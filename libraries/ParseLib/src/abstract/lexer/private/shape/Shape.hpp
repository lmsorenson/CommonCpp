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
public:
    enum Cardinality : int32_t
    {
        One,
        Many
    };

    Shape(Lexer *context, Cardinality cardinality = Cardinality::Many) 
    : context_(context)
    , cardinality_(cardinality) 
    , is_initialized_(false)
    , executions_(0)
    {}
    virtual ~Shape() = default;

    void init();
    void run(bool &should_buffer, char ch='\0');

    int32_t generate_token(std::string token) const;
    int32_t generate_token(std::pair<std::string, std::string> bracket);

    void handle_error(Error error);

    virtual bool is_complete() const = 0;
    virtual int32_t transition() const = 0;

    template<class T>
    void set_state(char ch = '\0');

    template<class T>
    bool state_equals();

    template<class T>
    void add_state(int32_t state_code);

protected:
    Lexer * const context_;
    Cardinality cardinality_;

    std::shared_ptr<LexerState> current_state_;
    std::map<std::string, std::shared_ptr<LexerState>> states_;

    bool is_initialized_;

    bool ready()
    {
        return (bool)(current_state_);
    }

private:
    virtual int32_t apply_transition(int32_t enum_value) = 0;

    int32_t executions_;
};

template<class T>
void Shape::set_state(char ch)
{
    current_state_->on_transition();

    std::string key = typeid(T).name();
    auto candidate = states_.at(key);
    

    current_state_ = candidate;

    //mark the occurance
    ++(*candidate);

    current_state_->initialize(ch);
}

template<class T>
bool Shape::state_equals()
{
    auto ptr = std::dynamic_pointer_cast<T>(current_state_);

    return (ptr != nullptr);
}

template<class T>
void Shape::add_state(int32_t state_code)
{
    std::string key = typeid(T).name();
    states_[key] = std::shared_ptr<T>(new T(this, state_code));

    if(!current_state_)
        current_state_ = states_.at(key);
}

}// namespace sdg