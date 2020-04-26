// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include <deque>
#include "../../../utils/patterns/observer/Subject.hpp"

namespace sdg {
namespace pipeline {

template<class T>
class Stream : public ::sdg::pattern::Subject
{
private:
    //the actual queue object
    std::deque<T> queue_;

public:
    //adds an element to the queue and notifies observers that content is available. 
    void add( T element )
    {
        queue_.push_back(element);
        this->notify_observers();
    }

    //returns true if the queue is empty
    bool is_empty() const
    {
        return queue_.empty();
    }

    //pulls a character off the queue.
    //removes the same character from the queue.
    T get_element()
    {
        T element = queue_.front();
        queue_.pop_front();

        return element;
    }
};

}// namespace pipeline
}// namespace sdg