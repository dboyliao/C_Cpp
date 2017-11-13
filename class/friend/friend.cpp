// https://stackoverflow.com/questions/6407691/friend-declaration-in-c-difference-between-public-and-private
#include <iostream>

using namespace std;

class A {
#ifdef B_IS_FRIEND
    friend class B;
#endif
    int count;
#ifdef C_IS_FRIEND
public:
    friend class C;
#endif
protected:
    int p_count;
public:
    A() : count(0), p_count(0) {};
};

class B {
    
public:
    B(){};
    void inspect(A const& a) {
        cout << "B" << endl;
        cout << a.count << endl;
        cout << a.p_count << endl;
    }
};

class C {
public:
    C(){};
    void inspect(A const& a) {
        cout << "C" << endl;
        cout << a.count << endl;
        cout << a.p_count << endl;
    }
};

int main(void) {
    A a;
    B b;
    C c;
    b.inspect(a);
    c.inspect(a);
    return 0;
}