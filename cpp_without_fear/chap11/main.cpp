#include "frac.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
  Fraction frac1(1, 2), frac2, frac3;
  frac2.set(1, 3);
  frac3 = frac1.add(frac2);
  cout << frac3.get_num() << '/' << frac3.get_den() << endl;
  frac3 = frac1.mul(frac2);
  cout << frac3.get_num() << '/' << frac3.get_den() << endl;

  Fraction frac4 = 3; // this called Fraction::Fraction(int den)
  cout << frac4.get_num() << '/' << frac4.get_den() << endl;
  vector<Fraction> v;
  v.push_back({1, 2}); // implicit copy, no move
  for (auto f : v)     // another copy, that's why move symantic is useful
  {
    cout << f.get_num() << '/' << f.get_den() << endl;
  }
  return 0;
}
