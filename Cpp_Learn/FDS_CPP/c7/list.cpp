#include <iostream.h>


class Element
{
public:
   int key;
   int other;
   int link;
   int linkb;
   Element(){other = 0;};
};


void List1(Element *list, const int n, int first)
// Rearrange the sorted chain @first@ so that the records @list[1],@ @...@, @list[n]@
// are in sorted order. Each record has an additional link field @linkb@.
{
    int prev = 0;
    for (int current = first; current; current = list[current].link) { // convert @first@ into a doubly linked list
	list[current].linkb = prev;
	prev = current;
    }

    for (int o = 1; o <= n ; o++) cout << list[o].key << ", " << list[o].link << ", " << list[o].linkb << endl;
    cout << endl;

    for (int i = 1; i <= n-1 ; i++) // move @list sub first@ to position @i@ while
    {			    // maintaining the list
	if (first != i) {
	    if (list[i].link) list[list[i].link].linkb = first;
	    list[list[i].linkb].link = first;
	    Element a = list[first]; list[first] = list[i]; list[i] = a;
	}
	first = list[i].link;

	for (o = 1; o <= n; o++) cout << list[o].key << ", " << list[o].link << ", " << list[o].linkb << endl;
	cout << endl;
    }
}


void main()
{

Element *b = new Element[11];
Element e;
e.key = 26; e.link = 9; b[1] = e;
e.key = 5; e.link = 6; b[2] = e;
e.key = 77; e.link = 0; b[3] = e;
e.key = 1; e.link = 2; b[4] = e;
e.key = 61; e.link = 3; b[5] = e;
e.key = 11; e.link = 8; b[6] = e;
e.key = 59; e.link = 5; b[7] = e;
e.key = 15; e.link = 10; b[8] = e;
e.key = 48; e.link = 7; b[9] = e;
e.key = 19; e.link = 1; b[10] = e;

List1(b, 10, 4);
}