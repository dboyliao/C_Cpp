#include <memory>
#include <stdlib.h>

using namespace std;

class Thing {};

int main(int argc, char* argv[]) {
    int n;
    if (argc == 2) {
        n = atoi(argv[1]);
    } else {
        n = 10000;
    }
    for (int i = 0; i < n; ++i) {
        shared_ptr<Thing> ptr = make_shared<Thing>();
    }
    return 0;
}
