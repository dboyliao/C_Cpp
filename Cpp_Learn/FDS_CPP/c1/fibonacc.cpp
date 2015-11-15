#include <iostream.h>

void fibonacci (int n)
// compute the Fibonacci number F sub n
{
   if (n <= 1)  cout << n << endl; // F sub 0 = 0 and F sub 1 = 1
   else { // compute F sub n
      int fn; int fnm2 = 0; int fnm1 = 1;
      for (int i = 2; i<=n; i++)
      {
	 fn = fnm1 + fnm2;
	 fnm2 = fnm1;
	 fnm1 = fn;
      } // end of for
      cout << fn << endl;
   } // end of else
} // end of fibonacci


void main()
{
  int n;
  cout << "Input n " << endl;
  cin >> n;
  cout << "The Fibonacci Number corresp to"  << n << " is ";
  fibonacci(n);
}
