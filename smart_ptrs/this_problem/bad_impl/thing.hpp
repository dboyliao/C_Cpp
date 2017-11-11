#ifndef THING_H
#define THING_H
#include <string>

class Thing {
public:
    std::string name;
    Thing(std::string name_);
    ~Thing();
    void talk(void);
    void do_stuff(void);
};
#endif // THING_H
