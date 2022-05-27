#include <iostream>

int& return_int_ref() {
    int a (123);
    return a; // Returning a copy now, see return type
}

void foo(int a){}

int main() {
    int &int_ref = return_int_ref(); // is now const

    std::cout << "Some stack overwriting intermediate print\n";
    foo(12345);
    std::cout << int_ref << '\n';
}
