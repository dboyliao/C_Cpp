#include <list>
#include <exception>
#include <iostream>

using std::cerr;
using std::endl;
using std::list;

class A
{
};

class MyException
{
public:
    MyException(char const *reason_) : reason(reason_) {}
    char const *reason;
};

void foo()
{
    throw MyException("Hello, error!");
}

int main(int argc, char const *argv[])
{
    list<A> l(10);
    try
    {
        foo();
    }
    catch (const MyException &e)
    {
        cerr << e.reason << endl;
    }
    return 0;
}
