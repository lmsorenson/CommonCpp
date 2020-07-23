// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../private/net/PropertyModel.hpp"
#include "../private/net/LexicalItem.hpp"
#include <string>
#include <unordered_map>



namespace sdg {

class SemanticNet
{
public:
    void add_item( std::string token, NodeProperties properties );

private:
    template <class T>
    T classify( ::std::string token, PropertySetBase *properties ) const;
    void decompose( LexicalItem token, PropertySetBase );
    void compare( ::std::vector<LexicalItem> lexical_item );

    ::std::unordered_map<::std::string, LexicalItem> item_;
};



/* -------------------------------------------------------------------------- */
/*                            Template Definitions                            */
/* -------------------------------------------------------------------------- */
template <class T>
T SemanticNet::classify( ::std::string token, PropertySetBase *properties ) const
{
    NodeProperties *props;
    if ((props != dynamic_cast<NodeProperties*>(properties)))
        return ItemType::Undefined;

    if (props->child_of_root_node() && props->get_label().compare("R")==0)
    {
        return ItemType::Record;
    }
    else if (props->child_of_root_node() && props->get_label().compare("H")==0)
    {
        return ItemType::Header;
    }
    else if (true)
    {
        return ItemType::Value;
    }
    else
    {
        return ItemType::Undefined;
    }
}

}// namespace sdg