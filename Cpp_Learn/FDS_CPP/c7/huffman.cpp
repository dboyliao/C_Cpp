#include <iostream.h>

enum Boolean { FALSE, TRUE};
template <class Type> class List;
template <class Type> class ListIterator;

template <class Type>
class ListNode {
friend class List<Type>;
friend class ListIterator<Type>;
private:
    Type data;
    ListNode *link;
    ListNode(Type);
};

template <class Type>
ListNode<Type>::ListNode(Type element)
{
    data = element;
    link = 0;
}

template <class Type>
class List {
friend class ListIterator<Type>;
public:
    List() {first = 0;};
    void Insert(Type);
    void Delete(Type);
private:
    ListNode<Type> *first;
};

template <class Type>
void List<Type>::Insert(Type k)
{
ListNode<Type> *newnode = new ListNode<Type>(k);
newnode->link = first;
first = newnode;
}

template <class Type>
void List<Type>::Delete(Type k)
{
    ListNode<Type> *previous = 0;
    for (ListNode<Type> *current = first; current && current->data != k;
	previous = current, current = current->link);
   if (current)
   {
       if (previous) previous->link = current->link;
       else first = first->link;
       delete current;
   }
}

template <class Type>
class ListIterator {
public:
    ListIterator(const List<Type>& l): list(l), current (l.first) {};
    Boolean NotNull();
    Boolean NextNotNull();
    Type* First();
    Type* Next();
private:
    const List<Type> &list;  // refers to an existing list
    ListNode<Type>* current; // points to a node in list
};

template <class Type> //check that current element in list is non-null
Boolean ListIterator<Type>::NotNull()
{
if (current) return TRUE;
else return FALSE;
}

template <class Type>  // check that the next element in list is non-null
Boolean ListIterator<Type>::NextNotNull()
{
if (current && current->link) return TRUE;
else return FALSE;
}

template <class Type> // return a pointer to the first element of list
Type* ListIterator<Type>::First() {
      if (list.first) return &list.first->data;
      else return 0;
}

template <class Type> // return a pointer to the next element of list
Type* ListIterator<Type>::Next() {
      if (current) {
	 current = current->link;
	 return &current->data;
      }
      else return 0;
}

//template <class Type>
ostream& operator<<(ostream& os, List<char>& l)
{
    ListIterator<char> li(l);
    if (!li.NotNull()) return os;
    os << *li.First() << endl;
    while  (li.NextNotNull())
	 os << *li.Next() << endl;
    return os;
}



class BinaryTreeNode {
friend BinaryTree;
private:
   int weight;
   BinaryTreeNode *LeftChild, *RightChild;
};

class BinaryTree {
public:
  int weight();
  BinaryTree(BinaryTree bt1, BinaryTree bt2) {
     root->LeftChild = bt1.root;
     root->RightChild = bt2.root;
     root->weight = bt1.root->weight + bt2.root->weight;
  };
private:
  BinaryTreeNode *root;
}

void huffman(List<BinaryTree> l)
// @l@ is a list of single node binary trees as described above
{
   int n = l.Size(); // number of binary trees in l
   for (int i = 0; i < n-1 ; i++) { // loop n-1 times
       BinaryTree first = l.DeleteMinWeight();
       BinaryTree second = l.DeleteMinWeight();
       BinaryTree *bt = new BinaryTree(first, second);
       l.Insert(bt);
   }
}