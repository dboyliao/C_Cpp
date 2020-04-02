#include <iostream>
#include <vector>

using namespace std;

class A
{
public:
    A() {}
    A(A const &other) { cout << "Copy!" << endl; }
};

int main(int argc, char *argv[])
{
    vector<A> vv(3);
    for (auto a : vv) // copy constructor invoked
    {
        cout << "loop without reference auto type" << endl;
    }

    for (auto &a : vv) // no copy constructor
    {
        cout << "loop with reference auto type" << endl;
    }

    return 0;
}