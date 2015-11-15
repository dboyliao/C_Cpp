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

void InterChange(Element* list, const int a, const int b)
{
    Element t = list[a]; list[a] = list[b]; list[b] = t;
}

void QuickSort(Element *list, const int left, const int right)
{
    if (left < right) {
	for (int m = 1; m <= 10; m++) cout << list[m].getKey() << " , "; cout << endl;
	int i = left,
	    j = right + 1,
	    pivot = list[left].getKey();
	do {
	   do i++; while (list[i].getKey() < pivot);
	   do j--; while (list[j].getKey() > pivot);
	   if (i < j) InterChange(list, i, j);
	} while (i < j);

	InterChange(list, left, j);
	QuickSort(list, left, j-1);
	QuickSort(list, j+1, right);
    }
}

void main()
{




Element *b = new Element[11];
Element e;
e.setKey(26);b[1] = e;
e.setKey(5);b[2] = e;
e.setKey(37);b[3] = e;
e.setKey(1);b[4] = e;
e.setKey(61);b[5] = e;
e.setKey(11);b[6] = e;
e.setKey(59);b[7] = e;
e.setKey(15);b[8] = e;
e.setKey(48);b[9] = e;
e.setKey(19);b[10] = e;
e.setKey(1000); b[11] = e;

QuickSort(b, 1, 10);
for (int m = 1; m <= 10; m++) cout << b[m].getKey() << " , "; cout << endl;
}