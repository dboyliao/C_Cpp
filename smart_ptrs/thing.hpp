#ifndef THING_H
#define THING_H
#include <string>

class Thing {
public:
    std::string name;
    Thing(std::string name_);
    ~Thing();
    void talk();
};
#endif // THING_H
