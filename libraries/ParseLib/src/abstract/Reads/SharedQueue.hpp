// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <deque>
#include "../patterns/observer/Subject.hpp"

namespace sdg {

template<class T>
class SharedQueue : public ::sdg::pattern::Subject
{
    std::deque<T> queue_;

public:
    void add(T element)
    {
        queue_.push_back(element);
        notify_observers();
    }

    bool is_empty()
    {
        return queue_.empty();
    }

    char get_char()
    {
        char ch = queue_.front();
        queue_.pop_front();

        return ch;
    }
};

}// namespace sdg