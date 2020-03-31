#include "frac.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  Fraction frac1, frac2, frac3;
  frac1.set(1, 2);
  frac2.set(1, 3);
  frac3 = frac1.add(frac2);
  cout << frac3.get_num() << '/' << frac3.get_den() << endl;
  frac3 = frac1.mul(frac2);
  cout << frac3.get_num() << '/' << frac3.get_den() << endl;
  return 0;
}
