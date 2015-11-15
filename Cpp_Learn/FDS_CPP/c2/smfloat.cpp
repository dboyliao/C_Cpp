#include <iostream.h>
#include <stdlib.h>

const int MaxTerms = 100;

char compare (int x, int y)
{
   if (x > y) return '>';
   else if (x < y) return '<';
	else return '=';
}

class SparseMatrix;

class MatrixTerm {
friend class SparseMatrix;
private:
int row, col, value;
};

class SparseMatrix
{
/*\fBobjects\fR: A set of triples, <\fIrow\fR, \fIcolumn\fR, \fIvalue\fR>,
where \fIrow\fR and \fIcolumn\fR are integers and form a unique
combination, and \fIvalue\fR is a floating point number.
*/

public:
SparseMatrix(int MaxRow =0, int MaxCol =0){};
SparseMatrix EmptyMatrix()
{
    SparseMatrix *sm = new SparseMatrix;
    sm->Rows = sm->Cols = sm->Terms = 0;
    return *sm;
}
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
SparseMatrix Multiply(SparseMatrix b);
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
void StoreSum(int, int&, int, int);
void Output();
void Init(int*);
void Init2(int*);
void Init3(int*);
private:

int Rows, Cols, Terms;
MatrixTerm smArray[MaxTerms];

};

void SparseMatrix::Output()
{
     cout << "\trow" << "\tcol" << "\tvalue" << endl;
     for (int i = 0; i < Terms; i++)
	 cout << "\t" << smArray[i].row << "\t" << smArray[i].col << "\t" << smArray[i].value << endl;
}

void SparseMatrix::Init(int *a)
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

void SparseMatrix::Init2(int *a)
{
Rows = 3; Cols = 3; Terms = 5;
smArray[0].row = 0; smArray[0].col = 0; smArray[0].value = a[0];
smArray[1].row = 0; smArray[1].col = 2; smArray[1].value = a[1];
smArray[2].row = 1; smArray[2].col = 1; smArray[2].value = a[2];
smArray[3].row = 1; smArray[3].col = 2; smArray[3].value = a[3];
smArray[4].row = 2; smArray[4].col = 0; smArray[4].value = a[4];
}

void SparseMatrix::Init3(int *a)
{
Rows = 3; Cols = 4; Terms = 3;
smArray[0].row = 0; smArray[0].col = 2; smArray[0].value = a[0];
smArray[1].row = 1; smArray[1].col = 0; smArray[1].value = a[1];
smArray[2].row = 2; smArray[2].col = 3; smArray[2].value = a[2];
}


SparseMatrix SparseMatrix::Transpose( )
// return the transpose of @a@ (\(**\fBthis\fR)
{
   SparseMatrix b;
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

SparseMatrix SparseMatrix::FastTranspose()
//The transpose of @a@ is placed in @b@ and is found in \*(OH(@terms+columns@) time.
{
    int *RowSize = new int[Cols];
    int *RowStart= new int[Cols];
    SparseMatrix b;
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

    delete [] RowSize;
    delete [] RowStart;
    return b;
} // of @FastTranspose@

void SparseMatrix::StoreSum (int sum, int& LastD, int r, int c)
/*If \fIsum\fP \(!= 0, then it along with its row and column position are stored
as the @LastD@+1'st entry in @d@.  @LastD@ is incremented.*/
{
//   cout << "LastD:" << LastD << "r:" << r << "c:" << c << "sum:" << sum << endl;
   if (sum != 0) {
     if (LastD < MaxTerms-1){
	 LastD++;
	 smArray[LastD].row = r;
	 smArray[LastD].col = c;
	 smArray[LastD].value = sum;
     }
     else {
      cerr << "Number of terms in product exceeds @MaxTerms@" << endl;
      exit(1); //terminate program
     }
   }
}// end of @StoreSum@

SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
//Multiply two sparse matrices @A@ (\(**\fBthis\fR) and @B@ producing @D@.
{
  if (Cols != b.Rows) {
  cout << "Incompatible matrices" << endl;
  return EmptyMatrix();
  }

  if ((Terms == MaxTerms) || (b.Terms == MaxTerms))
  {
      cout << "One additional space in @a@ or @b@ needed" << endl;
      return EmptyMatrix();
  }
  SparseMatrix bXpose = b.FastTranspose();
  SparseMatrix result;
  int currRowIndex = 0, LastD = -1, currRowBegin = 0, currRowA = smArray[0].row;
  // set boundary conditions
  smArray[Terms].row = Rows; bXpose.smArray[b.Terms].row = b.Cols;
  bXpose.smArray[b.Terms].col = -1; int sum = 0;
  while (currRowIndex < Terms) // generate row @currRowA@ of @result@
  {
      int currColB = bXpose.smArray[0].row; int currColIndex = 0;
	while (currColIndex <= b.Terms) // multiply row @currRowA@ of @a@ by column \fIcurrColB\fP of @b@
	{
 //	   cout << "currRowIndex:" << currRowIndex << " currColIndex:" << currColIndex << " currRowA:" << currRowA << " currColB:" << currColB << endl;
	   if(smArray[currRowIndex].row != currRowA) // end of row @currRowA@
	   {
//	      cout << "1: new col" << endl;
	      result.StoreSum(sum, LastD,currRowA,currColB);
	      currRowIndex = currRowBegin;
	      // go to next column
	      while (bXpose.smArray[currColIndex].row == currColB) currColIndex++;
	      currColB = bXpose.smArray[currColIndex].row;
	   }
	   else if (bXpose.smArray[currColIndex].row != currColB) // end of column \fIcurrColB\fP of @b@
	   {
//	      cout << "2: new row" << endl;
	      result.StoreSum(sum,LastD,currRowA,currColB);
	      // set to multiply row @currRowA@ with next column
	      currRowIndex = currRowBegin; currColB = bXpose.smArray[currColIndex].row;
	   }
	   else
	      switch (compare (smArray[currRowIndex].col, bXpose.smArray[currColIndex].col)) {
		 case '<':   // advance to next term in row.
//		     cout << "3a: next term in row" << endl;
		     currRowIndex++; break;
		 case '=':   // add to \fIsum\fP
//		     cout << "3b:  add to sum" << endl;
		     sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
		     currRowIndex++; currColIndex++; break;
		 case '>': // advance to next term in column \fIc\fP
//		     cout << "3c: next term in col" << endl;
		     currColIndex++;
	      } // end of switch
	} // of \fBwhile\fP (@currColIndex@ <= @b.Terms)@
	while (smArray[currRowIndex].row == currRowA) // advance to next row
	  currRowIndex++;
	currRowBegin = currRowIndex; currRowA = smArray[currRowIndex].row;
  } //end of \fBwhile\fP (@currRowIndex@ < @Terms@)
  result.Rows = Rows; result.Cols = b.Cols; result.Terms =  LastD+1;
  return result;
} // of @Multiply@


void main()
{
   int val[8] = {15, 22, -15, 11, 3, -6, 91, 28};
   int val2[5] = {1, 2, 1, 3, 1};
   int val3[3] = {1, 1, 1};
   SparseMatrix a;
   a.Init2(val2);
   SparseMatrix b;
   b.Init3(val3);
   a.Output();
   b.Output();
   SparseMatrix c = a.Multiply(b);
   c.Output();
}
