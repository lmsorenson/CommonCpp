#pragma once
#include <gmock/gmock.h>
#include "../../../../../../src/abstract/lexer/public/DependentEntity.hpp"
#include "../../../../../../src/abstract/lexer/private/queue/TokenTarget.hpp"



class MockDependentEntity : public ::sdg::DependentEntity
{
public:
    MockDependentEntity(Lexer *context, std::string entity_id, Shape::Cardinality cardinality)
    : DependentEntity(context, entity_id, cardinality, ',', "\r\n")
    {}
    virtual ~MockDependentEntity() = default;

    MOCK_METHOD(int32_t, generate_token, (std::string token), (const override));
    MOCK_METHOD(int32_t, generate_link_token, (), (const));
};

class MockTarget : public ::sdg::TokenTarget
{
public:
    MockTarget(::sdg::pipeline::Stream<std::string> * stream) : TokenTarget(stream) {}
    virtual ~MockTarget() = default;

    MOCK_METHOD(void, send_token, (std::string token), ());
};

class MockLexer : public ::sdg::Lexer
{
public:
    MockLexer() : Lexer() {
        this->set_target<MockTarget>(nullptr);
    }
    virtual ~MockLexer() = default;

    MOCK_METHOD(int32_t, send_token, (std::string token), (const override));

    void buffer(char ch)
    {
        buffer_.append(std::string(1, ch));
    }
    std::shared_ptr<MockTarget> get_mock_target()
    {
        return std::dynamic_pointer_cast<MockTarget>(target_);
    }
};