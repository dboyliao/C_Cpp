// Adjacency Lists + DFS.

#ifndef _IOSTREAM_H
#include <iostream.h>
#define _IOSTREAM_H
#endif

struct Pair {
int vertex, dur;
};

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

/*
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
*/

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

class Graph
{
private:
    List<Pair> *HeadNodes;
    int *count;
    int *ee;
    int n;
public:
    Graph(const int vertices = 0) : n(vertices)
    { HeadNodes = new List<Pair>[n];
      count = new int[n];
      ee = new int[n];
    };
    void Setup();
    void Setup2();
    void Setup3();
    void Setup4();
    void EarlyActivity();
    void TopologicalOrder();
};

/*
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

void Graph::Setup2()
{
   HeadNodes[0].Insert(1);                                                 //
   HeadNodes[1].Insert(2); HeadNodes[1].Insert(3); HeadNodes[1].Insert(0);//
   HeadNodes[2].Insert(1); HeadNodes[2].Insert(4); //
   HeadNodes[3].Insert(5); HeadNodes[3].Insert(1); HeadNodes[3].Insert(4);//
   HeadNodes[4].Insert(3); HeadNodes[4].Insert(2); //
   HeadNodes[5].Insert(7); HeadNodes[5].Insert(6);//
   HeadNodes[6].Insert(7); HeadNodes[6].Insert(5);//
   HeadNodes[7].Insert(6); HeadNodes[7].Insert(5); HeadNodes[7].Insert(8);
   HeadNodes[7].Insert(9);
   HeadNodes[8].Insert(7);
   HeadNodes[9].Insert(7);
}


void Graph::Setup3()
{
   HeadNodes[0].Insert(3); HeadNodes[0].Insert(2); HeadNodes[0].Insert(1); 						//
   HeadNodes[1].Insert(4);
   HeadNodes[2].Insert(5); HeadNodes[2].Insert(4);
   HeadNodes[3].Insert(4); HeadNodes[3].Insert(5);
   count[0] = 0; count[1] = 1; count[2] = 1;
   count[3] = 1; count[4] = 3; count[5] = 2;
}

void Graph::TopologicalOrder()
// The @n@ vertices of a network are listed in topological order
{
   int top = -1;
   for (int i = 0; i < n; i++)   // create a linked stack of verices with
       if (count[i] == 0)  {count[i] = top; top = i;} // no predecessors
   for (i = 0; i < n; i++)
       if (top == -1) { cout << " network has a cycle" << endl; return;}
       else {
	   int j = top; top = count[top]; // unstack a vertex
	   cout << j << endl;
	   ListIterator<int> li(HeadNodes[j]);
	   if (! li.NotNull()) continue;
	   int k = *li.First();
	   while (1) {
	      count[k]--;
	      if (count[k] == 0) {count[k] = top; top = k;}
	      if (li.NextNotNull()) k = *li.Next();
	      else break;
	   }
       }
}
*/

void Graph::Setup4()
{
   for (int i = 0; i < n; i++) ee[i] = 0;
   Pair p26, p34, p45, p51, p62, p79, p87, p84, p92, p94;
   p26.vertex = 1; p26.dur = 6;
   p34.vertex = 2; p34.dur = 4;
   p45.vertex = 3; p45.dur = 5;
   p51.vertex = 4; p51.dur = 1;
   p62.vertex = 5; p62.dur = 2;
   p79.vertex = 6; p79.dur = 9;
   p87.vertex = 7; p87.dur = 7;
   p84.vertex = 7; p84.dur = 4;
   p92.vertex = 8; p92.dur = 2;
   p94.vertex = 8; p94.dur = 4;

   HeadNodes[0].Insert(p45); HeadNodes[0].Insert(p34); HeadNodes[0].Insert(p26);
   count[0] = 0;

   HeadNodes[1].Insert(p51);
   count[1] = 1;

   HeadNodes[2].Insert(p51);
   count[2] = 1;

   HeadNodes[3].Insert(p62);
   count[3] = 1;

   HeadNodes[4].Insert(p87); HeadNodes[4].Insert(p79);
   count[4] = 2;

   HeadNodes[5].Insert(p84);
   count[5] = 1;

   HeadNodes[6].Insert(p92);
   count[6] = 1;

   HeadNodes[7].Insert(p94);
   count[7] = 2;

   count[8] = 2;

}

void Graph::EarlyActivity()
// The @n@ vertices of a network are listed in topological order
{
   int top = -1;
   for (int i = 0; i < n; i++)   // create a linked stack of verices with
       if (count[i] == 0)  {count[i] = top; top = i;} // no predecessors
   for (i = 0; i < n; i++)
       if (top == -1) { cout << " network has a cycle" << endl; return;}
       else {
	   int j = top; top = count[top]; // unstack a vertex
	   cout << j << endl;
	   ListIterator<Pair> li(HeadNodes[j]);
	   if (! li.NotNull()) continue;
	   Pair p = *li.First();
	   while (1) {
	      int k = p.vertex;
	      if (ee[k] < ee[j] + p.dur) ee[k] = ee[j] + p.dur;
	      count[k]--;
	      if (count[k] == 0) {count[k] = top; top = k;}
	      if (li.NextNotNull()) p = *li.Next();
	      else break;
	   }
       }
       for (int l = 0; l < n; l++) cout << ee[l] << " ";
}
void main()
{
 Graph g(9);
 g.Setup4();
 g.EarlyActivity();
}

