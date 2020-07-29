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

class ItemPayload
{
public:
    ItemPayload() = default;
    ItemPayload(std::string key, std::string value, std::string path)
    : key_(key)
    , value_(value)
    , path_(path)
    {}
    ~ItemPayload() = default;

    std::string key() const
    {
        return key_;
    }

    std::string value() const
    {
        return value_;
    }

    std::string path() const
    {
        return path_;
    }

    bool is_empty() const
    {
        return key_.empty() && value_.empty() && path_.empty();
    }

private:
    std::string key_, value_, path_;
};

class LexicalItem
{
public:
    LexicalItem(std::string item_value, ItemType type, std::shared_ptr<const PropertySetBase> props)
    : value_(item_value)
    , type_(type)
    , props_(props)
    {}
    virtual ~LexicalItem() = default;

    void print_line() const
    {
        std::cout << "Item Value: " << value_ << " ";
        props_->print();
        std::cout << std::endl;
    };
    
    ItemType type() const
    {
        return type_;
    }

    bool has_payload() const
    {
        return !payload_.is_empty();
    }

    const std::string value() const
    {
        return value_;
    }

    void set_payload(ItemPayload payload)
    {
        payload_ = payload;
    }

    std::shared_ptr<const PropertySetBase> properties() const
    {
        return props_;
    }

private:
    const ItemType type_;
    ItemPayload payload_;
    const std::string value_;
    const std::shared_ptr<const PropertySetBase> props_;
};

}// namespace sdg