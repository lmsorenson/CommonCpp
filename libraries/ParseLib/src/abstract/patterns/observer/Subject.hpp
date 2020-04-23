// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "Observer.hpp"
#include <vector>

namespace sdg {
namespace pattern {

class Observer;

class Subject 
{
    std::vector<Observer*> observers_;

public:
    void attach_observer(Observer * new_observer);
    void notify_observers();
};

}// namespace pattern
}// namespace sdg