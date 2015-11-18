#include<list>
#include<iostream>

int main(void)
{  
   using namespace std; 
   int i;
   list<int> obj;//創建一個空的list對像
   list<int>::iterator j,k;//聲明list游標i
   for(i=0;i<10;i++)
   {
       obj.push_back(i+1);//利用push_back()函數對list對像進行初始化
       obj.push_back(i+1);
   }
   for(j=obj.begin();j!=obj.end();j++)
      cout<<(*j)<<"  ";
   cout<<endl;  
   obj.unique();//刪除obj中所有連續重複的元素
   for(j=obj.begin();j!=obj.end();j++)
      cout<<(*j)<<"  ";
   cout<<endl;  
   obj.pop_front();//刪除第一個元素1
   obj.pop_back();//刪除最後一個元素10
   j=obj.begin();//j指向鏈表對像obj的第一個元素
   k=j;
   for(i=0;i<5;i++)//將游標指向第七個元素
      k++;
   obj.erase(j,k);//刪除區間[0,5)內的元素
   for(j=obj.begin();j!=obj.end();j++)
      cout<<(*j)<<"  ";
   cout<<endl;
   obj.remove(8);//刪除元素值等於8的元素
   for(j=obj.begin();j!=obj.end();j++)
      cout<<(*j)<<"  ";
   cout<<endl;
   obj.clear();//刪除obj內的所有元素
   for(j=obj.begin();j!=obj.end();j++)
      cout<<(*j)<<"  ";
   cout<<endl;
   return 1;
}