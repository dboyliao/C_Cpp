#include <functional>
#include <iostream>

class Object {
 public:
  Object() {}
  Object(const Object &other) { std::cout << "copy!" << std::endl; }
  Object(Object &&other) { std::cout << "move!" << std::endl; }
  Object &operator=(const Object &other) {
    std::cout << "copy assign!" << std::endl;
    return *this;
  }
  Object &operator=(Object &&other) {
    std::cout << "move assign" << std::endl;
    return *this;
  }
  int value = 0;
};

int main(int argc, char const *argv[]) {
  Object obj;
  std::cout << &obj << std::endl;
  auto lamb = [obj  // <- an implicit copy right here
  ]() mutable {
    std::cout << "Hello, world " << &obj << std::endl;
    obj.value = 3;
  };
  std::cout << "lambda created" << std::endl;
  std::function<void()> func = std::move(lamb);
  func();
  return 0;
}
