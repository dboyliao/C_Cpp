#include <iostream.h>
#include <fstream.h>

enum Boolean { FALSE, TRUE};

template <class KeyType>
class Element {
public:
    KeyType key;
};


ofstream outFile("two3.out" , ios::out);


template <class KeyType> class Two3; // forward declaration

template <class KeyType>
class Two3Node {
friend class Two3<KeyType>;
public:
private:
   Element<KeyType> dataL, dataR;
   Two3Node *LeftChild, *MiddleChild, *RightChild, *parent;

   void display(int i);
   void treeprint(int i);
   int compare(const Element<KeyType>&);
   void PutIn(const Element<KeyType>&, Two3Node<KeyType> *);
};


template <class KeyType>
class Two3 {
public:
   Two3(KeyType max, Two3Node<KeyType> *init = 0 )
   : MAXKEY(max), root(init) {};

   Boolean Insert(const Element<KeyType>&);
   Boolean Delete(const Element<KeyType>&);
   Two3Node<KeyType>* Search(const Element<KeyType>&);

   Two3Node<KeyType>* FindNode(const Element<KeyType>&);
   void NewRoot(const Element<KeyType>&, Two3Node<KeyType> *);
   Element<KeyType>& Split(Two3Node<KeyType>*, Element<KeyType>&, Two3Node<KeyType> *, Two3Node<KeyType> *);
   void treeprint() { outFile <<  endl; root->treeprint(1); }
   void display() {outFile <<  endl;
		   if (root) root->display(1);
		   else outFile << "0\n";};
private:
   Two3Node<KeyType> *root;
   KeyType MAXKEY;
};



template <class KeyType>
int Two3Node<KeyType>::compare(const Element<KeyType>& x)
{
   if (x.key < dataL.key) return 1;
   else if ((dataL.key < x.key) && (x.key < dataR.key)) return 2;
	else if (dataR.key < x.key) return 3;
	     else return 4;
}

template <class KeyType>
void Two3Node<KeyType>::PutIn(const Element<KeyType>& x, Two3Node<KeyType> *a)
{
   if (x.key < dataL.key) {
      dataR = dataL;
      RightChild = MiddleChild;
      dataL = x;
      MiddleChild = a;
      if (MiddleChild) MiddleChild->parent = this;
   }
   else {
      dataR = x;
      RightChild = a;
      if (RightChild) RightChild->parent = this;
   }
}

template <class KeyType>
Element<KeyType>& Two3<KeyType>::Split(Two3Node<KeyType>* p, Element<KeyType>& x, Two3Node<KeyType> *olda, Two3Node<KeyType> *newa)
{
   Element<KeyType> temp;
   if (x.key > p->dataR.key) {
      temp = p->dataR; p->dataR.key = MAXKEY;
      newa->dataL = x; newa->dataR.key = MAXKEY; x = temp;
      newa->LeftChild = p->RightChild; newa->MiddleChild = olda;
      if (newa->LeftChild) newa->LeftChild->parent = newa;
      if (newa->MiddleChild) newa->MiddleChild->parent = newa;
      p->RightChild = 0; newa->RightChild = 0;
      return x;
   }
   else {
      newa->dataL = p->dataR; newa->dataR.key = MAXKEY; newa->RightChild = 0;
      newa->MiddleChild = p->RightChild; p->RightChild = 0; p->dataR.key = MAXKEY;
      if (newa->MiddleChild) newa->MiddleChild->parent = newa;
      if (x.key > p->dataL.key) {
	 newa->LeftChild = olda;
	 if (newa->LeftChild) newa->LeftChild->parent = newa;
	 return x;
      }
      else {
	 newa->LeftChild = p->MiddleChild;
	 if (newa->LeftChild) newa->LeftChild->parent = newa;
	 p->MiddleChild = olda;
	 if(p->MiddleChild) p->MiddleChild->parent = p;
	 temp = p->dataL;
	 p->dataL = x;
	 x = temp;
	 return x;
      }
   }
}

template <class KeyType>
void Two3Node<KeyType>::display(int h)
{
   for (int i = 1; i <= h; i++) outFile << "    ";
   outFile << "Height " << h << " dataL " << dataL.key << " dataR " << dataR.key <<  endl;
   if (LeftChild) LeftChild->display(h+1);
   if (MiddleChild) MiddleChild->display(h+1);
   if (RightChild) RightChild->display(h+1);
}

/*
void Two3Node::treeprint(int l)
{
   if (this) {
      RightChild->treeprint(l+1);
      for (int i = 1; i <= l; i++) outFile << "     ";
      outFile <<  data.key << "(" << bf << ")\n";
      LeftChild->treeprint(l+1);
   }
}
*/


template <class KeyType>
Two3Node<KeyType>* Two3<KeyType>::Search(const Element<KeyType>& x)
{
   for (Two3Node<KeyType> *p = root; p;)
      switch(p->compare(x))
      {
	 case 1: p = p->LeftChild; break;
	 case 2: p = p->MiddleChild; break;
	 case 3: p = p->RightChild; break;
	 case 4: return p;
      }
   return 0;
}

template <class KeyType>
void Two3<KeyType>::NewRoot(const Element<KeyType>& x, Two3Node<KeyType> *a)
{
   Two3Node<KeyType> *newroot = new Two3Node<KeyType>;
   newroot->LeftChild = root;
   newroot->dataL = x;
   newroot->MiddleChild = a;
   newroot->dataR.key = MAXKEY;
   newroot->RightChild = 0;
   newroot->parent = 0;
   if (root) root->parent = newroot;
   if (a) a->parent = newroot;
   root = newroot;
}

template <class KeyType>
Two3Node<KeyType>* Two3<KeyType>::FindNode(const Element<KeyType>& x)
{
   Two3Node<KeyType> *p = root;
   while (p)
      switch(p->compare(x))
      {
	 case 1: if (p->LeftChild) p = p->LeftChild;
		 else return p;
		 break;
	 case 2: if (p->MiddleChild) p = p->MiddleChild;
		 else return p;
		 break;
	 case 3: if (p->RightChild) p = p->RightChild;
		 else return p;
		 break;
	 case 4: return 0;
      }
   return 0;
}

template <class KeyType>
Boolean Two3<KeyType>::Insert(const Element<KeyType>& y)
{
   Two3Node<KeyType> *p;
   Element<KeyType> x = y;
   if (x.key == MAXKEY) return FALSE;
   if (!root) { NewRoot(x, 0); return TRUE;}
   if (!(p = FindNode(x))) {/*InsertionError(); */ return FALSE;}
   for (Two3Node<KeyType> *a = 0;;)
      if (p->dataR.key == MAXKEY) {
	 p->PutIn(x,a);
	 return TRUE;
      }
      else {
	 Two3Node<KeyType> *olda = a;
	 a = new(Two3Node<KeyType>);
	 x = Split(p, x, olda, a);
	 if (root == p) {
	    NewRoot(x, a);
	    return TRUE;
	 }
	 else p = p->parent;
      }
}

main()
{
   Two3<int> m(1000);
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