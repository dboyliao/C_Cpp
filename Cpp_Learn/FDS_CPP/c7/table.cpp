#include <iostream.h>


class Element
{
public:
   int key;
   int other;
   Element(){other = 0;};
};


void table(Element *list, const int n, int *t)
// Rearrange @list[1],~... ,~list[n]@ to correspond to the \c
// sequence @list[t[1]],~... ,~list[t[n]],~n~\(>=~1@.
{
    for (int i = 1; i <= n-1; i++)
    {
	if (t[i] != i)  { // there is a non-trivial cycle starting at @i@
	    Element p = list[i]; int j = i;
	    do {
		int k = t[j]; list[j] = list[k]; t[j] = j;
		j = k;
	    } while (t[j] != i);
	    list[j] = p; // @j@ is position for record @p@
	    t[j] = j;
	}
	for (int o = 1; o <= n; o++) cout << list[o].key << ", " << t[o] << endl;
	cout << endl;
    }
}

void main()
{

Element *b = new Element[9];
int *t = new int[9];

Element e;
e.key = 35;  b[1] = e; t[1] = 3;
e.key = 14;  b[2] = e; t[2] = 2;
e.key = 12;  b[3] = e; t[3] = 8;
e.key = 42;  b[4] = e; t[4] = 5;
e.key = 26;  b[5] = e; t[5] = 7;
e.key = 50;  b[6] = e; t[6] = 1;
e.key = 31;  b[7] = e; t[7] = 4;
e.key = 18;  b[8] = e; t[8] = 6;


table(b, 8, t);
}