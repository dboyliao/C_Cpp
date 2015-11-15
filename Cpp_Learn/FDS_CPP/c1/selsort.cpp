#include <iostream.h>

void sort (int *a, int n)
// sort the n integers a[0] to a[n-1] into nondecreasing order
{
   for ( int i = 0; i < n; i++)
   {
      int j = i;
      // find smallest KeyType in a[i] to a[n-1]
      for (int k = i+1; k < n; k++)
	 if (a[k] < a[j]) j = k;
      int temp = a[i]; a[i] = a[j]; a[j] = temp;
   }
}

void main()
{

int array[100], i;
array[0] = 4; array[1] = 3; array[2] = 2; array[3] = 1; array[4] = -2;
sort(array, 5);

for (i= 0; i < 4; i++)
{
cout << array[i] << ", ";
}
cout << array[4] << "\n";
}
