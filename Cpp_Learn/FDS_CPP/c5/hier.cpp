#include <iostream.h>

enum Boolean {FALSE, TRUE};
const int DefaultSize = 20;

class MaxPQ {
public:
    virtual void Insert(const int) = 0;
    virtual int* DeleteMax(int&) = 0;
};

class SearchStruct {
public:
    virtual void Insert(const int) = 0;
    virtual int* Delete(int&) = 0;
    virtual Boolean Search(const int) = 0;
};

class BinaryTree {
public:
    virtual void inorder();
    virtual void setup();
    BinaryTree() {root = 0;};
protected:
    class BinaryTreeNode {
    public:
	BinaryTreeNode *LeftChild;
	int data;
	BinaryTreeNode *RightChild;
	BinaryTreeNode(int i, BinaryTreeNode *l, BinaryTreeNode *r)
	{
	   data = i;
	   l = LeftChild;
	   r = RightChild;
	}
    };
    BinaryTreeNode *root;
    virtual void inorder(BinaryTreeNode *);
};

void BinaryTree::inorder()
{
   inorder(root);
}

void BinaryTree::inorder(BinaryTreeNode *CurrentNode)
{
     if (CurrentNode) {
	 inorder(CurrentNode->LeftChild);
	 cout << CurrentNode->data;
	 inorder(CurrentNode->RightChild);
     }
}


class CompleteBinaryTree : public BinaryTree
{
public:
    virtual void inorder(); // hides BinaryTree::inorder
    virtual void setup();
    CompleteBinaryTree(int sz = DefaultSize) : MaxSize(sz), n(0) {
       tree = new int[MaxSize+1];
    };
protected:
    int *tree, MaxSize, n;
    virtual void inorder(int); // hides BinaryTree::inorder
};

void CompleteBinaryTree::inorder()
{
   inorder(1);
}

void CompleteBinaryTree::inorder(int current)
{
     if (current <= n) {
	 inorder(2*current);
	 cout << tree[current];
	 inorder(2*current+1);
     }
}

class MaxHeap : public MaxPQ, public CompleteBinaryTree
{
public:
   MaxHeap (int sz = DefaultSize) : CompleteBinaryTree(sz) {};
   virtual void Insert(const int);
   virtual int* DeleteMax(int&);
};

class WinnerTree : public CompleteBinaryTree
{
public:
   WinnerTree (int sz = DefaultSize) : CompleteBinaryTree(sz) {};
};

void MaxHeap::Insert(const int i) {}

int* MaxHeap::DeleteMax(int& i) {return &i;}

class BST : public SearchStruct, public BinaryTree
{
public:
   BST() {root = 0;};
   virtual void Insert(const int);
   virtual int* Delete(int&);
   virtual Boolean Search(const int);
};

void BST::Insert(const int i)
{}

Boolean BST::Search(const int i)
{return TRUE;}

int* BST::Delete(int& i)
{ return &i;}

void BinaryTree::setup()
{
    root = new BinaryTreeNode(10,0,0);
    root->LeftChild = new BinaryTreeNode(5,0,0);
    root->LeftChild->LeftChild = new BinaryTreeNode(2, 0, 0);
    root->LeftChild->RightChild = new BinaryTreeNode(8, 0, 0);
    root->LeftChild->LeftChild->LeftChild = new BinaryTreeNode(1, 0, 0);
}

void CompleteBinaryTree:: setup()
{
    tree[1] = 1; tree[2] = 2; tree[3] = 3;
    tree[4] = 4; tree[5] = 5; n = 5;
}



main()
{
  BST bst;
  CompleteBinaryTree cbt(5);
  MaxHeap h(5);
  BinaryTree b;

  cbt.setup();
  b.setup();
  h.setup();
  bst.setup();

  cbt.inorder();  cout << endl;
  b.inorder();  cout << endl;
  h.inorder();  cout << endl;
  bst.inorder(); cout << endl;

}