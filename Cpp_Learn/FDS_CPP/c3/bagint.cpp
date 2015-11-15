#include <iostream.h>
const int DefaultSize = 10;
enum Boolean {FALSE, TRUE};

class Bag
{
friend ostream& operator<<(ostream&, Bag&);
public:
   Bag (int MaxSize = DefaultSize); // constructor
   ~Bag(); // destructor

   void Add(int); // insert element into bag
   int* Delete(int&); // delete element from bag

   Boolean IsFull();  // return TRUE if the bag is full; FALSE otherwise
   Boolean IsEmpty(); // return TRUE if the bag is empty; FALSE otherwise

private:
   void Full(); //  action when bag is full
   void Empty(); // action when bag is empty

   int *array;
   int MaxSize; // size of array
   int top; // highest position in array that contains an element
};

Bag::Bag (int MaxBagSize): MaxSize(MaxBagSize)
{
   array = new int[MaxSize];
   top = -1;
}

Bag::~Bag()
{
   delete [ ] array;
}

inline Boolean Bag::IsFull()
{
   if (top == MaxSize - 1) return TRUE;
   else return FALSE;
}

inline Boolean Bag::IsEmpty()
{
   if (top == -1) return TRUE;
   else return FALSE;
}

inline void Bag::Full()
{
   cerr << "Data structure is full" << endl;
}

inline void Bag::Empty()
{
   cerr << "Data structure is empty" << endl;
}

void Bag::Add(int x)
{
   if (IsFull()) Full();
   else array[++top] = x;
}

int* Bag::Delete(int& x)
{
   if (IsEmpty()) { Empty(); return 0; }
   int deletePos = top / 2;
   x = array[deletePos];
   for (int index = deletePos; index < top; index++)
     array[index] = array[index + 1];   //compact upper half of array
   top--;
   return &x;
}

ostream& operator<<(ostream& os, Bag& b)
{
   for (int i = 0; i <= b.top; i++)
     os << b.array[i] << " ";
   os << endl;
   return os;
}

void main()
{
    Bag a(10);
    cout << a;

    a.Add(1);
    cout << a;

    a.Add(2);
    cout << a;

    a.Add(3);
    cout << a;

    int i;
    a.Delete(i);
    cout << a;

    a.Delete(i);
    cout << a;

    a.Delete(i);
    cout << a;
}