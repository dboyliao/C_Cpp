#include <iostream.h>
#include <fstream.h>

enum Boolean { FALSE, TRUE};

struct Triple
{
int value, row, col;
};

ostream& operator<<(ostream& os, Triple& t)
{
os <<  "row: " << t.row <<
       " col: " << t.col <<
       " value: " << t.value << endl;
return os;
}

class Matrix; // forward declaration

class MatrixNode
{
friend class Matrix;
friend istream& operator>>(istream&, Matrix&); // for reading in a matrix
friend ostream& operator<<(ostream&, Matrix&);
private:
      MatrixNode *down, *right;
      Boolean head;
      union { // anonymous union
	  MatrixNode *next;
	  Triple triple;
      };
MatrixNode(Boolean, Triple*);  // constructor
};

MatrixNode::MatrixNode(Boolean b, Triple* t)
{
head = b;
if (b) {right = next = this;} // row/column head node
else triple = *t;  // head node for list of headnodes OR element node
}

typedef MatrixNode* MatrixNodePtr;

class Matrix {
friend istream& operator>>(istream&, Matrix& m);
friend ostream& operator<<(ostream&, Matrix& m);
private:
   MatrixNode *headnode;
public:
   ~Matrix();
};

istream& operator>>(istream& is, Matrix& matrix)
// Read in a matrix and set up its linked representation.
// An auxiliary array \fIhead\fR is used.
{
    Triple s; int p;
    is >> s.row >> s.col >> s.value;   // matrix dimensions
    if (s.row > s.col) p = s.row; else p = s.col;

    // set up headnode for list of head nodes.
    matrix.headnode = new MatrixNode(FALSE, &s);

    if (p == 0) { matrix.headnode->right = matrix.headnode; return is;}
    // at least one row or column

    MatrixNodePtr *head = new MatrixNodePtr[p];  // initialize head nodes
    for (int i = 0; i < p; i++)
	head[i]  = new MatrixNode(TRUE, 0);

    int CurrentRow = 0; MatrixNode *last = head[0]; // last node in current row
    for (i = 0; i < s.value; i++)  // input triples
    {
	Triple t;
	is >> t.row >> t.col >> t.value;
	if (t.row > CurrentRow) {  // close current row
	   last->right = head[CurrentRow];
	   CurrentRow = t.row;
	   last = head[CurrentRow];
	}
	last = last->right = new MatrixNode(FALSE, &t);  // link new node into row list
	head[t.col]->next = head[t.col]->next->down = last; // link into column list
    }

    last->right = head[CurrentRow]; // close last row

    for (i = 0; i < s.col; i++) head[i]->next->down = head[i]; // close all column lists

    // link the head nodes together
    for (i = 0; i < p-1 ; i++) head[i]->next = head[i+1];
    head[p-1]->next = matrix.headnode;
    matrix.headnode->right =  head[0];
    delete [] head;
    return is;
}

ostream& operator<<(ostream& os, Matrix& m)
{
    MatrixNode *x = m.headnode;
    if (!x) return os << "Matrix destroyed" << endl;
    x = x->right;
    os << endl;
    while (x != m.headnode)
    {
       for (MatrixNode *y = x->right; y != x ; y = y->right)
	   os << y->triple;
       x = x->next;
    }

    x = m.headnode;
    x = x->right;
    os << endl;
    while ( x != m.headnode)
    {
       for (MatrixNode *y = x->down; y != x ; y = y->down)
	   os << y->triple;
       x = x->next;
    }
    return os;
}

MatrixNode *av = 0;

Matrix::~Matrix()
// Return all nodes to the @av@ list. This list is a chain linked via the \fIright\fR
// field. @av@ is a global variable of type @MatrixNode\(**@ and points to its first node.
{
    if (!headnode) return; // no nodes to dispose
    MatrixNode *x = headnode->right, *y;
    headnode->right = av; av = headnode; // return @headnode@
    while (x != headnode) { // erase by rows
	y = x->right;
	x->right = av;
	av = y;
	x = x->next; // next row
    }
    headnode = 0;
}

void main()
{
    ifstream inFile( "matrix.in", ios::in);
    if (!inFile)
    {
       cerr << "Cannot open input file " << endl;
       return;
    }
    Matrix m;
    inFile >> m;
    cout << m;
    m.~Matrix();
    cout << m;

/* int count = 0;
    for (MatrixNode *y = av;y; y = y->right)
       count++;
    cout << count;
*/
}