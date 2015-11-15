#include <iostream.h>

float sum (float *a, const int n)
{
 float s = 0;
 for (int i = 0; i < n; i++) s += a[i];
 return s;
}

float rsum (float *a, const int n)
{
 if (n <= 0) return 0;
 else return (rsum(a, n-1) + a[n-1]);
}

void main()
{
 float b[10];
 b[0] = 1.3;  b[1] = 2.43;  b[2] = 3.1; b[3] = 4;
 cout << sum(b,4) << endl;
 cout << rsum(b,4) << endl;
}
