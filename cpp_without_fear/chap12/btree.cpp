#include "btree.hpp"
#include <iostream>

using namespace std;

void BTree::insert(string value)
{
    BNode **node_cursor = &this->root;
    BNode *parent = nullptr;
    while (*node_cursor != nullptr)
    {
        parent = *node_cursor;
        node_cursor = value <= (*node_cursor)->value ? &((*node_cursor)->leftNode) : &((*node_cursor)->rightNode);
    }
    *node_cursor = new BNode(value);
    (*node_cursor)->parent = parent;
}

void BNode::print()
{
    if (this->leftNode == nullptr && this->rightNode == nullptr)
    {
        cout << this->value << endl;
        return;
    }
    if (this->leftNode != nullptr)
    {
        this->leftNode->print();
    }
    cout << this->value << endl;
    if (this->rightNode != nullptr)
    {
        this->rightNode->print();
    }
}

void BTree::print()
{
    root->print();
}

BNode *BTree::find(string value)
{
    BNode *current_node = root;
    while (current_node != nullptr && current_node->value != value)
    {
        current_node = value <= current_node->value ? current_node->leftNode : current_node->rightNode;
    }
    return current_node;
}