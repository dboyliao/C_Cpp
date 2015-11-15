#include <iostream.h>
#include <stdlib.h>

template <class KeyType>
class Element
{
public:
   KeyType key;
   int other;
   Element(){other = 0;};
};

template <class KeyType>
void permute(Element<KeyType> *a, int n)
{
    for (int i = n; i >=2; i--)
    {
	int j = rand() % i + 1;  cout << j << endl;
	Element<KeyType> k = a[j]; a[j] = a[i]; a[i] = k;
    }
}

void main()
{

Element<int> *b = new Element<int>[9];

Element<int> e;
e.key = 35;  b[1] = e;
e.key = 14;  b[2] = e;
e.key = 12;  b[3] = e;
e.key = 42;  b[4] = e;
e.key = 26;  b[5] = e;
e.key = 50;  b[6] = e;
e.key = 31;  b[7] = e;
e.key = 18;  b[8] = e;

permute(b, 8);
for (int i = 1; i < 9; i++) cout << b[i].key << ", " ;
cout << endl;
}