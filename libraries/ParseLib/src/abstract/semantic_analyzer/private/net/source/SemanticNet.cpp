// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../../../public/SemanticNet.hpp"

#include <iostream>
#include <vector>

using ::sdg::SemanticNet;
using ::sdg::LexicalItem;
using ::sdg::ItemPayload;
using ::sdg::PropertySetBase;
using ::sdg::NodeProperties;
using ::sdg::ItemType;
using ::std::string;
using ::std::vector;
using ::std::shared_ptr;
using ::std::make_shared;
using ::std::cout;
using ::std::endl;


const std::shared_ptr<const LexicalItem> SemanticNet::add_item(NodeProperties properties, vector<string> &err)
{
    shared_ptr<PropertySetBase> props = make_shared<NodeProperties>(properties);

    auto type = classify( props );

    auto item = MakeLexicalItem(static_cast<ItemType>(type), dynamic_pointer_cast<NodeProperties>(props),err);

    auto payload = decompose(item);

    if (item)
        item->set_payload(payload);

    //validate 
    if ( compare_semantics(item, err) == SemanticNet::Failure )
        return nullptr;

    return item;
}