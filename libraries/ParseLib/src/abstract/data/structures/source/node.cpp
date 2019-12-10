// Copyright 2019, Lucas Sorenson, All rights reserved.
#include "../node.hpp"
#include <iostream>

using namespace std;

plNode::plNode(string text, std::shared_ptr<plNode> aParent)
: value(text)
, parent(aParent)
{
}

plNode::plNode(const plNode &plNode)
{
    id = plNode.id;
    value = plNode.value;
    children = plNode.children;
    parent = plNode.parent;
}

plNode::~plNode()
{
    // cout << SetColor(RED, "deleting plNode:" ) << value << endl;
}

string plNode::GetValue(){return value;}
void plNode::SetValue(const char * text){value = text;}
string plNode::GetID(){return id;}
plNode plNode::AppendID(string new_id){id.append(new_id); return *this;}
bool plNode::EmptyID(){return (id.empty());};

string plNode::GetPath()
{
    string path;

    shared_ptr<plNode> current_node;
    
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

void plNode::AddChild(plNode n)
{
    children.push_back(make_shared<plNode>(n));
}
shared_ptr<plNode> plNode::GetChild(int32_t index){return this->children[index];}

int32_t plNode::GetNumberOfChildren(){return children.size();}
bool plNode::HasChildren(){return (children.size()>0);}
bool plNode::has_parent(){return ((bool)parent);}

void plNode::Print()
{
    for (int i=0; i < children.size(); ++i)
    {
        children[i]->Print();
    }
}