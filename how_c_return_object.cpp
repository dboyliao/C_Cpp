#include <iostream>

using namespace std;

class A {
public:
    int x;
    A(int x_) : x(x_) {}
    A(const A& other){
        cout << "copy!" << endl;
        this->x = other.x;
    }
    A& operator = (const A& other) {
        cout << "copy assign" << endl;
        this->x = other.x;
        return *this;
    }
};

A foo(int x) {
    // how c++ return object? with copy constructor or copy assignment or neither?
    return A(x);
}

int main(int argc, char* argv[]){
    A a = foo(3);
    a = foo(3);
    a = A(4);
    A b = a;
    return 0;
}
