#include <iostream.h>

enum Boolean { FALSE, TRUE};

template <class KeyType>
class Element {
public:
   KeyType key;
};

template <class KeyType>
class MinPQ {
public:

   virtual Element<KeyType>* DeleteMin(Element<KeyType>&) = 0;
//   virtual Element DeleteMax() = 0;
   virtual void Insert(const Element<KeyType>&) = 0;
   virtual void display() = 0;
};


template <class KeyType> class MinLeftistTree;

template <class KeyType>
class LeftistNode {
friend class MinLeftistTree<KeyType>;
private:
   Element<KeyType> data;
   LeftistNode *LeftChild, *RightChild;
   int shortest;

   void display(int i);
};


template <class KeyType>
class MinLeftistTree : public MinPQ<KeyType> {
public:
   MinLeftistTree(LeftistNode<KeyType> *init = 0) : root(init) {};

// MinLeftistTree& operator=(const MinLeftistTree&);

   void Insert(const Element<KeyType>& x);
   Element<KeyType>* DeleteMin(Element<KeyType>&);
   void MinCombine(MinLeftistTree<KeyType> *);

   void display() {cout << "\n";
		   if (root) root->display(1);
		   else cout << "0\n";};
private:
   LeftistNode<KeyType> *MinUnion(LeftistNode<KeyType> *, LeftistNode<KeyType> *);

   LeftistNode<KeyType> *root;
};


template <class KeyType>
void LeftistNode<KeyType>::display(int i)
{
   cout << "Position " << i << ": data.key " << data.key << " shortest = " << shortest << "\n";
   if (LeftChild) LeftChild->display(2*i);
   if (RightChild) RightChild->display(2*i + 1);
}

template <class KeyType>
LeftistNode<KeyType>* MinLeftistTree<KeyType>::MinUnion(LeftistNode<KeyType> *a, LeftistNode<KeyType> *b)
{
   if (a->data.key > b->data.key)
      {LeftistNode<KeyType> *t = a; a = b; b = t;}
   if (!a->RightChild) a->RightChild = b;
   else a->RightChild = MinUnion(a->RightChild, b);

   if (!a->LeftChild)
   {
      a->LeftChild = a->RightChild; a->RightChild = 0;
   }
   else if (a->LeftChild->shortest < a->RightChild->shortest)
   {
      cout << "Entered \n";
      LeftistNode<KeyType> *t = a->LeftChild; a->LeftChild = a->RightChild;
      a->RightChild = t;
   }

   if (!a->RightChild) a->shortest = 1;
   else a->shortest = a->RightChild->shortest + 1;
   return a;
}

template <class KeyType>
void MinLeftistTree<KeyType>::MinCombine(MinLeftistTree<KeyType> *b)
{
   if (!root) root = b->root;
   else if (b->root)
      root = MinUnion(root, b->root);
   b->root = 0;
}

template <class KeyType>
Element<KeyType>* MinLeftistTree<KeyType>::DeleteMin(Element<KeyType>& min)
{
   LeftistNode<KeyType> *temp = root;
   min = temp->data;
   MinLeftistTree Right(root->RightChild);
   root = root->LeftChild;
   MinCombine(&Right);
   delete temp;
   return &min;
}

template <class KeyType>
void MinLeftistTree<KeyType>::Insert(const Element<KeyType>& x)
{
   LeftistNode<KeyType> *xnode = new LeftistNode<KeyType>;
   xnode->LeftChild = 0;
   xnode->RightChild = 0;
   xnode->data = x;
   xnode->shortest = 1;
   MinLeftistTree Right(xnode);
   MinCombine(&Right);
}

main()
{
   MinLeftistTree<int> m;
   Element<int> a, b, c, d, e, f, g, h, i, j, k, l, temp;
   a.key = 5; b.key = 3; c.key = 11; d.key = 3; e.key = 15;
   f.key = 2; g.key = 8; h.key = 22; i.key = 20; j.key = 9;
   m.Insert(a);
//   m.display();
   m.Insert(b);
//   m.display();
   m.Insert(c);
//   m.display();
   m.Insert(d);
//   m.display();

   m.Insert(e);
//   m.display();
   m.Insert(f);
//   m.display();
   m.Insert(g);
//   m.display();
   m.Insert(h);
//   m.display();
   m.Insert(i);
//   m.display();
   m.Insert(j);
   m.display();



cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();
cout << m.DeleteMin(temp)->key << "\n";
m.display();

}
