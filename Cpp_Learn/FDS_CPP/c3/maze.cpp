#include <iostream.h>
#include <fstream.h>

const int DefaultSize = 10000;
enum Boolean {FALSE, TRUE};

template <class KeyType>
class Stack
{
// \fBobjects\fR: A finite ordered list with zero or more elements.

friend  ostream& operator<<(ostream&, Stack<KeyType>& );
public:
    Stack(int MaxStackSize = DefaultSize);
    // Create an empty stack whose maximum size is \fIMaxStackSize\fR

    Boolean IsFull();
    /* if number of elements in the stack is equal to the maximum size of
       the stack, return TRUE (1); otherwise, return FALSE (0) */

    void Add (const KeyType& item);
    // if IsFull(), then StackFull(); else insert item into the top of the stack.

    Boolean IsEmpty();
    // if number of elements in the stack is equal to 0, return TRUE (1) else return FALSE (0).

    KeyType* Delete(KeyType&);
    // if IsEmpty(), then StackEmpty(); else remove and return the topmost element of the stack

    void StackEmpty() {cout << "empty" << endl;};
    void StackFull() {cout << "full" << endl;};
    void Output();
private:
    int top;
    KeyType *stack;
    int MaxSize;
};

template <class KeyType>
Stack<KeyType>::Stack (int MaxStackSize) : MaxSize(MaxStackSize)
{
    stack = new KeyType[MaxSize];
    top = -1;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsFull()
{
    if (top == MaxSize -1) return TRUE;
    else return FALSE;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsEmpty()
{
    if (top == -1) return TRUE;
    else return FALSE;
}

template <class KeyType>
void Stack<KeyType>::Add (const KeyType& x)
// add x to the stack
{
    if (IsFull()) StackFull();
    else stack[++top] = x;
}

template <class KeyType>
KeyType* Stack<KeyType>::Delete (KeyType& x)
// remove and return top element from stack
{
    if (IsEmpty()) {StackEmpty(); return 0;}
    x = stack[top--];
    return &x;
}

template <class KeyType>
ostream& operator<<(ostream& os, Stack<KeyType>& s)
{
  os << "top = " << s.top << endl;
  for (int i = 0; i <= s.top; i++)
      os << i << ":" << s.stack[i] << endl;
  return os;
}

struct offsets {
   int a, b;
};

enum directions {N, NE, E, SE, S, SW, W, NW};
offsets move[8];

struct items {
  int x, y, dir;
};

ostream& operator<<(ostream& os, items& item)
{
   return os << item.x << "," << item.y << ","  << item.dir;
}

int maze[100][100];
int mark[100][100];

void path(int m, int p)
// Output a path (if any) in the maze; @maze@[0,@i@] = @maze[m+1,i@] =
// @maze[j@,0] = @maze[j,p+1@] = 1, 0 \(<= @i@ \(<= @p+1@, 0 \(<= @j@ \(<= @m@+1.
{
     ofstream outFile("stack.pos", ios::out);
     if (!outFile) {
      cerr << "cannot open stack.pos for output" << endl;
      return;
   };
  //start at (1,1)
  mark[1][1] = 1;
  Stack<items> stack(m*p);
  items temp;
  temp.x = 1; temp.y = 1; temp.dir = E;
  stack.Add(temp);

  while (!stack.IsEmpty()) // stack not empty
  {
    temp = *stack.Delete(temp); // unstack
    int i = temp.x; int j = temp.y; int d = temp.dir;
    while (d < 8) // move forward
    {
       outFile << i << " " << j << " " << d << endl;
       int g = i + move[d].a; int h = j + move[d].b;
       if ((g == m) && (h == p)) { // reached exit
	  // output @path@
	  cout << stack;
	  cout << i << " " << j << endl;
	  cout << m << " " << p << endl;
	  return;
       }
       if ((!maze[g][h]) && (!mark[g][h])) { // new position
	  mark[g][h] = 1;
	  temp.x = i;  temp.y = j; temp.dir = d+1;
	  stack.Add(temp); // stack it
	  i = g; j = h; d = N; // move to (@g,h@)
       }
       else d++; // try next direction
    }
  }
  cout << "no path in maze " << endl;
}


void main()
{
   ifstream inFile( "maze.in", ios::in);
   if (!inFile) {
      cerr << "cannot open maze.in for input" << endl;
      return;
   }

   move[N].a = -1; move[N].b = 0;
   move[NE].a = -1; move[NE].b = 1;
   move[E].a = 0; move[E].b = 1;
   move[SE].a = 1; move[SE].b = 1;
   move[S].a = 1; move[S].b = 0;
   move[SW].a = 1; move[SW].b = -1;
   move[W].a =  0; move[W].b = -1;
   move[NW].a = -1; move[NW].b = -1;

   char ch;
   for (int i = 0; i < 14; i++)
       for (int j = 0; j < 17; j++)
       {
	  if ( (!i) || (!j) || (i == 13) || (j == 16))
	      maze[i][j] = 1;
	  else {
	     inFile >> ch;
	     maze[i][j] = ch - '0';
	  };
	  mark[i][j] = 0;

       }
   for (i = 0; i <= 13; i++)
   {
       for (int j = 0; j <= 16; j++)
	  cout << maze[i][j] << " ";
       cout << endl;
   }
  path(12, 15);
}