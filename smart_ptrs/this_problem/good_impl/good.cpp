#include "thing.hpp"
#include <iostream>
#include <memory>

using namespace std;

int main(void) {
    shared_ptr<Thing> thing = make_shared<Thing>("GoodThing");
    // use_count is 1 outside member function call
    cout << "[outside do_stuff] use_count: " << thing.use_count() << endl;
    // use_count is 2 inside member function call
    thing->do_stuff();
    // so thing is not gone yet

    // work properly
    thing->talk();
    return 0;
}
