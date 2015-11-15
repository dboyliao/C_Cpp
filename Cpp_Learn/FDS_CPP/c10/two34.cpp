#include <iostream.h>
#include <fstream.h>

enum Boolean { FALSE, TRUE};
enum result {equal, leaf, lChild, lmChild, rmChild, rChild};

template <class KeyType>
class Element {
public:
    KeyType key;
};

enum Node234{TwoNode, ThreeNode};

template <class KeyType> class Two34; // forward declaration

template <class KeyType>
class Two34Node {
friend class Two34<KeyType>;
public:
   Two34Node(KeyType MAXKEY) {
      dataL.key = dataM.key = dataR.key = MAXKEY;
      LeftChild = LeftMidChild = RightMidChild = RightChild = 0;
   };

   Two34Node(const Element<KeyType>& x, KeyType MAXKEY) {
      dataM.key = dataR.key = MAXKEY;
      LeftChild = LeftMidChild = RightMidChild = RightChild = 0;
      dataL = x;
   };

private:
   Element<KeyType> dataL, dataM, dataR;
   Two34Node *LeftChild, *LeftMidChild, *RightMidChild, *RightChild;
   void display(int i);
   void treeprint(int i);
   result compare(const Element<KeyType>&);
   void PutIn(const Element<KeyType>&);
};

template <class KeyType>
class Two34 {
public:
   Two34(KeyType max, Two34Node<KeyType> *init = 0)
   : MAXKEY(max), root (init) {};

   Boolean Insert(const Element<KeyType>&);
   Boolean Delete(const Element<KeyType>&);
   Two34Node<KeyType>* IterSearch(const Element<KeyType>&);
   void NewRoot(const Element<KeyType>&);
   void SplitRoot();
   Node234 NodeType(Two34Node<KeyType>*);
   void treeprint() { outFile <<  endl; root->treeprint(1); }

   void display() {outFile <<  endl;
		   if (root) root->display(1);
		   else outFile << "0\n";};
private:
   void SplitChildOf3(Two34Node<KeyType> *, Two34Node<KeyType> *);
   void SplitChildOf2(Two34Node<KeyType> *, Two34Node<KeyType> *);
   Two34Node<KeyType> *root;
   Boolean FourNode(Two34Node<KeyType> *);
   KeyType MAXKEY;
};

ofstream outFile("two34.out" , ios::out);

template <class KeyType>
result Two34Node<KeyType>::compare(const Element<KeyType>& x)
{
   if ((x.key == dataL.key) || (x.key == dataM.key) || (x.key == dataR.key))
   return equal;
   if (!LeftChild) return leaf;
   if (x.key < dataL.key) return lChild;
   if ((dataL.key < x.key) && (x.key < dataM.key)) return lmChild;
   if ((dataM.key < x.key) && (x.key < dataR.key)) return rmChild;
   else /*if (dataR.key < x.key)*/ return rChild;
}

template <class KeyType>
void Two34Node<KeyType>::PutIn(const Element<KeyType>& x)
{
   if (x.key < dataL.key) {
      dataR = dataM; dataM = dataL;
      dataL = x;
   }
   else if (x.key < dataM.key) {
      dataR = dataM;
      dataM = x;}
   else dataR = x;
}

template <class KeyType>
void Two34Node<KeyType>::display(int h)
{
   for (int i = 1; i <= h; i++) outFile << "    ";
   outFile << "Height " << h << " dataL " << dataL.key << " dataM " << dataM.key << " dataR " << dataR.key <<  endl;
   if (LeftChild) LeftChild->display(h+1);
   if (LeftMidChild) LeftMidChild->display(h+1);
   if (RightMidChild) RightMidChild->display(h+1);
   if (RightChild) RightChild->display(h+1);
}

template <class KeyType>
Boolean Two34<KeyType>::FourNode(Two34Node<KeyType> *p)
{
   if (p->dataR.key == MAXKEY) return FALSE;
   return TRUE;
}

template <class KeyType>
Node234 Two34<KeyType>::NodeType(Two34Node<KeyType>* p)
{
   if (p->dataM.key == MAXKEY) return TwoNode;
   return ThreeNode;
}

