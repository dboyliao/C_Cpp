#include<list>
#include<iostream>
#define SIZE 10
int main()
{
	using namespace std;    
	int i;
	char temp[SIZE];//聲明一個臨時數組，暫存list中的數據
	list<char> l;//創建一個空的list對像	
	list<char>::iterator ri;//聲明list游標ri
	list<char>::reverse_iterator rj;//聲明list反向游標rj
	for(i=0;i<SIZE;i++)
	{
		l.push_back('a'+i);//利用push_back()函數對list對像進行初始化
	} 	
	cout<<"反序前，list容器中的元素為："<<endl; 
	for(ri=l.begin();ri!=l.end();ri++) 
		cout<<(*ri)<<"  "; 
	cout<<endl;
	//cout<<"111";
	i=0;
	for(rj=l.rbegin();rj!=l.rend();rj++) 
		temp[i++]=(*rj);
	l.clear();
	for(i=0;i<SIZE;i++)
	{
		l.push_back(temp[i]);//利用push_back()函數對list對像進行初始化
	} 	
	cout<<"反序後，list容器中的元素為："<<endl;  
	for(ri=l.begin();ri!=l.end();ri++) 
		cout<<(*ri)<<"  "; 
	cout<<endl;
	return 1;
}