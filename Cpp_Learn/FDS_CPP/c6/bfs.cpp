// Adjacency Lists + BFS.

#ifndef _IOSTREAM_H
#include <iostream.h>
#define _IOSTREAM_H
#endif

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
ListNode<Type>::ListNode(Type Default)
{
    data = Default;
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
    ListIterator(const List<Type>& l): list(l) {current = l.first;}
    Type* First();
    Type* Next();
    Boolean NotNull();
    Boolean NextNotNull();
private:
    const List<Type> &list;
    ListNode<Type>* current;
};

template <class Type>
Type* ListIterator<Type>::First() {
      if (current) return &current->data;
      else return 0;
}

template <class Type>
Type* ListIterator<Type>::Next() {
      current = current->link;
      return &current->data;
}

template <class Type>
Boolean ListIterator<Type>::NotNull()
{
if (current) return TRUE;
else return FALSE;
}

template <class Type>
Boolean ListIterator<Type>::NextNotNull()
{
if (current->link) return TRUE;
else return FALSE;
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

class Queue;

class QueueNode {
friend class Queue;
private:
    int data;
    QueueNode *link;
    QueueNode(int def = 0, QueueNode *l = 0)
    {
       data = def;
       link = l;
    };
};

class Queue {
private:
    QueueNode *front, *rear;
    void QueueEmpty() {};
public:
    Queue() { front = rear = 0;};
    void Insert(int);
    int* Delete(int&);
    Boolean IsEmpty() { if (front == 0) return TRUE; else return FALSE;};
};

void Queue::Insert(int y)
{
    if (front == 0) front = rear = new QueueNode(y, 0); // empty queue
    else rear = rear->link = new QueueNode(y, 0); // update \fIrear\fR
}

int* Queue::Delete(int& retvalue)
// delete the first node in queue and return a pointer to its data
{
    if (front == 0) {QueueEmpty(); return 0;};
    QueueNode *x = front;
    retvalue = front->data; // get data
    front = x->link;      // delete front node
    if (front == 0) rear = 0; // queue becomes empty after deletion
    delete x; // free the node
    return &retvalue;
}

class Graph
{
private:
    List<int> *HeadNodes;
    int n;
    Boolean *visited;
public:
    Graph(int vertices = 0) : n(vertices)
    { HeadNodes = new List<int>[n];};
    void BFS(int);
    void Setup();
};

void Graph::Setup()
{
   HeadNodes[0].Insert(2); HeadNodes[0].Insert(1);
   HeadNodes[1].Insert(4); HeadNodes[1].Insert(3); HeadNodes[1].Insert(0);
   HeadNodes[2].Insert(6); HeadNodes[2].Insert(5); HeadNodes[2].Insert(0);
   HeadNodes[3].Insert(7); HeadNodes[3].Insert(1);
   HeadNodes[4].Insert(7); HeadNodes[4].Insert(1);
   HeadNodes[5].Insert(7); HeadNodes[5].Insert(2);
   HeadNodes[6].Insert(7); HeadNodes[6].Insert(2);
   HeadNodes[7].Insert(6); HeadNodes[7].Insert(5); HeadNodes[7].Insert(4);
   HeadNodes[7].Insert(3);
}

void Graph::BFS(int v)
{
    visited = new Boolean[n]; // @visited@ is declared as a @Boolean@\(** data member of @Graph@.
    for (int i = 0; i < n; i++) visited[i] = FALSE; // initially, no vertices have been visited

    visited[v] = TRUE; cout << v << ",";
    Queue q;
    q.Insert(v);

    while (!q.IsEmpty()) {
	v = *q.Delete(v);
	ListIterator<int> li(HeadNodes[v]);
	if (! li.NotNull()) continue;
	int w = *li.First();
	while (1) {
	    if (! visited[w]) {q.Insert(w); visited[w] = TRUE; cout << w << ",";};
	    if (li.NextNotNull()) w = *li.Next();
	    else break;
	}
    }
    delete [] visited;
}

main()
{
 Graph g(8);
 g.Setup();
 g.BFS(0);
}