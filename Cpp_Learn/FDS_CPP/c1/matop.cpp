#include <iostream.h>

void transpose (float (*a)[7], int n)
{
  for (int i = 0; i < n-1; i++)
     for (int j = i+1; j < n; j++)
     {
	float t = a[i][j]; a[i][j] = a[j][i]; a[j][i] = t;
     }
} // end of transpose


void mult (float (*a)[7], float (*b)[7], float (*c)[7], int n)
{
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
	 c[i][j] = 0;
	 for (int k = 0; k < n; k++)
	     c[i][j] += a[i][k]*b[k][j];
      }
} // end of mult

void prod (float (*a)[7], float (*b)[7], float (*c)[7], int m, int n, int p)
{
  for (int i = 0; i < m; i++)
     for (int j = 0; j < p; j++)
     {
	c[i][j] = 0;
	for (int k = 0; k < n; k++)
	   c[i][j] += a[i][k]*b[k][j];
     }
} // end of prod

void main()
{
  float a[8][7], b[8][7], c[8][7];
  a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
  a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
  a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

  b[0][0] = 1; b[0][1] = 1; b[0][2] = 1;
  b[1][0] = 1; b[1][1] = 1; b[1][2] = 1;
  b[2][0] = 1; b[2][1] = 1; b[2][2] = 1;

  transpose(a,3);
  cout << a[0][0] << "," << a[0][1] << "," << a[0][2] << endl;
  cout << a[1][0] << "," << a[1][1] << "," << a[1][2] << endl;
  cout << a[2][0] << "," << a[2][1] << "," << a[2][2] << endl;

  mult(a,b,c,3);
  cout << c[0][0] << "," << c[0][1] << "," << c[0][2] << endl;
  cout << c[1][0] << "," << c[1][1] << "," << c[1][2] << endl;
  cout << c[2][0] << "," << c[2][1] << "," << c[2][2] << endl;

  prod(a,b,c,3,3,3);
  cout << c[0][0] << "," << c[0][1] << "," << c[0][2] << endl;
  cout << c[1][0] << "," << c[1][1] << "," << c[1][2] << endl;
  cout << c[2][0] << "," << c[2][1] << "," << c[2][2] << endl;
}
