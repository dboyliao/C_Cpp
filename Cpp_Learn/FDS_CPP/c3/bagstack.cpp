#include <iostream.h>
int DefaultSize = 100;
enum Boolean {FALSE, TRUE};

class Bag
{
friend ostream& operator<<(ostream&, Bag&);
public:
   Bag (int MaxSize = DefaultSize); // constructor
   virtual ~Bag(); // destructor

   virtual void Add(int); // insert element into bag
   virtual int* Delete(int&); // delete element from bag

   virtual Boolean IsFull();  // return TRUE if the bag is full; FALSE otherwise
   virtual Boolean IsEmpty(); // return TRUE if the bag is empty; FALSE otherwise

protected:
   virtual void Full(); //  action when bag is full
   virtual void Empty(); // action when bag is empty

   int *array;
   int MaxSize; // size of array
   int top; // highest position in array that contains an element
};

class Stack : public Bag
{
public:
   Stack (int MaxSize = DefaultSize); // constructor
   ~Stack(); // destructor
   int* Delete(int&); // delete element from bag
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

Boolean Bag::IsFull()
{
   if (top == MaxSize - 1) return TRUE;
   else return FALSE;
}

Boolean Bag::IsEmpty()
{
   if (top == -1) return TRUE;
   else return FALSE;
}

void Bag::Full()
{
   cerr << "Data structure is full" << endl;
}

void Bag::Empty()
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

Stack::Stack (int MaxStackSize) : Bag(MaxStackSize) {}

Stack::~Stack() {}

int* Stack::Delete(int& x)
{
   if (IsEmpty()) { Empty(); return 0; }
   x = array[top--];
   return &x;
}

void main()
{
    Bag *a = new Stack(10);
    Bag *b = new Bag(10);
    Stack *c = new Stack;
    cout << *a;

    a->Add(1);
    cout << *a;

    a->Add(2);
    cout << *a;

    a->Add(3);
    cout << *a;

    int i;
    a->Delete(i);
    cout << *a;

    a->Delete(i);
    cout << *a;

    a->Delete(i);
    cout << *a;

    delete a;
    delete b;
}