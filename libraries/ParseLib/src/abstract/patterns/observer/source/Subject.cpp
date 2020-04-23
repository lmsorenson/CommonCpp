// Copyright 2020, Lucas Sorenson, All rights reserved.
#include <iostream>
#include "../Observer.hpp"
#include "../Subject.hpp"

using ::sdg::pattern::Subject;
using ::std::cout;
using ::std::endl;

// attaches an observer to the "distribution list" if it is not null.
void Subject::attach_observer( Observer * new_observer )
{
    if(new_observer)
        observers_.push_back(new_observer);
    else
        cout << "Error: passed in observer was found a nullptr." << endl;
}

// notifies all observers of an event.
void Subject::notify_observers()
{
    for( auto observer : observers_ )
    {
        observer->receive_event();
    }
}