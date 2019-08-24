// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "node.hpp"
#include <iostream>
#include "../../colortext.hpp"

using namespace std;

node::node(string text, std::shared_ptr<node> aParent)
: value(text)
, parent(aParent)
{
    // cout << SetColor(CYAN, "constructing node: ") << text << endl;
}

node::node(const node &node)
{
    // cout << SetColor(YELLOW, "copying node:" ) << node.value << endl;
    id = node.id;
    value = node.value;
    children = node.children;
    parent = node.parent;
}

node::~node()
{
    // cout << SetColor(RED, "deleting node:" ) << value << endl;
}

string node::GetValue(){return value;}
void node::SetValue(const char * text){value = text;}
string node::GetID(){return id;}
node node::AppendID(string new_id){id.append(new_id); return *this;}
bool node::EmptyID(){return (id.empty());};

string node::GetPath()
{
    string path;

    shared_ptr<node> current_node;
    
    if (!current_node && this->has_parent())
    {
        current_node = this->parent;
    }

    if (current_node)
    {
        while(current_node->has_parent())
        {
            path.insert(0, current_node->GetID());
            current_node = current_node->parent;
        }
    }

    return path;
}

void node::AddChild(node n)
{
    children.push_back(make_shared<node>(n));
}
shared_ptr<node> node::GetChild(int32_t index){return this->children[index];}

int32_t node::GetNumberOfChildren(){return children.size();}
bool node::HasChildren(){return (children.size()>0);}
bool node::has_parent(){return ((bool)parent);}

void node::Print()
{
    for (int i=0; i < children.size(); ++i)
    {
        children[i]->Print();
    }
}