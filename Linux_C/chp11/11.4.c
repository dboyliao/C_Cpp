#include<list>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
int main()
{
	list<int> l;
	//list::iterator li;
	bool flag;
	l.push_back(42);
	l.push_back(37);
	l.push_back(77);
	l.push_back(10);
	l.push_back(28);
	l.push_back(9);
	l.sort();//對list對像進行升序排序
	flag=binary_search(l.begin(),l.end(),37);
	
	if(flag)
	{
		cout<<"在list對像中找到與37相同的元素"<<endl;
	}	
	return 1;

}