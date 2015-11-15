#include <iostream.h>

const int MININT = -100;

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

void insert(const Element& e, Element *list, int i)
// Insert element @e@ with key @e^.^key@ into the ordered sequence @list[0],~ ...@, @list[i]@
// such that the resulting sequence is also ordered. Assume that @e^.^key~\(>=~list[0]^.^key@.
{
    while (e.getKey() < list[i].getKey())
    {
	list[i+1] = list[i];
	i--;
    }
    list[i+1] = e;
}


void InsertionSort(Element *list, const int n)
// Sort @list@ in nondecreasing order of @key@
{
    list[0].setKey(MININT);
    for (int j = 2; j <= n; j++)
	insert(list[j], list, j-1);
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

InsertionSort(b, 10);
for (int i = 0; i <= 10; i++) cout << b[i].getKey() << " , ";
}