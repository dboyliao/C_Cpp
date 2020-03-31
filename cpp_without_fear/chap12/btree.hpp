#include <string>

using std::string;

class BNode
{
public:
    string value;
    BNode *parent = nullptr;
    BNode *leftNode = nullptr;
    BNode *rightNode = nullptr;
    BNode(string value_) : value(value_) {}
    void print();
};

class BTree
{
public:
    void insert(string value);
    void print();
    BTree() {}
    BTree(BNode *root_) { root = root_; }
    BTree goLeft() { return BTree(this->root->leftNode); }
    BTree goRight() { return BTree(this->root->rightNode); }
    BNode *find(string value);

private:
    BNode *root = nullptr;
};