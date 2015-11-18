#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int i;
	int array[100];
	for(i=0;i<100;i++)
		array[i]=i+1;
	for(i=0;i<100;i++)
		cout<<array[i]<<endl;
		if(binary_search(array,array+100,78))
		cout<<"用折半查找在數組array中找到元素78"<<endl;
	else
		cout<<"數組array中沒有元素78"<<endl;
	return 1;
}
