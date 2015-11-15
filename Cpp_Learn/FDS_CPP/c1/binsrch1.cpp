#include <iostream.h>

char compare (int x, int y)
{
  if (x > y) return '>';
  else if (x < y) return '<';
       else return '=';
}

int BinarySearch (int *a, int x, const int n)
// Search the sorted array a[0], ..., a[n-1] for x
{
 for (int left = 0,  right = n - 1; left <= right;) { // while more elements
   int middle = (left + right)/2;
   switch (compare (x, a[middle])){
      case '>':	left = middle + 1; break; // x > a[middle]
      case '<': right = middle - 1; break; // x < a[middle]
      case '=': return middle; // x == a[middle]
   } // end of switch
 } // end of for
 return -1; // not found
} // end of BinarySearch

void main()
{
   int b[10];
   b[0] = 2; b[1] = 4; b[2] = 5; b[3] = 7; b[4] = 10;
   b[5] = 12; b[6] = 14; b[7] = 15; b[8] = 17; b[9] = 25;

   cout << BinarySearch(b,2,10) << "in position 0\n";
   cout << BinarySearch(b,4,10) << "in position 1\n";
   cout << BinarySearch(b,5,10) << "in position 2\n";
   cout << BinarySearch(b,7,10) << "in position 3\n";
   cout << BinarySearch(b,10,10) << "in position 4\n";
   cout << BinarySearch(b,12,10) << "in position 5\n";
   cout << BinarySearch(b,14,10) << "in position 6\n";
   cout << BinarySearch(b,15,10) << "in position 7\n";
   cout << BinarySearch(b,17,10) << "in position 8\n";
   cout << BinarySearch(b,25,10) << "in position 9\n";
   cout << BinarySearch(b,-1,10) << "in position -1\n";
   cout << BinarySearch(b,9,10) << "in position -1\n";
   cout << BinarySearch(b,27,10) << "in position -1\n";
}
