// Adjacency Lists + DFS.

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

class Graph
{
private:
    List<int> *HeadNodes;
    int n;
    void DFS(const int);
    Boolean *visited;
    int num;
    int *low;
    int *dfn;
    void DfnLow(const int, const int);
public:
    Graph(const int vertices = 0) : n(vertices)
    { HeadNodes = new List<int>[n];};
    void DFS();
    void Setup();
    void Setup2();
    void DfnLow(const int);
    void Components();
    void Out();
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

// Driver
void Graph::DFS()
{
    visited = new Boolean[n]; // @visited@ is declared as a @Boolean@\(** data member of @Graph@.
    for (int i = 0; i < n; i++) visited[i] = FALSE; // initially, no vertices have been visited
    DFS(0); // start search at vertex 0
    delete [] visited;
}

// Workhorse
void Graph::DFS(const int v)
//  visit all previously unvisited vertices that are reachable from vertex @v@
{
     visited[v] = TRUE;  cout << v << ", ";
     ListIterator<int> li(HeadNodes[v]);
     if (! li.NotNull()) return;
     int w = *li.First();
     while (1) {
      if (! visited[w]) DFS(w);
      if (li.NextNotNull()) w = *li.Next();
      else return;
     }
}

void Graph::Components()
{
     visited = new Boolean[n];
     for (int i = 0; i < n; i++) visited[i] = FALSE;
     for (i = 0; i < n; i++)
	 if (! visited[i]) {
	     cout << endl << "New Component :";
	     DFS(i); // @DFS@ is modified to print a vertex when it is visited
	 }
     delete [] visited;
}

void Graph::DfnLow(const int x)
{
   num = 1;
   dfn = new int[n];
   low = new int[n];
   for (int i = 0; i < n; i++) { dfn[i] = low[i] = 0;}
   DfnLow(x, -1);
   delete [] dfn;
   delete [] low;
}

void Graph::DfnLow (const int u, const int v)
{
    dfn[u] = low[u] = num++;

    ListIterator<int> li(HeadNodes[u]);
    if (! li.NotNull()) return;
    int w = *li.First();
    while (1) {
	if (dfn[w] == 0) {
	    DfnLow(w, u);
	    if (low[w] < low[u]) low[u] = low[w];
	}
	else {
	    if (w != v) {if (dfn[w] < low[u])  low[u] = dfn[w];}
	}
	if (li.NextNotNull()) w = *li.Next();
	else return;
    }
}

void Graph::Out()
{
for (int i = 0; i < n; i++) {
    cout << i << ": " << dfn[i] << "    " << low[i] << endl;
}
}
void main()
{
 Graph g(10);
 g.Setup2();
// g.Components();
 g.DfnLow(3);
 g.Out();
}