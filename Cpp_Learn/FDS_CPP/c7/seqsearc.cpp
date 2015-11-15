// Seems to be a bug in the Borland C++ compiler

#include <iostream.h>

enum Boolean {FALSE, TRUE};


class Element
{
public:
   int getKey() const {return key;};
   int other() {return Other;};
   void setKey(int k) { key = k;};
   void setOther(int o) { Other = o;}
   Element(){Other = 0;};
private:
   int key;
   int Other;
};


int SeqSearch (Element *f, const int n, const int k)
// Search a list @f@ with key values @"f"^[1]^.^key@, @...@, @"f"^[n]^.^key@.  Return @i@
// such that @"f"^^[i]^.^key~==~k@.  If there is no such record, return 0.
{
   int i = n;
   f[0].setKey(k);
   while (f[i].getKey() != k) i--;
   return i;
}


void Verify1(Element* F1, Element* F2, const int n, const int m)
// Compare two unordered lists F1 and F2 of size @n@ and @m@, respectively.
{
    Boolean *marked = new Boolean[m];
    for (int i = 1; i <= m; i++) marked[i] = FALSE;
    for (i = 1; i <= n; i++) {
	int j = SeqSearch(F2, m, F1[i].getKey());
	if (j == 0) cout << F1[i].getKey() << " not in F2 " << endl; // satisfies (1)
	else {
	    if (F1[i].other() != F2[j].other()) // satisfies (3)
		 cout << "Discrepancy in " << F1[i].getKey() << ": "
		      << F1[i].other() << " and " << F2[j].other() << endl;
	    marked[j] = TRUE; // mark the record in F2[j] as being seen
	}
    }
    for (i = 1; i <= m; i++)
	if (! marked[i]) cout << F2[i].getKey() << " not in F1. " << endl; // satisfies (2)
    delete [] marked;
}

void main()
{
Element *b = new Element[11];
Element e;
e.setKey(2); b[1] = e;
e.setKey(4); b[2] = e;
e.setKey(5); b[3] = e;
e.setKey(7); b[4] = e;
e.setKey(10); b[5] = e;
e.setKey(12); b[6] = e;
e.setKey(14); b[7] = e;
e.setKey(15); b[8] = e;
e.setKey(17); b[9] = e;
e.setKey(25); b[10] = e;
e.setKey(10);
cout << SeqSearch(b, 10, 10) << "\n";
e.setKey(11);
cout << SeqSearch(b, 11, 10) << "\n";

Element *c = new Element[10];
e.setKey(2); c[1] = e;
e.setKey(4); c[2] = e;
e.setKey(5); c[3] = e;
e.setKey(6); c[4] = e;
e.setKey(11); c[5] = e;
e.setKey(12); c[6] = e;
e.setKey(14); c[7] = e;
e.setKey(16); c[8] = e;
e.setKey(17); c[9] = e;
const int nine = 9;
const int ten = 10;
Verify1(b, c, ten, nine);
}