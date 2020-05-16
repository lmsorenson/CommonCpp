// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../csv_token_filters.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include "../../../abstract/lexer/Lexer.hpp"

using ::sdg::csv::FieldToken;
using ::sdg::csv::RecordToken;
using ::std::cout;
using ::std::endl;
using ::std::shared_ptr;
using ::std::string;
using ::std::vector;




bool RecordToken::classify(std::string token)
{
    if (token.compare(type_id_) == 0)
    {
        char rec_buffer[10];
        sprintf(rec_buffer, "R%d", get_count()); // important to increment before

        owner_->produce_node(rec_buffer, string());

        return true;
    }

    return false;
}

bool FieldToken::classify(std::string token)
{

    if (token.substr(0, 1).compare(type_id_) == 0 && parent_)
    {
        int parent_id = parent_->get_count()-1;

        char buffer[10];
        sprintf(buffer, "R%d-F%d", parent_id, get_count());

        owner_->produce_child_node({parent_id}, buffer, token.substr(token.find("(") + 1, token.length() - (token.find("(") + 2)));

        return true;
    }

    return false;
}
