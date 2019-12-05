// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../../../../include/plDataSet.hpp"
#include <iostream>

using namespace std;




sdg::plDataSet::plDataSet()
: state(DATA_SET_EMPTY)
{
}
sdg::plDataSet::plDataSet(State s)
: state(s)
{
}
sdg::plDataSet::plDataSet(int32_t hash_table_size)
: hash_table(hash_table_size)
, state(DATA_SET_GOOD)
{
}

//deconstructors
sdg::plDataSet::~plDataSet(){}


plInstance sdg::plDataSet::operator[](std::string i)
{
    return this->get(i);
}



sdg::plDataSet::EntityKey::EntityKey()
:label("")
,index(-1)
,b_found(false){}
sdg::plDataSet::EntityKey::EntityKey(string a_label, bool a_required, bool a_has_index)
:label(a_label)
,index(-1)
,required(a_required)
,has_index(a_has_index)
,b_found(false){}
sdg::plDataSet::EntityKey::~EntityKey(){}

bool sdg::plDataSet::EntityKey::IsRequired() const
{
    return this->required;
}
bool sdg::plDataSet::EntityKey::HasIndex() const
{
    return this->has_index;
}

string sdg::plDataSet::EntityKey::GetLabel() const {return label;}

 int32_t sdg::plDataSet::EntityKey::SetIndex(int32_t a_index)
 {
     index = a_index;
     return 0;
 }

 int32_t sdg::plDataSet::EntityKey::SetFound()
 {
     b_found = true;
     return 0;
 }

  bool sdg::plDataSet::EntityKey::IsFound() const
 {
     return b_found;
 }

int32_t sdg::plDataSet::EntityKey::GetIndex() const {return index;}
