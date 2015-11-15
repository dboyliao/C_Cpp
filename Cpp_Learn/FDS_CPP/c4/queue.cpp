#include <iostream.h>

class Queue;

class QueueNode {
friend class Queue;
friend ostream& operator<<(ostream&, QueueNode);
friend ostream& operator<<(ostream&, Queue);
private:
    int data;
    QueueNode *link;
    QueueNode(int d = 0, QueueNode *l = 0) : data(d), link(l) {};
};

ostream& operator<<(ostream& os, QueueNode n)
{
     os << n.data << endl;
     return os;
}


class Queue {
friend ostream& operator<<(ostream&, Queue);
private:
    QueueNode *front, *rear;
    void QueueEmpty() {};
public:
    Queue() { front = rear = 0;};
    void Add(const int);
    int* Delete(int&);
};

ostream& operator<<(ostream& os, Queue l)
{
    QueueNode *temp = l.front;
    while (temp)
    {
	 os << (*temp);
	 temp = temp->link;
    }
    return os;
}

void Queue::Add(const int y)
{
    if (front == 0) front = rear = new QueueNode(y, 0); // empty queue
    else rear = rear->link = new QueueNode(y, 0); // update \fIrear\fR
}

int* Queue::Delete(int& retvalue)
// delete the first node in queue and return a pointer to its data
{
    if (front == 0) {QueueEmpty(); return 0;};
    QueueNode *x = front;
    retvalue = front->data; // get data
    front = x->link;      // delete front node
    delete x; // free the node
    return &retvalue;
}

main()
{
  int retvalue;
  int m = 50;
  Queue *s = new Queue[m];
  s[15].Add(20);
  s[15].Add(35);
  s[15].Add(45);
  cout << s[15] << endl;
  cout << *s[15].Delete(retvalue) << endl;
  cout << s[15] << endl;
  cout << *s[15].Delete(retvalue) << endl;
  cout << s[15] << endl;
  cout << *s[15].Delete(retvalue) << endl;
  cout << s[15] << endl;
}