#include <iostream>

using namespace std;

class A {
public:
    A(){
        for (size_t i = 0; i < 4; ++i)
            data[i] = i;
    }
    int operator[](int i) const {
        cout << "read!" << endl;
        return data[i];
    }
    int& operator[](int i) {
        cout << "write" << endl;
        return data[i];
    }
private:
    int data[4];
};

int main(int argc, const char** argv) {
    const A a;
    for (int i = 0; i < 4; ++i) {
        int j = a[i];
        cout << j << endl;
    }
    A b;
    b[0] = 3;
    for (int i = 0; i < 4; ++i) {
        int j = b[i];
        cout << j << endl;
    }
    return 0;
}