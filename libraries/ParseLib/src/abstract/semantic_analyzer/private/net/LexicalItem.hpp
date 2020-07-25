// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <unordered_map>

namespace sdg {

enum ItemType : int16_t
{
    Undefined,
    Header,
    Record,
    Value,
    Field
};

class LexicalItem
{
public:
    LexicalItem(std::string item_value, ItemType type, std::shared_ptr<const PropertySetBase> props)
    : value_(item_value)
    , type_(type)
    , props_(props)
    {}
    ~LexicalItem() = default;
    
    ItemType type() const
    {
        return type_;
    }

    std::shared_ptr<const PropertySetBase> properties() const
    {
        return props_;
    }

private:
    ItemType type_;
    std::string value_;
    std::shared_ptr<const PropertySetBase> props_;
};

}// namespace sdg