#include <iostream.h>

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

void PrintRest(Element* F, int current, const int last, int list)
{
   if (list == 1)
      for (int i = current; i <= last; i++)
	  cout << F[i].getKey() << " not in @F2@" << endl;
   else // list == 2
      for (int j = current; j <= last; j++)
	  cout << F[j].getKey() << " not in @F1@" << endl;
}

char compare (int i, int j)
{
if (i < j) return '<';
if (i > j) return '>';
else return '=';
}


void Verify2(Element* F1, Element* F2, const int n, const int m)
// Same task as @"Verify"2@. However this time sort @F1@ and @F2@ so that the keys are in
// increasing order in each list. We assume that the keys in each list are identical
{
    // sort(F1, n);
    // sort(F2, m);
    int i = 1, j = 1;
    while ( ( i <= n) && (j <= m) )
	switch (compare (F1[i].getKey(), F2[j].getKey()))
	{
	   case '<': cout << F1[i].getKey() << " not in @F2@" << endl;
		     i++;
		     break;
	   case '=': if (F1[i].other() != F2[j].other()) cout << "Discrepancy in " << F1[i].getKey() << ": " << F1[i].other() << " and " << F2[j].other() << endl;
		     i++; j++;
		     break;
	   case '>': cout << F2[j].getKey() << " not in @F1@" << endl;
		     j++;
	}
    if (i <= n) PrintRest(F1, i, n, 1); // print records @i@ through @n@ of @F1@
    else if (j <= m) PrintRest(F2, j, m, 2); // print records @j@ through @m@ of @F2@
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

const int ten = 10, nine = 9;
Verify2(b, c, ten, nine);
}