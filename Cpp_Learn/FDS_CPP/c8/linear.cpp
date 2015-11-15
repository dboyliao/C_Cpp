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

class SymbolTable
{
public:
  SymbolTable(int size = defaultsize) {
     buckets = size;
     ht = new identifier[buckets];
  };
   int LinearSearch(const identifier&, int (*) (identifier));
   void Insert(identifier, int (*) (identifier));
  private:
   int buckets;
   identifier *ht;
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
    int i = hashfunc(x);
    for (int j = i; ht[j].id && !(ht[j] == x); ) {
      j = (j++) % buckets;   // treat the table as circular
      if (j == i) return; // table full
    }
    if (ht[j] == x) return; // already there
    else ht[j] = x;
}

int SymbolTable::LinearSearch(const identifier& x, int (*hashfunc) (identifier) )
// Search the hash table @ht[0^..^b~-~1]@ (each bucket has exactly one slot) for @x@ using linear probing.
// @j@ is set such that if @x@ is already
// in the table, then @ht[j]@ = @x@.  If @x@ is not in the table and
// there is a free bucket, then @ht[j]~=~''@
// and @x@ can be entered here. @h@ is the hash function. */
{
    int i = hashfunc(x);
    for (int j = i; ht[j].id && !(ht[j] == x); ) {
      j = (j++) % buckets;   // treat the table as circular
      if (j == i) return -1; // back to start point
    }
    if (ht[j] == x) return j; else return -1;
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
   cout << st.LinearSearch(a, h) << endl;
   cout << st.LinearSearch(c, h) << endl;
   cout << st.LinearSearch(d, h) << endl;
}
