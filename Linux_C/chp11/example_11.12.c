#include<algorithm>
#include<iostream>
using namespace std;
int main()
{
	int array[]={7,9,2,5,1,-8,-4,10,0,3};
	//int array[]={3,9,6,8,-10,7,-11,19,30,12,23};
	int mid=5;
	int *i;	
	const int len=sizeof(array)/sizeof(int);
	partial_sort(array,array+mid,array+len,greater<int>());
	cout<<"經過局部排序，array[]=";
	for(i=array;i<array+len;i++)
		cout<<*i<<"   ";
    cout<<endl;
	return 1;
}