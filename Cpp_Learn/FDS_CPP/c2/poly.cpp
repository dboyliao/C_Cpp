#include<iostream.h>

const int MaxTerms = 100;

class Polynomial; // forward declaration

class term {
friend Polynomial;
private:
float coef; //coefficient
int exp; //exponent
};

char compare (int x, int y)
{
char t;

if (x > y) t = '>';
else if (x < y) t = '<';
     else t = '=';
return t;
}

class Polynomial {
/*\fBobjects\fR: @p(x)@ = @a sub 1 x sup e sub 1 ~+~ ... ~+~a sub n x sup e sub n@; a set
of ordered pairs of <@e sub i@, @a sub i@>, where @a sub i@ \(mo
@Coefficient@ and @e sub i@ \(mo
@Exponent@, @e sub i@ are integers >= 0
*/
public:

Polynomial(int start = -1, int finish = -1)
{
   Start = start;
   Finish = finish;
};

Polynomial Add(Polynomial poly);
// return the sum of the polynomial \(**\fBthis\fR and @poly@

void NewTerm (float, int);

void Init();
void Output();

private:
   static term termArray[MaxTerms];
   static int free;
   int Start, Finish;

}; // end of \fIPolynomial\fR

term Polynomial::termArray[MaxTerms];
int Polynomial::free = 0;

void Polynomial::Init()
{
termArray[0].coef = 2; termArray[0].exp = 1000;
termArray[1].coef = 1; termArray[1].exp = 0;
termArray[2].coef = 1; termArray[2].exp = 4;
termArray[3].coef = 10; termArray[3].exp = 3;
termArray[4].coef = 3; termArray[4].exp = 2;
termArray[5].coef = 1; termArray[5].exp = 0;
free = 6;
}

void Polynomial::Output()
{
   cout << "\t" << "Coef" << "\t" << "Exp" << endl;
   for (int i = 0; i < free; i++)
       cout << "\t" << termArray[i].coef << "\t" <<  termArray[i].exp << endl;
}

void Polynomial::NewTerm(float c, int e)
//Add a new term to @C(x)@.
{
   if (free > MaxTerms) {
	cout << "Too many terms in polynomials" << endl;
	return;
   }
   termArray[free].coef = c;
   termArray[free].exp = e;
   free++;
} // end of @NewTerm@



Polynomial Polynomial::Add(Polynomial B)
// return the sum of @A(x)@ (in \(**\fBthis\fR) and @B(x)@
{
Polynomial C ;int a = Start;int b = B.Start; C.Start = free;
float c;
while ((a <= Finish) && (b <= B.Finish))
   switch (compare(termArray[a].exp, termArray[b].exp)) {
       case '=':
	  c = termArray[a].coef + termArray[b].coef;
	  if (c) NewTerm(c, termArray[a].exp);
	  a++; b++;
	  break;
       case '<':
	  NewTerm(termArray[b].coef, termArray[b].exp);
	  b++;
	  break;
       case '>':
	  NewTerm(termArray[a].coef, termArray[a].exp);
	  a++;
   } // end of \fBswitch\fR and \fBwhile\fR}
   //add in remaining terms of @A(x)@
   for (; a <= Finish ;a++)
   NewTerm(termArray[a].coef, termArray[a].exp);
   //\fRadd in remaining terms of @B(x)@
   for ( ;b <= B.Finish; b++)
   NewTerm(termArray[b].coef, termArray[b].exp);
   C.Finish = free - 1;
   return C;
} // end of @Add@



void main()
{
   Polynomial a(0,1);
   Polynomial b(2,5);
   a.Init();
   a.Output();
   Polynomial c = a.Add(b);
   a.Output();
   a.Add(c);
   a.Output();
}