// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <unordered_map>
#include "PropertyModel.hpp"

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
    explicit ItemPayload(const std::string &key, const std::string &value, const std::string &path);
    ~ItemPayload() = default;

    void print() const;
    const std::string key() const;
    const std::string value() const;
    const std::string path() const;
    bool is_empty() const;

private:
    std::string key_, value_, path_;
};

class LexicalItem
{
public:
    explicit LexicalItem(const std::string &item_value, const ItemType &type, std::shared_ptr<const PropertySetBase> props);
    virtual ~LexicalItem() = default;

    void print_line() const;
    ItemType type() const;
    bool has_payload() const;
    const std::string value() const;
    void set_payload(const ItemPayload &payload);
    const ItemPayload get_payload() const;
    std::shared_ptr<const PropertySetBase> properties() const;

private:
    const ItemType type_;
    ItemPayload payload_;
    const std::string value_;
    const std::shared_ptr<const PropertySetBase> props_;
};

}// namespace sdg