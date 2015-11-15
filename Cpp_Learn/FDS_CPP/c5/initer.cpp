#ifndef _IOSTREAM_H
#include <iostream.h>
#define _IOSTREAM_H
#endif

enum Boolean { FALSE, TRUE};

template <class Type> class Stack;

template <class Type>
class StackNode {
friend class Stack<Type>;
private:
    Type data;
    StackNode<Type> *link;
    StackNode(Type def, StackNode<Type> *l = 0)
    {
       data = def;
       link = l;
    };
};

template <class Type>
class Stack {
private:
    StackNode<Type> *top;
public:
    Stack() { top = 0;};
    void Add(Type);
    Type* Delete(Type&);
    Boolean IsEmpty(){ if (!top) return TRUE; else return FALSE;};
};

template <class Type>
void Stack<Type>::Add(Type y)
{
    top = new StackNode<Type>(y, top);
}

template <class Type>
Type* Stack<Type>::Delete(Type& retvalue)
//Delete top node from stack and return its data field
{
    if (top == 0) {return 0;} // return NULL pointer
    StackNode<Type> *x = top;
    retvalue = top->data;  // get \fIdata\fR data member of top node
    top = x->link; // remove top node
    delete x;     // free the node
    return &retvalue;    // return pointer to data
}

class Tree;

class TreeNode {
friend class Tree;
friend class InorderIterator;
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
friend class InorderIterator;
private:
    TreeNode *root;
public:
    void inorder();
    void setup();
};

class InorderIterator {
public:
   char *Next();
   InorderIterator(Tree tree) :t(tree) { CurrentNode = t.root;};
private:
   Tree t;
   Stack<TreeNodePtr> s;
   TreeNodePtr CurrentNode;
};

char *InorderIterator::Next()
{
	while (CurrentNode) {
	  s.Add(CurrentNode);
	  CurrentNode = CurrentNode->LeftChild;
	}
	if (! s.IsEmpty()) {
	    CurrentNode = *s.Delete(CurrentNode);
	    char& temp = CurrentNode->data;
	    CurrentNode = CurrentNode->RightChild;
	    return &temp;
	}
	else return 0;;
}

void Tree::setup()
{
    root = new TreeNode('A',0,0);
    root->LeftChild = new TreeNode('B',0,0);
    root->LeftChild->LeftChild = new TreeNode('C', 0, 0);
    root->LeftChild->RightChild = new TreeNode('D', 0, 0);
    root->LeftChild->LeftChild->LeftChild = new TreeNode('E', 0, 0);
}

void Tree::inorder()
{
    Stack<TreeNode*>  s;
    TreeNode *CurrentNode = root;
    while (1) {
	while (CurrentNode) {
	  s.Add(CurrentNode);
	  CurrentNode = CurrentNode->LeftChild;
	}
	if (! s.IsEmpty()) {
	    CurrentNode = *s.Delete(CurrentNode);
	    cout << CurrentNode->data << endl;
	    CurrentNode = CurrentNode->RightChild;
	}
	else break;
    }
}

void main()
{
   Tree t;
   t.setup();
   InorderIterator li(t);
   char *next = li.Next();
   while (next) {
       cout << *next;
       next = li.Next();
   }
}

