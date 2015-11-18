#include<list>
#include<iostream>

int main(void)
{  
   using namespace std; 
   int i;
   list<int> obj;//創建一個空的list對像
   list<int>::iterator ri;//聲明list游標ri
   list<int>::reverse_iterator rj;//聲明list反向游標rj
   for(i=0;i<10;i++)
   {
       obj.push_back(i+1);//利用push_back()函數對list對像進行初始化
   } 
   cout<<"正向遍歷list容器中的元素："<<endl;
   for(ri=obj.begin();ri!=obj.end();ri++)//將list鏈表中的元素打印出來
      cout<<(*ri)<<"  ";//函數begin()和end()分別指向list鏈表的頭元素和尾元素
   cout<<endl;   
   cout<<"反向遍歷list容器中的元素："<<endl;  
   for(rj=obj.rbegin();rj!=obj.rend();rj++)//將list鏈表中的元素打印出來
      cout<<(*rj)<<"  ";//函數begin()和end()分別指向list鏈表的頭元素和尾元素
   cout<<endl;
   return 1;
}
