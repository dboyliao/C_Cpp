#ifndef _IOSTREAM_H
#include <iostream.h>
#define _IOSTREAM_H
#endif

enum Boolean { FALSE, TRUE};

class Tree;

class TreeNode {
friend class Tree;
friend int equal(TreeNode*, TreeNode*);
private:
    TreeNode *LeftChild;
    char data;
    TreeNode *RightChild;
    TreeNode() {LeftChild = RightChild = 0;};
    TreeNode(char ch, TreeNode *Lefty, TreeNode *Righty)
    {
	data = ch;
	LeftChild = Lefty;
	RightChild = Righty;
    }
};

class Tree {
friend int operator==(const Tree&, const Tree&);
private:
    TreeNode *root;
    void inorder(TreeNode *);
    void preorder(TreeNode *);
    void postorder(TreeNode *);
    TreeNode* copy(TreeNode *);
public:
    void setup();
    void inorder();
    void preorder();
    void postorder();
    Tree(const Tree&);
    Tree() {root = 0;};
};

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
   inorder(root);
}

void Tree::preorder()
{
   preorder(root);
}

void Tree::postorder()
{
   postorder(root);
}

void Tree::inorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 inorder(CurrentNode->LeftChild);
	 cout << CurrentNode->data;
	 inorder(CurrentNode->RightChild);
     }
}

void Tree::preorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 cout << CurrentNode->data;
	 preorder(CurrentNode->LeftChild);
	 preorder(CurrentNode->RightChild);
     }
}

void Tree::postorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 postorder(CurrentNode->LeftChild);
	 postorder(CurrentNode->RightChild);
	 cout << CurrentNode->data;
     }
}

Tree::Tree(const Tree& s)
{
  root = copy(s.root);
}

TreeNode* Tree::copy(TreeNode *orignode)
{
  if (orignode) {
      TreeNode *temp = new TreeNode;
      temp->data = orignode->data;
      temp->LeftChild = copy(orignode->LeftChild);
      temp->RightChild = copy(orignode->RightChild);
      return temp;
  }
  else return 0;
}

// Driver
int operator==(const Tree& s, const Tree& t)
{
   return equal(s.root, t.root);
}

// Workhorse
int equal(TreeNode *a, TreeNode *b)
/* This function returns 0 if the subtrees at @a@ and @b@ are not
   equivalent. Otherwise, it will return 1 */
{
 if ((!a) && (!b)) return 1;  // both @a@ and @b@ are 0
 if (a && b &&                // both @a@ and @b@ are non-0
    (a->data == b->data)      // @data@ is the same
    && equal(a->LeftChild, b->LeftChild) // left subtrees are the same
    && equal(a->RightChild, b->RightChild) ) // right subtrees are the same
       return 1;
 return 0;
}

void main()
{
Tree t;
t.setup();
Tree s = t;
s.inorder();
cout << endl;
if (s == t) cout << 1; else cout << 0;
cout << endl;
}

