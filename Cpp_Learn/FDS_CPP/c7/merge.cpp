#include <iostream.h>

class Element
{
public:
   int getKey() const {return key;};
   int other() {return Other;};
   void setKey(int k) { key = k;};
   void setOther(int o) { Other = o;}
   Element(){Other = 0;};
private:
   int key;
   int Other;
};

void merge(Element *initList, Element *mergedList, const int l, const int m, const int n)
// @(initList[l], ~... ,~initList[m])@ and @(initList[m~+~1],~... ,~initList[n])@ are sorted lists with keys
// @initList[l]^.^key~\(<=~ ... ~\(<=~initList[m]^.^key@ and @initList[m~+~1]^.^key~\(<=~...~\(<=~initList[n]^.^key@.  These lists are
// merged to obtain the sorted list @(mergedList[l],~... ,~mergedList[n])@, @mergedList[l]^.^key~\(<=~...~\(<=~mergedList[n]^.^key@.
{
   for (int i1 = l, i2 = m+1, iResult = l; // @i1@, @i2@, and @iResult@ are positions in the three lists
	i1 <= m && i2 <= n;
	iResult++)
	  if (initList[i1].getKey() <= initList[i2].getKey())
	  {
	     mergedList[iResult] = initList[i1];
	     i1++;
	  }
	  else
	  {
	     mergedList[iResult] = initList[i2];
	     i2++;
	  }
   if (i1 > m)
       for (int t = i2; t <= n; t++) mergedList[iResult+t-i2] = initList[t];
   else
       for (int t = i1; t <= m; t++) mergedList[iResult+t-i1] = initList[t];
}


void MergePass(Element *initList, Element *resultList, const int n, const int l)
/*  One pass of merge sort. Adjacent pairs of sublists of length @l@ are
merged from list @initList@ to list @resultList@. @n@ is the number of records in @initList@ */
{
   for (int i = 1;
	i <= n - 2*l + 1;
	i += 2*l)
       merge(initList, resultList, i, i+l-1, i+2*l-1);
   // merge remaining list of length < 2 \(** @l@
   if ((i+l-1) < n) merge(initList, resultList, i, i+l-1, n);
   else for (int t = i; t <= n; t++) resultList[t] = initList[t];
}


void MergeSort(Element *list, const int n)
// Sort list @list@ into nondecreasing order of the keys @list[1].key@, ..., @list[n].key@.
{
    Element *tempList = new Element[n+1];
    // @l@ is the length of the sublist currently being merged
    for (int l = 1; l < n; l *= 2)
    {
	MergePass(list, tempList, n, l);
	for (int m = 1; m <= 10; m++) cout << tempList[m].getKey() << " , "; cout << endl;
	l *= 2;
	MergePass(tempList, list, n, l); // interchange role of @list@ and @tempList@
	for (m = 1; m <= 10; m++) cout << list[m].getKey() << " , "; cout << endl;
    }
    delete [] tempList;
}

void main()
{


Element *b = new Element[11];
Element e;
e.setKey(26);b[1] = e;
e.setKey(5);b[2] = e;
e.setKey(77);b[3] = e;
e.setKey(1);b[4] = e;
e.setKey(61);b[5] = e;
e.setKey(11);b[6] = e;
e.setKey(59);b[7] = e;
e.setKey(15);b[8] = e;
e.setKey(48);b[9] = e;
e.setKey(19);b[10] = e;
e.setKey(1000); b[11] = e;

MergeSort(b, 10);
for (int m = 1; m <= 10; m++) cout << b[m].getKey() << " , "; cout << endl;
}