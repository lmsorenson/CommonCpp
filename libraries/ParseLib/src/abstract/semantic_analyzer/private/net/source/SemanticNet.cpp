// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../../../public/SemanticNet.hpp"

#include <iostream>
#include <vector>

#define SUCCESS (0)
#define FAILURE (-1)

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


shared_ptr<LexicalItem> MakeLexicalItem(ItemType type, shared_ptr<const NodeProperties> props, vector<string> &error)
{
    if (props == nullptr)
        return nullptr;

    switch (type) {
        case ItemType::Header:
            return make_shared<LexicalItem>(props->get_token_value(), type, make_shared<const ::sdg::HeaderProperties>(*props));
            break;

        case ItemType::Record:
            return make_shared<LexicalItem>(props->get_token_value(), type, make_shared<const ::sdg::RecordProperties>(*props));
            break;

        case ItemType::Value:
            return make_shared<LexicalItem>(props->get_token_value(), type, make_shared<const ::sdg::RecordProperties>(*props));
            break;

        default:
        case ItemType::Undefined:
            error.push_back("unknown type");
            return nullptr;
            break;
    }
}

const std::shared_ptr<const LexicalItem> SemanticNet::add_item(NodeProperties properties, vector<string> &err)
{
    shared_ptr<PropertySetBase> props = make_shared<NodeProperties>(properties);

    auto type = classify( props );

    auto item = MakeLexicalItem(static_cast<ItemType>(type), dynamic_pointer_cast<NodeProperties>(props),err);

    auto payload = decompose(item);

    if (item)
        item->set_payload(payload);

    //validate 
    if ( compare_semantics(item, err) == FAILURE )
        return nullptr;

    return item;
}

int16_t SemanticNet::classify( std::shared_ptr<const PropertySetBase> properties ) const
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

ItemPayload SemanticNet::decompose( shared_ptr<LexicalItem> token )
{
    if (token != nullptr && token->type() == ItemType::Value)
    {
        auto value = token->value();

        int32_t
            value_begin_pos = value.find("("),
            value_length = value.length() - (value_begin_pos+2);

        if (value_begin_pos != string::npos)
            return ItemPayload("", value.substr(value_begin_pos + 1, value_length), "");
        else
            return ItemPayload("", "", "");
    }
    else
    {
        return ItemPayload("", "", "");
    }
}

int8_t SemanticNet::compare_semantics( const std::shared_ptr<const LexicalItem> item, vector<string> &err )
{
    //There should be no precedent for undefined items.
    if ( !item || item->type() == ItemType::Undefined )
        return FAILURE;

    auto header_props = std::dynamic_pointer_cast<const HeaderProperties>(item->properties());
    auto record_props = std::dynamic_pointer_cast<const RecordProperties>(item->properties());
    auto value_props = std::dynamic_pointer_cast<const ValueProperties>(item->properties());

    if ((header_props = std::dynamic_pointer_cast<const HeaderProperties>(item->properties())) != nullptr)
    {
        return SUCCESS;
    }
    else if ((record_props = std::dynamic_pointer_cast<const RecordProperties>(item->properties())) != nullptr)
    {
        std::shared_ptr<const RecordProperties> expected;

        // if this lexical item type has no precedent, set the precedent.
        if ( (expected = std::dynamic_pointer_cast<const RecordProperties>(precedent_[item->type()])) == nullptr )
        {
            precedent_[item->type()] = item->properties();
            return SUCCESS;
        }

        if ( record_props && record_props->number_of_values() != expected->number_of_values() )
        {
            err.push_back("Record field count incorrect.");
            return FAILURE;
        }


        else
            return SUCCESS;
    }
    else if ((value_props = std::dynamic_pointer_cast<const ValueProperties>(item->properties())) != nullptr)
    {
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}


#undef FAILURE
#undef SUCCESS