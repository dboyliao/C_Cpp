#include <iostream.h>

int count =0;

void add (float (*a)[7], float (*b)[7], float (*c)[7], int m, int n)
{
 for (int i = 0; i < m; i++)
  for (int  j = 0; j < n; j++)
    c[i][j] = a[i][j] + b[i][j];
}


void cadd (float (*a)[7], float (*b)[7], float (*c)[7], int m, int n)
{
  for (int i = 0 ; i < m; i++)
  {
    count++; // for for i
    for (int j = 0; j < n; j++)
    {
       count++; // for for j
       c[i][j] = a[i][j] + b[i][j];
       count++; // for assignment
    }
    count++; // for last time of for j
  }
  count++; // for last time of for i
}

void conly (float (*a)[7], float (*b)[7], float (*c)[7], int m, int n)
{
  for (int i = 0; i < m; i++)
  {
     count+=2;
     for (int j = 0; j < n; j++)
	count += 2;
  }
  count++;
}

main()
{
   float a[8][7], b[8][7], c[8][7];
   a[0][0] = 1.3; a[0][1] = 2.43; a[0][2] = 3.1;
   a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;

   b[0][0] = -1.3; b[0][1] = -2.43; b[0][2] = -3.1;
   b[1][0] = -4; b[1][1] = -5; b[1][2] = -6;

   cadd(a,b,c,2,3);
   cout << c[0][0] << "," << c[0][1] << "," << c[0][2] << endl;
   cout << c[1][0] << "," << c[1][1] << "," << c[1][2] << endl;
   cout << count << endl;

   conly(a,b,c,2,3);
   cout << "count = " << count << endl;
}
