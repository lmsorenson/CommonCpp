// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../private/net/PropertyModel.hpp"
#include "../private/net/LexicalItem.hpp"
#include "../private/net/SemanticRule.hpp"
#include <string>
#include <unordered_map>



namespace sdg {

class SemanticNet
{
public:
    const std::shared_ptr<const LexicalItem> add_item( std::string token, NodeProperties properties );

private:
    template <class T>
    T classify( ::std::string token, std::shared_ptr<const PropertySetBase> properties ) const;
    void decompose( ::std::shared_ptr<LexicalItem> item );
    int8_t compare_semantics( const std::shared_ptr<const LexicalItem> item );

    ::std::unordered_map<::std::string, std::shared_ptr<LexicalItem>> item_;
    ::std::unordered_map<ItemType, std::shared_ptr<const PropertySetBase>> precedent_;
    ::std::vector<SemanticRule<PropertySetBase>> rule_set_;
};


/* -------------------------------------------------------------------------- */
/*                            Template Definitions                            */
/* -------------------------------------------------------------------------- */
template <class T>
T SemanticNet::classify( ::std::string token, std::shared_ptr<const PropertySetBase> properties ) const
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

}// namespace sdg