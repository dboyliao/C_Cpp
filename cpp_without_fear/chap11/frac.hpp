class Fraction
{
private:
  int num = 0, den;
  void normalize();
  int gcf(int a, int b);
  int lcm(int a, int b);

public:
  // user-defined constructor -> no auto default constructor
  Fraction(int num, int den) { set(num, den); }
  Fraction(int den_) { this->den = den_; }
  Fraction() : Fraction(1) {} // you need to add one, we use delegation here
  Fraction(Fraction const &other);
  Fraction &operator=(Fraction const &other);
  void set(int num, int den)
  {
    this->num = num;
    this->den = den;
    normalize();
  }
  // these functions are not inlined
  Fraction add(Fraction const &other);
  Fraction mul(Fraction const &other);
  // these functions are inlined
  int get_num() const { return this->num; }
  int get_den() const { return this->den; }
};