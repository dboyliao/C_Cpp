class Fraction {
private:
  int num, den;
  void normalize();
  int gcf(int a, int b);
  int lcm(int a, int b);

public:
  void set(int num, int den) {
    this->num = num;
    this->den = den;
    normalize();
  }
  // these functions are not inlined
  Fraction add(const Fraction &other);
  Fraction mul(const Fraction &other);
  // these functions are inlined
  int get_num() { return this->num; }
  int get_den() { return this->den; }
};