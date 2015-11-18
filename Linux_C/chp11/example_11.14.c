#include<algorithm>
#include<iostream>
using namespace std;
int main()
{
	int array[10]={7,2,6,4,3,1,8,10,9,15};
	int nth;
	int *i;	
	int n=5;
    nth_element(array,array+n,array+10);	
	for(i=array;i<array+10;i++)
		cout<<*i<<"   ";
	cout<<endl;
	cout<<"該數組升序排序後的第6個元素為"<<array[6]<<endl;
	return 1;
}
