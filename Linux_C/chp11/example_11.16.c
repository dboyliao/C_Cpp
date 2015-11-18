#include<list>
#include<iostream>
using namespace std;
int main()
{
	list<int>l;
	l.push_back(10);
	l.push_back(51);
	l.push_back(9);
	l.push_back(82);
	l.push_back(32);
	cout<<"鏈表l的最小元素為"<<	*min_element(l.begin(),l.end())<<endl;
	cout<<"鏈表l的最大元素為"<<	*max_element(l.begin(),l.end())<<endl;
	return 1;
}