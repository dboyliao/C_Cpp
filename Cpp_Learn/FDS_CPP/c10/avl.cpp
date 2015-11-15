#include <iostream.h>
#include <fstream.h>

enum Boolean { FALSE, TRUE};

template <class KeyType>
class Element {
public:
    KeyType key;
};


ofstream outFile("avl.out" , ios::out);
template <class KeyType> class AVL;

template <class KeyType>
class AvlNode {
friend class AVL<KeyType>;
private:
   Element<KeyType> data;
   AvlNode *LeftChild, *RightChild;
   int bf;
   void display(int i);
   void treeprint(int i);
};

template <class KeyType>
class AVL {
public:
   AVL(AvlNode<KeyType> *init = 0) : root (init) {};

   Boolean Insert(const Element<KeyType>& x);
   Boolean Delete(const Element<KeyType>&);
   AvlNode<KeyType>* Search(const Element<KeyType>&);

   void treeprint();
   void display() {outFile <<  endl;
		   if (root) root->display(1);
		   else outFile << " 0\n";};
private:
   AvlNode<KeyType> *root;
};


template <class KeyType>
void AvlNode<KeyType>::display(int i)
{
   outFile << "Position " << i << ": data.key " << data.key << "(" << bf << ")\n";
   if (LeftChild) LeftChild->display(2*i);
   if (RightChild) RightChild->display(2*i + 1);
}

template <class KeyType>
void AvlNode<KeyType>::treeprint(int l)
{
   if (this) {
      RightChild->treeprint(l+1);
      for (int i = 1; i <= l; i++) outFile << "     ";
      outFile <<  data.key << "(" << bf << ")\n";
      LeftChild->treeprint(l+1);
   }
}

template <class KeyType>
void AvlNode<KeyType>::display(int i)
{
   outFile << "Position " << i << ": data.key " << data.key << "(" << bf << ")\n";
   if (LeftChild) LeftChild->display(2*i);
   if (RightChild) RightChild->display(2*i + 1);
}

template <class KeyType>
void AvlNode<KeyType>::treeprint(int l)
{
   if (this) {
      RightChild->treeprint(l+1);
      for (int i = 1; i <= l; i++) outFile << "     ";
      outFile <<  data.key << "(" << bf << ")\n";
      LeftChild->treeprint(l+1);
   }
}


template <class KeyType>
void AVL<KeyType>::treeprint()
{
   outFile <<  endl; root->treeprint(1);
}


template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::Search(const Element<KeyType>& x)
{
   AvlNode<KeyType> *t = root;
   Boolean NotFound = TRUE;
   while (t && NotFound)
      if (x.key == t->data.key) NotFound = FALSE;
      else if (x.key < t->data.key) t = t->LeftChild;
	   else t = t->RightChild;
   if (NotFound) return  0;
   else return t;
}

template <class KeyType>
Boolean AVL<KeyType>::Insert(const Element<KeyType>& x)
{
   AvlNode<KeyType>  *a, *b, *c, *f, *p, *q, *y, *clchild, *crchild;
   Boolean Found, Unbalanced;
   int d;

   if (!root) {
      y = new AvlNode<KeyType>;
      y->data = x;
      root = y;
      root->bf = 0;
      root->LeftChild = root->RightChild = 0;
      return TRUE;
   }

   f = 0; a = p = root; q = 0; Found = FALSE;
   while(p && !Found) {
      if (p->bf) { a = p; f = q;}
      if (x.key < p->data.key) { q = p; p = p->LeftChild;}
      else if (x.key > p->data.key) { q = p; p = p->RightChild;}
	   else {y = p; Found = TRUE;}
   }

   if (!Found) {
      y = new AvlNode<KeyType>; y->data = x; y->LeftChild = y->RightChild = 0;
      y->bf = 0;

      if (x.key < q->data.key) q->LeftChild = y;
      else q->RightChild = y;
      if (x.key > a->data.key) {
	 p = a->RightChild; b = p; d = -1;
      }
      else {
	 p = a->LeftChild; b = p; d = 1;
      }
      while (p!= y)
	 if (x.key > p->data.key) {
	    p->bf = -1; p = p->RightChild;
	 }
	 else {
	    p->bf = 1; p = p ->LeftChild;
	 }
      Unbalanced = TRUE;
      if ( !(a->bf) || !(a->bf + d) ) {
	 a->bf += d; Unbalanced = FALSE;
      }
      if (Unbalanced) {
	 if (d == 1) {
	    if (b->bf == 1) {
	       a->LeftChild = b->RightChild;
	       b->RightChild = a; a->bf = 0; b->bf = 0;
	    }
	    else {
	       c = b->RightChild;
	       b->RightChild = c->LeftChild;
	       a->LeftChild = c->RightChild;
	       c->LeftChild = b;
	       c->RightChild = a;
	       switch (c->bf) {
		  case 1:
		     a->bf = -1; b->bf = 0;
		     break;
		  case -1:
		     b->bf = 1; a->bf = 0;
		     break;
		  case 0:
		     b->bf = 0; a->bf = 0;
		     break;
	       }
	       c->bf = 0; b = c;
	    }
	 }
	 else {
	 }

	 if (!f) root = b;
	 else if (a == f->LeftChild) f->LeftChild = b;
	      else if (a == f->RightChild) f->RightChild = b;
      }
      return TRUE;
   }
   return FALSE;
}

main()
{
   AVL<int> m;
   Element<int> a, b, c, d, e, f, g, h, i, j, k, l;
   a.key = 5; b.key = 3; c.key = 11; d.key = 3; e.key = 15;
   f.key = 2; g.key = 8; h.key = 22; i.key = 20; j.key = 9;

      if (!outFile) {
      cerr << "cannot open tree.out for output \n";
   }
   outFile <<  endl << m.Insert(a);
   outFile <<  endl << m.Insert(b);
   m.treeprint();
   outFile <<  endl << m.Insert(c);
   m.treeprint();
   outFile <<  endl << m.Insert(d);
   m.treeprint();

   outFile <<  endl << m.Insert(e);
   m.treeprint();
   outFile <<  endl << m.Insert(f);
   m.treeprint();
   outFile <<  endl << m.Insert(g);
   m.treeprint();
   outFile <<  endl << m.Insert(h);
   m.treeprint();
   outFile <<  endl << m.Insert(i);
   m.treeprint();
   outFile <<  endl << m.Insert(j);
   m.treeprint();

   /*
   outFile <<  endl << m.Delete(j);
   m.treeprint();
   outFile <<  endl << m.Delete(i);
   m.treeprint();
   outFile <<  endl << m.Delete(b);
   m.treeprint();
   outFile <<  endl << m.Delete(a);
   m.treeprint();
   outFile <<  endl << m.Delete(d);
   m.treeprint();
   outFile <<  endl << m.Delete(c);
   m.treeprint();
   outFile <<  endl << m.Delete(f);
   m.treeprint();
   outFile <<  endl << m.Delete(e);
   m.treeprint();
   outFile <<  endl << m.Delete(g);
   m.treeprint();
   outFile <<  endl << m.Delete(h);
   m.treeprint();
   */
}