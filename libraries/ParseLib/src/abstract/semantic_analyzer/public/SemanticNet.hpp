// Copyright 2020, Lucas Sorenson, All rights reserved.
#include "../private/net/PropertyModel.hpp"
#include "../private/net/LexicalItem.hpp"
#include <string>

namespace sdg {

class SemanticNet
{
public:
    void add_item( std::string token, Properties properties );

private:
    void decompose( ::std::string token );
    void classify( LexicalItem item );
    void compare( std::vector<LexicalItem> arr );

};

}
