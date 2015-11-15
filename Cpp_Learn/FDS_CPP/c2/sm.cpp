#include <iostream.h>
const int MaxTerms = 100;

char compare (int x, int y)
{
   if (x > y) return '>';
   else if (x < y) return '<';
	else return '=';
}

template <class Item> class SparseMatrix;

template <class Item>
class MatrixTerm {
friend class SparseMatrix<Item>;
private:
int row, col;
Item value;
};

template <class Item>
class SparseMatrix
{
/*\fBobjects\fR: A set of triples, <\fIrow\fR, \fIcolumn\fR, \fIvalue\fR>,
where \fIrow\fR and \fIcolumn\fR are integers and form a unique
combination, and \fIvalue\fR comes from the set \fIitem\fR.
*/

public:
SparseMatrix(int MaxRow =0, int MaxCol =0){};
/* the constructor function creates a \fISparseMatrix\fR
that can hold up to \fIMaxItems\fR =
\fIMaxRow\fR @times@ \fIMaxCol\fR and
whose maximum row size is
\fIMaxRow\fR and whose
maximum column size
is \fIMaxCol\fR  */
SparseMatrix Transpose();
SparseMatrix FastTranspose();
/* returns the \fISparseMatrix\fR obtained
by interchanging the
row and column value of every
triple in \(**\fBthis\fR.
*/
SparseMatrix Add(SparseMatrix b);
/*
\fBif\fR the dimensions of @a@ (\(**\fBthis\fR) and @b@ are the same
.br
then the matrix
produced by adding corresponding
items, namely those with
identical @"row"@ and
@"column"@ values is returned
.br
\fBelse\fR error
*/
SparseMatrix<Item> Multiply(SparseMatrix<Item> b);
/*\fBif\fR number of columns in @a@ (\(**\fBthis\fR) equals number of rows in @b@
.br
then the matrix @d@
produced by multiplying @a@ by @b@
according to the formula @d[i][j]@ =
@sum (a[i][k]~cdot~b[k][j])@,
where @d[i][j]@ is the (@i@, @j@)th
element, is returned. @k@ ranges from 0 to the number of
columns in @a@ (\(**\fBthis\fR) - 1
.br
\fBelse\fR error
*/
int StoreSum(int, int&, int, int);
void Output();
void Init(Item*);
void Init2(Item*);
void Init3(Item*);
private:

int Rows, Cols, Terms;
MatrixTerm<Item> smArray[MaxTerms];

};

template <class Item>
void SparseMatrix<Item>::Output()
{
     cout << "\trow" << "\tcol" << "\tvalue" << endl;
     for (int i = 0; i < Terms; i++)
	 cout << "\t" << smArray[i].row << "\t" << smArray[i].col << "\t" << smArray[i].value << endl;
}

template <class Item>
void SparseMatrix<Item>::Init(Item *a)
{
Rows = 6; Cols = 6; Terms = 8;
smArray[0].row = 0; smArray[0].col = 0; smArray[0].value = a[0];
smArray[1].row = 0; smArray[1].col = 3; smArray[1].value = a[1];
smArray[2].row = 0; smArray[2].col = 5; smArray[2].value = a[2];
smArray[3].row = 1; smArray[3].col = 1; smArray[3].value = a[3];
smArray[4].row = 1; smArray[4].col = 2; smArray[4].value = a[4];
smArray[5].row = 2; smArray[5].col = 3; smArray[5].value = a[5];
smArray[6].row = 4; smArray[6].col = 0; smArray[6].value = a[6];
smArray[7].row = 5; smArray[7].col = 2; smArray[7].value = a[7];
}

template <class Item>
void SparseMatrix<Item>::Init2(Item *a)
{
Rows = 3; Cols = 3; Terms = 5;
smArray[0].row = 0; smArray[0].col = 0; smArray[0].value = a[0];
smArray[1].row = 0; smArray[1].col = 2; smArray[1].value = a[1];
smArray[2].row = 1; smArray[2].col = 1; smArray[2].value = a[2];
smArray[3].row = 1; smArray[3].col = 2; smArray[3].value = a[3];
smArray[4].row = 2; smArray[4].col = 0; smArray[4].value = a[4];
}

template <class Item>
void SparseMatrix<Item>::Init3(Item *a)
{
Rows = 3; Cols = 4; Terms = 3;
smArray[0].row = 0; smArray[0].col = 2; smArray[0].value = a[0];
smArray[1].row = 1; smArray[1].col = 0; smArray[1].value = a[1];
smArray[2].row = 2; smArray[2].col = 3; smArray[2].value = a[2];
}


template <class Item>
SparseMatrix<Item> SparseMatrix<Item>::Transpose( )
// return the transpose of @a@ (\(**\fBthis\fR)
{
   SparseMatrix<Item> b;
   b.Rows = Cols; // rows in @b@ = columns in @a@
   b.Cols = Rows; // columns in @b@ = rows in @a@
   b.Terms = Terms; // terms in @b@ = terms in @a@
   if (Terms > 0) // nonzero matrix
   {
      int CurrentB = 0;
      for (int c = 0; c < Cols; c++) // transpose by columns
	 for (int i = 0; i <  Terms; i++)
	 // find elements in column @c@
	    if (smArray[i].col == c) {
	       b.smArray[CurrentB].row = c;
	       b.smArray[CurrentB].col = smArray[i].row;
	       b.smArray[CurrentB].value = smArray[i].value;
	       CurrentB++;
	    } // end of \fBif\fP (smArray[i].col == c)
   }
return b;
} // end of @transpose@

