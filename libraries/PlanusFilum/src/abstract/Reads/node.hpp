// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>

class node
{
public:
    node(const char * text);
    ~node();

    std::string GetValue();
    std::shared_ptr<std::vector<node>> GetChildren();
    void AddChildren(std::vector<node> n);
private:
    std::string value;
    std::vector<node> children;
};