#pragma once
#include "../../../../../src/abstract/lexer/private/shape/Shape.hpp"

class ShapeA : public ::sdg::Shape
{
public:
    ShapeA(Lexer *context, Shape::Cardinality cardinality)
    : Shape(context, cardinality){}
    virtual ~ShapeA() = default;

    void generate_link_token() const
    {

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