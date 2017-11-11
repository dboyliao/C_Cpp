#include "thing.hpp"
#include <iostream>
#include <memory>

using namespace std;

int main(void) {
    shared_ptr<Thing> thing = make_shared<Thing>("BadThing");
    thing->do_stuff();
    // your thing is gone after this line

    // invalid access
    thing->talk();
    return 0;
}
