#include "thing.hpp"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

// static void __do_stuff(Thing* ptr);
static void __do_stuff(shared_ptr<Thing>& ptr);

Thing::Thing(string name_) : name(name_) {}

Thing::~Thing() {
    cout << "[~Thing] Delete " << name << endl;    
}

void Thing::talk(void){ 
    cout << "Hello, I'm " << name << endl; 
}

void Thing::do_stuff(void) {
    shared_ptr<Thing> ptr = this->shared_from_this();
    __do_stuff(ptr);
    return;
}

void __do_stuff(shared_ptr<Thing>& ptr) {
    cout << "[__do_stuff] use_count: " << ptr.use_count() << endl;
    cout << ptr->name  << " is doing stuff" << endl;
    return;
}