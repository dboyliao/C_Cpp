#include <iostream.h>
const int HeapSize = 100;

class Sets {
public:
	Sets (int);
   void display();
   void SimpleUnion(int, int);
   int SimpleFind(int);
   void WeightedUnion(int, int);
   int CollapsingFind(int);
private:
   int *parent;
   int n;
};

Sets::Sets(int sz = HeapSize)
{
    n = sz;
    parent = new int[sz + 1]; // Don't want to use parent[0]
    for (int i = 1; i <= n; i++) parent[i] = -1;  // 0 for Simple versions
}

void Sets::SimpleUnion(int i, int j)
// Replace the disjoint sets with roots @i@ and @j@, @i != j@ with their union
{
    parent[j] = i;
}

int Sets::SimpleFind(int i)
// Find the root of the tree containing element @i@
{
    while (parent[i] > 0) i = parent[i];
    return i;
}

void Sets::WeightedUnion(int i, int j)
// Union sets with roots @i@ and @j@, @i != j@, using the weighting rule.
// @parent[i]~=~-count[i]@ and @parent[i]~=~-count[i]@.
{
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]) { // @i@ has fewer nodes
	parent[i] = j;
	parent[j] = temp;
    }
    else { // @j@ has fewer nodes
	parent[j] = i;
	parent[i] = temp;
    }
}

int Sets::CollapsingFind(int i)
// Find the root of the tree containing element @i@.
// Use the collapsing rule to collapse all nodes from @i@ to the root
{
    for (int r = i; parent[r] > 0; r = parent[r]); // find root
    while (i != r) {
       int s = parent[i];
       parent[i] = r;
       i = s;
    }
    return r;
}



void Sets::display()
{
for(int i=1; i <= n; i++) cout << i ;
cout << "\n";
for(i=1; i <= n; i++) cout << parent[i] ;
cout << "\n";
}


void main()
{
/*

Sets m(8);
m.display();
cout << "find 5" << m.SimpleFind(5) << endl;
m.SimpleUnion(1,2); m.SimpleUnion(3,4); m.SimpleUnion(5,6); m.SimpleUnion(7,8);
m.display();
cout << "find 5" << m.SimpleFind(5) << endl;
cout << "find 6" << m.SimpleFind(6) << endl;
m.SimpleUnion(1,3); m.SimpleUnion(5,7);
m.display();
cout << "find 5" << m.SimpleFind(5) << endl;
cout << "find 6" << m.SimpleFind(6) << endl;
cout << "find 7" << m.SimpleFind(7) << endl;
cout << "find 8" << m.SimpleFind(8) << endl;
m.SimpleUnion(1,5);
m.display();
cout << "find 1" << m.SimpleFind(1) << endl;
cout << "find 2" << m.SimpleFind(2) << endl;
cout << "find 3" << m.SimpleFind(3) << endl;
cout << "find 4" << m.SimpleFind(4) << endl;
cout << "find 5" << m.SimpleFind(5) << endl;
cout << "find 6" << m.SimpleFind(6) << endl;
cout << "find 7" << m.SimpleFind(7) << endl;
cout << "find 8" << m.SimpleFind(8) << endl;
*/

Sets m(8);
m.display();
cout << "find 5" << m.CollapsingFind(5) << endl;
m.WeightedUnion(1,2); m.WeightedUnion(3,4); m.WeightedUnion(5,6); m.WeightedUnion(7,8);
m.display();
cout << "find 5" << m.CollapsingFind(5) << endl;
cout << "find 6" << m.CollapsingFind(6) << endl;
m.WeightedUnion(1,3); m.WeightedUnion(5,7);
m.display();
cout << "find 5" << m.CollapsingFind(5) << endl;
cout << "find 6" << m.CollapsingFind(6) << endl;
cout << "find 7" << m.CollapsingFind(7) << endl;
cout << "find 8" << m.CollapsingFind(8) << endl;
m.WeightedUnion(1,5);
m.display();
cout << "find 1" << m.CollapsingFind(1) << endl;
cout << "find 2" << m.CollapsingFind(2) << endl;
cout << "find 3" << m.CollapsingFind(3) << endl;
cout << "find 4" << m.CollapsingFind(4) << endl;
cout << "find 5" << m.CollapsingFind(5) << endl;
cout << "find 6" << m.CollapsingFind(6) << endl;
cout << "find 7" << m.CollapsingFind(7) << endl;
cout << "find 8" << m.CollapsingFind(8) << endl;
m.display();
}
