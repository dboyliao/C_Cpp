#include <iostream.h>


class Element
{
public:
   int key[3];
   int other;
   int link;
   Element(){other = 0;};
};

const int radix = 10;


void RadixSort(Element *list, const int d, const int n)
// Records @list~=~(list[1],~... ,~list[n])@ are sorted on the keys @key[0],^... ,^key[d-1]@.
// The range of each key is @0~\(<=~key[i]~<~@\fIradix\fR.  \fIradix\fR is a constant.
// Sorting within a key is done using a bin sort.
{
   int e[radix], f[radix]; // queue pointers
   for (int i = 1; i <= n; i++) list[i].link = i+1; // link into a chain starting at @current@
   list[n].link = 0; int current = 1;
   for (i = d-1; i >= 0; i--) // sort on key @key[i]@
   {
      for (int j = 0; j < radix; j++) f[j] = 0; // initialize bins to empty queues
      for (;current; current = list[current].link) { // put records into queues
	 int k = list[current].key[i];
	 if (f[k] == 0) f[k] = current;
	 else list[e[k]].link = current;
	 e[k] = current;
      }

      for (j = 0; f[j] == 0; j++); // find first nonempty queue
      current = f[j]; int last = e[j];

      for (int k = j+1; k < radix; k++) // concatenate remaining queues
	  if (f[k]) {
	      list[last].link = f[k];
	      last = e[k];
	  }
      list[last].link = 0;

      for (int q = current; q; q= list[q].link)
      cout << list[q].key[0] << list[q].key[1] << list[q].key[2] << " , "; cout << endl;

   }
}


void main()
{

Element *b = new Element[11];
Element e;
e.key[0] = 1; e.key[1] = 7; e.key[2] = 9; b[1] = e;
e.key[0] = 2; e.key[1] = 0; e.key[2] = 8;b[2] = e;
e.key[0] = 3; e.key[1] = 0; e.key[2] = 6;b[3] = e;
e.key[0] = 0; e.key[1] = 9; e.key[2] = 3;b[4] = e;
e.key[0] = 8; e.key[1] = 5; e.key[2] = 9;b[5] = e;
e.key[0] = 9; e.key[1] = 8; e.key[2] = 4;b[6] = e;
e.key[0] = 0; e.key[1] = 5; e.key[2] = 5;b[7] = e;
e.key[0] = 0; e.key[1] = 0; e.key[2] = 9;b[8] = e;
e.key[0] = 2; e.key[1] = 7; e.key[2] = 1;b[9] = e;
e.key[0] = 0; e.key[1] = 3; e.key[2] = 3;b[10] = e;

RadixSort(b, 3, 10);
}