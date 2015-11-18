#include<list>
#include<iostream>

int main()
{  
   using namespace std; 
   int i;
   list<int> l1;//創建一個空的list對像
   list<int> l2;//創建一個空的list對像
   list<int>::iterator ri;//聲明list游標ri   
   for(i=0;i<10;i++)
   {
       l1.push_back(i+1);//利用push_back()函數對list對像進行初始化
   }       
   l2.push_back(11);
   l2.push_back(12);
   l2.push_back(13);
   l1.swap(l2);
   cout<<"經過交換，l1中的元素變為"<<endl;
   for(ri=l1.begin();ri!=l1.end();ri++)//將list鏈表中的元素打印出來
      cout<<(*ri)<<"  ";
   cout<<endl;   
   l1.merge(l2);
   cout<<"l1和l2合併後："<<endl;
   for(ri=l1.begin();ri!=l1.end();ri++)//將list鏈表中的元素打印出來
      cout<<(*ri)<<"  ";
   cout<<endl;   
   return 1;   
   
}