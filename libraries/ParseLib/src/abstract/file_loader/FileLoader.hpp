// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once

#include "private/CharacterTarget.hpp"
#include "../intermediate/observer/Subject.hpp"


namespace sdg {

class FileLoader : public pattern::Subject
{
    std::shared_ptr<CharacterTarget> target_;

public:
    FileLoader()=default;
    ~FileLoader()=default;

    int load(std::string filepath);


    template<class T>
    void set_target(pipeline::Stream<char> *queue_ptr)
    {
        target_=std::shared_ptr<T>( new T( queue_ptr ) );
    }
};

}// namespace sdg