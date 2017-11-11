#include "thing.hpp"
#include <iostream>
#include <string>

using namespace std;

Thing::Thing(string name_) : name(name_) {}

Thing::~Thing() {
    cout << "[~Thing] Delete " << name << endl;    
}

void Thing::talk(){ 
    cout << "Hello, I'm " << name << endl; 
}