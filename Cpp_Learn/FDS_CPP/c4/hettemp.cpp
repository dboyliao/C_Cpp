#include <iostream.h>

enum Boolean { FALSE, TRUE};

struct Data
{
    int id;
    union {
      int i;
      char c;
      float f;
    };
};

ostream& operator<<(ostream& os, Data& rl)
{
    switch (rl.id) {
     case 0: os << rl.c; break;
     case 1: os << rl.i; break;
     case 2: os << rl.f; break;
    }
    return os;
}

class Node {
friend class List;
friend class ListIterator;
protected:
  Node *link;
  virtual Data GetData() = 0;
};

template <class Type>
class DerivedNode: public Node
{
friend class List;
friend class ListIterator;
private:
   Type data;
   Data GetData();
public:
   DerivedNode(Type item): data(item) {link = 0;};
};

Data DerivedNode<char>::GetData()
{
   Data t; t.id = 0; t.c = data; return t;
}

Data DerivedNode<int>::GetData()
{
   Data t; t.id = 1; t.i = data; return t;
}

Data DerivedNode<float>::GetData()
{
   Data t; t.id = 2; t.f = data; return t;
}


class List
{
friend class ListIterator;
friend ostream& operator<<(ostream&, List& );
private:
   Node *first;
public:
   void Init();
   void GetSize();
//   void Print();
};

void List::GetSize()
{
    for (Node *temp = first; temp; temp = temp->link)
       cout << sizeof(*temp);
}

void List::Init()
{
  first = new DerivedNode<int>(1);
  Node *temp = first->link = new DerivedNode<char>('a');
  temp = temp->link = new DerivedNode<float>(1.5);
  temp = temp->link = new DerivedNode<int>(2);
  temp = temp->link = new DerivedNode<char>('b');
  temp = temp->link = new DerivedNode<float>(2.5);
}

class ListIterator {
public:
    ListIterator(const List& l): list(l), current (l.first) {};
    Data* First();
    Data* Next();
    Boolean NotNull();
    Boolean NextNotNull();
private:
    const List& list;
    Node* current;
    Data temp;
};

Data* ListIterator::First() {
      if (list.first) {
	 temp = list.first->GetData();
	 return &temp;
      }
      return 0;
}

Data* ListIterator::Next() {
      if (current) {
	 current = current->link;
	 temp = current->GetData();
	 return &temp;
      }
      return 0;
}

Boolean ListIterator::NotNull()
{
if (current) return TRUE;
else return FALSE;
}

Boolean ListIterator::NextNotNull()
{
if (current->link) return TRUE;
else return FALSE;
}

ostream& operator<<(ostream& os, List& l)
{
    ListIterator li(l);
    if (!li.NotNull()) return os;
    os << *li.First() << endl;
    while  (li.NextNotNull())
	 os << *li.Next() << endl;
    return os;
}

void main()
{
  List l;
  l.Init();
  cout << l << endl;

//  l.GetSize();
  DerivedNode<int> i(1); cout << sizeof(i) << endl;
  DerivedNode<char> c('c'); cout << sizeof(c) << endl;
  DerivedNode<float> f(53.4);  cout << sizeof(f) << endl;
}
