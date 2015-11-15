#include <iostream.h>

class Stack;  // forward declaration

class StackNode {
friend class Stack;
friend ostream& operator<<(ostream&, StackNode);
friend ostream& operator<<(ostream&, Stack);
private:
    int data;
    StackNode *link;
    StackNode(int d = 0, StackNode *l = 0) : data(d), link(l) {}; // constructor
};

ostream& operator<<(ostream& os, StackNode n)
{
     os << n.data << endl;
     return os;
}


class Stack {
friend ostream& operator<<(ostream&, Stack);
private:
    StackNode *top;
    void StackEmpty() {};
public:
    Stack() { top = 0;};  // constructor
    void Add(const int);
    int* Delete(int&);
};

ostream& operator<<(ostream& os, Stack l)
{
    StackNode *temp = l.top;
    while (temp)
    {
	 os << (*temp);
	 temp = temp->link;
    }
    return os;
}

void Stack::Add(const int y)
{
    top = new StackNode(y, top);
}

int* Stack::Delete(int& retvalue)
//Delete top node from stack and return a pointer to its data
{
    if (top == 0) {StackEmpty(); return 0;} // return null pointer constant
    StackNode *x = top;
    retvalue = top->data;  // get \fIdata\fR data member of top node
    top = x->link; // remove top node
    delete x;     // free the node
    return &retvalue;    // return pointer to data
}

main()
{
  Stack s[50];
  s[15].Add(20);
  s[15].Add(35);
  int retvalue;
  cout << s[15] << endl;
  cout << *s[15].Delete(retvalue);
  cout << s[15];
}