// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <memory>

namespace sdg {
namespace pattern {

class Subject;

class Observer 
{
    Subject *subject_;

public:
    void set_subject(Subject *new_subject);

    virtual void receive_subject_notification() = 0;
};

}// namespace pattern
}// namespace sdg