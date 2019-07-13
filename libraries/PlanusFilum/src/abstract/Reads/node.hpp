// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>

class node
{
public:
    node(const char * text);
    // node(const node &node);
    ~node();

    //Get and set the value on the node.
    std::string GetValue();
    void SetValue(const char * text);
    
    //Get Children
    std::shared_ptr<node> GetChild(int32_t index);
    // std::shared_ptr<std::vector<node>> GetChildren();

    //Add Children
    void AddChild(node n);
    // void AddChildren(std::vector<node> vn);

    //Printing
    void Print();
    
private:
    std::string value;
    std::vector<std::shared_ptr<node>> children;
     
};