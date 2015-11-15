#include <iostream.h>
const int DefaultSize = 10;
enum Boolean {FALSE, TRUE};

template <class Type>
class Bag
{
friend ostream& operator<<(ostream&, Bag<Type>&);
public:
   Bag (int MaxSize = DefaultSize); // constructor
   ~Bag(); // destructor

   void Add(const Type&); // insert element into bag
   Type* Delete(Type&); // delete element from bag

   Boolean IsFull();  // return TRUE if the bag is full; FALSE otherwise
   Boolean IsEmpty(); // return TRUE if the bag is empty; FALSE otherwise

private:
   void Full(); //  action when bag is full
   void Empty(); // action when bag is empty

   Type *array;
   int MaxSize; // size of array
   int top; // highest position in array that contains an element
};

template <class Type>
Bag<Type>::Bag (int MaxBagSize): MaxSize(MaxBagSize)
{
   array = new Type[MaxSize];
   top = -1;
}

template <class Type>
Bag<Type>::~Bag()
{
   delete [ ] array;
}

template <class Type>
inline Boolean Bag<Type>::IsFull()
{
   if (top == MaxSize - 1) return TRUE;
   else return FALSE;
}

template <class Type>
inline Boolean Bag<Type>::IsEmpty()
{
   if (top == -1) return TRUE;
   else return FALSE;
}

template <class Type>
inline void Bag<Type>::Full()
{
   cerr << "Data structure is full" << endl;
}

template <class Type>
inline void Bag<Type>::Empty()
{
   cerr << "Data structure is empty" << endl;
}

template <class Type>
void Bag<Type>::Add(const Type& x)
{
   if (IsFull()) Full();
   else array[++top] = x;
}

template <class Type>
Type* Bag<Type>::Delete(Type& x)
{
   if (IsEmpty()) { Empty(); return 0; }
   int deletePos = top / 2;
   x = array[deletePos];
   for (int index = deletePos; index < top; index++)
     array[index] = array[index + 1];   //compact upper half of array
   top--;
   return &x;
}

template <class Type>
ostream& operator<<(ostream& os, Bag<Type>& b)
{
   for (int i = 0; i <= b.top; i++)
     os << b.array[i] << " ";
   os << endl;
   return os;
}

void main()
{
    Bag<int> a(10);
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