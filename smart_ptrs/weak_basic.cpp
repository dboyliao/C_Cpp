#include "thing.hpp"
#include <memory>
#include <iostream>

using namespace std;

void use_weak(weak_ptr<Thing>& ptr) {
    if (!ptr.expired()) {
        cout << "weak ptr is valid!" << endl;
        shared_ptr<Thing> sh_ptr = ptr.lock();
        sh_ptr->talk();
    } else {
        cout << "weak ptr expire" << endl;
    }
    return;
}

void use_weak_catch(weak_ptr<Thing>& ptr) {
    try {
        shared_ptr<Thing> sh_ptr(ptr);
        sh_ptr->talk();
    } catch (bad_weak_ptr) {
        cout << "bad weak pointer" << endl;
    }
    return;
}

int main(void) {
    shared_ptr<Thing> sh_thing = make_shared<Thing>("thing");
    cout << "[Info] shared pointer is talking" << endl;
    sh_thing->talk();

    // construct with shared_ptr
    weak_ptr<Thing> wk_thing(sh_thing);
    cout << "[Info] before setting nullptr to shared_ptr" << endl;
    use_weak(wk_thing);

    cout << "[Info] setting nullptr (thing should be deleted by compiler)" << endl;
    sh_thing = nullptr;
    cout << "[Info] after setting nullptr" << endl;
    use_weak(wk_thing);

    // try-catch approach
    cout << "[Info] using weak_ptr with try-catch" << endl;
    use_weak_catch(wk_thing);
    
    return 0;
}
