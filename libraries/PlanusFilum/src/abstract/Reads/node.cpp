// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "node.hpp"
#include <iostream>

using namespace std;

node::node(const char * text)
{
    // cout << "constructing node: " << text << endl;
    value = string(text);
}

node::~node()
{
    // cout << "deleting node: " << value << endl;
}

string node::GetValue()
{
    return value;
}

shared_ptr<vector<node>> node::GetChildren()
{
    return make_shared<vector<node>>(children);
}

void node::AddChildren(vector<node> n)
{
    children = n;
}