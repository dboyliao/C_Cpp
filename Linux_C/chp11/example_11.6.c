#include<vector>
#include<iostream>
int main()
{
   using namespace std;    
   int i,size,maxsize,capacity;
   vector<int> v;//創建一個空的vector對像
   for(i=0;i<5;i++)
   {
       v.push_back(i+1);//利用push_back()函數對list對像進行初始化
   } 	
   vector<int>::iterator ri;//聲明vector游標ri     
   for(ri=v.begin();ri!=v.end();ri++)//將vector鏈表中的元素打印出來
      cout<<(*ri)<<"  ";
   cout<<endl; 
   size=v.size();
   maxsize=v.max_size();
   capacity=v.capacity(); 
   cout<<"size="<<size<<endl;
   cout<<"maxsize="<<maxsize<<endl;
   cout<<"capacity="<<capacity<<endl; 
   v.reserve(100);
   capacity=v.capacity();
   cout<<"capacity="<<capacity<<endl;
}