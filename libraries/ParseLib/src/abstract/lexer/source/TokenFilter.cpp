// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../public/TokenFilter.hpp"
#include <iostream>
#include "../Lexer.hpp"

using ::std::string;
using ::std::to_string;
using ::sdg::TokenFilter;
using ::sdg::ChildTokenFilter;

TokenFilter::TokenFilter(Lexer * owner, std::string new_filter_id)
: filter_id_(new_filter_id)
, owner_(owner) {}

ChildTokenFilter::ChildTokenFilter(Lexer * owner, std::string new_filter_id, TokenFilter * parent_filter)
: parent_(parent_filter)
, TokenFilter(owner, new_filter_id) {}


// string ParserFilter::name()
// {
//     return "abstract";
// }

// string TokenFilter::get_filter_id(int index)
// {
//     string out;
//     out.append(label).append(to_string(index));
//     return out;
// }

// std::string TokenFilter::GetLabel()
// {
//     return label;
// }
