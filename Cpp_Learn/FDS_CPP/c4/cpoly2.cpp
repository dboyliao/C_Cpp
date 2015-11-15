#include <iostream.h>

// Tested p + q; 0 + p; p + 0; p + p; 0 + 0; p + (-p)
enum Boolean { FALSE, TRUE};

template <class Type> class CircList;
template <class Type> class CircListIterator;

struct Term
{
    int coef;
    int exp;
    void Init(int c, int e) { coef = c; exp = e;};
    Term() { exp = -1;}
};

ostream& operator<<(ostream& os, Term e)
{
 os << e.coef << " " << e.exp;
 return os;
}

template <class Type>
class ListNode {
friend class CircList<Type>;
friend class CircListIterator<Type>;
private:
    Type data;
    ListNode *link;
    ListNode(Type);
    ListNode() {};
};

template <class Type>
ListNode<Type>::ListNode(Type d)
{
    data = d;
    link = 0;
}

template <class Type>
class CircList {
friend class CircListIterator<Type>;
// friend class Polynomial;
public:
    CircList() {first = new ListNode<Type>; first->link = first; last = first; };
    CircList(Type t) {first = new ListNode<Type>(t); first->link = first; last = first; };
    CircList(const CircList&);
    ~CircList();
    void Attach(Type);
private:
    ListNode<Type> *first;
    ListNode<Type> *last;
    static ListNode<Type> *av;
};

ListNode<Term>* CircList<Term>::av = 0;

template <class Type>
class CircListIterator {
public:
    CircListIterator(const CircList<Type>& l): list(l) {current = l.first->link;}
    Type* Next();
    Type* First();
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
      return &current->data;
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


ostream& operator<<(ostream& os, CircList<Term>& l)
{
    CircListIterator<Term> li(l);
    if (!li.NotNull()) return os;
    os << *li.First() << endl;
    while  (li.NextNotNull())
	 os << *li.Next() << endl;
    return os;
}


template <class Type>
void CircList<Type>::Attach(Type k)
{
ListNode<Type> *newnode = new ListNode<Type>(k);
if (first == 0) first = last = newnode;
else {
   newnode->link = last->link;
   last->link = newnode;
   last = newnode;
   }
}

Term sp;

class Polynomial
{
friend ostream& operator<<(ostream&, Polynomial&);
friend Polynomial operator+(const Polynomial&, const Polynomial&);
private:
    CircList<Term> poly;
public:
    void Add(Term);
};

void Polynomial::Add(Term e)
{
poly.Attach(e);
}



template <class Type>
CircList<Type>::CircList(const CircList<Type>& l)
{
  if (l.first == 0) {first = 0; return;}
  first = new ListNode<Type>(l.first->data);
  ListNode<Type> *newnode = first;
  for (ListNode<Type>* current = l.first->link; current != l.first; current = current->link)
  {
      newnode->link = new ListNode<Type>(current->data);
      newnode = newnode->link;
  }
  newnode->link = first;
}

template <class Type>
CircList<Type>::~CircList()
// Erase the circular list pointed by first
{
    if (first)
    {
      ListNode<Type> *second = first->link; // second node
      first->link = av;  // first node linked to av
      av = second;  // second node of list becomes front of av list
      first = 0;
    }
}

ostream& operator<<(ostream& os, Polynomial& p)
{
   os << p.poly;
   return os;
}

char compare(int a, int b)
{
if (a==b) return '=';
if (a < b) return '<';
return '>';
}

Polynomial operator+(const Polynomial& a, const Polynomial& b)
{
    Term *p, *q, temp;
    CircListIterator<Term> Aiter(a.poly); CircListIterator<Term> Biter(b.poly);
    Polynomial c;

    p = Aiter.First(); q = Biter.First();

    while (1)
	switch (compare(p->exp,q->exp)) {
	    case '=':
		 if (p->exp == -1) return c;
		 else {
		   int sum = p->coef + q->coef;
		   if (sum) {
		      temp.Init(sum, q->exp);
		      c.poly.Attach(temp);
		   }
		   p = Aiter.Next();
		   q = Biter.Next();
		 }
		 break;
	    case '<':
		 temp.Init(q->coef, q->exp);
		 c.poly.Attach(temp);
		 q = Biter.Next();
		 break;
	    case '>':
		 temp.Init(p->coef, p->exp);
		 c.poly.Attach(temp);
		 p = Aiter.Next();
	}
}

main()
{
Polynomial p;
Polynomial *q = new Polynomial;

Term e;
cout << "start" << endl;
e.Init(3, 14); p.Add(e);
e.Init(2,8); p.Add(e);
e.Init(1,0); p.Add(e);
cout << "p" << endl << p << endl;

e.Init(-3,13) ; q->Add(e);
e.Init(-2,8); q->Add(e);
e.Init(-1,1) ; q->Add(e);

cout << "q" << endl << *q << endl;

Polynomial r = p + *q;
cout << "r = p + q" << endl << r << endl;



Polynomial s;
cout << "s" << endl << s << endl;

Polynomial t = s + s;
cout << "t = s + s" << endl << t << endl;

Polynomial u = p + p;
cout << "u = p + p" << endl << u << endl;
}