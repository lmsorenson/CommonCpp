// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../../../public/SemanticNet.hpp"

#include <iostream>
#include <vector>

#define SUCCESS (0)
#define FAILURE (-1)

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


shared_ptr<LexicalItem> MakeLexicalItem(string token, ItemType type, shared_ptr<const NodeProperties> props)
{
    if (props == nullptr)
        return nullptr;

    switch (type) {
        case ItemType::Record:
            return make_shared<LexicalItem>(token, type, make_shared<const ::sdg::RecordProperties>(*props));
            break;

        case ItemType::Value:
            return make_shared<LexicalItem>(token, type, make_shared<const ::sdg::RecordProperties>(*props));
            break;

        default:
        case ItemType::Undefined:
            return nullptr;
            break;
    }
}

const std::shared_ptr<const LexicalItem> SemanticNet::add_item(string token, NodeProperties properties)
{
    shared_ptr<PropertySetBase> props = make_shared<NodeProperties>(properties);

    auto type = classify(token, props);

    auto item = MakeLexicalItem(token, static_cast<ItemType>(type), dynamic_pointer_cast<NodeProperties>(props));

    //currently does nothing
    decompose(item);

    //validate 
    if ( compare_semantics(item) == -1 )
        return nullptr;

    return item;
}

int16_t SemanticNet::classify( ::std::string token, std::shared_ptr<const PropertySetBase> properties ) const
{
    std::shared_ptr<const NodeProperties> props;
    if ( (props = std::dynamic_pointer_cast<const NodeProperties>(properties))==nullptr )
        return ItemType::Undefined;

    if (props->child_of_root_node() && props->compare_token_label("R"))
    {
        return ItemType::Record;
    }
    else if (props->child_of_root_node() && props->compare_token_label("H"))
    {
        return ItemType::Header;
    }
    else if (props->token_has_value())
    {
        return ItemType::Value;
    }
    else
    {
        return ItemType::Undefined;
    }
}

void SemanticNet::decompose( std::shared_ptr<LexicalItem> token )
{

}

int8_t SemanticNet::compare_semantics( const std::shared_ptr<const LexicalItem> item )
{
    std::shared_ptr<const RecordProperties> actual, expected;

    //There should be no precedent for undefined items.
    if ( !item || item->type() == ItemType::Undefined )
        return FAILURE;

    //if the argument is null, then it will not match the precedent.
    if ( (actual = std::dynamic_pointer_cast<const RecordProperties>(item->properties())) == nullptr )
        return FAILURE;

    // if this lexical item type has no precedent, set the precedent.
    if ( (expected = std::dynamic_pointer_cast<const RecordProperties>(precedent_[item->type()])) == nullptr )
    {
        precedent_[item->type()] = item->properties();
        return SUCCESS;
    }

    if ( actual->number_of_values() != expected->number_of_values() )
        return FAILURE;

    else
        return SUCCESS;
}


#undef FAILURE
#undef SUCCESS