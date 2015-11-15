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
    void Invert();
    void Concatenate(List<Type>);
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
void List<Type>::Invert()
// A chain x is inverted so that if x = (a0, a1, ..., an),
// then, after execution, x = (an, ..., a1)
{
    ListNode<Type> *p = first, *q = 0; // q trails p
    while (p) {
       ListNode<Type> *r = q; q = p; // r trails q
       p = p->link; // p moves to next node
       q->link = r; // link q to preceding node
    }
    first = q;
}

template <class Type>
void List<Type>::Concatenate(List<Type> b)
// this = (a1, ..., am) and y = (b1, ..., bm), m, n >= 0
// produces the new chain z = (a1, ..., am, b1, ..., bn) in this.
{
    if (! first) {first = b.first; return;}
    if (b.first) {
	for (ListNode<Type> *p = first; p->link; p = p->link); // no body
	p->link = b.first;
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

int sum(const List<int>& l)
{
  ListIterator<int> li(l);  //li is associated with list l
  if (!li.NotNull()) return 0; // empty list, return 0
  int retvalue = *li.First(); // get first element
  while (li.NextNotNull())  // make sure that next element exists
     retvalue += *li.Next(); // get it, add it to current total
  return retvalue;
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

main()
{
   List<int> intlist;
    intlist.Insert(5);
    intlist.Insert(15);
    intlist.Insert(25);
    intlist.Insert(35);
    cout << endl;
    cout << sum(intlist) << endl;
    intlist.Delete(20);
    intlist.Delete(15);
    intlist.Delete(35);
    cout << sum(intlist) << endl;

  List<char> charlist;
    cout << "shd be empty: " << charlist << endl;
    charlist.Invert();
    cout << "shd be empty: " << charlist << endl;
    charlist.Insert('d');
    charlist.Invert();
    cout << "shd have a d : " << charlist << endl;
    charlist.Insert('c');
    charlist.Insert('b');
    charlist.Insert('a');
    cout << "shd have abcd: ";
    cout << charlist << endl;
    charlist.Invert();
    cout << "shd invert prev list";
    cout << charlist << endl;

    List<char> char2list;
    charlist.Concatenate(char2list);
    cout << charlist << endl;
    char2list.Insert('e');
    char2list.Insert('f');
    char2list.Concatenate(charlist);
   charlist.Delete('e');
    charlist.Delete('c');
    cout << char2list << endl;
    char2list.Invert();
    cout << char2list << endl;
}