#include <iostream.h>

enum Boolean {FALSE, TRUE};
class GenList; // forward declaration

class GenListNode
{
friend class GenList;
friend int operator==(const GenList&, const GenList&);
friend int equal(GenListNode*, GenListNode*);
private:
    GenListNode *link;
    Boolean tag;
    union {
	char data;
	GenListNode *dlink;
    };
};


class GenList
{
friend int operator==(const GenList&, const GenList&);
friend int equal(GenListNode*, GenListNode*);
private:
    GenListNode *first;
    GenListNode*  Copy(GenListNode*);
    int depth(GenListNode*);
//    void Delete(GenListNode*);
public:
    void Copy(const GenList&);
//    ~GenList();
    int depth();
    void Init();
};


void GenList::Copy(const GenList& l)
{
    first = Copy(l.first);
}

/*

GenList::~GenList()
{
    Delete(first);
    first = 0;
}
*/


int operator==(const GenList& l, const GenList& m)
{
    return equal(l.first, m.first);
}


int GenList::depth()
{
    return depth(first);
}


void GenList::Init()
{
    GenListNode *second, *third, *fourth;
    first = new GenListNode;
    first->tag = FALSE; first->data = 'b'; first->link =  second =
	       new GenListNode;
    second->tag = TRUE; second->link = 0; second->dlink = third =
	       new GenListNode;
    third->tag = FALSE; third->data = 'b'; third->link = fourth
	     = new GenListNode;
    fourth->tag = FALSE; fourth->data = 'c'; fourth->link = 0;
}


GenListNode* GenList::Copy(GenListNode* p)
{
    GenListNode *q = 0;
    if (p) {
	q = new GenListNode;
	q->tag = p->tag;
	if (! p->tag) q->data = p->data;
	else q->dlink = Copy(p->dlink);
	q->link = Copy(p->link);
    }
    return q;
}


int equal(GenListNode* s, GenListNode *t)
{
    int x;
    if ((!s) && (!t)) return 1;
    if (s && t && (s->tag == t->tag)) {
	    if (! s->tag)
		if (s->data == t->data) x = 1; else x = 0;
	    else x = equal(s->dlink, t->dlink);
	    if (x) return  equal(s->link, t->link);
    }
    return 0;
}


int GenList::depth(GenListNode *s)
{
    if (!s) return 0;
    GenListNode *p = s; int m = 0;
    while (p) {
	if (p->tag) {
	    int n = depth(p->dlink);
	    if (m < n) m = n;
	}
	p = p->link;
    }
    return m+1;
}

/*

void GenList::Delete(GenListNode* x)
{
    x->ref--;
    if (!x->ref)
    {
	GenListNode *y = x;
	while (y->link) { y = y->link; if (y->tag) Delete(y->dlink);}
	y->link = av;
	av = x;
    }
}
*/

main()
{
GenList l;
l.Init();
GenList m;
m.Copy(l);
if (l == m) cout << "equal" << endl;
cout << "depth: " << l.depth();
}