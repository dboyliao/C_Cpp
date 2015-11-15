#include <iostream.h>

int count = 0;

float sum (float *a, const int n)
{
  float s = 0;
  count++; // count is global
  for (int i = 0; i < n; i++) {
    count++;  // for for
    s += a[i];
    count++; // for assignment
  }
  count++; // for last time of for
  count++; // for return
  return s;
}

// Prog 1.24
void csum (float *a, const int n)
{
   for (int i = 0; i < n; i++) count+=2;
   count+=3;
}

float rsum (float *a, const int n)
{
   count++; // for if conditional
   if (n <= 0) {
      count++;  // for return
      return 0;
   }
   else {
      count++;  // for return
      return (rsum(a, n-1) + a[n-1]);
   }
}

void main()
{
 float b[10];
 b[0] = 1.3; b[1] = 2.43; b[2] = 3.1; b[3] = 4;

 cout << count << endl;
 cout << sum(b,4) << endl;
 cout <<  " count = " << count << endl;
 csum(b,4);
 cout <<  "count = " << count << endl;
 cout << rsum(b,4);
 cout << "count = " << count << endl;
}
