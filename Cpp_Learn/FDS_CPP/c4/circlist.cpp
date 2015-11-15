#include <iostream.h>

enum Boolean { FALSE, TRUE};

template <class Type> class CircList;
template <class Type> class CircListIterator;

template <class Type>
class ListNode {
friend class CircList<Type>;
friend class CircListIterator<Type>;
private:
    Type data;
    ListNode *link;
    ListNode(Type);
    ListNode(){};
};

template <class Type>
ListNode<Type>::ListNode(Type element)
{
    data = element;
    link = 0;
}

template <class Type>
class CircList {
friend class CircListIterator<Type>;
public:
    CircList() {first = new ListNode<Type>; first->link = first;};
    void Insert(Type);
    void Delete(Type);
private:
    ListNode<Type> *first;
};

template <class Type>
void CircList<Type>::Insert(Type k)
{
ListNode<Type> *newnode = new ListNode<Type>(k);
newnode->link = first->link;
first->link = newnode;
}

template <class Type>
void CircList<Type>::Delete(Type k)
{
    ListNode<Type> *previous = first;
    for (ListNode<Type> *current = first->link;
	(current != first) && (current->data != k) ;
	previous = current, current = current->link);
   if (current != first)
   {
       previous->link = current->link;
       delete current;
   }
}
template <class Type>
class CircListIterator {
public:
    CircListIterator(const CircList<Type>& l): list(l) {current = l.first->link;}
    Type* First();
    Type* Next();
    Boolean NotNull();
    Boolean NextNotNull();
private:
    const CircList<Type> &list;
    ListNode<Type>* current;
};

template <class Type>
Type* CircListIterator<Type>::First() {
      if (current != list.first ) return &current->data;
      else return 0;
}

template <class Type>
Type* CircListIterator<Type>::Next() {
      current = current->link;
      if (current != list.first) return &current->data;
      else return 0;
}

template <class Type>
Boolean CircListIterator<Type>::NotNull()
{
if (current != list.first) return TRUE;
else return FALSE;
}

template <class Type>
Boolean CircListIterator<Type>::NextNotNull()
{
if (current->link != list.first) return TRUE;
else return FALSE;
}

int sum(CircList<int> l)
{
  CircListIterator<int> li(l);
  if (!li.NotNull()) return 0;
  int retvalue = *li.First();
  while (li.NextNotNull())
     retvalue += *li.Next();
  return retvalue;
}



//template <class Type>
ostream& operator<<(ostream& os, CircList<char>& l)
{
    CircListIterator<char> li(l);
    if (!li.NotNull()) return os;
    os << *li.First() << endl;
    while  (li.NextNotNull())
	 os << *li.Next() << endl;
    return os;
}

main()
{
    CircList<int> intlist;
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
    CircList<char> charlist;
    charlist.Insert('d');
    charlist.Insert('c');
    charlist.Insert('b');
    charlist.Insert('a');
    cout << charlist << endl;
    charlist.Delete('e');
    charlist.Delete('c');
    cout << charlist << endl;
}