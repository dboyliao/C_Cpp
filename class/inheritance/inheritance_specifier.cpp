#include <iostream>
#include <string>

using namespace std;

class Base {
// public to outside of the class (and its instances)
public:
  Base(string name) : name_(name), count_(0){}

  string name(void){
    return this->name_;
  }

  void speak(void) {
    this->talk();
    return;
  }
private:
/*
  Accessible "only" to this class:
  1. not accessible to the outside of this class.
  2. not accessible to the derived class
*/
  string name_ = "";
  int count_ = 0;
protected:
/*
  Accessible within the class and derived class
  That is, it is not accessible only outside of the class
*/
  virtual void talk(void) {
    this->count_ += 1;
    cout << "Hello, I'm " << this->name_ << endl
         << "talking count: " << this->count_ << endl << endl;
    return;
  }
};

// public mode
// 1. Base's public --> PubSub's public
// 2. Base's protected --> PubSub's protected
class PubSub : public Base {
public:
  PubSub(string name) : Base(name) {}
protected:
  void talk(void) {
    cout << "PubSub can use Base::talk()!" << endl;
    Base::talk();
    cout << "Say my name again! " << this->name() << endl;
  }
};

// protected mode
// 1. Base's public --> ProtSub's protected
// 2. Base's protected --> ProtSub's protected
class ProtSub : protected Base {
public:
  ProtSub(string name) : Base(name) {}
  void speaky(void) {
    cout << "ProtSub speak" << endl;
    Base::speak();
  }
};

// private mode
// 1. Base's public --> PrivSub's private
// 2. Base's protected --> PrivSub's private
class PrivSub : private Base {
public:
  PrivSub(string name) : Base(name){}
  void say(void) {
    speak();
  }
};

int main(void) {
  Base base("base");
  PubSub pub_sub("pub_sub");
  ProtSub prot_sub("prot_sub");
  PrivSub priv_sub("priv_sub");

  cout << "Base speak!" << endl;
  base.speak();
  base.speak();

  cout << "PubSub speak!" << endl;
  pub_sub.speak();
  pub_sub.speak();
  pub_sub.speak();

  cout << "ProtSub can't speak!" << endl;
  // prot_sub.speak() << endl; // not accessible
  cout << "ProtSub can be speaky" << endl;
  prot_sub.speaky();
  prot_sub.speaky();

  cout << "PrivSub can't speak and talk" << endl;
  cout << "It can only say it!" << endl;
  priv_sub.say();

  return 0;
}