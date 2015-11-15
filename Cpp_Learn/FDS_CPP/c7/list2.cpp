#include <iostream.h>


class Element
{
public:
   int key;
   int other;
   int link;
   Element(){other = 0;};
};


void List2(Element *list, const int n, int first)
// Same function as @list1@ except that a second link field @linkb@ is not required
{
    for (int i = 1; i <= n-1; i++)
    // Find correct record to place into @i@th position.  The index of this record must
    // be @\(>=~i@, as records in positions
    // 1, 2, @...@, @i~-~1@ are already correctly positioned.
    {
       while (first < i) first = list[first].link;
       int q = list[first].link; // @list sub q@ is next record with largest key
       if (first != i)
       // interchange @list sub i@ and @ list sub first@ moving @list sub first@ to its
       // correct spot as @list sub first@ has @i@th smallest key. Also set link
       // from old position of @list sub j@ to new one
       {
	   Element t = list[i];
	   list[i] = list[first]; list[first] = t; list[i].link = first;
       }
       first = q;
       for (int o = 1; o <= n; o++) cout << list[o].key << ", " << list[o].link << endl;
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

List2(b, 10, 4);
}