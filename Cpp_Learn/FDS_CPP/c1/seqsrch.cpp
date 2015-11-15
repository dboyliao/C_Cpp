#include <iostream.h>
#include <sys\timeb.h>

int seqsearch (int *a, const int n, const int x)  //a[0], ..., a[n]
{
   int i = n; a[0] = x;
   while (a[i] != x)
     i--;
   return i;
} // end of seqsearch

void TimeSearch() {
   int a[1001], n[20];
   for (int j = 1; j <= 1000; j++) // initialize a
      a[j] = j;
   for (j = 0; j < 10; j++)  {// values of n
      n[j] = 10*j; n[j+10] = 100 * (j+1);
   }
   cout << "n\ttime" << endl;
   for(j = 0; j < 20; j++)  { // obtain computing times
       struct timeb start;
       struct timeb stop;
       ftime(&start); // get time
       int k = seqsearch(a, n[j], 0); // unsuccessful search
       ftime(&stop); // get time
       long runTime = (stop.time - start.time) * 1000 + (stop.millitm - start.millitm);
       cout << n[j] << "\t" << runTime/10 << endl;
   }

   cout << "Times are in hundredths of a second.\n";
}

void TimeSearch2() {

   int a[1001], n[20];
   const long r[20] = {300000, 300000, 200000, 200000, 100000, 100000, 100000,
   80000, 80000, 50000, 50000, 25000, 15000, 15000, 10000, 7500, 7000,
   6000, 5000, 5000};
   for (int j = 1; j <= 1000; j++) // intialize z
      a[j] = j;
   for (j = 0; j < 10; j++)  {// values of n
      n[j] = 10*j; n[j+10] = 100 * (j+1);
   }
   cout << "\tn\ttotal\trunTime" << endl;
   for(j = 0; j < 20; j++)  { // obtain computing times
       struct timeb start;
       struct timeb stop;

       ftime(&start); // get time
       for (long b = 1; b <= r[j]; b++)
	   int k = seqsearch(a, n[j], 0); // unsuccessful search
       ftime(&stop); // get time
       long total = (stop.time - start.time) * 100 + (stop.millitm - start.millitm)/10;
       float runTime = total/r[j];
       cout << "\t" << n[j] << "\t" << total << "\t" << runTime << endl;
   }

   cout << "Times are in hundredths of a second.\n";
}


void TimeSearch3() {


       struct timeb h;
       struct timeb h1;

       ftime(&h); // get time
       for (long b = 1; b <= 300000; b++);
       ftime(&h1); // get time
       long t1 = (h1.time - h.time) * 100 + (h1.millitm - h.millitm)/10;

       cout <<t1 << endl;
}

void main()
{
//   TimeSearch3();

   int b[11];
   b[1] = 2; b[2] = 4; b[3] = 5; b[4] = 7; b[5] = 10;
   b[6] = 12; b[7] = 14; b[8] = 15; b[9] = 17; b[10] = 25;

   cout << seqsearch(b,10,10) << "\n";
   cout << seqsearch(b,10,11) << "\n";
}
