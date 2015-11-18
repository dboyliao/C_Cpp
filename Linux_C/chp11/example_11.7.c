#include<iostream>
#include<stack>
using namespace std;
int main()
{
   bool flag;//   
   stack<int>s;   
   s.push(1);
   s.push(10);
   s.push(5);
   s.push(23);
   s.pop();
   s.pop();
   flag=s.empty();
   if(flag==true)
      cout<<"該堆疊為空"<<endl;
   else
   { 
      cout<<"該堆疊不為空"<<endl;
      cout<<"堆疊元素為："<<s.top()<<endl;
      cout<<"堆疊長度為："<<s.size()<<endl;
   }
}