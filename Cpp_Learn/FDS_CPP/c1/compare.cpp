#include <iostream.h>

char compare (int x, int y)
{
  if (x > y) return '>';
  else if (x < y) return '<';
       else return '=';
}

void main()
{
char temp;
temp = compare (3, 5); cout << temp << "\n";
temp = compare (5, 3); cout << temp << "\n";
temp = compare (3, 3); cout << temp << "\n";
}
