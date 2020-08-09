// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "Observer.hpp"
#include <vector>

namespace sdg {
namespace pattern {

class Observer;

class Subject 
{
    //a set of observers that will want to receive notifications
    std::vector<Observer*> observers_;

public:
    Subject() = default;
    ~Subject() = default;

    //attaches an observer to a "distribution list".
    void attach_observer( Observer *new_observer );

    //notifies observers that the state_ of the subject has changed.
    void notify_observers();
};

}// namespace pattern
}// namespace sdg