// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../csv_net.hpp"


using ::sdg::CSVNet;
using ::sdg::ItemPayload;
using ::std::string;
using ::std::vector;
using ::std::shared_ptr;

int16_t CSVNet::classify( shared_ptr<const PropertySetBase> properties ) const
{
    shared_ptr<const NodeProperties> props;
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

ItemPayload CSVNet::decompose( shared_ptr<LexicalItem> token )
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

int8_t CSVNet::compare_semantics( const std::shared_ptr<const LexicalItem> item, vector<string> &err )
{
    //There should be no precedent for undefined items.
    if ( !item || item->type() == ItemType::Undefined )
        return SemanticNet::Failure;

    auto header_props = std::dynamic_pointer_cast<const HeaderProperties>(item->properties());
    auto record_props = std::dynamic_pointer_cast<const RecordProperties>(item->properties());
    auto value_props = std::dynamic_pointer_cast<const ValueProperties>(item->properties());

    if (header_props != nullptr)
    {
        if ( header_props->number_of_values() == 0 )
        {
            err.push_back("A record must contain one or more fields.");
            return SemanticNet::Failure;
        }
        else
        {
            return SemanticNet::Success;
        }
    }
    else if (record_props != nullptr)
    {
        std::shared_ptr<const RecordProperties> expected;

        // if this lexical item type has no precedent, set the precedent.
        if ( (expected = std::dynamic_pointer_cast<const RecordProperties>(precedent_[item->type()])) == nullptr )
        {
            if ( record_props->number_of_values() == 0 )
            {
                err.push_back("A record must contain one or more fields.");
                return SemanticNet::Failure;
            }
            else
            {
                precedent_[item->type()] = item->properties();
                return SemanticNet::Success;
            }
        }

        if ( record_props->number_of_values() != expected->number_of_values() )
        {
            err.push_back("Record field count incorrect.");
            return SemanticNet::Failure;
        }

        else
            return SemanticNet::Success;
    }
    else if (value_props != nullptr)
    {
        return SemanticNet::Success;
    }
    else
    {
        return SemanticNet::Failure;
    }
}