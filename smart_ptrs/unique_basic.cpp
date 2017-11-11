#include "thing.hpp"
#include <memory>
#include <iostream>
#include <string>

using namespace std;

static unique_ptr<Thing> create(string name) {
    unique_ptr<Thing> ptr(new Thing(name));
    return ptr;
}

int main(void) {
    {
        unique_ptr<Thing> uni_thing(new Thing("unique"));
        uni_thing->talk();
    
        // compilation error (no copy assign op, neither copy constructor)
        // unique_ptr<Thing> uni_thing2 = uni_thing;
        unique_ptr<Thing> uni_thing2;
        uni_thing.swap(uni_thing2);

        if (uni_thing) {
            cout << "uni_thing own the object" << endl;
            uni_thing->talk();
        } else if (uni_thing2) {
            cout << "uni_thing2 own the object" << endl;
            uni_thing2->talk();
        } else {
            cout << "it's gone!?" << endl;
        }
    }

    // move assign operation
    {
        unique_ptr<Thing> uni_thing3 = create("uni_thing3");
        uni_thing3->talk();
    }
    // move constructor
    {
        unique_ptr<Thing> uni_thing4(create("uni_thing4"));
        uni_thing4->talk();
    }

    return 0;
}