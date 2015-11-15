#include <iostream.h>
#include <fstream.h>

enum Boolean { FALSE, TRUE};

template <class KeyType>
class Element {
public:
    KeyType key;
};

ofstream outFile("pat.out" , ios::out);

template <class KeyType> class Patricia; // forward declaration

template <class KeyType>
class PatNode {
friend class Patricia<KeyType>;
public:

private:
   Element<KeyType> data;
   PatNode<KeyType> *LeftChild, *RightChild;
   int BitNumber;

   void display(int i);
   void treeprint(int i);
};

template <class KeyType>
class Patricia {
public:
   Patricia(PatNode<KeyType> *init = 0) {root = init;};

   Boolean Insert(const Element<KeyType>&);
   Boolean Delete(const Element<KeyType>&);
   PatNode<KeyType>* Search(const Element<KeyType>&);

   void treeprint() { outFile <<  endl; root->treeprint(1); }

   void display() {outFile <<  endl;
		   if (root) root->display(1);
		   else outFile << "0\n";};
private:
   PatNode<KeyType> *root;
};


template <class KeyType>
void PatNode<KeyType>::display(int h)
{
   for (int i = 1; i <= h; i++) outFile << "    ";
   outFile << "Height " << h << " Data (in reverse) ";
   int p = data.key;
   for (int j = 1; j <= 8; j++) {
      outFile << p%2;
      p /=2;
   }
   outFile <<   endl;
   if (LeftChild)
      if (this->BitNumber < LeftChild->BitNumber) LeftChild->display(h+1);
   if (RightChild)
      if (this->BitNumber < RightChild->BitNumber) RightChild->display(h+1);
}

int Bit(int k, int j)
{
   for (int i = 1; i < j; i++) k /= 2;
   return k % 2;
}

template <class KeyType>
PatNode<KeyType>* Patricia<KeyType>::Search(const Element<KeyType>& x)
{
   if (!root) return 0;
   PatNode<KeyType> *y = root->LeftChild;
   for (PatNode<KeyType> *p = root; y->BitNumber > p->BitNumber;) {
      p = y;
      if (!Bit(x.key, y->BitNumber))  y = y->LeftChild;
      else y = y->RightChild;
   }
   return y;
}

template <class KeyType>
Boolean Patricia<KeyType>::Insert(const Element<KeyType>& x)
{
   if (!root) {
      root = new PatNode<KeyType>; root->BitNumber = 0; root->data = x;
      root->LeftChild = root; return TRUE;
   }
   int k = x.key;
   PatNode<KeyType> *y = Search(x);
   if (y->data.key == k) /*InsertionError */ return FALSE;
   for (int j = 1; Bit(k, j) == Bit(y->data.key, j); j++);

   PatNode<KeyType> *s = root->LeftChild, *p = root;
   while ((s->BitNumber > p->BitNumber) && (s->BitNumber < j)) {
      p = s;
      if (!(Bit(k, s->BitNumber))) s = s->LeftChild;
      else s = s->RightChild;
   }

   PatNode<KeyType> *z;
   z = new PatNode<KeyType>;
   z->data = x; z->BitNumber = j;
   if (!Bit(k,j))  {
      z->LeftChild = z; z->RightChild = s;
   }
   else {
      z->LeftChild = s; z->RightChild = z;
   }

   if (s == p->LeftChild) p->LeftChild = z;
   else p->RightChild = z;
   return TRUE;
}

main()
{
   Patricia<int> m;
   Element<int> a, b, c, d, e, f, g, h, i, j, k, l;
   a.key = 5; b.key = 3; c.key = 11; d.key = 3; e.key = 15;
   f.key = 2; g.key = 8; h.key = 22; i.key = 20; j.key = 9;

      if (!outFile) {
      cerr << "cannot open tree.out for output \n";
   }
   outFile <<  endl << m.Insert(a);
   outFile <<  endl << m.Insert(b);
   m.display();
   outFile <<  endl << m.Insert(c);
   m.display();
   outFile <<  endl << m.Insert(d);
   m.display();

   outFile <<  endl << m.Insert(e);
   m.display();
   outFile <<  endl << m.Insert(f);
   m.display();
   outFile <<  endl << m.Insert(g);
   m.display();
   outFile <<  endl << m.Insert(h);
   m.display();
   outFile <<  endl << m.Insert(i);
   m.display();
   outFile <<  endl << m.Insert(j);
   m.display();

   /*
   outFile <<  endl << m.Delete(j);
   m.display();
   outFile <<  endl << m.Delete(i);
   m.display();
   outFile <<  endl << m.Delete(b);
   m.display();
   outFile <<  endl << m.Delete(a);
   m.display();
   outFile <<  endl << m.Delete(d);
   m.display();
   outFile <<  endl << m.Delete(c);
   m.display();
   outFile <<  endl << m.Delete(f);
   m.display();
   outFile <<  endl << m.Delete(e);
   m.display();
   outFile <<  endl << m.Delete(g);
   m.display();
   outFile <<  endl << m.Delete(h);
   m.display();
   */
}