// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../SemanticAnalyzer.hpp"
#include <iostream>

using ::sdg::SemanticAnalyzer;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::make_shared;
using ::std::string;

using ::sdg::SyntaxNode;




void SemanticAnalyzer::receive_event()
{
    this->analyze();
}


//This function is called every time there is a change made to the source.
void SemanticAnalyzer::analyze()
{
    while ( this->ready() && false )
    {   
    }
}