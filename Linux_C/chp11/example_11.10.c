#include <map>
#include <iostream>

int main( )
{
   using namespace std;
   map <int, char> m1, m2, m3;
   map <int,char>::iterator mi;
    map <int,char>::iterator mi2;
   typedef pair <int, int> Pair;

   m1.insert ( Pair ( 1, 'a' ) );
   m1.insert ( Pair ( 2, 'b' ) );
   m1.insert ( Pair ( 3, 'c') );
   m2.insert ( Pair ( 4, 'd') );
   m2.insert ( Pair ( 5, 'e') );
   m3.insert ( Pair ( 6, 'f') );

   cout << "m1的原始數據為:\n";
   for ( mi = m1.begin( ); mi!= m1.end( ); mi++ )
      cout << " " << mi -> first<<" " << mi -> second<<endl;
   

   // This is the member function version of swap
   //m2 is said to be the argument map; m1 the target map
   m1.swap( m2 );

   cout << "調用m1.swap( m2 )後，m1的數據變為:\n";
   for ( mi = m1.begin( ); mi!= m1.end( ); mi++ )
	   cout << " " << mi -> first<<" " << mi -> second<<endl;
   cout << "調用m1.swap( m2 )後，m2的數據為:\n";
   for ( mi2 = m2.begin( ); mi2!= m2.end( ); mi2++ )
	   cout << " " << mi2 -> first<<" " << mi2 -> second<<endl;

   // This is the specialized template version of swap
   swap( m1, m3 );
   cout << "調用swap( m1, m3 )後，m1的數據變為:\n";
   for ( mi = m1.begin( ); mi!= m1.end( ); mi++ )
	   cout << " " << mi -> first<<" " << mi -> second<<endl;
   cout << "調用swap( m1, m3 )後，m3的數據變為:\n";
   for ( mi = m3.begin( ); mi!= m3.end( ); mi++ )
	   cout << " " << mi -> first<<" " << mi -> second<<endl;
}