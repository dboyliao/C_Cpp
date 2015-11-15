#include <iostream.h>

const int defaultsize = 100;

struct identifier
{
char *id;
int n;
identifier(char*, int);
};

identifier::identifier(char *str = 0, int size = 0)
{
     n = size;
     if (n == 0) {id = 0; return;}
     id = new char[n];
     for (int i = 0; i < n; i++) id[i] = str[i];
 }

int operator==(identifier one, identifier two)
{
   if (one.n != two.n) return 0;
   for (int i = 0; i < one.n; i++)
     if (one.id[i] != two.id[i]) return 0;
   return 1;
}

class ListNode{
friend SymbolTable;
private:
    identifier ident;
    ListNode *link;
};

typedef ListNode* ListPtr;

class SymbolTable
{
public:
  SymbolTable(int size = defaultsize) {
     buckets = size;
     ht = new ListPtr[buckets];
  };
   identifier* ChainSearch(const identifier&, int (*) (identifier));
   void Insert(identifier, int (*) (identifier));
  private:
   int buckets;
   ListPtr *ht;
};

int h(identifier x)
{
  return (x.id[0] - 'a');
}

int g(identifier x)
{
  return (x.id[0] - 'a' +1);
}

void SymbolTable::Insert(identifier x, int (*hashfunc) (identifier))
{
    int j = hashfunc(x);
    ListNode *prev = 0;
    for (ListPtr ptr = ht[j]; ptr && !(ptr->ident == x); ptr = ptr->link)
       prev = ptr;
    if (ptr->ident == x) return; // already there
    ListNode *newnode = new ListNode;
    newnode->ident = x;
    newnode->link = 0;
    if (ht[j] == 0) ht[j] = newnode; // already there
    else prev->link = newnode;
}

identifier *SymbolTable::ChainSearch(const identifier& x, int (*hashfunc) (identifier) )
// Search the chained hash table @ht@ for @x@. On termination, return a pointer
// to the identifier in the hash table.  If the identifier does not exist, then return 0
{
    int j = hashfunc(x); // compute headnode address
    // search the chain starting at @ht[j]@
    for (ListPtr l = ht[j]; l; l = l->link)
	if (l->ident == x) return &l->ident;
    return 0;
}

void main()
{
   SymbolTable st(27);
   identifier a ("bcdef",5);
   identifier b ("bcdef",5);
   identifier c ("b",1);
   identifier d ("bc", 2);
   st.Insert(a, h);
   st.Insert(b, h);
   st.Insert(c, h);

//   if (a == b) cout << "OK1" << endl;
//   if (!(a == c)) cout << "OK2" << endl;
identifier *ix;

   ix = st.ChainSearch(a, h);
   if (ix)  cout << ix->id << endl;
   else cout << 0 << endl;
   ix = st.ChainSearch(c, h);
   if (ix) cout << ix->id  << endl;
   else cout << 0 << endl;
   ix = st.ChainSearch(d, h);
   if (ix) cout << ix->id  << endl;
   else cout << 0 << endl;
}
