#include <iostream.h>
enum Boolean { FALSE, TRUE};

class List;
class ListIterator;

class ListNode {
friend class List;
friend class ListIterator;
private:
    int data;
    ListNode *link;
    ListNode(int);
};

ListNode::ListNode(int element = 0) // 0 is the default argument
// constructor for ListNode
{
    data = element;
    link = 0; // null pointer constant
}

class List {
friend class ListIterator;
public:
    List() {first = 0;};
    void Create2();
    void Insert50(ListNode *x);
    void Insert();
    void Delete(ListNode *x, ListNode *y);
    void TestDelete();
private:
    ListNode *first;
};

class ListIterator {
public:
    ListIterator(const List& l): list(l), current(list.first) {};
    int Next();
private:
    const List &list;
    ListNode* current;
};

int ListIterator::Next()
{
    if (current) {
      current = current->link;
      int retvalue = current->data;
      return retvalue;
    }
    return 0;
}

ostream& operator<<(ostream& os, List l)
{
    ListIterator li(l);
    for (int contents = li.Next(); contents; contents = li.Next())
	 os << contents << endl;
    return os;
}

void List::Create2() {
    first = new ListNode(10); // create and initialize first node
    // create and initialize second node and place its address in first->link
    first->link = new ListNode(20);
}

void List::Insert50(ListNode *x)
{
    ListNode *t = new ListNode(50); // create and initialize new node
    if (!first) // insert into empty list
    {
       first = t;
       return; // exit List::Insert50
    }
    // insert after x
    t->link = x->link;
    x->link = t;
}

void List::Insert() {
    ListNode *temp = first;
    while (temp && temp->link) temp = temp->link;
    Insert50(temp);
}

void List::Delete(ListNode *x, ListNode *y)
{
     if (!y) first = first->link;
     else y->link = x->link;
     delete x; // return the node
}

void List::TestDelete()
{
   ListNode *temp = first;
   ListNode *prev = 0;
   while (temp && temp->link) {
      prev = temp;
      temp = temp->link;
   }
   Delete(temp, prev);
}

main()
{
cout << endl;
List l;
l.Create2();
cout << l;
l.Insert();
cout << l << endl;
l.TestDelete();
cout << l;

cout << endl;
List m;
m.Insert();
cout << m << endl;
m.TestDelete();
cout << m;
}