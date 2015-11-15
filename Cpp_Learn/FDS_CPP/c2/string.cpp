#include <iostream.h>

class String
{
// \fBobjects\fR: A finite ordered set of zero or more characters.
public:
String(int m);
//return a string whose maximum length is @m@ characters but is initially empty

String(char *c, int n);

int operator==(String t);
/* \fBif\fR (\(**\fBthis\fR equals @t@) \fBreturn\fR 1 (TRUE)
\fBelse\fR \fBreturn 0 (FALSE);*/

int operator!();
// \fBif\fR \(**\fBthis\fR is empty \fBthen\fR \fBreturn\fR 1 (TRUE);
// \fBelse\fR \fBreturn\fR 0 (FALSE);

int Length() {return length;};
// \fBreturn\fR the number of characters in @s@

String Concat(String t);
// return a string whose elements are those of \(**\fBthis\fR followed by those of @t@.

String Substr(int i,int j);
/* return a string containing the characters of \(**\fBthis\fR at positions
@i@, @i+1@, ..., @i+j-1@ if these are valid positions of \(**\fBthis\fR;
otherwise, return the empty string. */

int Find(String);
int FastFind(String);
void fail();
void out();

private:
  int length;
  char *str;
  int f[100];
};

String::String(char *c, int n) {
   str = c;
   length = n;
}

int String::Find(String pat)
/*@i@ is set to -1 if @pat@ does not occur in @s@ (\(**\fBthis\fR);
otherwise @i@
is set to point to the first position in \(**\fBthis\fR, where @pat@ begins.*/
{
  char *p = pat.str, *s = str;
  int i = 0;  // @i@ is starting point
  if (*p && *s)
      while ( i <= Length() - pat.Length())
	 if (*p++ == *s++) { //characters match, get next char in \fIpat\fR and @s@
	     if (!*p) return i; // match found
	 }
	 else { // no match
	     i++; s = str + i; p = pat.str;
	 }
  return -1; //@pat@ is empty or does not occur in @s@
} // end of @"f"ind@

int String::FastFind(String pat) {
   // Determine if @pat@ is a substring of @s@
   int PosP = 0, PosS = 0;
   int LengthP = pat.Length(), LengthS = Length();

   while((PosP < LengthP) && (PosS < LengthS))
      if (pat.str[PosP] == str[PosS]) {
	 PosP++; PosS++;
      }
      else
	 if (PosP == 0) PosS++;
	 else PosP = pat.f[PosP-1] + 1;
   if (PosP < LengthP) return -1;
   else return PosS-LengthP;
}

void String::fail()
{
   int LengthP = Length();
   f[0] = -1;
   for (int j = 1; j < LengthP; j++)
   {
       int i = f[j-1];
       while((*(str+j) != *(str+i+1)) && (i >= 0)) i = f[i];
       if (*(str+j) == *(str+i+1)) f[j] = i + 1;
       else f[j] = -1;
   }
}

void String::out() {
   for (int i = 0; i < Length(); i++)
      cout << f[i] << endl;
}

void main()
{
   String s("abcabcdefg",10);
   String pat1("cde", 3);
//   pat1.fail();
//   cout << s.FastFind(pat1) << endl;
   String pat2("abd", 3);
//   pat2.fail();
//   cout << s.FastFind(pat2) << endl;
   String Pat3("abc", 3);
//   Pat3.fail();
//   cout << s.FastFind(Pat3) << endl;
   String pat4("abcabcacab", 10);
//   pat4.fail();
//   pat4.out();
   cout << s.Find(pat1) << endl;
   cout << s.Find(pat2) << endl;
   cout << s.Find(Pat3) << endl;
   cout << s.Find(pat4) << endl;
}