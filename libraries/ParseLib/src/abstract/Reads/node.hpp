// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>

class node
{
public:
    node(std::string text, std::shared_ptr<node> aParent);
    node(const node &node);
    ~node();

    //Get and set the value on the node.
    std::string GetValue();
    void SetValue(const char * text);
    std::string GetID();
    node AppendID(std::string new_id);
    bool EmptyID();
    std::string GetPath();
    
    //Get Children
    std::shared_ptr<node> GetChild(int32_t index);
    int32_t GetNumberOfChildren();
    bool HasChildren();
    bool has_parent();

    //Add Children
    void AddChild(node n);

    //Printing
    void Print();
    
private:
    std::string id;
    std::string value;
    std::shared_ptr<node> parent;
    std::vector<std::shared_ptr<node>> children;
};