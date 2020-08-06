#pragma once
#include "../../../../../src/abstract/lexer/private/shape/Shape.hpp"

#include "TestStates.hpp"


class ShapeA : public ::sdg::Shape
{
public:
    ShapeA(Lexer *context, ShapeA::Cardinality cardinality)
    : Shape(context, cardinality){}
    virtual ~ShapeA() = default;

    void generate_link_token() const
    {

    }

    virtual int32_t apply_transition(int32_t enum_value) override
    {
        switch ( enum_value )
        {
        case StateTransition::SetStateA:
            this->set_state<MockStateA>(); 
            break;

        case StateTransition::SetStateB:
            this->set_state<MockStateB>();
            break;

        case StateTransition::SetStateC:
            this->set_state<MockStateC>();
            break;

        default:
        case StateTransition::None: break;
        }

        return 1;
    }

    bool is_complete() const override
    {
        return true;
    }

    virtual int32_t transition() const override
    {
        return 0;
    }

    template<class t>
    std::shared_ptr<sdg::LexerState> get_state()
    {
        return states_[std::string(typeid(t).name())];
    }
};