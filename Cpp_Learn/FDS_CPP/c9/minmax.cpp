#include <iostream.h>

enum Boolean { FALSE, TRUE};

template <class Type>
class Element {
public:
    Type key;
};

template <class KeyType>
class DEPQ {
public:

   virtual Element<KeyType>* DeleteMin(Element<KeyType>&) = 0;
//   virtual Element DeleteMax() = 0;
   virtual void Insert(const Element<KeyType>&) = 0;

   virtual void display() = 0;
//   virtual ~DEPQ() = 0;
};

// DEPQ::~DEPQ() {}

const int DefaultHeapSize = 1000;
const int MIN = 0;
const int MAX = 1;

template <class KeyType>
class MinMaxHeap : public DEPQ<KeyType> {
public:
   MinMaxHeap(const int);
    //   ~MinMaxHeap() { delete [] h;};
   void Insert(const Element<KeyType>& x);
   Element<KeyType>* DeleteMin(Element<KeyType>&);
   Element<KeyType>* DeleteMax(Element<KeyType>&);
   void display();
private:
   Element<KeyType> *h;
   int n; // current size of MinMaxHeap
   int MaxSize; // Maximum allowable size of MinMaxHeap
   void VerifyMax(int i, const Element<KeyType>& x);
   void VerifyMin(int i, const Element<KeyType>& x);
   void MinMaxEmpty(){ cout << "Heap Empty" << "\n";};
   void MinMaxFull(){ cout << "Heap Full";};
   int MinChildGrandChild(int i);
};

template<class KeyType>
MinMaxHeap<KeyType>::MinMaxHeap (const int sz = DefaultHeapSize)
: MaxSize(sz), n(0)
{
   h = new Element<KeyType> [MaxSize + 1]; // Don't want to use h[0]
}

int level(int p)
{
int product = 1;
int i = 0;
   while (product <= p)
   {
      product *= 2;
      i++;
   }
   i--;
   return (i % 2);
};

template <class KeyType>
void MinMaxHeap<KeyType>::display()
{
int i;
for(i=1; i <= n; i++) cout << i << ": " << h[i].key << " ";
cout << "\n";
}

template <class KeyType>
int MinMaxHeap<KeyType>::MinChildGrandChild(int i)
{
int min;
if (2*i <= n) min = 2 * i;
if (2*i + 1 <= n)
   if (h[2*i + 1].key < h[min].key) min = 2 * i + 1;
if (4*i <= n)
   if (h[4*i].key < h[min].key) min = 4 * i;
if (4*i +1 <= n)
   if (h[4*i + 1].key < h[min].key) min = 4 * i + 1;
if (4*i +2 <= n)
   if (h[4*i + 2].key < h[min].key) min = 4 * i + 2;
if (4*i +3 <= n)
   if (h[4*i + 3].key < h[min].key) min = 4 * i + 3;
return min;
}

template <class KeyType>
void MinMaxHeap<KeyType>::VerifyMax(int i, const Element<KeyType>& x)
{
for (int gp = i/4; gp && (x.key > h[gp].key); gp /=4 )
{
     h[i] = h[gp];
     i = gp;
}
h[i] = x;
}

template <class KeyType>
void MinMaxHeap<KeyType>::VerifyMin(int i, const Element<KeyType>& x)
{
for (int gp = i/4; gp && (x.key < h[gp].key); gp /=4 )
{
     h[i] = h[gp];
     i = gp;
}
h[i] = x;
}

template <class KeyType>
void MinMaxHeap<KeyType>::Insert(const Element<KeyType>& x)
{
   if (n == MaxSize) {MinMaxFull(); return;}   // I'm assuming that MinMaxFull aborts
   n++;
   int p = n/2;
   if (!p) {  h[1] = x; return; }
   switch (level(p)) {
     case MIN: if (x.key < h[p].key) {
				     h[n] = h[p];
				     VerifyMin(p,x);
	       }
	       else
	       VerifyMax(n,x);
	       break;
     case MAX: if (x.key > h[p].key) {
				     h[n] = h[p];
				     VerifyMax(p,x);
	       }
	       else            VerifyMin(n,x);
     }
}

template <class KeyType>
Element<KeyType>* MinMaxHeap<KeyType>::DeleteMin(Element<KeyType>& y)
{
   if (!n) {MinMaxEmpty(); return 0;}     //Assume that this aborts the Deletemin op
   y = h[1];
   Element<KeyType> x = h[n--];

   int i = 1, j = n/2;

    while (i<=j) {
       int k = MinChildGrandChild(i);
       if (x.key <= h[k].key)
	  break;
       else {
	  h[i] = h[k];
	  if (k <= 2*i + 1)
	     break;
	  else {
	     int p = k/2;
	     if (x.key > h[p].key) {
		Element<KeyType> t = h[p]; h[p] = x; x = t;
	     }
	  }
	  i = k;
       }
   }
   h[i] = x;
   return &y;
}


main()
{
MinMaxHeap<int> m(20);
Element<int> a, b, c, d, e, f, g, h, i, j, k, l, temp;
a.key = 5; b.key = 3; c.key = 11; d.key = 3; e.key = 15;
f.key = 2; g.key = 8; h.key = 22; i.key = 20; j.key = 9;


m.Insert(a);
m.Insert(b);
m.Insert(c);
m.Insert(d);
m.Insert(e);
m.Insert(f);
m.Insert(g);
m.Insert(h);
m.Insert(i);
m.Insert(j);

m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
cout << m.DeleteMin(temp)->key << endl;
m.display();
}
