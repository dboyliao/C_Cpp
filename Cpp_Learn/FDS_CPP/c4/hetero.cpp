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
friend List;
friend class ListIterator;
protected:
  Node *link;
  virtual Data GetData() = 0;
};

class CharNode: public Node
{
friend List;
friend class ListIterator;
private:
   char data;
   Data GetData() { Data t; t.id = 0; t.c = data; return t;};
public:
   CharNode(char c) {data = c; link = 0;};
};

class IntNode: public Node
{
friend List;
friend class ListIterator;
private:
   int data;
   Data GetData() { Data t; t.id = 1; t.i = data; return t;};
public:
   IntNode(int i) {data = i; link = 0;};
};

class FloatNode: public Node
{
friend List;
friend class ListIterator;
private:
   float data;
   Data GetData() { Data t; t.id = 2; t.f = data; return t;};
public:
   FloatNode(float f) {data = f; link = 0;};
};

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
  first = new IntNode(1);
  Node *temp = first->link = new CharNode('a');
  temp = temp->link = new FloatNode(1.5);
  temp = temp->link = new IntNode(2);
  temp = temp->link = new CharNode('b');
  temp = temp->link = new FloatNode(2.5);
}

class ListIterator {
public:
    ListIterator(const List& l): list(l) {current = l.first;}
    Data* First();
    Data* Next();
    Boolean NotNull();
    Boolean NextNotNull();
private:
    const List &list;
    Node* current;
    Data temp;
};

Data* ListIterator::First() {
      if (current) {
	 temp = current->GetData();
	 return &temp;
      }
      return 0;
}

Data* ListIterator::Next() {
      if (current && current->link) {
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
  cout << l;

//  l.GetSize();
  IntNode i(1); cout << sizeof(i) << endl;
  CharNode c('c'); cout << sizeof(c) << endl;
  FloatNode f(53.4);  cout << sizeof(f) << endl;
}
