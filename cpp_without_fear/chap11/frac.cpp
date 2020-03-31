#include <iostream>
#include "frac.hpp"

using namespace std;

Fraction::Fraction(Fraction const &other)
{
  cout << "copy!" << endl;
  num = other.get_num();
  den = other.get_den();
  normalize();
}

Fraction &Fraction::operator=(Fraction const &other)
{
  cout << "copy assignment" << endl;
  // *this = other; // infinite recursion
  num = other.get_num();
  den = other.get_den();
  return *this;
}

int Fraction::gcf(int a, int b)
{
  if (b == 0)
    return a;
  return gcf(b, a % b);
}

int Fraction::lcm(int a, int b)
{
  int gcf_ = gcf(a, b);
  return a * b / gcf_;
}

void Fraction::normalize()
{
  if (den == 0 || num == 0)
  {
    num = 1;
    den = 0;
  }
  if (den < 0)
  {
    num *= -1;
    den *= -1;
  }
  int n = gcf(den, num);
  num /= n;
  den /= n;
}

Fraction Fraction::add(const Fraction &other)
{
  int lcm_ = lcm(this->den, other.den);
  int a = lcm_ / other.den;
  int b = lcm_ / this->den;
  Fraction frac;
  frac.set(this->num * a + other.num * b, lcm_);
  return frac;
}

Fraction Fraction::mul(const Fraction &other)
{
  int new_num = this->num * other.num;
  int new_den = this->den * other.den;
  Fraction frac;
  frac.set(new_num, new_den);
  return frac;
}