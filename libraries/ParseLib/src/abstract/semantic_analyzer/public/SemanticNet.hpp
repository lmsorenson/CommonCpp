// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "PropertyModel.hpp"
#include "../private/net/LexicalItem.hpp"
#include "../private/net/SemanticRule.hpp"
#include <string>
#include <unordered_map>

namespace sdg {

class SemanticNet
{
public:
    const std::shared_ptr<const LexicalItem> add_item( NodeProperties properties, std::vector<std::string> &err );

    enum : int8_t
    {
        Failure,
        Success
    };

protected:
    ::std::unordered_map<::std::string, std::shared_ptr<LexicalItem>> item_;
    ::std::unordered_map<ItemType, std::shared_ptr<const PropertySetBase>> precedent_;
    ::std::vector<SemanticRule<PropertySetBase>> rule_set_;

private:
    virtual int16_t classify( std::shared_ptr<const PropertySetBase> properties ) const = 0;
    virtual ItemPayload decompose( ::std::shared_ptr<LexicalItem> item ) = 0;
    virtual int8_t compare_semantics( const std::shared_ptr<const LexicalItem> item, std::vector<std::string> &err ) = 0;

    virtual std::shared_ptr<LexicalItem> MakeLexicalItem(ItemType type, std::shared_ptr<const NodeProperties> props, std::vector<std::string> &error) = 0;
};

}// namespace sdg