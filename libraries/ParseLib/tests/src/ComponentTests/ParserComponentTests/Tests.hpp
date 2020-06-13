#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <cstdio>
#include <ctime>

#include <gtest/gtest.h>
#include <ParseLib.hpp>
#include "../../TestFramework.hpp"
#include "../../../../src/abstract/lexer/Lexer.hpp"
#include "../../../../src/abstract/intermediate/Stream.hpp"

using sdg::Lexer;
using std::deque;
using sdg::pipeline::Stream;
using std::string;
using sdg::TokenTarget;
using sdg::CharacterSource;
using sdg::Error;
using sdg::ErrorQueue;

class ParserComponentTests : public ::testing::Test
{

protected:

    ParserComponentTests()
    {

    }

    virtual ~ParserComponentTests()
    {

    }

    virtual void SetUp()
    {
    }
    
    virtual void TearDown()
    {
    }
    
};