#include <iostream.h>

class Rectangle {
    friend ostream& operator << (ostream& os, Rectangle& s);
public:
    int operator< (const Rectangle&);
    void Fill(int a, int b, int c, int d) {
	x1 = a; y1 = b; h = c; w = d;
    }
private:
    int x1, y1, h, w;
};

ostream& operator << (ostream& os, Rectangle& s)
{
    return os << "\t" << s.h << "\t" << s.w << endl;
}

// Assume that class Rectangle contains a prototype of member
// function operator<(Rectangle) in its class definition
int Rectangle::operator<(const Rectangle& s)
{
    if ((h*w) < (s.h*s.w)) return 1;
    else return 0;
}

template <class KeyType>
void sort (KeyType *a, int n)
// sort the n KeyTypes a[0] to a[n-1] into nondecreasing order
{
   for ( int i = 0; i < n; i++)
   {
      int j = i;
      // find smallest KeyType in a[i] to a[n-1]
      for (int k = i+1; k < n; k++)
	 if (a[k] < a[j]) j = k;
      KeyType temp = a[i]; a[i] = a[j]; a[j] = temp;
   }
}

void main()
{
Rectangle rect[6];
rect[0].Fill(1,1,3,5);
rect[1].Fill(1,1,4,4);
rect[2].Fill(1,1,6,6);
rect[3].Fill(1,1,6,5);
rect[4].Fill(1,1,2,6);
sort(rect, 5);
for (int i = 0; i <= 4; i++)
  cout << rect[i];

//int array[100], i;
//array[1] = 4; array[2] = 3; array[3] = 2; array[4] = 1; array[5] = -2;
//sort(array, 5);

//for (i=1; i <= 4; i++)
// {
//cout << array[i] << ",";
// }
//cout << array[5] << "\n";
//float a2[100];
//a2[1] = 0.34; a2[2] = 2.33; a2[3] = -0.22; a2[4] = .65; a2[5] = 111.1;
//sort(a2,5);
//for (i=1; i <= 4; i++)
// {
//cout << a2[i] << ",";
// }
//cout << a2[5] << "\n";
}
