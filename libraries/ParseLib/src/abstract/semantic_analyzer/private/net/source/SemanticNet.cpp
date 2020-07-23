// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../../../public/SemanticNet.hpp"

#include <iostream>
#include <vector>

using ::sdg::SemanticNet;
using ::sdg::LexicalItem;
using ::sdg::PropertySetBase;
using ::sdg::NodeProperties;
using ::sdg::ItemType;
using ::std::string;
using ::std::vector;
using ::std::shared_ptr;
using ::std::make_shared;
using ::std::cout;
using ::std::endl;


template<class T>
shared_ptr<LexicalItem> ConstructLexicalItem(T type, PropertySetBase *properties)
{
    if (type == ItemType::Header)
        return make_shared<::sdg::LHeaderItem>();

    else if (type == ItemType::Record)
        return make_shared<::sdg::LRecordItem>();

    else if (type == ItemType::Value)
        return make_shared<::sdg::LValueItem>();

    else 
        return nullptr;
}

void SemanticNet::add_item(string token, NodeProperties properties)
{
    auto type = classify<ItemType>(token, &properties);

    auto item = ConstructLexicalItem(type, &properties);

    // decompose();

    // compare();
}

void SemanticNet::decompose( LexicalItem token, PropertySetBase properties )
{

}

void SemanticNet::compare( vector<LexicalItem> lexical_item )
{

}