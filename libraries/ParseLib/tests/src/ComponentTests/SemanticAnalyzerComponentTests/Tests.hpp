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

class SemanticAnalyzerComponentTests : public ::testing::Test
{

protected:

    SemanticAnalyzerComponentTests()
    {

    }

    virtual ~SemanticAnalyzerComponentTests()
    {

    }

    virtual void SetUp()
    {
    }
    
    virtual void TearDown()
    {
    }
    
};