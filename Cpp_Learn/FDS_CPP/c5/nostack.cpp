#ifndef _IOSTREAM_H
#include <iostream.h>
#define _IOSTREAM_H
#endif

class Tree;

class TreeNode {
friend class Tree;
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

class Tree {
private:
    TreeNode *root;
public:
    void setup();
    void NoStackInorder();
};

void Tree::setup()
{
    root = new TreeNode('A',0,0);
    root->LeftChild = new TreeNode('B',0,0);
    root->LeftChild->LeftChild = new TreeNode('C', 0, 0);
    root->LeftChild->RightChild = new TreeNode('D', 0, 0);
    root->LeftChild->LeftChild->LeftChild = new TreeNode('E', 0, 0);
}

void Tree::NoStackInorder()
// Inorder traversal of binary tree using a fixed amount of additional storage
{
   if (!root) return; // empty binary tree
   TreeNode *top = 0, *LastRight = 0, *p, *q, *r, *r1;
   p = q = root;
   while (1) {
       while (1) {
	   if ((!p->LeftChild) && (!p->RightChild)) { // leaf node
	       cout << p->data; break;
	   }
	   if (!p->LeftChild) { // visit p and move to p->RightChild
	       cout << p->data;
	       r = p->RightChild; p->RightChild = q;
	       q = p; p = r;
	   }
	   else { // move to p->LeftChild
	       r = p->LeftChild; p->LeftChild = q;
	       q = p; p = r;
	   }
       } // end of inner \fBwhile\fR
       /* @p@ is a leaf node, move upward to a node whose
	  right subtree has not yet been examined */
       TreeNode *av = p;
       while (1) {
	   if (p == root) return;
	   if (!q->LeftChild) { // @q@ is linked via \fRRightChild\fR
	       r = q->RightChild; q->RightChild = p;
	       p = q; q = r;
	   }
	   else if (!q->RightChild) { // @q@ is linked via \fILeftChild\fR
	       r = q->LeftChild; q->LeftChild = p;
	       p = q; q = r; cout << p->data;
	   }
	   else // check if @p@ is a \fIRightChild\fR of @q@
	     if (q == LastRight) {
		 r = top; LastRight = r->LeftChild;
		 top = r->RightChild; // unstack
		 r->LeftChild = r->RightChild = 0;
		 r = q->RightChild; q->RightChild = p;
		 p = q; q = r;
	     }
	     else { // @p@ is \fILeftChild\fR of @q@
		 cout << q->data; // visit @q@
		 av->LeftChild = LastRight; av->RightChild = top;
		 top = av; LastRight = q;
		 r = q->LeftChild; q->LeftChild = p; // restore link to @p@
		 r1 = q->RightChild; q->RightChild = r;
		 p = r1;
		 break;
	     }
       } // end of inner \fBwhile\fR loop
   } // end of outer \fBwhile\fR loop
}

void main()
{
Tree t;
t.setup();
t.NoStackInorder();
}