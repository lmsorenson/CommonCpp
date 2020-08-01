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
    ItemPayload(const std::string &key, const std::string &value, const std::string &path)
    : key_(key)
    , value_(value)
    , path_(path)
    {}
    ~ItemPayload() = default;

    void print() const
    {
        std::cout << "Payload {" << key() << "," << value() << "," << path() << "," << "} ";
    }

    const std::string key() const
    {
        return key_;
    }

    const std::string value() const
    {
        return value_;
    }

    const std::string path() const
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
    LexicalItem(const std::string &item_value, const ItemType &type, std::shared_ptr<const PropertySetBase> props)
    : value_(item_value)
    , type_(type)
    , props_(props)
    {}
    virtual ~LexicalItem() = default;

    void print_line() const
    {
        std::cout << "Lexical Item: ";
        payload_.print();
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

    void set_payload(const ItemPayload &payload)
    {
        payload_ = payload;
    }

    const ItemPayload get_payload() const
    {
        return payload_;
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