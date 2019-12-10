// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>

class plNode
{
public:
    plNode(std::string text, std::shared_ptr<plNode> aParent);
    plNode(const plNode &plNode);
    ~plNode();

    //Get and set the value on the plNode.
    std::string GetValue();
    void SetValue(const char * text);
    std::string GetID();
    plNode AppendID(std::string new_id);
    bool EmptyID();
    std::string GetPath();
    
    //Get Children
    std::shared_ptr<plNode> GetChild(int32_t index);
    int32_t GetNumberOfChildren();
    bool HasChildren();
    bool has_parent();

    //Add Children
    void AddChild(plNode n);

    //Printing
    void Print();
    
private:
    std::string id;
    std::string value;
    std::shared_ptr<plNode> parent;
    std::vector<std::shared_ptr<plNode>> children;
};