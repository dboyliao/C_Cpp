#ifndef _IOSTREAM_H
#include <iostream.h>
#define _IOSTREAM_H
#endif

enum Boolean { FALSE, TRUE};
enum TypesOfData {LogicalNot, LogicalAnd, LogicalOr,
		  LogicalTrue, LogicalFalse};

class SatTree;

class SatNode {
friend class SatTree;
private:
    SatNode *LeftChild;
    TypesOfData data;
    Boolean value;
    SatNode *RightChild;
    SatNode() {LeftChild = RightChild = 0;};
    SatNode(TypesOfData tod, SatNode *Lefty, SatNode *Righty)
    {
	data = tod;
	LeftChild = Lefty;
	RightChild = Righty;
    }
};

class SatTree {
private:
    SatNode *root;
    void PostOrderEval(SatNode *);
public:
    void PostOrderEval();
    SatTree() {root = 0;};
    void setup();
    void rootvalue() {cout << root->value;};
};

void SatTree::setup()
{
    root = new SatNode(LogicalAnd,0,0);
    root->LeftChild = new SatNode(LogicalOr,0,0);
    root->LeftChild->LeftChild = new SatNode(LogicalFalse, 0, 0);
    root->LeftChild->RightChild = new SatNode(LogicalTrue, 0, 0);
    root->RightChild = new SatNode(LogicalNot, 0, 0);
    root->RightChild->RightChild = new SatNode(LogicalFalse, 0, 0);
}

void SatTree::PostOrderEval()
{
    PostOrderEval(root);
}

void SatTree::PostOrderEval(SatNode *s)
{
    if(s) {
	PostOrderEval(s->LeftChild);
	PostOrderEval(s->RightChild);
	switch (s->data) {
		case LogicalNot: s->value = ! s->RightChild->value; break;
		case LogicalAnd: s->value = s->LeftChild->value && s->RightChild->value;
				 break;
		case LogicalOr: s->value = s->LeftChild->value || s->RightChild->value;
				break;
		case LogicalTrue: s->value = TRUE; break;
		case LogicalFalse: s->value = FALSE;
	}
    }
}

void main()
{
SatTree t;
t.setup();
t.PostOrderEval();
t.rootvalue();
}