template <class KeyType>
void Two34<KeyType>::SplitChildOf2(Two34Node<KeyType> *p, Two34Node<KeyType> *q)
{
   Two34Node<KeyType> *r;
   if (p == q->LeftChild)
   {
      q->dataM = q->dataL;
      q->RightMidChild = q->LeftMidChild;
      q->dataL = p->dataM;
      p->dataM.key = MAXKEY;
      r = new Two34Node<KeyType>(p->dataR, MAXKEY);
      r->LeftChild = p->RightMidChild;
      r->LeftMidChild = p->RightChild;
      p->RightMidChild = p->RightChild = 0;
      p->dataR.key = MAXKEY; q->LeftMidChild = r;
   }
   else
   {
      q->dataM = p->dataM;
      p->dataM.key = MAXKEY;
      r = new Two34Node<KeyType>(p->dataR, MAXKEY);
      p->dataR.key = MAXKEY;
      r->LeftChild = p->RightMidChild;
      r->LeftMidChild = p->RightChild;
      p->RightMidChild = p->RightChild = 0;
      q->RightMidChild = r;
   }
}

template <class KeyType>
void Two34<KeyType>::SplitChildOf3(Two34Node<KeyType> *p, Two34Node<KeyType> *q)
{
   Two34Node<KeyType> *r;
   if (q->LeftChild == p)
   {
      q->dataR = q->dataM; q->RightChild = q->RightMidChild;
      q->dataM = q->dataL; q->RightMidChild = q->LeftMidChild;
      q->LeftMidChild = r = new Two34Node<KeyType>(p->dataR, MAXKEY);
      q->dataL = p->dataM;
      r->LeftChild = p->RightMidChild;
      r->LeftMidChild = p->RightChild;
      p->dataM.key = p->dataR.key = MAXKEY;
      p->RightMidChild = p->RightChild = 0;
      return;
   }
   if (q->LeftMidChild == p)
   {
      q->dataR = q->dataM; q->RightChild = q->RightMidChild;
      q->dataM = p->dataM;
      q->RightMidChild = r = new Two34Node<KeyType>(p->dataR, MAXKEY);
      r->LeftChild = p->RightMidChild;
      r->LeftMidChild = p->RightChild;
      p->dataM.key = p->dataR.key = MAXKEY;
      p->RightMidChild = p->RightChild = 0;
      return;
   }
if (q->RightMidChild == p)
   {
      q->dataR = p->dataM;
      q->RightChild = r = new Two34Node<KeyType>(p->dataR, MAXKEY);
      r->LeftChild = p->RightMidChild;
      r->LeftMidChild = p->RightChild;
      p->dataM.key = p->dataR.key = MAXKEY;
      p->RightMidChild = p->RightChild = 0;
      return;
   }
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
Two34Node<KeyType>* Two34<KeyType>::IterSearch(const Element<KeyType>& x)
{
   Two34Node<KeyType> *p = root;
   while (p)
      switch(p->compare(x))
      {
	 case lChild:  p = p->LeftChild; break;
	 case lmChild: p = p->LeftMidChild; break;
	 case rmChild: p = p->RightMidChild; break;
	 case rChild : p = p->RightChild; break;
	 case equal: return p;
      }
   return 0;
}

template <class KeyType>
void Two34<KeyType>::NewRoot(const Element<KeyType>& x)
{
   Two34Node<KeyType> *newroot;
   newroot = new Two34Node<KeyType>(x, MAXKEY);
   root = newroot;
}

template <class KeyType>
void Two34<KeyType>::SplitRoot()
{
Two34Node<KeyType> *left, *right;
left =  new Two34Node<KeyType>(root->dataL,MAXKEY);
right = new Two34Node<KeyType>(root->dataR, MAXKEY);
left->LeftChild = root->LeftChild;
left->LeftMidChild = root->LeftMidChild;
right->LeftChild = root->RightMidChild;
right->LeftMidChild = root->RightChild;
root->LeftChild = left; root->LeftMidChild = right;
root->RightMidChild = root->RightChild = 0;
root->dataL = root->dataM; root->dataM.key = root->dataR.key = MAXKEY;
}

template <class KeyType>
Boolean Two34<KeyType>::Insert(const Element<KeyType>& y)
{
   if (y.key >= MAXKEY) return FALSE;
   if (!root) {NewRoot(y); return TRUE;}
   if (FourNode(root)) SplitRoot();
   for (Two34Node<KeyType> *p = root, *q = 0; ;) {
      if (FourNode(p)) {
	 if (NodeType(q) == TwoNode) SplitChildOf2(p, q);
	 else SplitChildOf3(p, q);
	 p = q;
      }
      q = p;
      switch (p->compare(y)) {
	 case equal: /* InsertionError */ return FALSE;
	 case leaf: p->PutIn(y); return TRUE;
	 case lChild: p = p->LeftChild; break;
	 case lmChild: p = p->LeftMidChild; break;
	 case rmChild: p = p->RightMidChild; break;
	 case rChild: p = p->RightChild; break;
      }
   }
}

main()
{
   Two34<int> m(1000);
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