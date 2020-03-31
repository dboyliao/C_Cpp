#include "btree.hpp"
#include <iostream>

using namespace std;

class A
{
public:
    string v = "default";
    A() {}
    A(string v_) : v(v_) {}
} arrA[3];

int main(int argc, char const *argv[])
{
    BTree tree;
    tree.insert("C");
    tree.insert("A");
    tree.insert("B");
    tree.insert("D");
    tree.insert("a");
    tree.print();
    cout << endl;
    tree.goLeft().print();
    cout << endl;
    tree.goRight().print();

    BNode *ptrNode = tree.find("A");
    if (ptrNode)
    {
        cout << "found: " << ptrNode->value << endl;
    }
    for (auto a : arrA)
    {
        cout << a.v << endl;
    }
    A aa("hello, class A");
    cout << aa.v << endl;
    return 0;
}
