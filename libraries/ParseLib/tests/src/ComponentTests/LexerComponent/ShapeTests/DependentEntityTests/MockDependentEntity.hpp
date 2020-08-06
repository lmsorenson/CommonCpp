#pragma once
#include <gmock/gmock.h>
#include "../../../../../../src/abstract/lexer/public/DependentEntity.hpp"
#include "../../../../../../src/abstract/lexer/private/queue/TokenTarget.hpp"
#include "../../../../../../src/abstract/lexer/private/queue/ErrorQueue.hpp"
#include "../../../../../../src/abstract/intermediate/Error.hpp"



class MockDependentEntity : public ::sdg::DependentEntity
{
public:
    explicit MockDependentEntity(Lexer *context, const std::string &entity_id, Shape::Cardinality cardinality)
    : DependentEntity(context, entity_id, cardinality, ',', "\r\n", std::pair('\"', '\"'), '\"')
    {}
    virtual ~MockDependentEntity() = default;

    MOCK_METHOD(int32_t, generate_token, (std::string token), (const override));
    MOCK_METHOD(int32_t, generate_link_token, (), (const));
};

class MockDependentEntityB : public ::sdg::DependentEntity
{
public:
    explicit MockDependentEntityB(Lexer *context, const std::string &entity_id, Shape::Cardinality cardinality)
    : DependentEntity(context, entity_id, cardinality, '|', std::pair('{','}'), std::pair('(', ')'), '\\')
    {}
    virtual ~MockDependentEntityB() = default;

    MOCK_METHOD(int32_t, generate_token, (std::string token), (const override));
    MOCK_METHOD(int32_t, generate_link_token, (), (const));
};

class MockTarget : public ::sdg::TokenTarget
{
public:
    explicit MockTarget(::sdg::pipeline::Stream<std::string> * stream) : TokenTarget(stream) {}
    virtual ~MockTarget() = default;

    MOCK_METHOD(void, send_token, (std::string token), ());
};

class MockErrorQueue : public ::sdg::ErrorQueue
{
public:
    explicit MockErrorQueue(::sdg::pipeline::Stream<sdg::Error> * stream) : ErrorQueue(stream) {}
    virtual ~MockErrorQueue() = default;

    MOCK_METHOD(void, add_error, (const ::sdg::Error err), ());
};

class MockLexer : public ::sdg::Lexer
{
public:
    MockLexer() : Lexer() {
        this->set_target<MockTarget>(nullptr);
        this->set_error_queue<MockErrorQueue>(nullptr);
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

    std::shared_ptr<MockErrorQueue> get_mock_error_queue()
    {
        return std::dynamic_pointer_cast<MockErrorQueue>(error_queue_);
    }
};