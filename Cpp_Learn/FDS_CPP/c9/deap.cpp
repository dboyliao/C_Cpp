#include <iostream.h>

enum Boolean { FALSE, TRUE};

template <class KeyType>
class Element {
public:
    KeyType key;
};

template <class KeyType>
class DEPQ {
public:

//   virtual Element<KeyType>* DeleteMin(Element<KeyType>&) = 0;
//   virtual Element<KeyType>* DeleteMax(Element<KeyType>&) = 0;
   virtual void Insert(const Element<KeyType>&) = 0;

   virtual void display() = 0;
//   virtual ~DEPQ() = 0;
};

// DEPQ::~DEPQ() {}

const int DefaultHeapSize = 1000;

int log2floor(int p) {
   int product = 1;
   int i = 0;
   while (product <= p) {
      product *= 2;
      i++;
   }
   i--;
   return i;
}

int exp2(int p) {
   int product = 1;
   for (int i = 1; i <= p; i++)
      product *= 2;
   return (product);
}

template <class KeyType>
class Deap : public DEPQ<KeyType> {
public:
   Deap (const int);
// ~Deap() {};
   void Insert(const Element<KeyType>& x);
   Element<KeyType>* DeleteMin(Element<KeyType>&);
   Element<KeyType>* DeleteMax(Element<KeyType>&);
   void display();
private:
   Element<KeyType> *d;
   int n;                        // current size of Deap
   int MaxSize;                  // Maximum allowable size of Deap
   void DeapEmpty() { cout << "Heap Empty" << "\n";};
   void DeapFull()  { cout << "Heap Full" << "\n";};
   Boolean MaxHeap(int i);
   int MinPartner(int i) { return (i - exp2(log2floor(i) - 1));};
   int MaxPartner(int i) { return (i + exp2(log2floor(i) - 1))/2;};
   void MinInsert(int i, const Element<KeyType>& x);
   void MaxInsert(int i, const Element<KeyType>& x);
};

template <class KeyType>
Deap<KeyType>::Deap (const int sz = DefaultHeapSize)
: MaxSize(sz), n(0)
{
      d = new Element<KeyType> [MaxSize + 2];
}

template <class KeyType>
Boolean Deap<KeyType>::MaxHeap(int i) {
   int l1 = log2floor(i);
   int l2 = log2floor(MinPartner(i));
   if (l1 == l2) return (TRUE);
   else return(FALSE);
}

template <class KeyType>
void Deap<KeyType>::MinInsert(int i, const Element<KeyType>& x) {
   Boolean NotDone = TRUE;
   while (NotDone) {
      if (i == 2) NotDone = FALSE;
      else if (x.key >= d[i/2].key) NotDone = FALSE;
      else {
	 d[i] = d[i/2];
	 i = i/2;
      };
   };
   d[i] = x;
}

template <class KeyType>
void Deap<KeyType>::MaxInsert(int i, const Element<KeyType>& x) {
   Boolean NotDone = TRUE;
   while (NotDone) {
      if (i == 3) NotDone = FALSE;
      else if (x.key <= d[i/2].key) NotDone = FALSE;
      else {
	 d[i] = d[i/2];
	 i = i/2;
      };
   };
   d[i] = x;
}

template <class KeyType>
void Deap<KeyType>::display() {
   int i;
   for (i=2; i <= (n+1); i++) cout << i << ": " << d[i].key << " ";
   cout << "\n";
}

template <class KeyType>
void Deap<KeyType>::Insert(const Element<KeyType>& x) {
   int i;
   if (n == MaxSize) {DeapFull(); return;}
   n++;
   if (n == 1) { d[2] = x; return;}
   int p = n + 1;
   switch (MaxHeap(p)) {
      case TRUE:
	 i = MinPartner(p);
	 if (x.key < d[i].key) {
	    d[p] = d[i];
	    MinInsert(i,x);
	 }
	 else MaxInsert(p,x);
	 break;
      case FALSE:
	 i = MaxPartner(p);
	 if (x.key > d[i].key) {
	    d[p] = d[i];
	    MaxInsert(i,x);
	 }
	 else MinInsert(p,x);
   }
}

/* Element Deap::DeleteMin()
   {
    }
*/

main()
{
   Deap<int> m(20);
   Element<int> a, b, c, d, e, f, g, h, i, j, k, l;
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

/*
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
cout << m.DeapDeleteMin().key << "\n";
m.display();
*/

}
