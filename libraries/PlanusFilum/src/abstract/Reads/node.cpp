// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "node.hpp"
#include <iostream>
#include "../../colortext.hpp"

using namespace std;

node::node(const char * text)
{
    cout << SetColor(CYAN, "constructing node: ") << text << endl;
    value = string(text);

}

// node::node(const node &node)
// {
//     cout << SetColor(YELLOW, "copying node:" ) << node.value << endl;
//     value = node.value;
//     children = node.children;
// }

node::~node()
{
    cout << SetColor(RED, "deleting node:" ) << value << endl;
}

string node::GetValue()
{
    return value;
}

void node::SetValue(const char * text)
{
    value = text;
}

// shared_ptr<vector<node>> node::GetChildren()
// {
//     return make_shared<vector<node>>(children);
// }

void node::AddChild(node n)
{
    cout << "Adding child. . . " << endl;
    children.push_back(make_shared<node>(n));
}

// void node::AddChildren(vector<node> vn)
// {
//     cout << "Adding children. . . " << endl;
//     children.insert(children.end(), vn.begin(), vn.end());
// }

shared_ptr<node> node::GetChild(int32_t index)
{
    return this->children[index];
}

void node::Print()
{
    // cout << SetColor(BLUE, string(this->GetValue()).c_str()) << endl;
    cout << "Print: " << value << endl;
    
    // if (children != nullptr)
    // {
        cout << SetColor(BLUE, "CHILDREN SIZE: ") << children.size() << endl;
        for (int i=0; i < children.size(); ++i)
        {
            children[i]->Print();
        }
    // }
    
}