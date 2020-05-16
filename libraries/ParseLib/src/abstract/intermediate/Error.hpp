// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once


namespace sdg {
    
enum : int32_t
{
    SUCCESS = 0,
    FILE_FORMAT_INVALID,
    UNKNOWN_ERROR
};

struct Error
{
    int code;
};

}// namespace sdg