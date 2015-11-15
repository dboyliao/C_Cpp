#ifndef _IOSTREAM_H
#include <iostream.h>
#define _IOSTREAM_H
#endif

enum Boolean { FALSE, TRUE};

class ThreadedTree;

class ThreadedNode {
friend class ThreadedTree;
friend class ThreadedInorderIterator;
private:
    Boolean LeftThread;
    ThreadedNode *LeftChild;
    char data;
    ThreadedNode *RightChild;
    Boolean RightThread;

    ThreadedNode() {LeftChild = RightChild = 0;};
    ThreadedNode(char ch) { data = ch;};
    ThreadedNode(char ch, ThreadedNode *lefty, ThreadedNode *righty,
		 Boolean lthread, Boolean rthread)
    { data = ch; LeftChild = lefty; RightChild = righty;
      LeftThread = lthread;  RightThread = rthread;};
};

class ThreadedTree {
friend class ThreadedInorderIterator;
private:
    ThreadedNode *root;
public:
    void setup();
    ThreadedTree() {
	root = new ThreadedNode;
	root->RightChild = root->LeftChild = root;
	root->LeftThread = TRUE; root->RightThread = FALSE;
    };
    void InsertRight(ThreadedNode*, char);
    ThreadedNode* ThreadedTree::InorderSucc(ThreadedNode*);
};

ThreadedNode* ThreadedTree::InorderSucc(ThreadedNode *current)
{
    ThreadedNode *temp = current->RightChild;
    if (! current->RightThread)
       while (! temp->LeftThread) temp = temp->LeftChild;
    return temp;
}


void ThreadedTree::InsertRight(ThreadedNode *s, char ch)
// Create node @r@; store @ch@ in @r@; insert @r@ as the right child of @s@
{
    ThreadedNode *r = new ThreadedNode(ch);
    r->RightChild = s->RightChild;
    r->RightThread = s->RightThread;
    r->LeftChild = s;
    r->LeftThread = TRUE; // \fILeftChild\fR is a thread
    s->RightChild = r; // attach @r@ to @s@
    s->RightThread = FALSE;
    if (! r->RightThread) {
	ThreadedNode *temp = InorderSucc(r); // returns the inorder successor of @r@
	temp->LeftChild = r;
    }
}

class ThreadedInorderIterator {
public:
   void Inorder();
   char *Next();
   ThreadedInorderIterator(ThreadedTree tree): t (tree) {
       CurrentNode = t.root;
   };
private:
   ThreadedTree t;
   ThreadedNode *CurrentNode;
};

char* ThreadedInorderIterator::Next()
// Find the inorder successor of \fICurrentNode\fR in a threaded binary tree
{
    ThreadedNode *temp = CurrentNode->RightChild;
    if (! CurrentNode->RightThread)
       while (! temp->LeftThread) temp = temp->LeftChild;
    CurrentNode = temp;
    if (CurrentNode == t.root) return 0; // all tree nodes have been traversed
    else return &CurrentNode->data;
}

void ThreadedInorderIterator::Inorder()
{
    for (char *ch = Next(); ch; ch = Next()) cout << *ch << endl;
}



void ThreadedTree::setup()
{
    ThreadedNode *A, *B, *C, *D, *E, *F, *G, *H, *I;

    root->LeftChild = A = new ThreadedNode('A', 0, 0, FALSE, FALSE);
    root->LeftThread = FALSE;

    A->LeftChild = B = new ThreadedNode('B', 0, 0, FALSE, FALSE);
    A->RightChild = C = new ThreadedNode('C', 0, 0, FALSE, FALSE);

    B->LeftChild = D = new ThreadedNode('D', 0, 0, FALSE, FALSE);
    B->RightChild = E = new ThreadedNode('E', 0, 0, TRUE, TRUE);

    D->LeftChild = H = new ThreadedNode('H', 0, 0, TRUE, TRUE);
    D->RightChild = I = new ThreadedNode('I', 0, 0, TRUE, TRUE);

    C->LeftChild = F = new ThreadedNode('F', 0, 0, TRUE, TRUE);
    C->RightChild = G = new ThreadedNode('G', 0, 0, TRUE, TRUE);

    H->LeftChild = root; H->RightChild = D;
    I->LeftChild = D; I->RightChild = B;
    E->LeftChild = B; E->RightChild = A;
    F->LeftChild = A; F->RightChild = C;
    G->LeftChild = C; G->RightChild = root;

    InsertRight(A, 'X');
    InsertRight(E, 'Y');
}



void main()
{
ThreadedTree t;
t.setup();
ThreadedInorderIterator ti(t);
ti.Inorder();
}

