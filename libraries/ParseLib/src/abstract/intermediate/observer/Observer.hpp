// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <memory>

namespace sdg {
namespace pattern {

class Subject;

class Observer 
{
    // adds a subject
    Subject *subject_;

public:
    Observer() : subject_(nullptr) {}
    virtual ~Observer() = default;

    // sets the subject 
    void set_subject( Subject *new_subject );

    // receives an event notificaton
    virtual void receive_event() = 0;
};

}// namespace pattern
}// namespace sdg