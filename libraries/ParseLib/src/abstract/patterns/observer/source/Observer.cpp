// Copyright 2020, Lucas Sorenson, All rights reserved.
#include <iostream>
#include "../Observer.hpp"
#include "../Subject.hpp"

using ::sdg::pattern::Observer;
using ::std::shared_ptr;
using ::std::cout;
using ::std::endl;

//sets the subject pointer
void Observer::set_subject(Subject *new_subject)
{
    if (new_subject)
    {
        subject_ = new_subject;
        subject_->attach_observer(this);
    }
    else
    {
        cout << "Error: passed in subject was found a nullptr." << endl;
    }
    
}