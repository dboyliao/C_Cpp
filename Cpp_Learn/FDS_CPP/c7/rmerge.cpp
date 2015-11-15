#include <iostream.h>


class Element
{
public:
   int key;
   int other;
   int link;
   Element(){other = 0; link = 0;};
};


int ListMerge(Element *list, const int start1, const int start2)
// The sorted linked lists whose first elements are indexed by @start@1 and @start@2,
// respectively, are merged to obtain the sorted linked list. The index of the first element of the
// sorted list is returned. Integer links are used.
{
   int iResult = 0;
   for (int i1 = start1, i2 = start2; i1 && i2; )
       if (list[i1].key <= list[i2].key) {
	   list[iResult].link = i1;
	   iResult = i1; i1 = list[i1].link;
       }
       else {
	   list[iResult].link = i2;
	   iResult = i2; i2 = list[i2].link;
       }
   // move remainder
   if (i1 == 0) list[iResult].link = i2;
   else list[iResult].link = i1;
   return list[0].link;
}


int rMergeSort(Element *list, const int left, const int right)
// List @list~=~(list[left],~... ,~list[right])@ is to be sorted on the field @key@.
// @link@ is a link field in each record that is initially 0.
// @rMergeSort@ returns the index of the first element in the sorted chain.
// @list[0]@ is a record for intermediate results used only in @ListMerge@.
{
  if (left >= right) return left;
  int mid = (left + right)/2;
  return ListMerge( list, rMergeSort(list, left, mid), rMergeSort(list, mid+1, right));
}

void main()
{


/*

Element *b = new Element[11];
Element e;
e.key = 2;b[1] = e;
e.key = 4;b[5] = e;
e.key = 5;b[7] = e;
e.key = 7;b[8] = e;
e.key = 10;b[2] = e;
e.key = 12;b[6] = e;
e.key = 14;b[3] = e;
e.key = 15;b[4] = e;
e.key = 17;b[9] = e;
e.key = 25;b[10] = e;
e.key = 1000; b[11] = e;

QuickSort(b, 1, 10);
for (int i = 0; i <= 10; i++) cout << b[i].key << " , ";
*/

Element *b = new Element[11];
Element e;
e.key = 26;b[1] = e;
e.key = 5;b[2] = e;
e.key = 77;b[3] = e;
e.key = 1;b[4] = e;
e.key = 61;b[5] = e;
e.key = 11;b[6] = e;
e.key = 59;b[7] = e;
e.key = 15;b[8] = e;
e.key = 48;b[9] = e;
e.key = 19;b[10] = e;
e.key = 1000; b[11] = e;

int start = rMergeSort(b, 1, 10);
for (; start; start = b[start].link) cout << b[start].key << " , "; cout << endl;
}