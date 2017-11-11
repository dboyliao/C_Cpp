#ifndef THING_H
#define THING_H
#include <string>
#include <memory>

class Thing : public std::enable_shared_from_this<Thing> {
public:
    std::string name;
    Thing(std::string name_);
    ~Thing();
    void talk(void);
    void do_stuff(void);
};
#endif // THING_H
