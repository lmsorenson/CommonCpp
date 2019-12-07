// Copyright 2019, Lucas Sorenson, All rights reserved.
#include <objects/data_set.hpp>
#include <iostream>

using namespace std;




sdg::DataSet::DataSet()
: state(DATA_SET_EMPTY)
{
}
sdg::DataSet::DataSet(State s)
: state(s)
{
}
sdg::DataSet::DataSet(int32_t hash_table_size)
: hash_table(hash_table_size)
, state(DATA_SET_GOOD)
{
}

//deconstructors
sdg::DataSet::~DataSet(){}


sdg::Instance sdg::DataSet::operator[](std::string i)
{
    return this->get(i);
}



sdg::DataSet::EntityKey::EntityKey()
:label("")
,index(-1)
,b_found(false){}
sdg::DataSet::EntityKey::EntityKey(string a_label, bool a_required, bool a_has_index)
:label(a_label)
,index(-1)
,required(a_required)
,has_index(a_has_index)
,b_found(false){}
sdg::DataSet::EntityKey::~EntityKey(){}

bool sdg::DataSet::EntityKey::IsRequired() const
{
    return this->required;
}
bool sdg::DataSet::EntityKey::HasIndex() const
{
    return this->has_index;
}

string sdg::DataSet::EntityKey::GetLabel() const {return label;}

 int32_t sdg::DataSet::EntityKey::SetIndex(int32_t a_index)
 {
     index = a_index;
     return 0;
 }

 int32_t sdg::DataSet::EntityKey::SetFound()
 {
     b_found = true;
     return 0;
 }

  bool sdg::DataSet::EntityKey::IsFound() const
 {
     return b_found;
 }

int32_t sdg::DataSet::EntityKey::GetIndex() const {return index;}
