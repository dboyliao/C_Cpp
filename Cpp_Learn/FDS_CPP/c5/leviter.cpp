#ifndef _IOSTREAM_H
#include <iostream.h>
#define _IOSTREAM_H
#endif

enum Boolean { FALSE, TRUE};

template <class Type> class Queue;

template <class Type>
class QueueNode {
friend class Queue<Type>;
private:
    Type data;
    QueueNode<Type> *link;
    QueueNode(Type def, QueueNode<Type> *l = 0)
    {
       data = def;
       link = l;
    };
};

template <class Type>
class Queue {
private:
    QueueNode<Type> *front, *rear;
public:
    Queue() { front = rear = 0;};
    void Add(Type);
    Type* Delete(Type&);
    Boolean IsEmpty(){ if (!front) return TRUE; else return FALSE;};
};

template <class Type>
void Queue<Type>::Add(Type y)
{
    if (front == 0) front = rear = new QueueNode<Type>(y, 0); // empty queue
    else rear = rear->link = new QueueNode<Type>(y, 0); // update \fIrear\fR
}

template <class Type>
Type* Queue<Type>::Delete(Type& retvalue)
//Delete top node from stack and return its data field
{
    if (front == 0) {return 0;};
    QueueNode<Type> *x = front;
    retvalue = front->data; // get data
    front = x->link;      // delete front node
    if (front == 0) rear = 0; // queue becomes empty after deletion
    delete x; // free the node
    return &retvalue;
}

class Tree;

class TreeNode {
friend class Tree;
friend class LevelIterator;
private:
    TreeNode *LeftChild;
    char data;
    TreeNode *RightChild;
    TreeNode(char ch, TreeNode *Lefty, TreeNode *Righty)
    {
	data = ch;
	LeftChild = Lefty;
	RightChild = Righty;
    }
};

typedef TreeNode* TreeNodePtr;

class Tree {
friend class LevelIterator;
private:
    TreeNode *root;
public:
    void LevelOrder();
    void setup();
};

class LevelIterator {
public:
   char *Next();
   LevelIterator(Tree tree) {t = tree; CurrentNode = t.root;};
private:
   Tree t;
   Queue<TreeNodePtr> q;
   TreeNodePtr CurrentNode;
};

char* LevelIterator::Next()
{
   if (CurrentNode) {
       char temp =  CurrentNode->data;
       if (CurrentNode->LeftChild) q.Add(CurrentNode->LeftChild);
       if (CurrentNode->RightChild) q.Add(CurrentNode->RightChild);
       CurrentNode = *q.Delete(CurrentNode);
       return &temp;
   }
   return 0;
}

void Tree::setup()
{
    root = new TreeNode('A',0,0);
    root->LeftChild = new TreeNode('B',0,0);
    root->LeftChild->LeftChild = new TreeNode('C', 0, 0);
    root->LeftChild->RightChild = new TreeNode('D', 0, 0);
    root->LeftChild->LeftChild->LeftChild = new TreeNode('E', 0, 0);
}

void Tree::LevelOrder()
// Traverse the binary tree in level order
{
    Queue<TreeNode*>  q;
     TreeNode *CurrentNode = root;
    while (CurrentNode) {
	cout << CurrentNode->data << endl;
	if (CurrentNode->LeftChild) q.Add(CurrentNode->LeftChild);
	if (CurrentNode->RightChild) q.Add(CurrentNode->RightChild);
	CurrentNode = *q.Delete(CurrentNode);
    }
}

void main()
{
   Tree t;
   t.setup();
   LevelIterator li(t);
   char *next = li.Next();
   while (next) {
       cout << *next;
       next = li.Next();
   }
}

