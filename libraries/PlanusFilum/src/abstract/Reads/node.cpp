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

node::node(const node &node)
{
    cout << SetColor(YELLOW, "copying node:" ) << node.value << endl;
    value = node.value;
    children = node.children;
}

node::~node()
{
    cout << SetColor(RED, "deleting node:" ) << value << endl;
}

string node::GetValue(){return value;}
void node::SetValue(const char * text){value = text;}

void node::AddChild(node n){children.push_back(make_shared<node>(n));}
shared_ptr<node> node::GetChild(int32_t index){return this->children[index];}

int32_t node::GetNumberOfChildren(){return children.size();}
bool node::HasChildren(){return (children.size()>0);}


void node::Print()
{
    cout << "Print: " << value << endl;

    cout << SetColor(BLUE, "CHILDREN SIZE: ") << children.size() << endl;
    for (int i=0; i < children.size(); ++i)
    {
        children[i]->Print();
    }
}