// Copyright 2020 Lucas Sorenson, All rights reserved.
#include <iostream>
#include <string>
#include "../Shape.hpp"
#include "../../../Lexer.hpp"

using ::sdg::Shape;
using ::std::pair;
using ::std::map;
using ::std::string;
using ::std::cout;
using ::std::endl;

typedef pair<int32_t, int32_t> TransitionID;
class Transition
{
public:
    Transition() : num_occurances_(0) {}
    ~Transition() = default;

    void increment()
    {
        num_occurances_++;
    }

    bool has_not_occured()
    {
        return num_occurances_ == 0;
    }

private:
    int32_t num_occurances_;
};



void Shape::init()
{
    current_state_->initialize();
    is_initialized_ = true;
}

void Shape::run(bool &should_buffer, char ch)
{
    if (this->ready() && !this->is_initialized_)
        this->init();

    if( this->ready() )
    {
        int32_t transition_code = 0;
        auto original_state = current_state_;

        //remember history so no state loops are created
        map<TransitionID, Transition> history;

        do
        {
            int32_t from_code = current_state_->to_state_code();
            int32_t to_code  = current_state_->perform_scan(ch);

            auto current_transition = pair(from_code,to_code);
            auto inverse_transition = pair(to_code,from_code);

            if (history[current_transition].has_not_occured() && 
                history[inverse_transition].has_not_occured() && 
                to_code != transition_code)
            {
                transition_code = to_code;
            }
            else
            {
                transition_code = 0;
            }

            //make transition.
            if ( this->apply_transition(transition_code) )
            {
                history[current_transition].increment();
            }

        } while (transition_code != 0);

        // check if buffering the current character is allowed
        // in this state.
        current_state_->should_buffer(should_buffer, ch);

        original_state->update();
        current_state_->update();
    }
    else
    {
        cout << "shape error: the shape is not properly configured to process characters." << endl;
        this->handle_error({UNKNOWN_ERROR});
    }
}

void Shape::generate_token(string token) const
{
    if (context_)
        context_->produce_token(token);
}

void Shape::generate_token(std::pair<std::string, std::string> bracket)
{
    if (context_)
        context_->produce_tagged_token( pair(bracket.first, bracket.second) );
}

void Shape::handle_error(Error error)
{
    if (context_)
    {
        context_->handle_error(error);
    }
}