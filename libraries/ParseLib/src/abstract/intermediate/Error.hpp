// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once


namespace sdg {
    
enum : int32_t
{
    SUCCESS = 0,
    FILE_FORMAT_INVALID,
    UNKNOWN_ERROR
};

class Error
{
public:
    explicit Error(int16_t code)
    : code_(code)
    {}

    int16_t code()
    {
        return code_;
    }

private:
    int code_;
};

}// namespace sdg