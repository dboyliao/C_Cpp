#include<list>
#include<iostream>

int main(void)
{  
   using namespace std; 
   int i;
   list<int> obj;//創建一個空的list對像
   list<int>::iterator j;//聲明list游標i
   for(i=0;i<10;i++)
   {
       obj.push_back(i+1);//利用push_back()函數對list對像進行初始化
   }
   for(j=obj.begin();j!=obj.end();j++)
      cout<<(*j)<<"  ";
   cout<<endl;
   obj.push_front(0);//在list對像obj頭部插入一個頭節點
   
   j=obj.begin();//j指向鏈表對像obj的第一個元素
   for(i=0;i<7;i++)//將游標指向第七個元素
      j++;
   obj.insert(j,11);//在第七個元素之前插入數據11
   for(j=obj.begin();j!=obj.end();j++)
      cout<<(*j)<<"  ";
   cout<<endl;
   return 1;
}
