// Copyright 2020 Lucas Sorenson, All rights reserved.
#include "../DependentEntity.hpp"
#include <iostream>



using sdg::parse::DependentEntity;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::string;
using std::cout;
using std::endl;


string DependentEntity::get_id() const
{
    return string();
}

void DependentEntity::dependent_on(shared_ptr<TokenType> token)
{ 
    cout << " --- dependent_on ---> ";
    token->print();
    owner_=token;
}

void DependentEntity::new_node()
{
    //check if there is a new scope
    shared_ptr<Shape> shape;
    if( (shape = dynamic_pointer_cast<Shape>(owner_)) )
    {
        if(scope_ < shape->number())
        {
            scope_=shape->number();
            reset();
        }
    }
    count_up();
}

string DependentEntity::dependent_on_typeid() const
{
    return owner_->get_typeid();
}