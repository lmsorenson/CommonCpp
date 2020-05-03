// Copyright 2019, Lucas Sorenson, All rights reserved.
#pragma once
#include <vector>
#include <string>
#include "observer/Subject.hpp"




namespace sdg
{


class SyntaxNode : public sdg::pattern::Subject
{
public:
    SyntaxNode(std::string a_value, std::shared_ptr<SyntaxNode> a_parent);
    SyntaxNode(const SyntaxNode &SyntaxNode);
    ~SyntaxNode();

    //Get and set the value on the SyntaxNode.
    std::string get_item_value();
    void set_value(const char * text);
    std::string get_item_key();
    SyntaxNode append_key(std::string a_new_id);
    bool is_empty_key();
    std::string get_path();
    
    //Get Children
    std::shared_ptr<SyntaxNode> get_child(int32_t index);
    int32_t get_number_of_children();
    bool has_children();
    bool has_parent();

    //Add Children
    void AddChild(SyntaxNode n);

    //Printing
    void Print();
    
private:
    std::string id_;
    std::string value_;
    std::shared_ptr<SyntaxNode> parent_;
    std::vector<std::shared_ptr<SyntaxNode>> children_;
};

} //namespace sdg