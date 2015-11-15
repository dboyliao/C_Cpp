#include <iostream.h>
enum Boolean {FALSE, TRUE};

struct Data
{
    int id; // id = 0, 1, or 2 if the node contains a char, an int, or float
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

class CombinedNode {
friend List;
friend class ListIterator;
private:
  Data data;
  CombinedNode *link;
public:
  CombinedNode() {link = 0;};
};


class List
{
friend class ListIterator;
friend ostream& operator<<(ostream&, List& );
private:
   CombinedNode *first;
public:
   void Init();

};


void List::Init()
{
  first = new CombinedNode; first->data.id = 1; first->data.i = 1;
  CombinedNode *temp = first->link = new CombinedNode; temp->data.id = 0; temp->data.c = 'a';
  temp = temp->link = new CombinedNode;  temp->data.id = 2; temp->data.f = 1.5;
  temp = temp->link = new CombinedNode;  temp->data.id = 1; temp->data.i = 2;
  temp = temp->link = new CombinedNode;  temp->data.id = 0; temp->data.c = 'b';
  temp = temp->link = new CombinedNode;  temp->data.id = 2; temp->data.f = 2.5;
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
    CombinedNode* current;
};

Data* ListIterator::First() {
      if (list.first) return &list.first->data;
      return 0;
}

Data* ListIterator::Next()
{
      if (current) {
	 current = current->link;
	 return &current->data;
      }
      else return 0;
}

Boolean ListIterator::NotNull()
{
if (current) return TRUE;
else return FALSE;
}

Boolean ListIterator::NextNotNull()
{
if (current && current->link) return TRUE;
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
  CombinedNode cn;
  Data d;
  cout << endl << sizeof(cn) << endl;
  int i; char c; float f;
  cout <<  sizeof(c) << endl;
  cout << sizeof(i) << endl;
  cout << sizeof(f) << endl;
  cout << sizeof(d) << endl;
  cout << sizeof(&i) << " " << sizeof(&c) << " " << sizeof(&f) << endl;

//  l.GetSize();
//  IntNode i(1); cout << sizeof(i) << endl;
//  CharNode c('c'); cout << sizeof(c) << endl;
//  FloatNode f(53.4);  cout << sizeof(f) << endl;
}
