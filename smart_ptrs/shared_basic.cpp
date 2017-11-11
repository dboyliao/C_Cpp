#include "thing.hpp"
#include <memory>
#include <iostream>

using namespace std;

int main(void) {
    // Nice one (two dynamic alloc, slower)
    shared_ptr<Thing> thing(new Thing("first"));
    cout << "thing->talk()" << endl;
    thing->talk();
    
    // use get method to get raw pointer
    (*(thing.get())).talk();

    shared_ptr<Thing> thing2 = thing;
    cout << "thing2->talk()" << endl;
    thing2->talk();

    // use reset to decrement the ref count
    thing.reset();

    // or set to nullptr
    thing2 = nullptr; // Thing is gone

    // Better calling convention (one dynamic alloc, faster
    thing = make_shared<Thing>("second");
    cout << "thing->talk()" << endl;
    thing->talk();

    thing = nullptr;

    return 0;
}
