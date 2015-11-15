#include <iostream.h>
#include <fstream.h>

enum Boolean { FALSE, TRUE};

class ListNode {
friend void equivalence();
private:
    int data;
    ListNode *link;
    ListNode(int);
};

typedef ListNode* ListNodePtr;
// so we can create an array of pointers using new

ListNode::ListNode(int d)
{
    data = d;
    link = 0;
}

void equivalence()
// Input the equivalence pairs and output the equivalence classes
{
    ifstream inFile( "equiv.in", ios::in); // "equiv.in" is the input file
    if (!inFile)
    {
       cerr << "Cannot open input file " << endl;
       return;
    }

    int i, j, n;
    inFile >> n;  // read number of objects

    // initialize @seq@ and @out@
    ListNodePtr *seq = new ListNodePtr[n];
    Boolean *out = new Boolean[n];
    for (i = 0; i < n; i++) {
	 seq[i] = 0;
	 out[i] = FALSE;
    }

    // Phase 1: input equivalence pairs
    inFile >> i >> j;
    while (inFile.good())  // check end of file
    {
       ListNode *x = new ListNode(j); x->link = seq[i]; seq[i] = x; // add @j@ to @seq[i]@
       ListNode *y = new ListNode(i); y->link = seq[j]; seq[j] = y; // add @i@ to @seq[j]@
       inFile  >> i >> j;
    }

    // Phase 2: output equivalence classes
    for (i = 0; i < n; i++)
	if (out[i] == FALSE) { // needs to be output
	    cout << endl << "A new class: " << i;
	    out[i] = TRUE;
	    ListNode *x = seq[i]; ListNode *top = 0; // init stack
	    while (1) // find rest of class
	    {
		while (x) { // process the list
		   j = x->data;
		   if (out[j] == FALSE) {
		       cout << ", " << j;
		       out[j] = TRUE;
		       ListNode *y = x ->link;
		       x->link = top;
		       top = x;
		       x = y;
		   }
		   else x = x->link;
		} // end of \fBwhile\fR(@x@)
		if (!top) break;
		else {
		    x = seq[top->data];
		    top = top->link; // unstack
		}
	    }  // end of while(1)
	} // end of \fBif\fR(@out[i])@
	delete [] seq;
	delete [] out;
} // end of @equivalence@

main()
{
equivalence();
}