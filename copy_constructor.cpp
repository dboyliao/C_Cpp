#include <iostream>
#include <string>

using namespace std;

template <typename T>
class A {
    A(A const&){};
public:
    string name;
    A(string name_) : name(name_){}
    A(A& other) : name(other.name) { 
        cout << "copy A" << endl;
    }
};

int main(void) {
    A<int> a("object");
    A<int> aa(a);

    return 0;
}
