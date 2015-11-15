#include <iostream.h>

class DblList;

class DblListNode {
friend class DblList;
private:
    int data;
    DblListNode *llink, *rlink;
};

class DblList {
public:
    void Insert(DblListNode*, DblListNode*);
    void Delete(DblListNode*);
private:
    DblListNode *first;  // points to head node
};

void DblList::Insert(DblListNode *p, DblListNode *x)
// insert node @p@ to the right of node @x@
{
    p->llink = x; p->rlink = x->rlink;
    x->rlink->llink = p; x->rlink = p;
}

void DblList::Delete(DblListNode *x)
{
    if (x == first) cerr << "Deletion of head node not permitted" << endl;
    else {
	x->llink->rlink = x->rlink;
	x->rlink->llink = x->llink;
	delete x;
    }
}

main()
{
   DblList intlist;
}