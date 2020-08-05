// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../LexicalItem.hpp"
#include <iostream>

using ::sdg::ItemPayload;
using ::sdg::LexicalItem;
using ::sdg::ItemType;
using ::sdg::PropertySetBase;
using ::std::string;
using ::std::shared_ptr;
using ::std::cout;

ItemPayload::ItemPayload(const string &key, const string &value, const string &path)
: key_(key)
, value_(value)
, path_(path)
{}

void ItemPayload::print() const
{
    cout << "Payload {" << key() << "," << value() << "," << path() << "," << "} ";
}

const std::string ItemPayload::key() const
{
    return key_;
}

const std::string ItemPayload::value() const
{
    return value_;
}

const std::string ItemPayload::path() const
{
    return path_;
}

bool ItemPayload::is_empty() const
{
    return key_.empty() && value_.empty() && path_.empty();
}


LexicalItem::LexicalItem(const string &item_value, const ItemType &type, shared_ptr<const PropertySetBase> props)
: value_(item_value)
, type_(type)
, props_(props)
{}

void LexicalItem::print_line() const
{
    std::cout << "Lexical Item: ";
    payload_.print();
    props_->print();
    std::cout << std::endl;
};

ItemType LexicalItem::type() const
{
    return type_;
}

bool LexicalItem::has_payload() const
{
    return !payload_.is_empty();
}

const string LexicalItem::value() const
{
    return value_;
}

void LexicalItem::set_payload(const ItemPayload &payload)
{
    payload_ = payload;
}

const ItemPayload LexicalItem::get_payload() const
{
    return payload_;
}

std::shared_ptr<const PropertySetBase> LexicalItem::properties() const
{
    return props_;
}
