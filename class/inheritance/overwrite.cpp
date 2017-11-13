#include <iostream>

using namespace std;

class Base {
public:
    virtual void vmethod(void) const {
        cout << "Base vmethod" << endl;
    }

    void method(void) const {
        cout << "Base method" << endl;
    }
private:
    void pmethod(void) {}
};

class Derived : public Base {
    int count;
public:
    Derived() : count(0) {}
    void vmethod(void) {
        count += 1;
        cout << "Derived vmethod" << endl;
        cout << count << endl;
    }

    void method(void) {
        cout << "Derived method" << endl;
    }

    void pmethod(void) {
        cout << "Derived pmethod" << endl;
    }
};

static void do_stuff(const Base& b);

int main(void) {
    Base b;
    Derived d;
    do_stuff(b);
    do_stuff(d);
    d.pmethod();
}

void do_stuff(const Base& b) {
    b.vmethod();
    b.method();
}
