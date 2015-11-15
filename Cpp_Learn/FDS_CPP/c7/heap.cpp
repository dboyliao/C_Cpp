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

void adjust(Element *tree, const int root, const int n)
// Adjust the binary tree with root @root@ to satisfy the heap property. The left and right
// subtrees of @root@ already satisfy the heap property.  No node has index greater than @n@.
{
   Element e = tree[root];
   int k = e.getKey();
   for (int j = 2*root; j <= n; j *= 2)
   { // first find max of left and right child
       if (j < n) if (tree[j].getKey() < tree[j+1].getKey()) j++;
       // compare max child with @k@. If @k@ is max, then done
       if (k >= tree[j].getKey()) break;
       tree[j/2] = tree[j]; // move @j@th record up the tree
   }
   tree[j/2] = e;
}


void HeapSort(Element *list, const int n)
// The list @list~=~(list[1], ... ,~list[n])@ is sorted into nondecreasing order of the field @key@.
{
  for (int i = n/2; i >= 1; i--) // convert @list@ into a heap
      adjust(list, i, n);
  for (i = n-1; i >= 1; i--)  // sort @list@
  {
     Element t = list[i+1]; // interchange @list sub 1@ and @list sub i+1@
     list[i+1] = list[1];
     list[1] = t;
     adjust(list, 1, i);  // recreate heap
  }
}

void main()
{

Element *b = new Element[11];
Element e;
e.setKey(26);b[1] = e;
e.setKey(5);b[2] = e;
e.setKey(77);b[3] = e;
e.setKey(1);b[4] = e;
e.setKey(61);b[5] = e;
e.setKey(11);b[6] = e;
e.setKey(59);b[7] = e;
e.setKey(15);b[8] = e;
e.setKey(48);b[9] = e;
e.setKey(19);b[10] = e;
e.setKey(1000); b[11] = e;


HeapSort(b, 10);
for (int m = 1; m <= 10; m++) cout << b[m].getKey() << " , "; cout << endl;
}