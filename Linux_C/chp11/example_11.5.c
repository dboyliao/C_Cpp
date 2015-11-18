#include<list>
#include<iostream>
int main()
{
   using namespace std;    
   list<int> l;//創建一個空的list對像
   l.push_back(11);
   l.push_back(2);
   l.push_back(25);
   l.push_back(7);
   l.push_back(31);	
   list<int>::iterator ri;//聲明list游標ri 
   l.sort();//對list容器進行默認的升序排序
   cout<<"排序後，list容器中的元素順序變為："<<endl;
   for(ri=l.begin();ri!=l.end();ri++)//將list鏈表中的元素打印出來
      cout<<(*ri)<<"  ";
   cout<<endl; 
   l.reverse();//對list容器進行反序排序
   cout<<"反序排序後，list容器中的元素順序變為："<<endl;
   for(ri=l.begin();ri!=l.end();ri++)//將list鏈表中的元素打印出來
      cout<<(*ri)<<"  ";
   cout<<endl;  
}