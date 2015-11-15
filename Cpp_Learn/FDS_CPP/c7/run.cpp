

class Element
{
public:
   int key;
   int other;
   Element(){other = 0;};
};


void runs(Element *r)
{
    r = new Element[k];
    int *key = new int[k]; int *rn = new int[k]; int *l = new int[k];
    for (int i = 0; i < k; i++) {  // input records
	InputRecord(r[i]); rn[i] = 1;
    }
    InitializeLoserTree();
    q = l[0]; // tournament winner

    int rq = 1; int rc = 1; int rmax = 1; int LastKey = MAXINT;
    while(1) { // output runs
	if (rq != rc) { // end of run
	    output end of run marker;
	    if (rq > rmax) return;
	    else rc = rq;
	}
	// output record r[q]
	WriteRecord(r[q]); LastKey = key[q];
	// input new record into tree
	if (end of input) rn[q] = rmax + 1;
	else {
	    ReadRecord(r[q]);
	    if (key[q] < LastKey)  // new record belongs to next run
	       rn[q] = rmax = rq + 1;
	    else rn[q] = rc;
	}
	rq = rn[q];

	// adjust losers
	for (t = (k+q)/2; t; t /= 2;) // @t@ is initialized to be parent of @q@
	    if ((rn[l[t]] < rq) || ((rn[l[t]] == rq) && (key[l[t]] < key[q])))
	    { // @t@ is the winner
		int temp = q; q = l[t]; l[t] = temp;
		rq = rn[q];
	    }
    }
    delete [] r; delete [] key;
    delete [] rn; delete [] l;
}

main()
{

}