// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/SyntaxTreeSource.hpp"
#include <iostream>
#include <vector>

using ::std::string;
using ::std::vector;
using ::sdg::SyntaxTreeSource;
using ::sdg::SyntaxNode;
using ::std::cout;
using ::std::endl;



SyntaxNode SyntaxTreeSource::get_syntax_tree()
{
    return *syntax_tree_;
}

