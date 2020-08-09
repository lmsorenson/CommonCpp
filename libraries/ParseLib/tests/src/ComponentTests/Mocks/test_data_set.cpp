#include "test_data_set.hpp"

using ::std::make_shared;
using ::std::shared_ptr;

TestDataSet::TestDataSet(::sdg::DataSet::State state)
: ::sdg::DataSet(100)
{
    state_ = state;

    shared_ptr<::sdg::Entity>
            entityA = make_shared<::sdg::Entity>("A", "entity a"),
            entityB = make_shared<::sdg::Entity>("B", "entity b"),
            entityC = make_shared<::sdg::Entity>("G", "entity c");

    shared_ptr<::sdg::Attribute>
            a_id_attribute,
            b_id_attribute;

    entityA->add_descriptor(a_id_attribute=make_shared<::sdg::Attribute>(::sdg::Attribute("a_id", "A", ::sdg::Attribute::Scale::Ordinal)), true);
    entityB->add_descriptor(b_id_attribute=make_shared<::sdg::Attribute>(::sdg::Attribute("b_id", "B", ::sdg::Attribute::Scale::Ordinal)), true);

    shared_ptr<::sdg::Relationship>
            C_A = make_shared<::sdg::Relationship>("c_to_a", entityC, entityA, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1),
            C_B = make_shared<::sdg::Relationship>("c_to_b", entityC, entityB, false, ::sdg::Relationship::IDENTIFY_BY::LINK_1);

    logical_data_structure.add_thing(entityA);
    logical_data_structure.add_thing(entityB);
    logical_data_structure.add_thing(entityC);
    logical_data_structure.add_thing(C_A);
    logical_data_structure.add_thing(C_B);
}