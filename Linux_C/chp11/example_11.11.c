#include<set>
#include<iostream>
using namespace std;
int main()
{
	set<char>s;
	set<char>::iterator si;
	s.insert('b');
	s.insert('d');
	s.insert('t');
	s.insert('a');
	for(si=s.begin();si!=s.end();si++)
		cout<<*si<<"   ";
	cout<<endl;
	s.erase(s.begin(),s.end());//實現函數clear（）的功能
	if(s.empty()==true)
		cout<<"set容器為空"<<endl;
	return 1;
}