#include <iostream>

using namespace std;

class A {
public:
    void foo() {
        cout << "Foo!!" << endl;
    }
};

class B
{
private:
    A* ptrA;
public:
    B(A& a) : ptrA(&a) {}
    A* operator->(){
        return ptrA;
    }
};

int main(int argc, char const *argv[])
{
    A a;
    B b(a);
    b->foo();
    return 0;
}