template <class Item>
SparseMatrix<Item> SparseMatrix<Item>::FastTranspose()
//The transpose of @a@ is placed in @b@ and is found in \*(OH(@terms+columns@) time.
{
    int *RowSize = new int[Cols];
    int *RowStart= new int[Cols];
    SparseMatrix<Item> b;
    b.Rows = Cols; b.Cols = Rows; b.Terms = Terms;
    if (Terms > 0) // nonzero matrix
    {
	// compute @RowSize[i@] = number of terms in row @i@ of @b@
	for (int i = 0; i < Cols; i++) RowSize[i] = 0; // initialize
	for (i = 0; i < Terms; i++) RowSize[smArray[i].col]++;

	//@RowStart[i@] = starting position of row @i@ in @b@
	RowStart[0] = 0;
	for (i = 1; i < Cols; i++) RowStart[i] = RowStart[i-1] + RowSize[i-1];

	for (i = 0 ; i < Terms; i++) // move from @a@ to @b@
	{
	   int j = RowStart[smArray[i].col];
	   b.smArray[j].row = smArray[i].col;
	   b.smArray[j].col = smArray[i].row;
	   b.smArray[j].value = smArray[i].value;
	   RowStart[smArray[i].col]++;
	}  // of \fBfor\fR
    } // of \fBif\fP
    return b;
} // of @FastTranspose@

template <class Item>
int SparseMatrix<Item>::StoreSum (int sum, int& LastD, int r, int c)
/*If \fIsum\fP \(!= 0, then it along with its row and column position are stored
as the @LastD@+1'st entry in @d@.  \fIsum\fR is reset to zero and @LastD@ incremented.*/
{
//   cout << "LastD:" << LastD << "r:" << r << "c:" << c << "sum:" << sum << endl;
   if (sum != 0) { 
     if (LastD < MaxTerms-1){ 
	 LastD++;
         smArray[LastD].row = r;
         smArray[LastD].col = c;
         smArray[LastD].value = sum;
         return 0;
     }
     else {
      cout << "Number of terms in product exceeds @MaxTerms@" << endl;
      return 1; //terminate program
     }
   }
   else return 0;
}// end of @StoreSum@

template <class Item>
SparseMatrix<Item> SparseMatrix<Item>::Multiply(SparseMatrix<Item> b)
//Multiply two sparse matrices @A@ (\(**\fBthis\fR) and @B@ producing @D@.
{
  if (Cols != b.Rows) {
  cout << "Incompatible matrices" << endl;
  return NULL;
  };

  if ((Terms == MaxTerms) || (b.Terms == MaxTerms))
  {
      cout << "One additional space in @a@ or @b@ needed" << endl;
      return NULL;
  };
  SparseMatrix<Item> e = b.FastTranspose();
  SparseMatrix<Item> d;
  int i = 0; int LastD = -1; int RowBegin = 0; int r = smArray[0].row;
  // set boundary conditions
  smArray[Terms].row = Rows; e.smArray[b.Terms].row = b.Cols;
  e.smArray[b.Terms].col = -1; int sum = 0;
  while (i < Terms) // generate row @r@ of @d@
  {
      int c = e.smArray[0].row; int j = 0;
	while (j <= b.Terms) // multiply row @r@ of @a@ by column \fIc\fP of @b@
	{
           cout << "i:" << i << " j:" << j << " r:" << r << " c:" << c << endl; 
	   if(smArray[i].row != r) // end of row @r@
	   {  
              cout << "1: new col" << endl;
	      sum = d.StoreSum(sum, LastD,r,c); if(sum) return NULL;
	      i = RowBegin;
	      // go to next column
	      while (e.smArray[j].row == c) j++;
	      c = e.smArray[j].row;
              continue;
	   }
	   if (e.smArray[j].row != c) // end of column \fIc\fP of @b@
           {
              cout << "2: new row" << endl;
              sum = d.StoreSum(sum,LastD,r,c); if (sum) return NULL;
              // set to multiply row @r@ with next column
              i = RowBegin; c = e.smArray[j].row;
              continue;
           }
           switch (compare (smArray[i].col, e.smArray[j].col)) {
              case '<':   // advance to next term in row.
		  cout << "3a: next term in row" << endl;
                  i++; break; 
              case '=':   // add to \fIsum\fP
                  cout << "3b:  add to sum" << endl;
                  sum += smArray[i].value * e.smArray[j].value;
                  i++; j++; break;
              case '>': // advance to next term in column \fIc\fP
		  cout << "3c: next term in col" << endl;
                  j++;
           }; // end of switch
	} // of \fBwhile\fP (@j@ <= @B.Terms)@
	while (smArray[i].row == r) // advance to next row
	  i++;
	RowBegin = i; r = smArray[i].row;
  } //end of \fBwhile\fP (@i@ < @Terms@)
  d.Rows = Rows; d.Cols = b.Cols; d.Terms =  LastD+1;
  return d;
} // of @Multiply@


void main()
{
   int val[8] = {15, 22, -15, 11, 3, -6, 91, 28};
   int val2[5] = {1, 2, 1, 3, 1};
   int val3[3] = {1, 1, 1};
   SparseMatrix<int> a;
   a.Init2(val2);
   SparseMatrix<int> b;
   b.Init3(val3);
   a.Output();
   b.Output();
   SparseMatrix<int> c = a.Multiply(b);
   c.Output();
}
